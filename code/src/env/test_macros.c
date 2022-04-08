#include "test_macros.h"
#include "mstatus.h"

bool end_test = SET_0;

__attribute__((weak)) 
int test_case(void){}

__attribute__((weak)) 
__attribute__((interrupt("supervisor"))) 
void s_mode_trap(void){}
