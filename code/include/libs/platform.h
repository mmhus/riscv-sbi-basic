#ifndef PLATFORM_H
#define PLATFORM_H

#include "spike_platform.h"

#define MMR_MTIME_LO(hartid)    (MTIME_BASE + (4 * hartid))
#define MMR_MTIME_HI(hartid)    (MTIME_BASE + (4 * hartid) + 4)
#define MMR_MTIMECMP_LO(hartid) (MTIMECMP_BASE + (4 * hartid))
#define MMR_MTIMECMP_HI(hartid) (MTIMECMP_BASE + (4 * hartid) + 4)
#define MMR_IPI(hartid)         (MSIP_BASE + (4 * hartid))

#endif /* PLATFORM_H */