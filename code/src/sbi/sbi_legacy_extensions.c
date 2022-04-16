#include "sbi_common.h"
#include "fw_macros.h"

void sbi_set_timer(uint64_t stime_value) {
  asm volatile(
    "li a7, "xstr(EID_0)";"
    "ecall;"
    ::: "memory"
  );
}

void sbi_console_putchar(int ch) {
  asm volatile(
    "li a7, "xstr(EID_1)";"
    "ecall;"
    ::: "memory"
  );
}

int sbi_console_getchar(void) {
  return sbi_inner_wrapper(EID_2, FID_0).value;
}

void sbi_clear_ipi(void) {
  asm volatile(
    "li a7, "xstr(EID_3)";"
    "ecall;"
    ::: "memory"
  );
}

void sbi_send_ipi(const unsigned long *hart_mask) {
  asm volatile(
    "li a7, "xstr(EID_4)";"
    "ecall;"
    ::: "memory"
  );
}

void sbi_remote_fence_i(const unsigned long *hart_mask) {
  asm volatile(
    "li a7, "xstr(EID_5)";"
    "ecall;"
    ::: "memory"
  );
}

void sbi_remote_sfence_vma(
  const unsigned long *hart_mask,
  unsigned long start,
  unsigned long size) {
  asm volatile(
    "li a7, "xstr(EID_6)";"
    "ecall;"
    ::: "memory"
  );
}

void sbi_remote_sfence_vma_asid(
  const unsigned long *hart_mask,
  unsigned long start,
  unsigned long size,
  unsigned long asid) {
  asm volatile(
    "li a7, "xstr(EID_7)";"
    "ecall;"
    ::: "memory"
  );
}

void sbi_shutdown(void) {
  asm volatile(
    "li a7, "xstr(EID_8)";"
    "ecall;"
    ::: "memory"
  );
}