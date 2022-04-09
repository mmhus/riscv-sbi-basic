#include "fw_macros.h"
#include "fw_func.h"

#ifdef DEBUG
  #include "test_macros.h"
#endif

extern void _m_trap_handler(void);
void setup(void);

/**
 * @brief inline setup function
 * 
 */
inline void setup(void) {
  enable_pmp();
  write_csr(mtvec, &_m_trap_handler);
  write_csr(stvec, &s_mode_trap);
}

/**
 * @brief run m-mode code
 * 
 * @return int 
 */
int run(void) {
  setup();
  switch_priv_M_to_S();

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
