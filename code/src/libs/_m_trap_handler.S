#if __riscv_xlen == 64
  #define LOAD_SP  c.ldsp
  #define STORE_SP c.sdsp
  #define REG_SIZE 8
#elif __riscv_xlen == 32
  #define LOAD_SP  c.lwsp
  #define STORE_SP c.swsp
  #define REG_SIZE 4
#else
  #error "Unknown RISC-V xlen parameter"
#endif

#define ALIGNED_8_BYTES 2

.global _m_trap_handler
.align ALIGNED_8_BYTES
.option push
.option norvc
_m_trap_handler:
  j _m_trap_handler_exceptions
  j supervisor_software_interrupt
  j virtual_supervisor_software_interrupt
  j machine_software_interrupt
  j __reserved
  j supervisor_timer_interrupt
  j virtual_supervisor_timer_interrupt
  j machine_timer_interrupt
  j __reserved
  j supervisor_external_interrupt
  j virtual_supervisor_external_interrupt
  j machine_external_interrupt
  j supervisor_guest_external_interrupt
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  j __reserved
  .option pop

.global supervisor_software_interrupt
.align ALIGNED_8_BYTES
.weak supervisor_software_interrupt
supervisor_software_interrupt:


.global virtual_supervisor_software_interrupt
.align ALIGNED_8_BYTES
.weak virtual_supervisor_software_interrupt
virtual_supervisor_software_interrupt:


.global machine_software_interrupt
.align ALIGNED_8_BYTES
.weak machine_software_interrupt
machine_software_interrupt:


.global supervisor_timer_interrupt
.align ALIGNED_8_BYTES
.weak supervisor_timer_interrupt
supervisor_timer_interrupt:


.global virtual_supervisor_timer_interrupt
.align ALIGNED_8_BYTES
.weak virtual_supervisor_timer_interrupt
virtual_supervisor_timer_interrupt:


.global machine_timer_interrupt
.align ALIGNED_8_BYTES
.weak machine_timer_interrupt
machine_timer_interrupt:


.global supervisor_external_interrupt
.align ALIGNED_8_BYTES
.weak supervisor_external_interrupt
supervisor_external_interrupt:


.global virtual_supervisor_external_interrupt
.align ALIGNED_8_BYTES
.weak virtual_supervisor_external_interrupt
virtual_supervisor_external_interrupt:


.global machine_external_interrupt
.align ALIGNED_8_BYTES
.weak machine_external_interrupt
machine_external_interrupt:


.global supervisor_guest_external_interrupt
.align ALIGNED_8_BYTES
.weak supervisor_guest_external_interrupt
supervisor_guest_external_interrupt:


.global __reserved
.align ALIGNED_8_BYTES
__reserved:

.extern m_mode_trap
.section .text, "aw", @progbits #Todo: fix later
.global _m_trap_handler_exceptions
.align ALIGNED_8_BYTES
_m_trap_handler_exceptions:
  c.addi16sp	sp,  -REG_SIZE*28

  STORE_SP    ra,   1*REG_SIZE(sp)
  STORE_SP    t0,   2*REG_SIZE(sp)
  STORE_SP    t1,   3*REG_SIZE(sp)
  STORE_SP    t2,   4*REG_SIZE(sp)
  STORE_SP    s0,   5*REG_SIZE(sp)
  STORE_SP    s1,   6*REG_SIZE(sp)
  STORE_SP    a0,   7*REG_SIZE(sp)
  STORE_SP    a1,   8*REG_SIZE(sp)
  STORE_SP    a2,   9*REG_SIZE(sp)
  STORE_SP    a3,  10*REG_SIZE(sp)
  STORE_SP    a4,  11*REG_SIZE(sp)
  STORE_SP    a5,  12*REG_SIZE(sp)
  STORE_SP    a6,  12*REG_SIZE(sp)
  STORE_SP    a7,  12*REG_SIZE(sp)
  STORE_SP    s2,  12*REG_SIZE(sp)
  STORE_SP    s3,  12*REG_SIZE(sp)
  STORE_SP    s4,  12*REG_SIZE(sp)
  STORE_SP    s5,  12*REG_SIZE(sp)
  STORE_SP    s6,  12*REG_SIZE(sp)
  STORE_SP    s7,  12*REG_SIZE(sp)
  STORE_SP    s8,  12*REG_SIZE(sp)
  STORE_SP    s9,  12*REG_SIZE(sp)
  STORE_SP    s10, 12*REG_SIZE(sp)
  STORE_SP    s11, 12*REG_SIZE(sp)
  STORE_SP    t3,  12*REG_SIZE(sp)
  STORE_SP    t4,  12*REG_SIZE(sp)
  STORE_SP    t5,  12*REG_SIZE(sp)
  STORE_SP    t6,  12*REG_SIZE(sp)

  jal m_trap_handler

  LOAD_SP    ra,   1*REG_SIZE(sp)
  LOAD_SP    t0,   2*REG_SIZE(sp)
  LOAD_SP    t1,   3*REG_SIZE(sp)
  LOAD_SP    t2,   4*REG_SIZE(sp)
  LOAD_SP    s0,   5*REG_SIZE(sp)
  LOAD_SP    s1,   6*REG_SIZE(sp)
  LOAD_SP    a0,   7*REG_SIZE(sp)
  LOAD_SP    a1,   8*REG_SIZE(sp)
  LOAD_SP    a2,   9*REG_SIZE(sp)
  LOAD_SP    a3,  10*REG_SIZE(sp)
  LOAD_SP    a4,  11*REG_SIZE(sp)
  LOAD_SP    a5,  12*REG_SIZE(sp)
  LOAD_SP    a6,  12*REG_SIZE(sp)
  LOAD_SP    a7,  12*REG_SIZE(sp)
  LOAD_SP    s2,  12*REG_SIZE(sp)
  LOAD_SP    s3,  12*REG_SIZE(sp)
  LOAD_SP    s4,  12*REG_SIZE(sp)
  LOAD_SP    s5,  12*REG_SIZE(sp)
  LOAD_SP    s6,  12*REG_SIZE(sp)
  LOAD_SP    s7,  12*REG_SIZE(sp)
  LOAD_SP    s8,  12*REG_SIZE(sp)
  LOAD_SP    s9,  12*REG_SIZE(sp)
  LOAD_SP    s10, 12*REG_SIZE(sp)
  LOAD_SP    s11, 12*REG_SIZE(sp)
  LOAD_SP    t3,  12*REG_SIZE(sp)
  LOAD_SP    t4,  12*REG_SIZE(sp)
  LOAD_SP    t5,  12*REG_SIZE(sp)
  LOAD_SP    t6,  12*REG_SIZE(sp)

  c.addi16sp	sp,  REG_SIZE*28
  mret