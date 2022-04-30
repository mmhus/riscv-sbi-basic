#!/usr/bin/env bash
set -euo pipefail

source export.sh
make TEST_DIR="code/src/test/test_sbi_set_timer" CFLAGS="-DDEBUG"
make spike
