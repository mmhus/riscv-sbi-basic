#----------------- MAKEFILE VARIABLES -----------------
MAKEFILE_DIR := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
TEST_DIR ?=

#----------------- COMPILER VARIABLES -----------------
# Architecture options to compiler.
CARCH ?= -march=rv64gc_zba2p0_zbb2p0_zbc2p0
# Optimization options to compiler.
COPT ?= -O0
# Additional options to compiler.
CFLAGS ?=

#----------------- ISS VARIABLES -----------------
# Timeout
TIMEOUT ?= 5s
TIMEOUT_CMD = timeout --foreground ${TIMEOUT}

# Number of harts.
NUM_HARTS ?= 1
#----------------- INTERNAL VARIABLES -----------------
CODE_DIR := ${MAKEFILE_DIR}/code
RUN_DIR := ${MAKEFILE_DIR}/RUN
COMPILE_DIR := ${MAKEFILE_DIR}/COMPILE
ELF_FILE := ${COMPILE_DIR}/sbi.elf
DIS_FILE := ${COMPILE_DIR}/sbi.asm

#----------------- INCLUDE VARIABLES -----------------

FW_INCL := $(CODE_DIR)/include/firmware
SBI_INCL := $(CODE_DIR)/include/sbi
LIB_INCL := $(CODE_DIR)/include/libs
ENV_INCL := $(CODE_DIR)/include/env
TEST_INCL := $(CODE_DIR)/include/test

ALL_INCL := ${TEST_INCL} ${FW_INCL} ${SBI_INCL} ${LIB_INCL} ${ENV_INCL}

#----------------- SOURCE VARIABLES -----------------

