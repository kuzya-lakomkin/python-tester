#ifndef _NSTU_TEST_READER_H
#define _NSTU_TEST_READER_H

#include "test.h"

#include <stdio.h>

struct TestReader {
    FILE * _hFile;
    size_t _amount;
    char _sep;
};
typedef struct TestReader TestReader;

/**
 * 
 */
TestReader init_test_reader(FILE * tests, size_t tests_amount, char sep);

/**
 * 
 */
int next_test(TestReader * reader, Test * test, char sep);

#endif