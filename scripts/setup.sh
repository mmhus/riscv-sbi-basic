
#!/usr/bin/env bash

set -euo pipefail
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# SPIKE
git submodule update --init --recursive

# RISC-V TOOLCHAIN
RISCV_PATH=$(realpath "$SCRIPT_DIR/../toolchain")
EXPORT_PATH=$(realpath "$SCRIPT_DIR/../export.sh")
WGET_PATH="https://toolchains.bootlin.com/downloads/releases/toolchains/riscv64-lp64d/tarballs/riscv64-lp64d--uclibc--bleeding-edge-2021.11-1.tar.bz2"

mkdir -p "$RISCV_PATH"
echo "[I] RISCV=$RISCV_PATH"
wget -nc "$WGET_PATH"
echo "[I] Extracting files, please wait ... "
tar -xjvf riscv64-lp64d--uclibc*.tar.bz2 -C "$RISCV_PATH" >> /dev/null
echo "[I] Extracting Complete!"

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

# Make source.sh executable
chmod u+x "$EXPORT_PATH"
echo "[I] Run: 'source $EXPORT_PATH' in your terminal"
