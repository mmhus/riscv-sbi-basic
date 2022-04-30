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
//  Puts all the harts to shutdown state from supervisor point of view. This SBI call doesn’t return.
/**
 * @brief  
 *        Does not return
 * @return int 
 */
int test_case(void) {
  sbi_shutdown();

  exit_test(TEST_FAIL);
}

