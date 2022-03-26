#include "riscv_abi_encoding.h"
#include "riscv_sbi_encoding.h"
#include "riscv_encoding.h"

#include <stdint.h>
#include <stdbool.h>

bool tb_fail = 0;

__attribute__((interrupt("machine")))
void handle_trap(void) {
    uint64_t cause = read_csr(mcause);

    switch (cause) {
        case CAUSE_ILLEGAL_INSTRUCTION:
        {
            write_csr(mepc, read_csr(mepc)+4);
            break;
        }
        default:
            tb_fail = 1;
    }
}

/**
 * @brief 
 * 
 * @return int 
 */
int main(void) {
    // asm volatile(".word 0xFFFFFFFF");  //illegal instruction
    return 0;
}
