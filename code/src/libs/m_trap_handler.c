#include <stdint.h>
#include <stdbool.h>

#include "riscv_encoding.h"
#include "mstatus.h"
#include "sbi_common.h"

#ifdef DEBUG
  #include "test_macros.h"
#endif

struct sbiret handle_sbi_call(void) {
  // Load eid, fid in variables from registers
  sbi_t eid = 0xFFFFFFFF;
  sbi_t fid = 0xFFFFFFFF;
  asm volatile(
    "mv %0, a7;"
    "mv %1, a6;"
    :"=r"(eid), "=r"(fid)
    :
    : "memory"
  );

  // setup sbi return struct
  struct sbiret ret = {
    .error = SBI_ERR_NOT_SUPPORTED,
    .value = 0xFFFFFFFF
  };

  // Do the sbi call
  switch (eid) {
    case EID_10:
    {
      switch (fid) {
        case FID_0: {
          sbi_spec_version sbi_version;
          sbi_version.major_ver = 0;
          sbi_version.minor_ver = 2;
          ret.value = sbi_version.full_ver;
          ret.error = SBI_SUCCESS;
          break;
        }
        case FID_1: {
          break;
        }
        case FID_2: {
          break;
        }
        case FID_3: {
          break;
        }
        case FID_4: {
          break;
        }
        case FID_5: {
          break;
        }
        case FID_6: {
          break;
        }
        default:
          exit_test(TEST_FAIL);
      }
      break;
    }
    default:
      exit_test(TEST_FAIL);
  }
  return ret;
}

  // // Put retval values in a0, a1
  // asm volatile(
  //   "mv a0, %0"
  //   "mv a1, %1"
  //   :
  //   : "r"(ret.error), "r"(ret.value)
  //   : "memory"
  // );

__attribute__((naked))
void m_trap_handler(void) {
  uint64_t cause = read_csr(mcause);

  switch (cause) {
    case CAUSE_SUPERVISOR_ECALL:
    {
      #ifdef DEBUG
        if (end_test) {
          return_to_M_mode();  // Always the same for every test_case
          write_csr(mepc, read_csr(mepc)+4);
        } else {
      #endif
        handle_sbi_call();
      #ifdef DEBUG
        }
      #endif
      break;
    }
    // Default for mcause
    default:
      exit_test(TEST_FAIL);
  }
  asm("ret");
}