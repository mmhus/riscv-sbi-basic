#ifndef RISCV_MVENDORID_H
#define RISCV_MVENDORID_H

#define MVENDORID_OFFSET_SHIFT  0
#define MVENDORID_BANK_SHIFT    7

#define MVENDORID_OFFSET_MASK   0x000000000000007Full
#define MVENDORID_BANK_MASK     0xFFFFFFFFFFFFFF80ull

#endif  /* RISCV_MVENDORID_H */