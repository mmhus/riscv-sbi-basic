#include "test_macros.h"
#include "mstatus.h"

bool end_test = SET_0;

__attribute__((weak)) 
int test_case(void){}

__attribute__((weak)) 
__attribute__((interrupt("supervisor"))) 
void s_mode_trap(void){}

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

void return_to_M_mode() {
  uint64_t mstatus1 = read_csr(mstatus); //csrr
  write_field(mstatus1, MSTATUS_MPP, MSTATUS_MPP_SHIFT, M_MODE)
  write_csr(mstatus, mstatus1);
}

__attribute__((interrupt("machine")))
void m_mode_trap(void) {
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
      if (end_test) {
        return_to_M_mode();  // Always the same for every test_case
        write_csr(mepc, read_csr(mepc)+4);
      } else {
        // Do the sbi call
      }
      break;
    }
    default:
    {
      exit_test(TEST_FAIL);
      break;
    }
  }
}
