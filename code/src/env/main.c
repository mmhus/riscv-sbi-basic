#include "test_macros.h"

/**
 * @brief test_case wrapper to return to m-mode
 * 
 * @return int 
 */
int run_test(void) {
  write_csr(mtvec, &m_mode_trap);
  write_csr(stvec, &s_mode_trap);
  asm volatile("ecall");  // Switch to S-mode
  int retval = test_case();
  asm volatile("ecall");  // Return to M-mode
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
