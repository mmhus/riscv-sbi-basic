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
  struct sbiret get_spec = sbi_get_spec_version();

  if (get_spec.error != SBI_SUCCESS)
    exit_test(TEST_FAIL);

  sbi_spec_version val;
  val.full_ver = get_spec.value;
  if (val.major_ver != 0)
    exit_test(TEST_FAIL);
  if (val.minor_ver != 2)
    exit_test(TEST_FAIL);

  exit_test(TEST_PASS);
}