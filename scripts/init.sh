
#!/usr/bin/env bash

git submodule init --recursive
wget "https://toolchains.bootlin.com/downloads/releases/toolchains/riscv64-lp64d/tarballs/riscv64-lp64d--uclibc--bleeding-edge-2021.11-1.tar.bz2"
tar -xjvf "riscv64-lp64d--uclibc*.tar.bz2" -C "toolchain"
