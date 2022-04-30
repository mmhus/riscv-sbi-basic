#include "test_macros.h"
#include "spike_platform.h"

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
 * @brief Test case for Extension: Remote SFENCE.VMA with ASID
 * 
 * Instruct the remote harts to execute one or more SFENCE.VMA instructions, covering the range of
   virtual addresses between start and size. This covers only the given ASID.
 * 
 * @return int 
 */

int test_case(void) {
    uint64_t hart_mask = 0x01ul;
    uint64_t start = SPIKE_BASE+0x100000;
    uint64_t size = 0x10000ul;
    uint64_t asid = 20;
    sbi_remote_sfence_vma_asid(&hart_mask, start, size, asid);

    hart_mask = 0x02ul;
    sbi_remote_sfence_vma_asid(&hart_mask, start, size, asid);

    hart_mask = 0x03ul;
    sbi_remote_sfence_vma_asid(&hart_mask, start, size, asid);

    exit_test(TEST_PASS);
}
