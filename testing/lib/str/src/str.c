#include "str.h"

#include <stdio.h>

static const size_t INITIAL_CAPACITY = 4;

static size_t __strlen(char * str) {
    if (NULL == str) {
        return 0;
    }

    size_t cnt = 0;

    while (str[cnt] != '\0') {
        cnt += 1;
    }

    return cnt;
}


int create_str(str * s) {
    if (NULL == s) {
        return -1;
    }
    
    *s = (str){NULL, 0, 0};
    const size_t capacity = INITIAL_CAPACITY;
    char * new_str = (char *)malloc(capacity * sizeof(char));
    if (NULL == new_str) {
        return -1;
    }

    s->_str = new_str;
    s->_capacity = capacity;
    s->_length = 0;
    
    return 0;
}

int copy_str(str * dst, str * src) {
    if (NULL == dst || NULL == src) {
        return -1;
    }

    if (is_str_empty(src)) {
        return -1;
    }

    if (dst == src) {
        return 0;
    }

    /*
    if (!is_str_empty(dst)) {
        delete_str(dst);
    }
        */

    const size_t dst_capacity = src->_length;
    char * new_dst = (char *)malloc(dst_capacity + 1 * sizeof(char));
    if (NULL == new_dst) {
        return -1;
    }

    for (size_t i = 0; i < src->_length; ++i) {
        new_dst[i] = src->_str[i];
    }

    new_dst[src->_length] = 0;

    dst->_str = new_dst;
    dst->_capacity = dst_capacity + 1;
    dst->_length = dst_capacity;

    return 0;
}

int copy_char_str(str * dst, char * src) {
    if (NULL == dst || NULL == src) {
        return -1;
    }

    size_t src_len = __strlen(src);

    if (0 == src_len) {
        return -1;
    }

    /*
    if (!is_str_empty(dst)) {
        delete_str(dst);
    }
    */

    const size_t dst_capacity = src_len;
    char * new_dst = (char *)malloc((dst_capacity + 1) * sizeof(char));
    if (NULL == new_dst) {
        return -1;
    }

    for (size_t i = 0; i < src_len + 1; ++i) {
        new_dst[i] = src[i];
    }

    dst->_str = new_dst;
    dst->_capacity = dst_capacity + 1;
    dst->_length = dst_capacity;

    return 0;
}

void delete_str(str * s) {
    if (NULL == s || NULL == s->_str) {
        return;
    }

    free(s->_str);

    s->_str = NULL;
    s->_capacity = 0;
    s->_length = 0;
}

char * str_ptr(str * s) {
    if (NULL == s) {
        return NULL;
    }

    return s->_str;
}

size_t str_length(str * s) {
    if (NULL == s) {
        return 0;
    }

    return s->_length;
}

size_t str_capacity(str * s) {
    if (NULL == s) {
        return 0;
    }

    return s->_capacity;
}

int str_symbol(str * s, size_t id, char * res) {
    if (NULL == s || id >= s->_length || NULL == res) {
        return -1;
    }

    *res = s->_str[id];
    return 0;
}

int is_str_empty(str * s) {
    return (NULL == s || NULL == s->_str || 0 == s->_length);
}

int is_str_valid(str * s) {
    return (NULL != s && NULL != s->_str);
}

int str_concat(str * a, str * b, str * dst) {
    if (NULL == a || NULL == b || NULL == dst) {
        return -1;
    }

    str a_tmp, b_tmp;
    if (copy_str(&a_tmp, a)) {
        return -1;
    }

    if (copy_str(&b_tmp, b)) {
        delete_str(&a_tmp);
        return -1;
    }

    /*
    if (!is_str_empty(dst)) { delete_str(dst); }
    */

    if (a == dst) { 
        char * aptr = a->_str;
        free(aptr);
    }
    if (b == dst) { 
        char * bptr = b->_str;
        free(bptr);
    }

    dst->_str = realloc(a_tmp._str, a_tmp._length + b_tmp._length + 1);
    if (NULL == dst->_str) {
        delete_str(&b_tmp);
        return -1;
    }

    dst->_capacity = a_tmp._length + b_tmp._length + 1;
    for (size_t i = 0; i < b_tmp._length; i++) {
        dst->_str[a->_length + i] = b_tmp._str[i];
    }

    dst->_str[dst->_capacity - 1] = 0;

    dst->_length = dst->_capacity - 1;

    delete_str(&b_tmp);

    return 0;
}

int str_cmp(str * a, str * b) {
    if (!is_str_valid(a) || !is_str_valid(b)) {
        return 0;
    }

    if (str_length(a) != str_length(b)) {
        return 0;
    }

    for (size_t i = 0; i < str_length(a); ++i) {
        char as = 0, bs = 0;
        str_symbol(a, i, &as);
        str_symbol(b, i, &bs);
        if (as != bs) {
            return 0;
        }
    }

    return 1;
}

int str_set_sym(str * s, size_t i, char sym) {
    if (NULL == s || i >= s->_length) {
        return -1;
    }

    s->_str[i] = sym;
    if (sym == 0) {
        s->_length = i;
        return 0;
    }

    return 0;
}

str str_slice(str * src, int start, int end) {
    str new = {NULL, 0, 0};
    if (NULL == src || start < (int)src->_length * -1 || start >= (int)src->_length || end < (int)src->_length * -1 || end >= (int)src->_length) {
        return new;
    }

    start += src->_length * (start < 0);
    end += src->_length * (end < 0);
    if (start >= end) {
        return new;
    }

    size_t new_capacity = end - start + 1;
    char * slice_str = (char *)malloc(new_capacity * sizeof(char));
    if (NULL == slice_str) {
        return new;
    }
    
    for (size_t i = 0; i < new_capacity; ++i) {
        slice_str[i] = src->_str[i + start];
    }

    new._str = slice_str;
    new._capacity = new_capacity;
    new._length = new_capacity;

    return new;
}
