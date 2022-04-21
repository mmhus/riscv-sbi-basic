#!/usr/bin/env bash
<<<<<<< HEAD
set -euo pipefail

source export.sh
make TEST_DIR="code/src/test/test__sbi_probe_extension" CFLAGS="-DDEBUG"
=======

source export.sh
make TEST_DIR="code/src/test_srcs/test__sbi_probe_extension" CFLAGS="-DDEBUG"
>>>>>>> d66a705a65e2ec95925d57798e17f05f11aa73f6
make spike
