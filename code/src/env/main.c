#include "test_macros.h"

extern void _m_trap_handler(void);

/**
 * @brief run m-mode code
 * 
 * @return int 
 */
int run(void) {
  write_csr(mtvec, &_m_trap_handler);
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
  int retval = run();
  return retval;
}
