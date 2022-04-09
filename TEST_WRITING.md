# How To Write a test

## Adding header files

```c
code/include/
├── env
│   ├── marchid.h
│   ├── mcause.h
│   ├── mcounteren.h
│   ├── mcountinhibit.h
│   ├── medeleg.h
│   ├── menvcfg.h
│   ├── mideleg.h
│   ├── mie.h
│   ├── mimpid.h
│   ├── mip.h
│   ├── misa.h
│   ├── mseccfg.h
│   ├── mstatus.h
│   ├── mstatush.h
│   ├── mtime.h
│   ├── mtvec.h
│   ├── mvendorid.h
│   ├── sstatus.h
│   └── stvec.h
├── libs
│   ├── riscv_encoding.h
│   └── util.h
├── sbi_headers
│   ├── riscv_abi_encoding.h
│   ├── riscv_sbi_encoding.h
│   ├── riscv_sbi_functions_eid_0x10.h
│   └── riscv_sbi_functions.h
└── test_headers
    └── test_macros.h

4 directories, 26 files
```

Add any required header files in the path at dir `code/include/test_headers` . Before adding any extra headers, discuss if you really need to add headers. Only add headers which are common or used in multiple tests here.

## Adding test case source files

```c
code/src
├── env
│   ├── main.c
│   └── test_macros.c
├── libs
│   ├── crt0.S
│   ├── syscalls.c
│   └── trap_handler.S
├── sbi_srcs
│   └── sbi_functions_eid_0x10.c
└── test_srcs
    └── example
        └── example_test.c

5 directories, 7 files
```

Create a new folder in `code/src/test_srcs/<test_name>`, replacing `<test_name>` with `test__<test_name>` the actual name of the test. Please follow the format of the example test given.

## Running a test case

- All test case, run scripts, should be added in the `testlists` directory, where each test case should ideally have a separate testlist file. See `testlists/example.sh` to gain an understanding of how to use the testlist.
- Pass the test directory using the `TEST_DIR=<test_name_dir>` flag as given in `example.sh`. Make sure to only give the test directory and not the full path to the test in `TEST_DIR=`.
- Pass any extra cflags using the `CFLAGS=` variable.
- To run a test just call the testlist from the top level directory in the repository e.g. `testlists/example.sh`.
- You can also give a timeout, so that the test only runs for a specific amount of time (useful for testcases that get stuck in loops). e.g. `TIMEOUT=10`. By default, without giving the `TIMEOUT` flag, the timeout is 5s.
