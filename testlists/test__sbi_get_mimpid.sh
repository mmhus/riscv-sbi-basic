#!/usr/bin/env bash

source export.sh
make TEST_DIR="code/src/test_srcs/test__sbi_get_mimpid" CFLAGS="-DDEBUG"
make spike