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
 * @brief Return a value that is legal for the mvendorid CSR and 0 is always a legal value for this CSR
 * 
 * @return int 
 */
int test_case(void) {
  struct sbiret get_mvendorid = sbi_get_mvendorid();

  if (get_mvendorid.error != SBI_SUCCESS)
    exit_test(TEST_FAIL);
  if (get_mvendorid.value == 0)
    exit_test(TEST_PASS);
}
