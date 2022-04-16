#ifndef RISCV_ABI_ENCODING_H
#define RISCV_ABI_ENCODING_H

#include "riscv_encoding.h"

/* Upto 32-bit addresses */
#ifdef MCMODEL_MEDLOW
  // Load value from a symbol
  #define LOAD_VALUE_SYMBOL(symbol)    \
  asm volatile(                        \
    "lui a0, %hi("xstr(symbol)");"     \
    "lw a0, %lo("xstr(symbol)")(a0)"   \
  );

  // Store value to a symbol
  #define STORE_VALUE_SYMBOL(symbol)   \
  asm volatile(                        \
    "lui a0, %hi("xstr(symbol)");"     \
    "sw a1, %lo("xstr(symbol)")(a0)"   \
  );

  // Calculate address
  #define LOAD_ADDRESS_SYMBOL(symbol)  \
  asm volatile(                        \
    "lui a0, %hi("xstr(symbol)");"     \
    "addi a0, a0, %lo("xstr(symbol)")" \
  );

/* > 32-bit address ranges, MCMODEL_MEDANY */
#else
  #ifndef MCMODEL_MEDANY
    #define MCMODEL_MEDANY
  #endif
  
  // Load value from a symbol
  #define LOAD_VALUE_SYMBOL(symbol)         \
  asm volatile(                             \
    "0:;"                                   \
    "auipc a0, %pcrel_hi("xstr(symbol)");"  \
    "lw a0, %pcrel_lo(0b)(a0)"              \
  );

  // Store value to a symbol
  #define STORE_VALUE_SYMBOL(symbol)        \
  asm volatile(                             \
    "1:;"                                   \
    "auipc a0, %pcrel_hi("xstr(symbol)");"  \
    "sw %pcrel_lo(1b)(a0)"                  \
  );

  // Calculate address
  #define LOAD_ADDRESS_SYMBOL(symbol)       \
  asm volatile(                             \
    "2:;"                                   \
    "auipc a0, %pcrel_hi("xstr(symbol)");"  \
    "addi a0, a0, %pcrel_lo(2b)"            \
  );
#endif

#endif /* RISCV_ABI_ENCODING_H */
