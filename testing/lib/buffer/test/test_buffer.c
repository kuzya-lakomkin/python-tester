#include "../buffer.h"

#include <criterion/criterion.h>

Test(buffer_suite, test_create) {
    CharBuffer buff;
    buff = create_buffer(10);

    cr_assert_neq(buffer_raw_ptr(&buff), NULL);
    cr_assert_eq(buffer_capacity(&buff), 10);
    cr_assert_eq(buffer_length(&buff), 0);
    cr_assert_eq(buffer_index(&buff), 0);

    delete_buffer(&buff);
}

Test(buffer_suite, test_push_ch) {
    CharBuffer buff = create_buffer(20);
    char str1[10] = "123456789";

    cr_assert_eq(push_ch_buffer(&buff, str1, 9), 0);
    cr_assert_eq(buffer_length(&buff), 9);
    char a;
    for (size_t i = 0; i < 9; ++i) {
        cr_assert_eq(buffer_index(&buff), i);
        cr_assert_eq(next_buffer_sym(&buff, &a), 0);
        cr_assert_eq(a, str1[i]);
    }
    cr_assert_eq(next_buffer_sym(&buff, &a), -1);

    char str2[21] = "01234567890123456789";
    cr_assert_eq(push_ch_buffer(&buff, str2, 20), 0);
    cr_assert_eq(buffer_length(&buff), 20);
    for (size_t i = 0; i < 20; ++i) {
        cr_assert_eq(buffer_index(&buff), i);
        cr_assert_eq(next_buffer_sym(&buff, &a), 0);
        cr_assert_eq(a, str2[i]);
    }
    cr_assert_eq(next_buffer_sym(&buff, &a), -1);

    char str3[22] = "012345678901234567890";
    cr_assert_eq(push_ch_buffer(&buff, str3, 21), -1);

    delete_buffer(&buff);
}

Test(buffer_suite, test_push_str) {
    CharBuffer buff = create_buffer(20);
    str str;
    copy_char_str(&str, "123456789");

    cr_assert_eq(push_str_buff(&buff, &str), 0);
    cr_assert_eq(buffer_length(&buff), 9);

    char a, b;
    for (size_t i = 0; i < 9; ++i) {
        cr_assert_eq(buffer_index(&buff), i);
        cr_assert_eq(next_buffer_sym(&buff, &a), 0);
        str_symbol(&str, i, &b);
        cr_assert_eq(a, b);
    }
    cr_assert_eq(next_buffer_sym(&buff, &a), -1);

    delete_str(&str);

    copy_char_str(&str, "01234567890123456789");

    cr_assert_eq(push_str_buff(&buff, &str), 0);
    cr_assert_eq(buffer_length(&buff), 20);

    for (size_t i = 0; i < 20; ++i) {
        cr_assert_eq(buffer_index(&buff), i);
        cr_assert_eq(next_buffer_sym(&buff, &a), 0);
        str_symbol(&str, i, &b);
        cr_assert_eq(a, b);
    }
    cr_assert_eq(next_buffer_sym(&buff, &a), -1);

    delete_str(&str);
    
    copy_char_str(&str, "01234567890123456789012345678");
    cr_assert_eq(push_str_buff(&buff, &str), -1);
    delete_str(&str);

    delete_buffer(&buff);
}

Test(buffer_suite, test_next_sym) {
    CharBuffer buff = create_buffer(1024);
    push_ch_buffer(&buff, "slon1337 slon1337 slon1337 slon1337 slon1337 slon1337", 45);
    str test, next = invalid_str();
    copy_char_str(&test, "slon1337");
    next_buffer_substr(&buff, &next, 8);

    cr_assert_eq(str_length(&test), str_length(&next));

    char a, b;
    for (size_t i = 0; i < str_length(&test); ++i) {
        str_symbol(&next, i, &a);
        str_symbol(&test, i, &b);
        cr_assert_eq(a, b);
    }

    delete_str(&test);
    delete_str(&next);
    delete_buffer(&buff);
}
