#ifndef MOS6502_H
#define MOS6502_H

#include <stdint.h>
#include <stdbool.h>

// CPU Status Flags
#define FLAG_C 0x01  // Carry
#define FLAG_Z 0x02  // Zero
#define FLAG_I 0x04  // Interrupt Disable
#define FLAG_D 0x08  // Decimal Mode
#define FLAG_B 0x10  // Break Command
#define FLAG_V 0x40  // Overflow
#define FLAG_N 0x80  // Negative

// Memory size definitions
#define MEMORY_SIZE 0x10000
#define STACK_BASE 0x0100

typedef struct {
    // Registers
    uint8_t A;    // Accumulator
    uint8_t X;    // X Index Register
    uint8_t Y;    // Y Index Register
    uint8_t SP;   // Stack Pointer
    uint16_t PC;  // Program Counter
    uint8_t P;    // Status Register

    // Memory
    uint8_t memory[MEMORY_SIZE];

    // System
    uint32_t cycles;
    bool nmi_pending;
    bool irq_pending;

    // Debug features
    bool trace_enabled;
    uint16_t breakpoints[256];
    int breakpoint_count;
} MOS6502;

// Function prototypes
void cpu_init(MOS6502* cpu);
void cpu_reset(MOS6502* cpu);
int cpu_execute(MOS6502* cpu);
void cpu_nmi(MOS6502* cpu);
void cpu_irq(MOS6502* cpu);

// Memory access handlers
typedef uint8_t (*memory_read_handler)(uint16_t address, void* user_data);
typedef void (*memory_write_handler)(uint16_t address, uint8_t value, void* user_data);

// Memory management structure
typedef struct {
    memory_read_handler read;
    memory_write_handler write;
    void* user_data;
    uint16_t start_addr;
    uint16_t end_addr;
} MemoryHandler;

#endif // MOS6502_H