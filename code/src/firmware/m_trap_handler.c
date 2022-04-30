#include <stdint.h>
#include <stdbool.h>

#include "riscv_encoding.h"
#include "mstatus.h"
#include "sbi_common.h"
#include "platform.h"

#ifdef DEBUG
  #include "test_macros.h"
#endif

extern void* ecall_args;
sbi_t* args = 0;

unsigned long fencei_mask = 0;
unsigned long sfence_mask = 0;

unsigned long sfence_asid_mask = 0;
unsigned long sfence_start = 0;
unsigned long sfence_size = 0;
unsigned long sfence_asid = 0;

static void set_timer_interrupt(struct sbiret* ret) {
  uint64_t cmp_val = args[0];
  uint64_t hartid = read_csr(mhartid);
  volatile uint32_t* mtimecmp_hi = (volatile uint32_t*)MMR_MTIME_HI(hartid);
  volatile uint32_t* mtimecmp_lo = (volatile uint32_t*)MMR_MTIME_LO(hartid);
  *mtimecmp_hi = -1;
  *mtimecmp_lo = (uint32_t)(cmp_val >> 32);
  *mtimecmp_hi = (uint32_t)(cmp_val);
  set_csr(mie, MIP_MTIP);
  ret->error = SBI_SUCCESS;
}

static void clear_timer_interrupt(void) {
  uint64_t hartid = read_csr(mhartid);
  volatile uint32_t* mtimecmp_hi = (volatile uint32_t*)MMR_MTIME_HI(hartid);
  volatile uint32_t* mtimecmp_lo = (volatile uint32_t*)MMR_MTIME_LO(hartid);
  *mtimecmp_hi = -1;
  *mtimecmp_lo = -1;
  while(read_csr(mip) & MIP_MTIP){}
}

static void sbi_probe_extension_inner(long extension_id, struct sbiret* ret) {
  if (!ret) {
    assert(3780);
  }
  switch (extension_id) {
    case EID_10: {
      ret->value = 1;
      ret->error = SBI_SUCCESS;
      break;
    }
    default: {
      ret->value = 0;
      ret->error = SBI_ERR_NOT_SUPPORTED;
      break;
    }
  }
}

static void execute_fence(void) {
  uint64_t hartid = read_csr(mhartid);
  bool is_fencei = (fencei_mask >> hartid) & 0x1;
  bool is_sfence = (sfence_mask >> hartid) & 0x1;
  bool is_sfence_asid = (sfence_asid_mask >> hartid) & 0x1;

  if (is_fencei) {
    asm volatile("fence.i");
  } else if (is_sfence || is_sfence_asid) {
    for (unsigned long i=0; i<sfence_size; i+=sizeof(unsigned long)) {
      set_csr(mstatus, MSTATUS_MPRV);
      if (is_sfence_asid)
        asm volatile("sfence.vma %0, %1"::"r"(sfence_start+i), "r"(sfence_asid) :"memory");
      else
        asm volatile("sfence.vma %0"::"r"(sfence_start+i):"memory");
      clear_csr(mstatus, MSTATUS_MPRV);
    }
  }
}

static inline void send_ipi_inner(unsigned long mask, struct sbiret* ret) {
  for (int i=0; i<NUM_HARTS; i++) {
    if ((mask >> i) & 0x1) {
      volatile uint32_t* ipi_mmr = (volatile uint32_t*)MMR_IPI(i);
      *ipi_mmr = 1;
    }
  }
  ret->error = SBI_SUCCESS;
}

static void send_ipi(struct sbiret* ret) {
  const unsigned long* hart_mask = (const unsigned long*)args[0];
  set_csr(mstatus, MSTATUS_MPRV);
  unsigned long ipi_mask = *hart_mask;   // Todo: Might be an issue as, page for ipi_mask will not be set
  clear_csr(mstatus, MSTATUS_MPRV);
  send_ipi_inner(ipi_mask, ret);
}

static void remote_fence_i(struct sbiret* ret) {
  const unsigned long* hart_mask = (const unsigned long*)args[0];
  set_csr(mstatus, MSTATUS_MPRV);
  fencei_mask = *hart_mask;
  clear_csr(mstatus, MSTATUS_MPRV);
  send_ipi_inner(fencei_mask, ret);
}

