#include "test_macros.h"
#include "mstatus.h"

bool end_test = SET_0;

__attribute__((weak)) 
int test_case(void){
  exit_test(TEST_FAIL);
}

__attribute__((weak)) 
__attribute__((interrupt("supervisor"))) 
void s_mode_trap(void){
  exit_test(TEST_FAIL);
}

extern volatile uint64_t tohost;
__attribute__((noreturn))
void exit_test(int code)
{
  tohost = (code << 1) | 1;
  while (1);
}

void return_to_M_mode(void) {
  uint64_t mstatus1 = read_csr(mstatus); //csrr
  write_field(mstatus1, MSTATUS_MPP, MSTATUS_MPP_SHIFT, M_MODE)
  write_csr(mstatus, mstatus1);
}
