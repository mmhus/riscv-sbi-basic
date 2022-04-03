#include "riscv_abi_encoding.h"
#include "riscv_sbi_encoding.h"
#include "riscv_encoding.h"

#include <stdint.h>
#include <stdbool.h>

#define U_MODE 0
#define S_MODE 1
#define M_MODE 3

bool tb_fail = 0;

#define write_field(reg, mask, shift, value) \
  reg = (reg & ~mask) | ((value << shift) & mask);


__attribute__((interrupt("machine")))
void handle_trap(void) {
  uint64_t cause = read_csr(mcause);

  switch (cause) {
    case CAUSE_ILLEGAL_INSTRUCTION:
    {
      write_csr(mepc, read_csr(mepc)+4);
      break;
    }
    case CAUSE_MACHINE_ECALL:
    {
      static bool itr = 0;
      uint64_t mstatus1 = read_csr(mstatus); //csrr
      if (itr == 0) {
        write_field(mstatus1, MSTATUS_MPP, 11, S_MODE)
        itr++;
      } else {
        write_field(mstatus1, MSTATUS_MPP, 11, M_MODE)
        write_csr(mepc, read_csr(mepc)+4);
      }  
      write_csr(mstatus, mstatus1);
      break;
    }
    case CAUSE_SUPERVISOR_ECALL: 
    {
      uint64_t mstatus1 = read_csr(mstatus); //csrr
      write_field(mstatus1, MSTATUS_MPP, 11, M_MODE)
      write_csr(mstatus, mstatus1);
      write_csr(mepc, read_csr(mepc)+4);
      break;
    }
    default:
      tb_fail = 1;
      break;
  }
}

/**
 * @brief 
 * 
 * @return int 
 */
int main(void) {
  // asm volatile(".word 0xFFFFFFFF");  //illegal instruction
  write_csr(pmpaddr0, 0xFFFFFFFFFFFFFFFF);
  write_csr(pmpcfg0, (PMP_A & PMP_TOR) | PMP_R | PMP_W | PMP_X);
  asm volatile("sfence.vma");
  asm volatile("ecall");
  return 0;
  
}
