#ifndef RISCV_SBI_BASE_EXTENSION_H
#define RISCV_SBI_BASE_EXTENSION_H

#include "sbi_common.h"

/**======================================================================
 * Base Extension EID #0x10
 *=======================================================================
 * Function_Name              SBI_Version   FID     EID
 * sbi_get_sbi_spec_version   0.2           0       0x10
 * sbi_get_sbi_impl_id        0.2           1       0x10
 * sbi_get_sbi_impl_version   0.2           2       0x10
 * sbi_probe_extension        0.2           3       0x10
 * sbi_get_mvendorid          0.2           4       0x10
 * sbi_get_marchid            0.2           5       0x10
 * sbi_get_mimpid             0.2           6       0x10
 *=======================================================================/
 */

#define EID_10             0x10ul 

#define SBI_imp_id_BBL     0x00ul //Berkeley Boot Loader (BBL)
#define SBI_imp_id_OpenSBI 0x01ul
#define SBI_imp_id_Xvisor  0x02ul
#define SBI_imp_id_KVM     0x03ul
#define SBI_imp_id_RustSBI 0x04ul
#define SBI_imp_id_Diosix  0x05ul
#define SBI_imp_id_Coffer  0x06ul



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

#endif /* RISCV_SBI_BASE_EXTENSION_H */