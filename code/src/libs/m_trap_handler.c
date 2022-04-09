#include <stdint.h>
#include <stdbool.h>

#include "riscv_encoding.h"
#include "mstatus.h"
#include "sbi_common.h"

#ifdef DEBUG
  #include "test_macros.h"
#endif

void sbi_probe_extension_inner(extension_id, struct sbiret* ret) {
  if(!ret)
    assert(3780);

  switch (extension_id) {
    case EID_10: {
      ret->value = 1;
      ret->error = SBI_SUCCESS;
    }
    case default: {
      ret->value = 0;
      ret->error = SBI_ERR_NOT_SUPPORTED;
      break;
    }
  }
}

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
    .error = SBI_ERR_FAILED,
    .value = 0xFFFFFFFF
  };

  // Do the sbi call
  switch (eid) {
    case EID_10: {
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
          ret.value = 7;
          ret.error = SBI_SUCCESS;
          break;
        }
        case FID_2: {
          ret.value = 1000;
          ret.error = SBI_SUCCESS;
          break;
        }
        case FID_3: {
          long extension_id = 0xFFFFFFFF;
          asm volatile(
            "mv %0, a0;"
            :"=r"(extension_id)
            :
            : "memory"
          );
          sbi_probe_extension_inner(extension_id, ret);
          break;
        }
        case FID_4: {
          ret.value = read_csr(mvendorid);
          ret.error = SBI_SUCCESS;
          break;
        }
        case FID_5: {
          ret.value = read_csr(marchid);
          ret.error = SBI_SUCCESS;
          break;
        }
        case FID_6: {
          ret.value = read_csr(mimpid);
          ret.error = SBI_SUCCESS;
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    // eid switch case
    default: {
      break;
    }
  }
  return ret;
}

__attribute__((naked))
void m_trap_handler(void) {
  uint64_t ret_pc = 0xFFFFFFFFFFFFFFFF;  //Invalid default pc ret
  asm volatile("mv %0, ra" :"=r"(ret_pc)::"memory");
  uint64_t cause = read_csr(mcause);

  switch (cause) {
    case CAUSE_SUPERVISOR_ECALL:
    {
      handle_sbi_call();
      write_csr(mepc, read_csr(mepc)+4);
      break;
    }
    // Default for mcause
    default:
      assert(3781);
  }
  asm volatile(
    "mv ra, %0;"
    "ret"
    ::"r"(ret_pc):"memory"
  );
}