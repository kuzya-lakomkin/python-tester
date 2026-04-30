#ifndef _NSTU_TEST_READER_H
#define _NSTU_TEST_READER_H

#include <stdio.h>

struct TestReader {
    FILE _hFile;
    size_t _amount;
};
typedef struct TestReader TestReader;

TestReader init_test_reader(FILE * tests, size_t tests_amount);

#endif