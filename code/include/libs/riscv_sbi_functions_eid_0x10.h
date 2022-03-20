#ifndef RISCV_SBI_EID_10_H
#define RISCV_SBI_EID_10_H

#include "riscv_sbi_encoding.h"

/**=======================================================================
 * Base Extension EID #0x10
 *=======================================================================/
/**
 * @brief FID #0
 * Returns the current SBI specification version. This function must always succeed. 
 * The minor number of the SBI specification is encoded in the low 24 bits, 
 * with the major number encoded in the next 7 bits. 
 * Bit 31 must be 0 and is reserved for future expansion.
 * 
 * @return struct sbiret 
 */
struct sbiret sbi_get_spec_version(void);

/**
 * @brief FID #1
 * Returns the current SBI implementation ID, which is different for every SBI implementation.
 * It is intended that this implementation ID allows software to probe for SBI implementation quirks.
 * 
 * @return struct sbiret 
 */
struct sbiret sbi_get_impl_id(void);

/**
 * @brief FID #2
 * Returns the current SBI implementation version. 
 * The encoding of this version number is specific to the SBI implementation.
 * 
 * @return struct sbiret 
 */
struct sbiret sbi_get_impl_version(void);

/**
 * @brief FID #3
 * Returns 0 if the given SBI extension ID (EID) is not available, 
 * or an extension-specific non-zero value if it is available.
 * 
 * @param extension_id 
 * @return struct sbiret 
 */
struct sbiret sbi_probe_extension(long extension_id);

/**
 * @brief FID #4
 * Return a value that is legal for the mvendorid CSR and 0 is always a legal value for this CSR.
 * 
 * @return struct sbiret 
 */
struct sbiret sbi_get_mvendorid(void);

/**
 * @brief FID #5
 * Return a value that is legal for the marchid CSR and 0 is always a legal value for this CSR.
 * 
 * @return struct sbiret 
 */
struct sbiret sbi_get_marchid(void);

/**
 * @brief FID #6
 * Return a value that is legal for the mimpid CSR and 0 is always a legal value for this CSR.
 * 
 * @return struct sbiret 
 */
struct sbiret sbi_get_mimpid(void);

#endif /* RISCV_SBI_EID_10_H */