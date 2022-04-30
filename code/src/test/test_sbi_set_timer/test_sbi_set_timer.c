#include "test_macros.h"
int test_case(void);

bool interrupt_ok = false;


/**
 * @brief interrupt handler function that runs in S-mode. Not used in this test
 * 
 */
__attribute__((interrupt("supervisor")))
void s_mode_trap(void) {
  uint64_t cause = read_csr(scause);

  switch (cause) {
    case CAUSE_IRQ_S_TIMER:
      interrupt_ok = true;
      break;
    default:
      exit_test(TEST_FAIL);      break;
  }
}

/**
 * @brief Programs the clock for next event after stime_value time. This function also clears the pending timer
          interrupt bit.If the supervisor wishes to clear the timer interrupt without scheduling the next timer event, it can
          either request a timer interrupt infinitely far into the future (i.e., (uint64_t)-1), or it can instead mask
          the timer interrupt by clearing sie.STIE CSR bit.
 * 
 * @return int 
 */
  uint64_t stime_value = 5;
int test_case(void) {
  sbi_set_timer(stime_value);
  while (!interrupt_ok){}
}