#ifndef _NSTU_TEST_BUFFER_H
#define _NSTU_TEST_BUFFER_H

#include "../str/str.h"

#include <stdlib.h>

struct CharBuffer {
    char * _storage;
    size_t _size, _capacity, _id;
};
typedef struct CharBuffer CharBuffer;

/**
 * 
 */
CharBuffer create_buffer(size_t size);

/**
 * 
 */
void delete_buffer(CharBuffer * buff);

/**
 * 
 */
int push_ch_buffer(CharBuffer * buff, char * s, size_t size);

/**
 * 
 */
int push_str_buff(CharBuffer * buff, str * s);

/**
 * 
 */
int next_buffer_sym(CharBuffer * buff, char * dst);

/**
 * 
 */
int next_buffer_substr(CharBuffer * buff, str * dst, size_t size);

/**
 * 
 */
char * buffer_raw_ptr(CharBuffer * buff);

/**
 * 
 */
size_t buffer_length(CharBuffer * buff);

/**
 * 
 */
size_t buffer_capacity(CharBuffer * buff);

/**
 * 
 */
size_t buffer_index(CharBuffer * buff);

#endif