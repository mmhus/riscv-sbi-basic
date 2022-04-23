#ifndef SPIKE_PLATFORM_H
#define SPIKE_PLATFORM_H

// #define SPIKE_BASE    0x80000000ull  // Offset given to spike for now
#define SPIKE_BASE    0x0ull  // Offset given to spike for now

// Only supports upto 2 harts, didnt confirm yet, copied form clint.cc in riscv-isa-sim
#define MSIP_BASE	    (SPIKE_BASE + 0x0)
#define MTIMECMP_BASE	(SPIKE_BASE + 0x4000)
#define MTIME_BASE	  (SPIKE_BASE + 0xbff8)

#define NUM_HARTS 2

#endif /* SPIKE_PLATFORM_H */