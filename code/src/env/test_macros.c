#include "test_macros.h"

bool test_end_code = TEST_FAIL;  // Should be in every test

void switch_to_S_mode() {
  uint64_t mstatus1 = read_csr(mstatus); //csrr
  write_field(mstatus1, MSTATUS_MPP, 11, M_MODE)
  write_csr(mstatus, mstatus1);
}

void return_to_M_mode() {
  uint64_t mstatus1 = read_csr(mstatus); //csrr
  write_field(mstatus1, MSTATUS_MPP, 11, M_MODE)
  write_csr(mepc, read_csr(mepc)+4);
}