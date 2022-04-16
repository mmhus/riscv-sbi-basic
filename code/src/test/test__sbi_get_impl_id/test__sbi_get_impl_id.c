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
  struct sbiret get_impl = sbi_get_impl_id();

  if (get_impl.error != SBI_SUCCESS)
    exit_test(TEST_FAIL);

  if (get_impl.value >= 0 ||  get_impl.value <= 6)
    exit_test(TEST_PASS);
}
