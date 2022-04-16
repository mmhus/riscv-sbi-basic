#ifndef SBI_LEGACY_EXTENSIONS_H
#define SBI_LEGACY_EXTENSIONS_H

#define EID_0 0x0ul
#define EID_1 0x1ul
#define EID_2 0x2ul
#define EID_3 0x3ul
#define EID_4 0x5ul
#define EID_5 0x6ul
#define EID_6 0x7ul
#define EID_7 0x8ul
#define EID_8 0x9ul

/**
 * ==================================================================
 * Function_Name               SBI_Version FID   EID Replacement_EID
 * ==================================================================
 * sbi_set_timer               0.1 0       0x00  0x54494D45*
 * sbi_console_putchar         0.1 0       0x01  N/A*
 * sbi_console_getchar         0.1 0       0x02  N/A*
 * sbi_clear_ipi               0.1 0       0x03  N/A*
 * sbi_send_ipi                0.1 0       0x04  0x735049*
 * sbi_remote_fence_i          0.1 0       0x05  0x52464E43*
 * sbi_remote_sfence_vma       0.1 0       0x06  0x52464E43*
 * sbi_remote_sfence_vma_asid  0.1 0       0x07  0x52464E43*
 * sbi_shutdown                0.1 0       0x08  0x53525354*
 * RESERVED                    0x09-0x0F
*/

/**
 * @brief Set Timer (EID #0x00)
 * Programs the clock for next event after stime_value time. 
 * This function also clears the pending timer interrupt bit.
 * If the supervisor wishes to clear the timer interrupt without scheduling the next timer event, 
 * it can either request a timer interrupt infinitely far into the future (i.e., (uint64_t)-1), 
 * or it can instead mask the timer interrupt by clearing sie.STIE CSR bit.
 */
void sbi_set_timer(uint64_t stime_value);

/**
 * @brief Console Putchar (EID #0x01)
 * Write data present in ch to debug console.
 * Unlike sbi_console_getchar(), this SBI call will block if there remain any pending characters to be
 * transmitted or if the receiving terminal is not yet ready to receive the byte. However, if the console
 * doesn’t exist at all, then the character is thrown away.
 */
void sbi_console_putchar(int ch);

/**
 * @brief Console Getchar (EID #0x02)
 * Read a byte from debug console; returns the byte on success, or -1 for failure. Note. 
 * This is the only SBI call in the legacy extension that has a non-void return type.
 * 
 * @return int 
 */
int sbi_console_getchar(void);

/**
 * @brief Clear IPI (EID #0x03)
 * Clears the pending IPIs if any. The IPI is cleared only in the hart for which this SBI call is invoked.
 * sbi_clear_ipi() is deprecated because S-mode code can clear sip.SSIP CSR bit directly.
 */
void sbi_clear_ipi(void);

/**
 * @brief Send IPI (EID #0x04)
 * Send an inter-processor interrupt to all the harts defined in hart_mask. Interprocessor interrupts
 * manifest at the receiving harts as Supervisor Software Interrupts.
 * hart_mask is a virtual address that points to a bit-vector of harts. The bit vector is represented as a
 * sequence of unsigned longs whose length equals the number of harts in the system divided by the
 * number of bits in an unsigned long, rounded up to the next integer.
 */
void sbi_send_ipi(const unsigned long *hart_mask);

/**
 * @brief Remote FENCE.I (EID #0x05)
 * Instructs remote harts to execute FENCE.I instruction. The hart_mask is same as described in 
 * sbi_send_ipi().
 */
void sbi_remote_fence_i(const unsigned long *hart_mask);

/**
 * @brief Remote SFENCE.VMA (EID #0x06)
 * Instructs the remote harts to execute one or more SFENCE.VMA instructions, covering the range of
 * virtual addresses between start and size.
 */
void sbi_remote_sfence_vma(
  const unsigned long *hart_mask,
  unsigned long start,
  unsigned long size);

/**
 * @brief Remote SFENCE.VMA with ASID (EID #0x07)
 * Instruct the remote harts to execute one or more SFENCE.VMA instructions, covering the range of
 * virtual addresses between start and size. This covers only the given ASID.
 */
void sbi_remote_sfence_vma_asid(
  const unsigned long *hart_mask,
  unsigned long start,
  unsigned long size,
  unsigned long asid);

/**
 * @brief System Shutdown (EID #0x08)
 * Puts all the harts to shutdown state from supervisor point of view. This SBI call doesn’t return.
 */
void sbi_shutdown(void);

#endif /* SBI_LEGACY_EXTENSIONS_H */