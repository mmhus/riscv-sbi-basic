#include "test_macros.h"

bool interrupt_check = false;
int test_case(void);

/**
 * @brief interrupt handler function that runs in S-mode. Not used in this test
 * 
 */
__attribute__((interrupt("supervisor")))
void s_mode_trap(void) {
  uint64_t cause = read_csr(scause);

  switch (cause) {
    case (CAUSE_IRQ_S_SOFT):
    interrupt_check = true;
    sbi_clear_ipi();
    break;
    default:
    exit_test(TEST_FAIL);
      break;
  }
}

/**
 * @brief Test case example checks for marchid
 * 
 * @return int 
 */
uint64_t hart_mask = 1;


int test_case(void) {
  int x;

  for (x=0; x <= 1; x++) {
  sbi_send_ipi(&hart_mask);
  if (interrupt_check == true) {
    interrupt_check = false;
  } else {
    exit_test(TEST_FAIL);
  }
hart_mask <<=1;
}
}
