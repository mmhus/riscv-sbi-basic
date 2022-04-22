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
  struct sbiret get_spec = sbi_probe_extension(EID_10);
  if (get_spec.value == 1) {
    if (get_spec.error == SBI_SUCCESS) {
        exit_test(TEST_PASS);}
  } else {
    exit_test(TEST_FAIL);}

  struct array {
        uint64_t a[21];
  } myArray = { { 0x01ul, 0x02ul, 0x03ul, 0x04ul, 0x05ul, 0x06ul, 0x07ul, 0x08ul,
  0x09ul, 0x0Aul, 0x0Bul, 0x0Cul, 0x0Dul, 0x0Eul, 0x0Ful, 0x54494D45ul, 0x735049ul,
  0x52464E43ul, 0x48534Dul, 0x53525354ul, 0x504D55ul } };
  int i;
  for (i = 0; i < 21; ++i) {
    get_spec = sbi_probe_extension(myArray.a[i]);
    if (get_spec.value == 0) {
    if (get_spec.error == SBI_ERR_NOT_SUPPORTED) {
        exit_test(TEST_PASS);}
  } else {
    exit_test(TEST_FAIL);}}
}
