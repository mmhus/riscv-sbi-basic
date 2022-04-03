#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#include "riscv_abi_encoding.h"
#include "riscv_sbi_encoding.h"
#include "riscv_encoding.h"

#include <stdint.h>
#include <stdbool.h>

#define SET_0 0ull
#define SET_1 1ull

#define U_MODE 0
#define S_MODE 1
#define M_MODE 3

#define TEST_PASS SET_0
#define TEST_FAIL SET_1

#define write_field(reg, mask, shift, value) \
  reg = (reg & ~mask) | ((value << shift) & mask);

#define read_field(reg, mask, shift, value) \
  reg = (reg & ~mask) | ((value << shift) & mask);

#define END_TEST(end_code) \
  pass_fail = end_code;  \
  return pass_fail;

extern bool test_end_code;

void switch_to_S_mode();

#endif /* TEST_MACROS_H */