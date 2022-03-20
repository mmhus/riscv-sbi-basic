/* See LICENSE for license details. */

#ifndef RISCV_SBI_ENCODING_H
#define RISCV_SBI_ENCODING_H


/** 
 * Table 1. Standard SBI Errors
 * Error_Type            Value
 */
#define SBI_SUCCESS               0
#define SBI_ERR_FAILED            -1
#define SBI_ERR_NOT_SUPPORTED     -2
#define SBI_ERR_INVALID_PARAM     -3
#define SBI_ERR_DENIED            -4
#define SBI_ERR_INVALID_ADDRESS   -5
#define SBI_ERR_ALREADY_AVAILABLE -6
#define SBI_ERR_ALREADY_STARTED   -7
#define SBI_ERR_ALREADY_STOPPED   -8

/* sbi return struct, analogue to a0, a1 registers */
struct sbiret {
  long error;
  long value;
};

/* Every SBI function should prefer unsigned long as the data type, i.e. uint32_t */
typedef unsigned long sbi_t;

#endif /* RISCV_SBI_ENCODING_H */