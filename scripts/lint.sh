#!/usr/bin/env bash

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
echo "[I] script_dir: $script_dir"

repo_dir=$(dirname "$script_dir")
echo "[I] repo_dir: $repo_dir"

help() {
  echo "       "
  echo "[HELP] LINT HELP:"
  echo "  Defaults: If no option is given show help"
  echo "      shellcheck runs on all shell files in the repo recursively"
  echo "      shfmt      runs on all shell files in the repo recursively"
  echo "      cpplint    runs on all shell files in the repo recursively"
  echo "      Lint results are given inside the LINT_RESULTS dir in the repo"
  echo "       "
  echo "  Options: "
  echo "  -a     Lint both shell and cpplints"
  echo "          Note: Lint -sc or -cs is the same as -a"
  echo "  -s     Lint shell files only"
  echo "  -f     Lint specific file only, can only be used with -s or -c option"
  echo "          Requires full path to file OR relative path from current directory"
  echo "  -c     Lint .h, .c, .cpp files only"
  echo "  -h     Show help"
  echo "  -x     Clean ALL lint output"
  echo "       "
}

non_blocking_wait() {
  PID=$1
  if [ ! -d "/proc/$PID" ]; then
    wait "$PID"
    CODE=$?
  else
    CODE=127
  fi
  return $CODE
}

shell_lint() {
  lint_output_local="$2"
  j=$(basename -s ".sh" "$1")
  echo "[I] CURRENT LINT FILE IS: $1"
  shell_lint_output="$lint_output_local/shell/$j"

  mkdir -p "$shell_lint_output"
  shfmt -i=2 -ci -l -d "$1" >"$shell_lint_output/$j.log" 2>&1
  shellcheck --shell=bash --color=auto --severity=style --exclude=SC1090 --exclude=SC1091 "$1" >>"$shell_lint_output/$j.log" 2>&1

  temp=$(wc -l "$shell_lint_output/$j.log" | awk '{ print $1 }')
  if [[ $temp -gt 0 ]]; then
    echo "[WARN] Shell Lint Failed: $shell_lint_output/$j.log" | tee -a "$lint_output_local/shell_lint_results.log"
    return 1
  else
    rm -rf "$shell_lint_output"
    return 0
  fi
}

cpp_lint() {
  lint_output_local="$2"
  j=$(basename "$1")
  echo "[I] CURRENT LINT FILE IS: $1"
  cpp_output_dir="$lint_output_local/cpplint/$j"

  mkdir -p "$cpp_output_dir"
  cpplint --output=sed --linelength=165 --filter="$filters" "$1" >>"$cpp_output_dir/$j.sh" 2>&1

  temp=$(wc -l "$cpp_output_dir/$j.sh" | awk '{ print $1 }')
  if [[ $temp -gt 0 ]]; then
    echo "[WARN] cpplint Failed: $cpp_output_dir/$j.sh" | tee -a "$lint_output_dir/cpp_lint_results.log"
    chmod u+x "$cpp_output_dir/$j.sh"
    return 1
  else
    rm -rf "$cpp_output_dir"
    return 0
  fi
}

SHELL_OPTION=0
CPP_OPTION=0
FILE_OPTION="0"

lint_output_dir="$repo_dir/LINT_RESULTS"
lint_fail=0

while getopts "achsxf:" OPTION; do
  case $OPTION in
    a)
      SHELL_OPTION=1
      CPP_OPTION=1
      ;;
    c)
      CPP_OPTION=1
      ;;
    f)
      if [[ SHELL_OPTION -eq 1 ]] && [[ CPP_OPTION -eq 0 ]]; then
        FILE_OPTION=$(realpath "$OPTARG")
      elif [[ SHELL_OPTION -eq 0 ]] && [[ CPP_OPTION -eq 1 ]]; then
        FILE_OPTION=$(realpath "$OPTARG")
      else
        echo "[ERR] You must choose either -s or -c option with -f but not both or none"
        exit 1
      fi
      if [[ ! -f "$FILE_OPTION" ]]; then
        echo "[ERR] File does not exist, check path"
        exit 1
      fi
      ;;
    h)
      help
      exit 1
      ;;
    s)
      SHELL_OPTION=1
      ;;
    x)
      echo "[I] REMOVING ANY PREVIOUS SHELL LINT OUTPUT ..."
      rm -rf "$lint_output_dir"
      exit 0
      ;;
    *)
      echo "[ERR] Incorrect options provided. See Help."
      help
      exit 1
      ;;
  esac
