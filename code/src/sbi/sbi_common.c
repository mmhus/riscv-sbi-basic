#include "sbi_common.h"

/**
 * Using local struct sbiret so that functions are re-entrant
 */
struct sbiret sbi_inner_wrapper(sbi_t eid, sbi_t fid) {
    struct sbiret ret = { 
    .error = SBI_ERR_FAILED,
    .value = 0xFFFFFFFF
  };
  asm volatile (
    "mv a7, a0;"
    "mv a6, a1;"
    "ecall;"
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