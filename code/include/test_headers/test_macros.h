#ifndef TEST_MACROS_H
#define TEST_MACROS_H

// ============================ INCLUDES ===============================

#include "riscv_abi_encoding.h"
#include "riscv_sbi_encoding.h"
#include "riscv_encoding.h"

#include <stdint.h>
#include <stdbool.h>

// ============================ DEFINES ===============================

#define SET_0 0ull
#define SET_1 1ull

#define U_MODE 0
#define S_MODE 1
#define M_MODE 3

#define TEST_PASS SET_0
#define TEST_FAIL SET_1

// ============================ MACROS ===============================

#define write_field(reg, mask, shift, value) \
  reg = (reg & ~mask) | ((value << shift) & mask);

// TODO: incomplete
#define read_field(reg, mask, shift, value) \
  reg = (reg & ~mask) | ((value << shift) & mask);

#define END_TEST(end_code) \
  end_test = SET_1;  \
  return end_code;

// ============================ GLOBAL VARIABLES ===============================

extern bool end_test;

// ============================ FUNCTIONS ===============================

/**
 * @brief interrupt handler function that runs in M-mode
 * 
 */
__attribute__((interrupt("machine"))) 
void m_mode_trap(void);

__attribute__((noreturn))
void exit_test(int code);

void switch_to_S_mode(void);

// ============================ WEAK FUNCTIONS ===============================

/**
 * @brief pure virtual test_case function for test cases
 * 
 * @return int 
 */
__attribute__((weak))
int test_case(void);

/**
 * @brief interrupt handler function that runs in S-mode.
 * 
 */
__attribute__((weak)) 
__attribute__((interrupt("supervisor"))) 
void s_mode_trap(void);

// ============================ END ===============================


#endif /* TEST_MACROS_H */