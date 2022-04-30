#!/usr/bin/env bash
set -euo pipefail

source export.sh
make TEST_DIR="code/src/test/test__sbi_remote_sfence_vma_asid" CFLAGS="-DDEBUG" NUM_HARTS=2
make spike
