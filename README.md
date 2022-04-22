# riscv-sbi-basic

## Intro

Implement the RISC-V SBI spec on Spike. More simulator/emulators to come later.
Eventually port to hardware. It's a learning experience.

### Some Loose Goals

1. Write all functions for SBI extensions
2. Test all functions for SBI extensions
3. Add a device tree file for spike
4. Make spike boot with our firmware
5. Build linux kernel for spike manually
6. Make spike run our own linux kernel
7. Add platform specific code for differentiation
8. Add linux driver for platform specific components

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

Run the following script inside the `riscv-sbi-basic` directory:

```bash
scripts/setup.sh
```

The script will:

- init the spike isa simulator repo in `riscv-isa-sim` and build it.
- ~~Download the latest pre-built RISC-V gcc toolchain from `toolchains.bootlin.com` of the `lp64d` ABI variety with uclibc as the c library. Rather than compiling the toolchain locally as it is faster to download a pre-built one. See,
`toolchains.bootlin.com` to see details regarding the toolchain downloaded. The toolchain will be download as an archive and then extracted into `toolchain` folder~~. This is not working for now, temporarily, you can download the pre-built toolchain from google drive and place the file as is in the `riscv-sbi-basic` directory. Then run `scripts/setup.sh`
- An export file with updated paths for the toolchain and spike iss will be generated, so that it can be sourced before using the Makefile.

### Compiling

Use to terminal to navigate to the `riscv-sbi-basic` directory, and run the following commands in the terminal. Sourcing is required only once per teriminal session:

```bash
source export.sh
make
```

### Running ELF on Spike ISS

Use to terminal to navigate to the `riscv-sbi-basic` directory, and run the following commands in the terminal. Sourcing is required only once per teriminal session:

```bash
source export.sh
make spike
```

### Spike version

24b962dec17e78d74e4040f572b429e57eb7ee8b
