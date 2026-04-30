#include "../test_reader.h"

TestReader init_test_reader(FILE * tests, size_t tests_amount, char sep) {
    TestReader new_reader = {NULL, 0, 0};
    if (NULL == tests) { return new_reader; }
    
}

int next_test(TestReader * reader, Test * test, char sep) {

}
