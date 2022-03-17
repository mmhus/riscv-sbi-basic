
#!/usr/bin/env bash

set -euo pipefail
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# RISC-V TOOLCHAIN
RISCV_PATH=$(realpath "$SCRIPT_DIR/../toolchain")
EXPORT_PATH=$(realpath "$SCRIPT_DIR/../export.sh")
WGET_PATH="https://toolchains.bootlin.com/downloads/releases/toolchains/riscv64-lp64d/tarballs/riscv64-lp64d--uclibc--bleeding-edge-2021.11-1.tar.bz2"

echo "[I] RISCV=$RISCV_PATH"
if [[ ! -d "$SCRIPT_DIR/../toolchain" ]]; then
  mkdir "$RISCV_PATH"
  wget -nc "$WGET_PATH"
  echo "[I] Extracting files, please wait ... "
  tar -xjvf riscv64-lp64d--uclibc*.tar.bz2 -C "$RISCV_PATH" >> /dev/null
  echo "[I] Extraction Complete!"
fi

TOOLCHAIN_BIN_PATH=$(find "$SCRIPT_DIR/.." -name "riscv64-linux-gcc")
# echo "[I] TOOLCHAIN_BIN_PATH=$TOOLCHAIN_BIN_PATH"

TOOLCHAIN_BIN_PATH=$(dirname $TOOLCHAIN_BIN_PATH)
# echo "[I] TOOLCHAIN_BIN_PATH=$TOOLCHAIN_BIN_PATH"

TOOLCHAIN_BIN_PATH=$(realpath $TOOLCHAIN_BIN_PATH)
echo "[I] TOOLCHAIN_BIN_PATH=$TOOLCHAIN_BIN_PATH"

rm -f "$EXPORT_PATH"
touch "$EXPORT_PATH"
echo "#!/usr/bin/env bash" >> "$EXPORT_PATH"
echo "" >> "$EXPORT_PATH"
echo "export RISCV=$TOOLCHAIN_BIN_PATH" >> "$EXPORT_PATH"

# SPIKE
git submodule update --init --recursive
cd "$SCRIPT_DIR/../riscv-isa-sim"
if [[ ! -d "./build" ]]; then
  mkdir build
  cd build
  ../configure
  make -j $(nproc)
  cd ..
fi
cd ..
SPIKE_PATH=$(realpath "riscv-isa-sim/build")
echo "export SPIKE=$SPIKE_PATH" >> "$EXPORT_PATH"
echo "[I] SPIKE_PATH=$SPIKE_PATH"

# Make source.sh executable
chmod u+x "$EXPORT_PATH"
echo "[I] Run: 'source $EXPORT_PATH' in your terminal"