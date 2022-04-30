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
 * @brief Test case for Extension: Remote FENCE.I:
 *  Instructs remote harts to execute FENCE.I instruction.
 * @return void 
 */

int test_case(void) {
    uint64_t hart_mask = 0x01ul;
    sbi_remote_fence_i(&hart_mask);

    hart_mask = 0x02ul;
    sbi_remote_fence_i(&hart_mask);

    hart_mask = 0x03ul;
    sbi_remote_fence_i(&hart_mask);
    exit_test(TEST_PASS);
}

