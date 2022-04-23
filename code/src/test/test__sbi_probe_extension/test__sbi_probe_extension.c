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
 * @brief Test case for all EIDs(entries of array) that are not supported and returns zero. Short description 
 * of each ID is written in comments along with each entry in array.
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

  uint64_t a[] = {0x00ul,                   // Extension: Set Timer
                  0x01ul,                   // Extension: Console Putchar
                  0x02ul,                   // Extension: Console Getchar
                  0x03ul,                   // Extension: Clear IPI
                  0x04ul,                   // Extension: Send IPI
                  0x05ul,                   // Extension: Remote FENCE.I
                  0x06ul,                   // Extension: Remote SFENCE.VMA
                  0x07ul,                   // Extension: Remote SFENCE.VMA with ASID
                  0x08ul,                   // Extension: System Shutdown
                  0x54494D45ul,             // Timer Extension
                  0x735049ul,               // IPI Extension
                  0x52464E43ul,             // RFENCE Extension
                  0x48534Dul,               // Hart State Management Extension
                  0x53525354ul,             // System Reset Extension
                  0x504D55ul };             // Performance Monitoring Unit Extension
  int i;
  for (i = 0; i < (sizeof(a)/sizeof(a[0])); ++i) {
    get_spec = sbi_probe_extension(a[i]);
    if (get_spec.value == 0) {
    if (get_spec.error == SBI_ERR_NOT_SUPPORTED) {
        exit_test(TEST_PASS);}
  } else {
    exit_test(TEST_FAIL);}}
}

