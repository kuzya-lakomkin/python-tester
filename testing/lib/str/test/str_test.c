#include <criterion/criterion.h>
#include <stdio.h>

#include "../str.h"

Test(str_suite, test_create) {
    str new;
    int res = create_str(&new);
    if (!res) {
        cr_assert_neq(new._str, NULL);
        cr_assert_neq(new._capacity, 0);
        cr_assert_eq(new._length, 0);
    }
    delete_str(&new);
}

Test(str_suite, test_copy_rvalue) {
    str new;
    int res = copy_char_str(&new, "hello!");

    if (!res) {
        cr_assert_neq(new._str, NULL);
        cr_assert_neq(new._capacity, 0);
        cr_assert_eq(new._length, 6);

        cr_assert_eq(new._str[0], 'h');
        cr_assert_eq(new._str[1], 'e');
        cr_assert_eq(new._str[2], 'l');
        cr_assert_eq(new._str[3], 'l');
        cr_assert_eq(new._str[4], 'o');
        cr_assert_eq(new._str[5], '!');
    }

    cr_assert_eq(str_capacity(&new), 7);
    cr_assert_eq(str_length(&new), 6);

    delete_str(&new);
}

Test(str_suite, test_copy_lvalue) {
    char src[7] = "hello!";
    str new;
    int res = copy_char_str(&new, src);

    if (!res) {
        for (size_t i = 0; i < 6; ++i) {
            cr_assert_eq(new._str[i], src[i]);
        }
    }

    cr_assert_eq(str_capacity(&new), 7);
    cr_assert_eq(str_length(&new), 6);

    delete_str(&new);
}

Test(str_suite, test_copy) {
    str a;
    if(copy_char_str(&a, "LOOOOOOOL")) {
        cr_assert_eq(1, 2);
    }

    cr_assert_eq(str_length(&a), 9);
    cr_assert_eq(str_capacity(&a), 10);

    str b;
    if (!copy_str(&b, &a)) {
        cr_assert_neq(b._str, NULL);
        cr_assert_neq(b._capacity, 0);
        cr_assert_eq(b._length, 9);
        
        for (size_t i = 0; i > str_length(&b); ++i) {
            cr_assert_eq(a._str[i], b._str[i]);
        }
    }

    delete_str(&a);
    delete_str(&b);
}

Test(str_suite, test_length) {
    str new;
    if(copy_char_str(&new, "LOOOOL")) {
        cr_assert_eq(1, 2);
    }

    cr_assert_eq(str_length(&new), 6);
    delete_str(&new);
}

Test(str_suite, test_capacity) {
    str new;
    if(create_str(&new)) {
        cr_assert_eq(1, 2);
    }

    cr_assert_eq(str_capacity(&new), 4);

    delete_str(&new);
}

Test(str_suite, test_is_empty) {
    str new;
    if(create_str(&new)) {
        cr_assert_eq(1, 2);
    }
    cr_assert_eq(is_str_empty(&new), 1);
    delete_str(&new);

    copy_char_str(&new, "aaaaaaaaaaaaaaaaaaaaa");
    cr_assert_eq(is_str_empty(&new), 0);
    delete_str(&new);
}

Test(str_suite, test_is_valid) {
    cr_assert_eq(is_str_valid(NULL), 0);

    str s = {NULL, 0, 0};
    cr_assert_eq(is_str_valid(&s), 0);

    create_str(&s);
    cr_assert_eq(is_str_valid(&s), 1);

    delete_str(&s);
    cr_assert_eq(is_str_valid(&s), 0);

    str a = invalid_str();
    cr_assert_eq(is_str_valid(&a), 0);
}

Test(str_suite, test_get_symbol) {
    str s;
    copy_char_str(&s, "www.google.com");

    char res;
    int op;

    for (size_t i = 0; i < str_length(&s); ++i) {
        op = str_symbol(&s, i, &res);
        cr_assert_eq(res, s._str[i]);
        cr_assert_eq(op, 0);
    }

    op = str_symbol(&s, -1, &res);
    cr_assert_eq(op, -1);

    op = str_symbol(&s, 300, &res);
    cr_assert_eq(op, -1);

    delete_str(&s);
}

Test(str_suite, test_cmp) {
    str a;
    copy_char_str(&a, "1234567890");

    cr_assert_eq(str_length(&a), 10);
    cr_assert_eq(str_capacity(&a), 11);

    str b;
    copy_str(&b, &a);

    cr_assert_eq(str_cmp(&a, &b), 1);

    str_set_sym(&a, 0, 'e');
    cr_assert_eq(str_cmp(&a, &b), 0);

    cr_assert_eq(str_cmp(&a, &a), 1);
    cr_assert_eq(str_cmp(&b, &b), 1);
    cr_assert_eq(str_cmp(NULL, NULL), 0);

    delete_str(&a);
    delete_str(&b);
}

Test(str_suite, test_slice) {
    str s;
    copy_char_str(&s, "macintosh.py");
    str res = str_slice(&s, -3, -1);

    str postfix;
    copy_char_str(&postfix, ".py");

    cr_assert_eq(str_cmp(&postfix, &res), 1);
    cr_assert_eq(str_length(&postfix), 3);

    delete_str(&s);
    delete_str(&res);
    delete_str(&postfix);
}

Test(str_suite, test_concat) {
    str a, b, c, test;

    copy_char_str(&a, "petr");
    copy_char_str(&b, " hohlin");
    str_concat(&a, &b, &c);

    copy_char_str(&test, "petr hohlin");

    cr_assert_eq(str_cmp(&test, &c), 1);
    cr_assert_eq(str_length(&c), 11);

    delete_str(&a);
    delete_str(&b);
    delete_str(&c);

    copy_char_str(&a, "petr");
    copy_char_str(&b, " hohlin");
    int res = str_concat(&a, &b, &a);
    
    cr_assert_eq(res, 0);
    cr_assert_eq(str_cmp(&test, &a), 1);
    cr_assert_eq(str_length(&a), 11);

    delete_str(&a);
    delete_str(&b);

    copy_char_str(&a, "petr");
    copy_char_str(&b, " hohlin");
    res = str_concat(&a, &b, &b);
    
    cr_assert_eq(res, 0);
    cr_assert_eq(str_cmp(&test, &b), 1);
    cr_assert_eq(str_length(&b), 11);

    delete_str(&test);
    delete_str(&a);
    delete_str(&b);
}

Test(str_suite, test_add_str) {
    str a, b, test;
    copy_char_str(&a, "Hello Hello Hello Hello Hello");
    copy_char_str(&b, " World! World! World! World! World!");
    copy_char_str(&test, "Hello Hello Hello Hello Hello World! World! World! World! World!");
    str_add_str(&a, &b);

    cr_assert_eq(str_cmp(&a, &test), 1);
    cr_assert_eq(str_length(&test), str_length(&a));

    delete_str(&a);
    delete_str(&b);
    delete_str(&test);
}

Test(str_suite, test_add_char) {
    str a, test;
    char b[10] = " Wooorld!";
    copy_char_str(&a, "Hello Hello Hello Hello Hello");
    copy_char_str(&test, "Hello Hello Hello Hello Hello Wooorld!");
    str_add_char(&a, b, 9);

    cr_assert_eq(str_cmp(&a, &test), 1);
    cr_assert_eq(str_length(&test), str_length(&a));

    delete_str(&a);
    delete_str(&test);
}
