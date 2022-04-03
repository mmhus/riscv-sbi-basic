# How To Write a test

## Adding header files

Add any required header files in the path at dir `code/include/test_headers` . Before adding any extra headers, discuss if you really need to add headers. Only add headers which are common or used in multiple tests here.

## Adding test case source files

Create a new folder in `code/src/test_srcs/<test_name>`, replacing `<test_name>` with the actual name of the test. Please follow the format of the example test given.

## Running a test case

All test case, run scripts, should be added in the `testlists` directory, where each test case should ideally have a separate testlist file. See `testlists/example.sh` to gain an understanding of how to use the testlist. Pass the test directory using the `TEST_DIR=<test_name_dir>` flag as given in `example.sh`. Make sure to only give the test directory and not the full path to the test in `TEST_DIR=`. Pass any extra cflags using the `CFLAGS=` variable.