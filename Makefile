#----------------- MAKEFILE VARIABLES -----------------
MAKEFILE_DIR := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
ENV_DIR = $(shell dirname ${dir ${SRCS}}/dummy)

#----------------- COMPILER VARIABLES -----------------
# Architecture options to compiler.
CARCH ?= -march=rv64gc_zba2p0_zbb2p0_zbc2p0_zbs2p0_zicbom_zicbop_zicboz
# Optimization options to compiler.
COPT ?= -O2
# Additional options to compiler.
CFLAGS ?=
# Number of harts.
NUM_HARTS ?= 1

SPIKE_CMD ?= 

#----------------- ISS VARIABLES -----------------
# Timeout
TIMEOUT ?= 30s
TIMEOUT_CMD = timeout ${TIMEOUT}

# Custom Library Directory
LIB_DIR := ""

#----------------- INTERNAL VARIABLES -----------------
CODE_DIR := ${MAKEFILE_DIR}/code
COMPILE_DIR := ${MAKEFILE_DIR}/COMPILE
ELF_FILE := ${COMPILE_DIR}/sbi.elf
DIS_FILE := ${COMPILE_DIR}/sbi.asm

LIB_INCL := $(CODE_DIR)/include/libs
LIB_SRCS := \
	$(wildcard $(CODE_DIR)/src/libs/*.c) \
	$(wildcard $(CODE_DIR)/src/libs/*.S)

ENV_INCL := $(CODE_DIR)/include/env
ENV_SRCS := \
	$(wildcard $(CODE_DIR)/src/env/*.c) \
	$(wildcard $(CODE_DIR)/src/env/*.S)
 
BASE_CFLAGS := \
	-Werror \
	-ffreestanding \
	-nostdlib \
	-mcmodel=medany \
	-fno-builtin \
	-I${LIB_INCL} \
	-I${ENV_INC} \
	-g \
	-ggdb \
	-Wl,--entry=test_top

DISASSEMBLY_FLAGS := \
	--all-headers \
	--demangle \
	--disassemble-all \
	--disassembler-options=no-aliases,numeric \
	--full-contents \
	--prefix-addresses \
	--line-numbers \
	--show-raw-insn \
	--source

#if given default LD
LD_DEFAULT ?=
LDFLAGS = -T${CODE_DIR}/linker.ld

# Expansions
COMPILE_EXP = $(shell echo "riscv64-linux-gcc ${BASE_CFLAGS} ${CARCH} ${COPT} ${CFLAGS} ${FRAMEWORK_SRCS} ${COMMON_SRCS} ${ENV_SRCS} ${LIB_SRCS} ${LDFLAGS} -o $@")
DISM_EXP = $(shell echo "riscv64-linux-objdump ${DISASSEMBLY_FLAGS} $< > $@")
# ISS_EXP = $(shell echo "timeout --preserve-status --foreground ${TIMEOUT} $(SPIKE_CMD)")

# Targets

.PHONY: default setup spike clean compile

default: compile

setup:
	mkdir -p ${COMPILE_DIR}
	@echo "CMP_DIR : "${COMPILE_DIR}
	@echo "ELF_FILE: "${ELF_FILE}
	@echo "DIS_FILE: "${DIS_FILE}
	@echo "ENV_INCL: "${ENV_INCL}
	@echo "ENV_SRCS: "${ENV_SRCS}
	@echo "LIB_INCL: "${LIB_INCL}
	@echo "LIB_SRCS: "${LIB_SRCS}
	@echo "LDFLAGS : "${LDFLAGS}

${ELF_FILE}: setup ${SRCS}
	@echo ${COMPILE_EXP} > ${COMPILE_DIR}/compile_cmd.sh.sh
	@chmod u+x ${COMPILE_DIR}/compile_cmd.sh.sh
	$(RISCV)/riscv64-linux-gcc ${BASE_CFLAGS} ${CARCH} ${COPT} ${CFLAGS} ${FRAMEWORK_SRCS} ${COMMON_SRCS} ${ENV_SRCS} ${LIB_SRCS} ${LDFLAGS} -o $@

${DIS_FILE}: ${ELF_FILE}
	@echo ${DISM_EXP} > ${COMPILE_DIR}/disassembly_cmd.sh.sh
	@chmod u+x ${COMPILE_DIR}/disassembly_cmd.sh.sh
	$(RISCV)/riscv64-linux-objdump ${DISASSEMBLY_FLAGS} $< > $@
	@echo "export DBG=${ELF_FILE}" > ${COMPILE_DIR}/run_gdb.sh.sh
	@echo "riscv64-linux-gdb --exec=${realpath ${ELF_FILE}} --symbols=${realpath ${ELF_FILE}}" >> ${COMPILE_DIR}/run_gdb.sh.sh

compile: ${ELF_FILE} ${DIS_FILE}
	touch ${COMPILE_DIR}/failed.txt
	@mv ${COMPILE_DIR}/failed.txt ${COMPILE_DIR}/passed.txt

spike:
	$(SPIKE)/spike --isa=rv64imafdcv -l --log-commits ${ELF_FILE} 1> $@.out 2> $@.err

clean:
	rm -rf $(MAKEFILE_DIR)/COMPILE
	rm -rf $(MAKEFILE_DIR)/LINT_RESULTS
	rm -rf $(MAKEFILE_DIR)/RUN
