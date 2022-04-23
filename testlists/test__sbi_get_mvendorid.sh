#!/usr/bin/env bash
set -euo pipefail

source export.sh
make TEST_DIR="code/src/test/test__sbi_get_mvendorid" CFLAGS="-DDEBUG"
make spike
