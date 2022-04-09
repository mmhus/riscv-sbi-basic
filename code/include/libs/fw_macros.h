#ifndef FW_MACROS_H
#define FW_MACROS_H

// ============================ DEFINES ===============================

#define SET_0 0ull
#define SET_1 1ull

#define U_MODE 0
#define S_MODE 1
#define M_MODE 3

#define BYTE_ALIGMENT           0
#define HALF_WORD_ALIGNMENT     1
#define WORD_ALIGNMENT          2
#define DOUBLE_WORD_ALIGNMENT   3

// Ld/St Instruction Size
#define DOUBLE_WORD    8
#define WORD           4
#define HALF_WORD      2
#define BYTE           1

#define ILLEGAL_INSTRUCTION 0xffffffff

#define str(x)  #x
#define xstr(x) str(x)

// ============================ MACROS ===============================

#ifndef __ASSEMBLER__
  #ifdef __GNUC__

    #define read_csr(reg) \
      __extension__ \
      ({ \
        unsigned long long __tmp; \
        asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
        __tmp; \
      }) \

    #define write_csr(reg, val) \
      __extension__ \
      ({ \
        asm volatile ("csrw " #reg ", %0" :: "rK"(val)); \
      }) \

    #define swap_csr(reg, val) \
      __extension__ \
      ({ \
        unsigned long long __tmp; \
        asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val)); \
        __tmp; \
      }) \

    #define set_csr(reg, bit) \
      __extension__ \
      ({ \
        unsigned long long __tmp; \
        asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
        __tmp; \
      }) \

    #define clear_csr(reg, bit) \
      __extension__ \
      ({ \
        unsigned long long __tmp; \
        asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
        __tmp; \
      }) \

    #define read_csr_addr(reg) \
      __extension__ \
      ({ \
        unsigned long long __tmp; \
        asm volatile ("csrr %0, " xstr(reg) : "=r"(__tmp)); \
        __tmp; \
      }) \

    #define write_csr_addr(reg, val) \
      __extension__ \
      ({ \
        asm volatile ("csrw " xstr(reg) ", %0" :: "rK"(val)); \
      }) \

    #define set_csr_addr(reg, bit) \
      __extension__ \
      ({ \
        unsigned long long __tmp; \
        asm volatile ("csrrs %0, " xstr(reg) ", %1" : "=r"(__tmp) : "rK"(bit)); \
      __tmp; \
      }) \

    #define clear_csr_addr(reg, bit) \
      __extension__ \
      ({ \
        unsigned long long __tmp; \
        asm volatile ("csrrc %0, " xstr(reg) ", %1" : "=r"(__tmp) : "rK"(bit)); \
        __tmp; \
      }) \

    #define rdtime() read_csr(time)
    #define rdcycle() read_csr(cycle)
    #define rdinstret() read_csr(instret)

  #endif /* __GNUC__ */
#endif /* __ASSEMBLER__ */

#define write_field(reg, mask, shift, value) \
  reg = (reg & ~mask) | ((value << shift) & mask);

// TODO: incomplete
#define read_field(reg, mask, shift, value) \
  reg = (reg & ~mask) | ((value << shift) & mask);

#endif /* FW_MACROS_H */