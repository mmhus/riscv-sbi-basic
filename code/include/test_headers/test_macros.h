#ifndef TEST_MACROS_H
#define TEST_MACROS_H

// ============================ INCLUDES ===============================

#include "sbi_common.h"
#include "riscv_encoding.h"
#include "fw_macros.h"

#include <stdint.h>
#include <stdbool.h>

// ============================ DEFINES ===============================

#define TEST_PASS SET_0
#define TEST_FAIL SET_1

#define END_TEST(end_code) \
  end_test = SET_1;  \
  return end_code;

// ============================ GLOBAL VARIABLES ===============================

extern bool end_test;

// ============================ FUNCTIONS ===============================

/**
 * @brief exit the test case with exit code
 * 
 * @param code integer exit code value
 */
__attribute__((noreturn))
void exit_test(int code);

/**
 * @brief test_case function to return to m_mode
 * 
 */
void return_to_M_mode(void);

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