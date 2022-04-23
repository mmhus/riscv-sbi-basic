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
  struct sbiret get_impl_ver = sbi_get_impl_version();

    if (get_impl_ver.error != SBI_SUCCESS)
        exit_test(TEST_FAIL);

    if (get_impl_ver.value == 0x3e8)
        exit_test(TEST_PASS);
    else
        exit_test(TEST_FAIL);
}
