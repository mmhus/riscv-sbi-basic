#include "test_macros.h"

/**
 * @brief pure virtual test_case function for test cases
 * 
 * @return int 
 */
__attribute__((weak))
int test_case (void) {}

/**
 * @brief test_case wrapper to return to m-mode
 * 
 * @return int 
 */
int run_test(void) {
  switch_to_S_mode();
  int retval = test_case();
  asm volatile("ecall");
}

/**
 * @brief enables pmp in m-mode using pmpcfg0
 * 
 */
void enable_pmp(void) {
  write_csr(pmpaddr0, 0xFFFFFFFFFFFFFFFF);
  write_csr(pmpcfg0, (PMP_A & PMP_TOR) | PMP_R | PMP_W | PMP_X);
  asm volatile("sfence.vma");
}

/**
 * @brief 
 * 
 * @return int 
 */
int main(void) {
  enable_pmp();
  int retval = run_test();
  return retval;
}
