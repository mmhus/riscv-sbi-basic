#include <stdint.h>
#include <stdbool.h>
#include "riscv_encoding.h"
#include "mstatus.h"

#ifdef DEBUG
  #include "test_macros.h"
#endif

extern volatile uint64_t tohost;
__attribute__((noreturn))
void exit_test(int code)
{
  tohost = (code << 1) | 1;
  while (1);
}

void switch_to_S_mode(void) {
  uint64_t mstatus1 = read_csr(mstatus); //csrr
  write_field(mstatus1, MSTATUS_MPP , MSTATUS_MPP_SHIFT , S_MODE)
  write_field(mstatus1, MSTATUS_MPIE, MSTATUS_MPIE_SHIFT, SET_1)
  write_csr(mstatus, mstatus1);
}

void return_to_M_mode(void) {
  uint64_t mstatus1 = read_csr(mstatus); //csrr
  write_field(mstatus1, MSTATUS_MPP, MSTATUS_MPP_SHIFT, M_MODE)
  write_csr(mstatus, mstatus1);
}

__attribute__((naked))
void m_trap_handler(void) {
  uint64_t cause = read_csr(mcause);

  switch (cause) {
    case CAUSE_ILLEGAL_INSTRUCTION:
    {
      write_csr(mepc, read_csr(mepc)+4);
      break;
    }
    case CAUSE_MACHINE_ECALL:
    {
      static bool s_priv = SET_0;
      if (!s_priv) {
        switch_to_S_mode();
        s_priv = SET_1;
        write_csr(mepc, read_csr(mepc)+4);
      } else {
        exit_test(TEST_FAIL);  //Invalid m-mode to m-mode ecall
      }
      break;
    }
    case CAUSE_SUPERVISOR_ECALL:
    {
      #ifdef DEBUG
        if (end_test) {
          return_to_M_mode();  // Always the same for every test_case
          write_csr(mepc, read_csr(mepc)+4);
        } else {
      #endif
        // Do the sbi call

      #ifdef DEBUG
        }
      #endif
      break;
    }
    default:
    {
      exit_test(TEST_FAIL);
      break;
    }
  }
  asm("ret");
}
