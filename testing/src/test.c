#include "../test.h"

Test create_test(char * input, char * expected) {
    Test t = {invalid_str(), invalid_str()};
    if (NULL == input || NULL == expected) {
        return t;
    }

    if (copy_char_str(&(t._input), input)) {
        return t;
    }

    if (copy_char_str(&(t._expected), expected)) {
        delete_str(&(t._input));
        return t;
    }

    return t;
}

void delete_test(Test * test) {
    if (NULL == test) { return; }

    delete_str(&(test->_input));
    delete_str(&(test->_expected));
}

str test_input(Test * test) {
    if (NULL == test) {
        return invalid_str();
    }

    return test->_input;
}

str test_expected(Test * test) {
    if (NULL == test) {
        return invalid_str();
    }

    return test->_expected;
}
