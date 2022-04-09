#ifndef RISCV_MISA_H
#define RISCV_MISA_H

#define MISA_EXTENTIONS_SHIFT           0
#define MISA_ZERO_SHIFT                 26
#define MISA_MXL_SHIFT                  61
#define MISA_A_SHIFT                    0
#define MISA_C_SHIFT                    2
#define MISA_D_SHIFT                    3
#define MISA_E_SHIFT                    4
#define MISA_F_SHIFT                    5
#define MISA_H_SHIFT                    7
#define MISA_I_SHIFT                    8
#define MISA_M_SHIFT                    12
#define MISA_N_SHIFT                    13
#define MISA_P_SHIFT                    15
#define MISA_Q_SHIFT                    16
#define MISA_S_SHIFT                    18
#define MISA_U_SHIFT                    20
#define MISA_V_SHIFT                    21
#define MISA_X_SHIFT                    23

#define MISA_EXTENTIONS_MASK            0x0000000001FFFFFFull
#define MISA_ZERO_MASK                  0x0000000000000000ull
#define MISA_MXL_MASK                   0xC000000000000002ull
#define MISA_A_MASK                     0x0000000000000001ull
#define MISA_C_MASK                     0x0000000000000004ull
#define MISA_D_MASK                     0x0000000000000008ull
#define MISA_E_MASK                     0x0000000000000010ull
#define MISA_F_MASK                     0x0000000000000020ull
#define MISA_H_MASK                     0x0000000000000080ull
#define MISA_I_MASK                     0x0000000000000100ull
#define MISA_M_MASK                     0x0000000000001000ull
#define MISA_N_MASK                     0x0000000000002000ull
#define MISA_P_MASK                     0x0000000000008000ull
#define MISA_Q_MASK                     0x0000000000010000ull
#define MISA_S_MASK                     0x0000000000040000ull
#define MISA_U_MASK                     0x0000000000100000ull
#define MISA_V_MASK                     0x0000000000200000ull
#define MISA_X_MASK                     0x0000000002000000ull

#endif /* RISCV_MISA_H */
