#!/usr/bin/env bash

source export.sh
make spike TEST_DIR="code/src/test/test__sbi_get_mimpid" CFLAGS="-DDEBUG"
