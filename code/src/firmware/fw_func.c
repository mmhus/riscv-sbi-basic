#include "fw_func.h"
#include "fw_macros.h"
#include "mstatus.h"
#include "riscv_encoding.h"
#include <stdint.h>

void enable_pmp(void) {
  write_csr(pmpaddr0, 0xFFFFFFFFFFFFFFFF);
  write_csr(pmpcfg0, (PMP_A & PMP_TOR) | PMP_R | PMP_W | PMP_X);
  asm volatile("sfence.vma");
}

void switch_priv_M_to_S(void) {
  uint64_t mstatus_tmp = read_csr(mstatus); //csrr
  write_field(mstatus_tmp, MSTATUS_MPP , MSTATUS_MPP_SHIFT , S_MODE)
  write_field(mstatus_tmp, MSTATUS_MPIE, MSTATUS_MPIE_SHIFT, SET_1)
  write_csr(mstatus, mstatus_tmp);
  asm volatile(
    "lla t0, 1f;"
    "csrw mepc, t0;"
    "mret;"
    "1:"
    :
    :
    : "t0"
  );
}