#ifndef SBI_COMMON_H
#define SBI_COMMON_H

#include <stdint.h>

#include "riscv_abi_encoding.h"
#include "sbi_base_extension.h"
#include "sbi_legacy_extensions.h"

// -------------------------------------------------------------------

/** 
 * Table 1. Standard SBI Errors
 *      Error_Type                Value
 */
#define SBI_SUCCESS                0l
#define SBI_ERR_FAILED            -1l
#define SBI_ERR_NOT_SUPPORTED     -2l
#define SBI_ERR_INVALID_PARAM     -3l
#define SBI_ERR_DENIED            -4l
#define SBI_ERR_INVALID_ADDRESS   -5l
#define SBI_ERR_ALREADY_AVAILABLE -6l
#define SBI_ERR_ALREADY_STARTED   -7l
#define SBI_ERR_ALREADY_STOPPED   -8l

#define FID_0  0ul
#define FID_1  1ul
#define FID_2  2ul
#define FID_3  3ul
#define FID_4  4ul
#define FID_5  5ul
#define FID_6  6ul

// -------------------------------------------------------------------

/* sbi return struct, analogue to a0, a1 registers */
struct sbiret {
  long error;
  long value;
 };

/* Every SBI function should prefer unsigned long as the data type, i.e. uint32_t */
typedef unsigned long sbi_t;
typedef long s_sbi_t;  //signed type

typedef union {
  sbi_t full_ver;
  struct {
    sbi_t major_ver : 24;
    sbi_t minor_ver : 7;
    sbi_t zero_ver  : 1;
  } __attribute__((packed));
} sbi_spec_version;

// -------------------------------------------------------------------

/**
 * @brief sbi wrapper function to call eid, fid
 * 
 * @param eid major function number
 * @param fid minor function number
 * @return struct sbiret 
 */
struct sbiret sbi_inner_wrapper(sbi_t eid, sbi_t fid);

// -------------------------------------------------------------------


#endif /* SBI_COMMON_H */