FW_SRCS := \
	$(wildcard $(CODE_DIR)/src/firmware/*.c) \
	$(wildcard $(CODE_DIR)/src/firmware/*.S)
SBI_SRCS := \
	$(wildcard $(CODE_DIR)/src/sbi/*.c) \
	$(wildcard $(CODE_DIR)/src/sbi/*.S)
LIB_SRCS := \
	$(wildcard $(CODE_DIR)/src/libs/*.c) \
	$(wildcard $(CODE_DIR)/src/libs/*.S)
ENV_SRCS := \
	$(wildcard $(CODE_DIR)/src/env/*.c) \
	$(wildcard $(CODE_DIR)/src/env/*.S)
FULL_TEST_DIR_PATH := $(abspath $(TEST_DIR))
TEST_SRCS := \
	$(wildcard $(FULL_TEST_DIR_PATH)/*.c) \
	$(wildcard $(FULL_TEST_DIR_PATH)/*.S)

ALL_SRCS :=  ${TEST_SRCS} ${FW_SRCS} ${SBI_SRCS} ${LIB_SRCS} ${ENV_SRCS}

#----------------- OPTIONS VARIABLES -----------------

BASE_CFLAGS := \
	-Werror \
	-ffreestanding \
	-nostdlib \
	-mcmodel=medany \
	-fno-builtin \
	-g \
	-ggdb \
	-Wl,--entry=_entry \
	-I${FW_INCL} \
	-I${SBI_INCL} \
	-I${LIB_INCL} \
	-I${ENV_INCL} \
	-I${TEST_INCL}

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

SPIKE_OPTIONS := \
	--isa=rv64imafdcv \
	-m0x0:0x90000000 \
	-p${NUM_HARTS} \
	--real-time-clint \
	-l --log-commits

#if given default LD
LD_DEFAULT ?=
LDFLAGS = -T${CODE_DIR}/linker.ld

# Expansions
COMPILE_EXP = $(shell echo "$(RISCV)/riscv64-unknown-elf-gcc ${BASE_CFLAGS} ${CARCH} ${COPT} ${CFLAGS} ${ALL_SRCS} ${LDFLAGS} -o $@")
DISM_EXP = $(shell echo "$(RISCV)/riscv64-unknown-elf-objdump ${DISASSEMBLY_FLAGS} $< > $@")
ISS_EXP = $(shell echo "timeout --preserve-status --foreground ${TIMEOUT} $(SPIKE)/spike ${SPIKE_OPTIONS} ${ELF_FILE} 1> ${RUN_DIR}/$@.out 2> ${RUN_DIR}/$@.err")


# @echo "FW_INCL  : "${FW_INCL}
# @echo "LIB_INCL : "${LIB_INCL}
# @echo "ENV_INCL : "${ENV_INCL}
# @echo "SBI_INCL : "${SBI_INCL}
# @echo "TEST_INCL: "${TEST_INCL}
# @echo ""
# @echo "FW_SRCS  : "${FW_SRCS}
# @echo "SBI_SRCS : "${SBI_SRCS}
# @echo "ENV_SRCS : "${ENV_SRCS}
# @echo "LIB_SRCS : "${LIB_SRCS}
# @echo "TEST_SRCS: "${TEST_SRCS}

# Targets

.PHONY: default setup spike clean compile

default: compile

setup:
	@echo "\n==== SETUP INFO ==== "
	@mkdir -p ${COMPILE_DIR}
	@echo ""
	@echo "TEST_DIR : "${TEST_DIR}
	@echo "CMP_DIR  : "${COMPILE_DIR}
	@echo "ELF_FILE : "${ELF_FILE}
	@echo "DIS_FILE : "${DIS_FILE}
	@echo "RUN_DIR  : "${RUN_DIR}
	@echo ""
	@echo "ALL_INCL : "${ALL_INCL}
	@echo ""
	@echo "ALL_SRCS : "${ALL_SRCS}
	@echo ""
	@echo "LDFLAGS  : "${LDFLAGS}
	@echo "CFLAGS   : "${CFLAGS}

${ELF_FILE}: setup ${SRCS}
	@echo "\n==== COMPILING ==== "
	@echo ${COMPILE_EXP} > ${COMPILE_DIR}/compile_cmd.sh
	@chmod u+x ${COMPILE_DIR}/compile_cmd.sh
	$(RISCV)/riscv64-unknown-elf-gcc ${BASE_CFLAGS} ${CARCH} ${COPT} ${CFLAGS} ${ALL_SRCS} ${LDFLAGS} -o $@

${DIS_FILE}: ${ELF_FILE}
	@echo "\n==== DISASSEMBLING ==== "
	@echo ${DISM_EXP} > ${COMPILE_DIR}/disassembly_cmd.sh
	@chmod u+x ${COMPILE_DIR}/disassembly_cmd.sh
	$(RISCV)/riscv64-unknown-elf-objdump ${DISASSEMBLY_FLAGS} $< > $@
	@echo "export DBG=${ELF_FILE}" > ${COMPILE_DIR}/run_gdb.sh
	@echo "$(RISCV)/riscv64-unknown-elf-gdb --exec=${realpath ${ELF_FILE}} --symbols=${realpath ${ELF_FILE}}" >> ${COMPILE_DIR}/run_gdb.sh

compile: ${ELF_FILE} ${DIS_FILE}
	@touch ${COMPILE_DIR}/failed.txt
	@mv ${COMPILE_DIR}/failed.txt ${COMPILE_DIR}/passed.txt

spike:
	@echo "\n==== RUNNING SPIKE ==== "
	@mkdir -p "${RUN_DIR}"
	@rm -f "${RUN_DIR}/spike.err"
	@rm -f "${RUN_DIR}/spike.out"
	@echo ${ISS_EXP} > ${RUN_DIR}/iss_cmd.sh
	@chmod u+x ${RUN_DIR}/iss_cmd.sh
	${TIMEOUT_CMD} ${SPIKE}/spike ${SPIKE_OPTIONS} ${ELF_FILE} 1> ${RUN_DIR}/$@.err 2> ${RUN_DIR}/$@.out

clean:
	rm -rf $(MAKEFILE_DIR)/COMPILE
	rm -rf $(MAKEFILE_DIR)/LINT_RESULTS
	rm -rf ${RUN_DIR}
