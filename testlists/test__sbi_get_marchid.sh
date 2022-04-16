#!/usr/bin/env bash

source export.sh
make TEST_DIR="code/src/test/test__sbi_get_marchid" CFLAGS="-DDEBUG"
make spike
