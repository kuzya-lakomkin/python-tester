#include "../buffer.h"

CharBuffer create_buffer(size_t size) {
    CharBuffer buff = (CharBuffer){NULL, 0, 0, 0};
    if (0 == size) {
        return buff;
    }

    buff._storage = (char *)(malloc(size * sizeof(char)));
    if (NULL == buff._storage) {
        return buff;
    }

    buff._capacity = size;
    buff._size = 0;
    buff._id = 0;

    return buff;
}

void delete_buffer(CharBuffer * buff) {
    if (NULL == buff) {
        return;
    }

    if (NULL != buff->_storage) {
        free(buff->_storage);
    }

    buff->_storage = NULL;
    buff->_capacity = 0;
    buff->_size = 0;
    buff->_id = 0;
}

int push_ch_buffer(CharBuffer * buff, char * s, size_t size) {
    if (NULL == buff || NULL == s || size > buff->_capacity || buff->_id < buff->_size) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        buff->_storage[i] = s[i];
    }

    buff->_id = 0;
    buff->_size = size;

    return 0;
}

int push_str_buff(CharBuffer * buff, str * s) {
    if (NULL == buff || NULL == s || !str_length(s) || str_length(s) > buff->_capacity) {
        return -1;
    }

    for (size_t i = 0; i < str_length(s); ++i) {
        str_symbol(s, i, buff->_storage + i);
    }

    buff->_id = 0;
    buff->_size = str_length(s);

    return 0;
}

int next_buffer_sym(CharBuffer * buff, char * dst) {
    if (NULL == buff || NULL == dst || buff->_id >= buff->_size) {
        return -1;
    }

    *dst = buff->_storage[buff->_id];
    buff->_id++;

    return 0;
}

int next_buffer_substr(CharBuffer * buff, str * dst, size_t size) {
    if (NULL == buff || NULL == dst || 0 == size || buff->_id + size >= buff->_size) {
        return -1;
    }

    str_add_char(dst, buff->_storage + buff->_id, size);

    return 0;
}

char * buffer_raw_ptr(CharBuffer * buff) {
    if (NULL == buff) {
        return NULL;
    }

    return buff->_storage;
}

size_t buffer_length(CharBuffer * buff) {
    if (NULL == buff) {
        return 0;
    }

    return buff->_size;
}

size_t buffer_capacity(CharBuffer * buff) {
    if (NULL == buff) {
        return 0;
    }

    return buff->_capacity;
}

size_t buffer_index(CharBuffer * buff) {
    if (NULL == buff) {
        return 0;
    }

    return buff->_id;
}
