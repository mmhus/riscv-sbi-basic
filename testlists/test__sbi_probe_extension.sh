#!/usr/bin/env bash
set -euo pipefail

source export.sh
make spike TEST_DIR="code/src/test/test__sbi_probe_extension" CFLAGS="-DDEBUG"
