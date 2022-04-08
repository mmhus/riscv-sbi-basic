#include "test_macros.h"

int test_case(void);

/**
 * @brief interrupt handler function that runs in S-mode. Not used in this test
 * 
 */
__attribute__((interrupt("supervisor")))
void s_mode_trap(void) {
  uint64_t cause = read_csr(scause);

  switch (cause) {
    default:
      break;
  }
}

/**
 * @brief Test case example checks for illegal instruction exception
 * 
 * @return int 
 */
int test_case(void) {
  asm volatile(".word 0xFFFFFFFF");  //illegal instruction

  END_TEST(TEST_PASS);
}