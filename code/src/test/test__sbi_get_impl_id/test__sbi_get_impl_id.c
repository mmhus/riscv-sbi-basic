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

  switch (get_impl.value) {
  case SBI_imp_id_BBL:
  case SBI_imp_id_OpenSBI:
  case SBI_imp_id_Xvisor:
  case SBI_imp_id_KVM:
  case SBI_imp_id_RustSBI:
  case SBI_imp_id_Diosix:
  case SBI_imp_id_Coffer:
  case 7:  // FIRST FREE VALUE
    exit_test(TEST_PASS);
    break;
  default:
  exit_test(TEST_FAIL);
    break;
  }
}
