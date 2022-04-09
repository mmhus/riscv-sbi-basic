#!/usr/bin/env bash

source export.sh
make TEST_DIR="code/src/test_srcs/test__sbi_probe_extension" CFLAGS="-DDEBUG"
make spike
