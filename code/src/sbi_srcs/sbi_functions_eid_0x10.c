#include "sbi_common.h"
#include "fw_macros.h"

#define EID_10 0x10ul

struct sbiret sbi_get_spec_version(void) {
  return sbi_inner_wrapper(EID_10, FID_0);
}

struct sbiret sbi_get_impl_id(void) {
  return sbi_inner_wrapper(EID_10, FID_1);
}

struct sbiret sbi_get_impl_version(void) {
  return sbi_inner_wrapper(EID_10, FID_2);
}

struct sbiret sbi_probe_extension(long extension_id) {
    struct sbiret ret = { 
    .error = SBI_ERR_FAILED,
    .value = 0xFFFFFFFF
  };
  // eid 0x10, fid 3
  asm volatile(
    "li a7, 0x10;"
    "li a6, 3;"
    "mv a0, %0;"
    "ecall;"
    :
    : "r"(extension_id)
    : "memory"
  );
  asm volatile(
    "mv %[error], a0;"
    "mv %[value], a1;"
    : [error]"=r"(ret.error), [value]"=r"(ret.value)
    :
    : "memory"
  );
  return ret;
}

struct sbiret sbi_get_mvendorid(void) {
  return sbi_inner_wrapper(EID_10, FID_4);
}

struct sbiret sbi_get_marchid(void) {
  return sbi_inner_wrapper(EID_10, FID_5);
}

struct sbiret sbi_get_mimpid(void) {
  return sbi_inner_wrapper(EID_10, FID_6);
}
