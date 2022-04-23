#include "fw_macros.h"
#include "fw_func.h"
#include "riscv_encoding.h"

#ifdef DEBUG
  #include "test_macros.h"
#endif

void setup_m(void);
void setup_s(void);

/**
 * @brief inline setup function for m-mode
 * 
 */
inline void setup_m(void) {
  enable_pmp();
  uint64_t mideleg_mask = (1ull << IRQ_S_TIMER) |
                          (1ull << IRQ_S_EXT)   | 
                          (1ull << IRQ_S_SOFT);
  set_csr(mideleg, mideleg_mask);
  write_csr(mtvec, &_m_trap_handler);
  set_csr(mie, MIP_SEIP | MIP_SSIP);
}

/**
 * @brief inline setup function for s-mode
 * 
 */
inline void setup_s(void) {
  write_csr(stvec, &s_mode_trap);
  set_csr(sstatus, MSTATUS_SIE);
  set_csr(sie, MIP_STIP | MIP_SEIP | MIP_SSIP);
}

/**
 * @brief run m-mode code
 * 
 * @return int 
 */
int run(void) {
  setup_m();
  switch_priv_M_to_S();
  setup_s();

  #ifdef DEBUG
    test_case();
  #endif

  return 0;
}

/**
 * @brief 
 * 
 * @return int 
 */
int main(void) {
  int retval = run();
  return retval;
}
