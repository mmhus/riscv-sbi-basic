# riscv-sbi-basic

## Intro

Implement the RISC-V SBI spec on Spike. More simulator/emulators to come later.
Eventually port to hardware. It's a learning experience.

## Requirements

### Linux Distributions

- Ubuntu 20.04 LTS

### List of Software

You will need to install the following list of software to get started:

```bash
sudo apt-get install libtool autoconf automake cmake libncurses5-dev g++ shellcheck python3-venv device-tree-compiler
```

And the following ubuntu snap packages:

```bash
sudo snap install shfmt
```

Also requires the use of open source RISC-V ISA spike simulator, which is already included as a submodule within the repo
and does not need to be installed.

## Getting started

### Run Script

Run the following script:

```bash
scripts/setup.sh
```

The script will:

- init the spike isa simulator repo in `riscv-isa-sim` and build it.
- Download the latest pre-built RISC-V gcc toolchain from `toolchains.bootlin.com` of the `lp64d` ABI variety with uclibc as the c library. Rather than compiling the toolchain locally as it is faster to download a pre-built one. See,
`toolchains.bootlin.com` to see details regarding the toolchain downloaded. The toolchain will be download as an archive and then extracted into `toolchain` folder
- An export file with updated paths for the toolchain and spike iss will be generated, so that it can be sourced before using the Makefile.
