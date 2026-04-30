#ifndef _NSTU_TEST_H
#define _NSTU_TEST_H

#include "lib/str/str.h"

struct Test {
    str _input, _expected;
};
typedef struct Test Test;

Test create_test(char * input, char * expected);
void delete_test(Test * test);

str test_input(Test * test);
str test_expected(Test * test);

#endif