done

if [ $SHELL_OPTION -eq 0 ] && [ $CPP_OPTION -eq 0 ]; then
  echo "[ERR] No linting option selected. See Help."
  help
  exit 1
fi

#BEGIN LINT
# set -euxo pipefail

#SHELL LINT
if [[ $SHELL_OPTION -eq 1 ]]; then

  echo ""
  echo "[I] STARTING SHELL LINT ..."
  echo "[I] REMOVING ANY PREVIOUS SHELL LINT OUTPUT ..."
  rm -rf "$lint_output_dir/shell"
  rm -f "$lint_output_dir/shell_lint_results.log"

  if ! [[ "$FILE_OPTION" == "0" ]]; then
    shellfiles=$FILE_OPTION
  else
    shellfiles=$(find "$repo_dir" -type f -iname "*.sh" | grep -v "LINT_RUN" | grep -v "RUN")
  fi

  pids=()
  for file in $shellfiles; do
    name_path=$(realpath "$file")
    out_path=$(realpath "$lint_output_dir")
    shell_lint "$name_path" "$out_path" &
    pids+=("$!")
  done
  for pid in "${pids[@]}"; do
    while /bin/true; do
      non_blocking_wait "$pid"
      code=$?
      if [ $code -ne 127 ]; then
        if [ $code -ne 0 ]; then
          # echo "PID $pid terminated with exit code $code"
          lint_fail=$((lint_fail + 1))
        fi
        break
      fi
    done
  done

  echo "[I] COMPLETED SHELL LINT: Results in $lint_output_dir"
  echo " . . . "
fi

#CPP LINT
if [[ $CPP_OPTION -eq 1 ]]; then

  # SETUP REQUIREMENTS, python virtual env and load modules
  p_env_dir="$script_dir/.local"
  mkdir -p "$p_env_dir"
  echo "[I] Python Virtual Environment IS: $p_env_dir"

  cd "$p_env_dir" || exit 2
  python3 --version
  python3 -m venv venv
  source "$script_dir/.local/venv/bin/activate"
  cd ..
  pip3 install -r lint_requirements.txt

  echo ""
  echo "[I] STARTING CPP LINT ..."
  echo "[I] REMOVING ANY PREVIOUS CPPLINT OUTPUT ..."
  rm -rf "$lint_output_dir/cpplint"
  rm -f "$lint_output_dir/cpp_lint_results.log"

  # Remove these rules
  filters="-build/class,
    -build/c++11,
    -build/c++14,
    -build/c++tr1,
    -build/deprecated,
    -build/endif_comment,
    -build/explicit_make_pair,
    -build/forward_decl,
    -build/header_guard,
    -build/include,
    -build/include_subdir,
    -build/include_alpha,
    -build/include_order,
    -build/include_what_you_use,
    -build/namespaces_headers,
    -build/namespaces_literals,
    -build/namespaces,
    -build/printf_format,
    -build/storage_class,
    -readability/casting,
    -legal/copyright"

  if ! [[ "$FILE_OPTION" == "0" ]]; then
    cfiles=$FILE_OPTION
  else
    cfiles=$(find "$repo_dir" -type f -iname "*.h" -o -iname "*.c")
  fi

  pids=()
  for file in $cfiles; do
    name_path=$(realpath "$file")
    out_path=$(realpath "$lint_output_dir")
    cpp_lint "$name_path" "$out_path" &
    pids+=("$!")
  done
  for pid in "${pids[@]}"; do
    while /bin/true; do
      non_blocking_wait "$pid"
      code=$?
      if [ $code -ne 127 ]; then
        if [ $code -ne 0 ]; then
          # echo "PID $pid terminated with exit code $code"
          lint_fail=$((lint_fail + 1))
        fi
        break
      fi
    done
  done

  echo "[I] COMPLETED CPPLINT: Results in $lint_output_dir"
  echo " . . . "
fi

#EXIT
wait

if [[ $lint_fail -gt 0 ]]; then
  echo "[ERR] LINT FAILED"
  exit 1
else
  echo "[I] LINT OK"
  exit 0
fi
