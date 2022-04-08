#include <stdint.h>
#include <stdbool.h>
#include "riscv_encoding.h"
#include "mstatus.h"

#ifdef DEBUG
  #include "test_macros.h"
#endif

__attribute__((naked))
void m_trap_handler(void) {
  uint64_t cause = read_csr(mcause);

  switch (cause) {
    #ifdef DEBUG
    case CAUSE_ILLEGAL_INSTRUCTION:
    {
      write_csr(mepc, read_csr(mepc)+4);
      break;
    }
    #endif
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
      #ifdef DEBUG
        exit_test(TEST_FAIL);
      #endif
      break;
    }
  }
  asm("ret");
}