static void remote_sfence_vma(struct sbiret* ret) {
  const unsigned long* hart_mask = (const unsigned long*)args[0];
  set_csr(mstatus, MSTATUS_MPRV);
  sfence_mask = *hart_mask;
  clear_csr(mstatus, MSTATUS_MPRV);
  send_ipi_inner(sfence_mask, ret);
}

static void remote_sfence_vma_asid(struct sbiret* ret) {
  const unsigned long* hart_mask = (const unsigned long*)args[0];
  set_csr(mstatus, MSTATUS_MPRV);
  sfence_asid_mask = *hart_mask;
  clear_csr(mstatus, MSTATUS_MPRV);
  send_ipi_inner(sfence_asid_mask, ret);
}

static void sbi_putc(void) {

}

static int sbi_getc(void) {
  
}

static void sbi_system_reset(void) {
  assert(0);
}

static void legacy_extension_impl(sbi_t eid, struct sbiret* ret) {
  switch (eid) {
    case EID_0: {
      set_timer_interrupt(ret);
      break;
    }
    case EID_1: {
      sbi_putc();
      ret->error = SBI_SUCCESS;
      break;
    }
    case EID_2: {
      ret->value = sbi_getc();
      ret->error = SBI_SUCCESS;
      break;
    }
    case EID_3: {
      clear_csr(mip, MIP_MSIP);
      ret->error = SBI_SUCCESS;
      break;
    }
    case EID_4: {
      send_ipi(ret);
      break;
    }
    case EID_5: {
      remote_fence_i(ret);
      break;
    }
    case EID_6: {
      remote_sfence_vma(ret);
      break;
    }
    case EID_7: {
      remote_sfence_vma_asid(ret);
      break;
    }
    case EID_8: {
      sbi_system_reset();
      break;
    }
    default: {
      assert(3781);  // Should not ever get to this point
    }
  }
}

static void base_extension_impl(sbi_t fid, struct sbiret* ret) {
  switch (fid) {
    case FID_0: {
      sbi_spec_version sbi_version;
      sbi_version.major_ver = 0;
      sbi_version.minor_ver = 2;
      ret->value = sbi_version.full_ver;
      ret->error = SBI_SUCCESS;
      break;
    }
    case FID_1: {
      ret->value = 7;
      ret->error = SBI_SUCCESS;
      break;
    }
    case FID_2: {
      ret->value = 1000;
      ret->error = SBI_SUCCESS;
      break;
    }
    case FID_3: {
      sbi_probe_extension_inner((long)args[0], ret);
      break;
    }
    case FID_4: {
      ret->value = read_csr(mvendorid);
      ret->error = SBI_SUCCESS;
      break;
    }
    case FID_5: {
      ret->value = read_csr(marchid);
      ret->error = SBI_SUCCESS;
      break;
    }
    case FID_6: {
      ret->value = read_csr(mimpid);
      ret->error = SBI_SUCCESS;
      break;
    }
    default: {
      break;
    }
  }
}

struct sbiret handle_sbi_call(void) {
  // Load eid, fid, arguments in variables from registers
  if (!args)
    args = (sbi_t*)&ecall_args;
    
  sbi_t eid, fid;
  eid = args[7];
  fid = args[6];

  // setup sbi return struct
  struct sbiret ret = {
    .error = SBI_ERR_FAILED,
    .value = 0xFFFFFFFF
  };

  // Do the sbi call
  switch (eid) {
    case EID_10: {
      base_extension_impl(fid, &ret);
      break;
    }
    case EID_0:
    case EID_1:
    case EID_2:
    case EID_3:
    case EID_4:
    case EID_5:
    case EID_6:
    case EID_7:
    case EID_8: {
      legacy_extension_impl(eid, &ret);
      break;
    }
    default: {
      ret.error = SBI_ERR_NOT_SUPPORTED;
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
    case CAUSE_IRQ_M_TIMER:
    {
      clear_timer_interrupt();
      set_csr(sip, MIP_STIP);
      break;
    }
    case CAUSE_IRQ_M_SOFT:
    {
      clear_csr(mip, MIP_MSIP);

      if (fencei_mask || sfence_mask || sfence_asid_mask) {
        execute_fence();
      } else {
        set_csr(sip, MIP_SSIP);
      }
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
