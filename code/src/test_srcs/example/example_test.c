
#include "test_macros.h"

bool pass_fail = TEST_FAIL;

/**
 * @brief interrupt handler function that runs in M-mode
 * 
 */
__attribute__((interrupt("machine")))
void handle_trap(void) {
  uint64_t cause = read_csr(mcause);

  switch (cause) {
    case CAUSE_ILLEGAL_INSTRUCTION:
    {
      write_csr(mepc, read_csr(mepc)+4);
      pass_fail = TEST_PASS;
      break;
    }
    case CAUSE_MACHINE_ECALL:
    {
      if (end_test) {
        return_to_M_mode();  // Always the same for every test_case
      } 
      write_csr(mstatus, mstatus1);
      break;
    }
    default:
    {
      break;
    }
  }
}

/**
 * @brief interrupt handler function that runs in S-mode. Not used in this test
 * 
 */
__attribute__((interrupt("supervisor")))
void handle_trap(void) {
  uint64_t cause = read_csr(mcause);

  switch (cause) {
    default:
      END_TEST(TEST_FAIL);
  }
}

/**
 * @brief Test case example checks for illegal instruction exception
 * 
 * @return int 
 */
int test_case(void) {
  asm volatile(".word 0xFFFFFFFF");  //illegal instruction

  END_TEST(pass_fail);
}