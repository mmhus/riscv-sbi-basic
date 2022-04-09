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
  //unsigned long input = 0x10ul;
  struct sbiret get_spec = sbi_probe_extension(EID_10);
  if(get_spec.value == 1)
  {
    if(get_spec.error == SBI_SUCCESS)
    {
        exit_test(TEST_PASS);
    }
  }

  /*sbi_spec_version val;
  val.full_ver = get_spec.value;
  if (val.major_ver != 0)
    exit_test(TEST_FAIL);
  if (val.minor_ver != 2)
    exit_test(TEST_FAIL);*/
else
  {exit_test(TEST_FAIL);}
}