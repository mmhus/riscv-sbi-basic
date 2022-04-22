#!/usr/bin/env bash
set -euo pipefail

source export.sh
<<<<<<< HEAD
make TEST_DIR="code/src/test/test__sbi_get_spec_version" CFLAGS="-DDEBUG"
=======
make TEST_DIR="code/src/test_srcs/test__sbi_probe_extension" CFLAGS="-DDEBUG"
>>>>>>> 7fd2c642f9fc90197f13c87618e452b8d6697a24
make spike
