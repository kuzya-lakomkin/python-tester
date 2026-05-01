#ifndef _NSTU_TESTER_STR_H
#define _NSTU_TESTER_STR_H

#include <stdlib.h>

struct str {
    char * _str;
    size_t _length, _capacity; 
};

typedef struct str str;

/**
 * @brief Creates new empty string.
 * 
 * @param src String to create.
 * 
 * @return 0 if string was created successfully, -1 if failure. 
 */
int create_str(str * s);

/**
 * @brief Returns invalid string.
 * 
 * @return Invalid string.
 */
str invalid_str(void);

/**
 * @brief Creates new string from raw char array.
 * 
 * @param dst New string.
 * @param src Char array to copy.
 * 
 * @return 0 if string was copied successfully, -1 if failure.
 */
int copy_char_str(str * dst, char * src);

/**
 * @brief Creates new string as copy of specified string.
 * 
 * @param dst New string. Should not be created before this operation. If dst is not empty then it get deleted.
 * @param src String to copy.
 * 
 * @return 0 if string was copied successfully, -1 if failure.
 */
int copy_str(str * dst, str * src);

/**
 * @brief Deletes specified string; raw pointer to string becomes invalidated after this operation.
 * 
 * @param s String to delete.
 */
void delete_str(str * s);

/**
 * @brief Returns a raw pointer to specified string.
 * 
 * @param s String.
 * 
 * @return Raw pointer to string; NULL if string is invalid.
 */
char * str_ptr(str * s);

/**
 * @brief Returns a length of specified string.
 * 
 * @param s String.
 * 
 * @return String length; 0 if string is invalid.
 */
size_t str_length(str * s);

/**
 * @brief Returns a capacity of specified string.
 * 
 * @param s String.
 * 
 * @return String capacity; 0 if string is invalid.
 */
size_t str_capacity(str * s);

/**
 * @brief Finds symbol from specified string by index, then writes result into given pointer.
 * 
 * @param s String to find symbol.
 * @param id Symbol index.
 * @param res Place to write a symbol.
 * 
 * @return 0 if symbol was found successfully; -1 if failure. 
 */
int str_symbol(str * s, size_t id, char * res);

/**
 * @brief Concatenates two strings; writes operation result into specified destination.
 * 
 * @param a First operand.
 * @param b Second operand.
 * @param dst Destination; result will be written right there.
 * 
 * @return 0 if operation completed successfully; -1 if opearation failed.
 */
int str_concat(str * a, str * b, str * dst);

/**
 * @brief Checks is given string valid.
 * 
 * @param s String to check.
 * 
 * @return 1 if given is valid; 0 if given string is not valid.
 */
int is_str_valid(str * s);

/**
 * @brief Checks is given string empty.
 * 
 * @param s String to check.
 * 
 * @return 1 if given is empty; 0 if given string is not empty.
 */
int is_str_empty(str * s);

/**
 * @brief Compares two strings.
 * 
 * @param a First operand.
 * @param b Second operand.
 * 
 * @return 1 if strings are equal to each other; 0 if strings are not equal or if failed to complete operation.
 */
int str_cmp(str * a, str * b);

/**
 * @brief Sets string symbol by index.
 * 
 * @param s String to set symbol.
 * @param i Symbol index.
 * @param sym Symbol to set.
 * 
 * @return 0 if symbol was setted successfully; -1 if failure. 
 */
int str_set_sym(str * s, size_t i, char sym);

/**
 * @brief Creates slice from specified string by indexes.
 * 
 * @param src String to slice.
 * @param start Slice start index.
 * @param end Slice end index.
 * 
 * @return Sliced string. src stays valid after this operation. Invalid sttring can be returned if operation failed.
 */
str str_slice(str * src, int start, int end);

/**
 * @brief Adds substring to the end of specified string.
 * 
 * @param dst String.
 * @param postfix Substring to add.
 * 
 * @return 0 if substring was added successfully; -1 if failure. 
 */
int str_add_str(str * dst, str * postfix);

/**
 * @brief Adds substring to the end of specified string.
 * 
 * @param dst String.
 * @param postfix Substring to add.
 * @param length Substring length.
 * 
 * @return 0 if substring was added successfully; -1 if failure. 
 */
int str_add_char(str * dst, char * postfix, size_t length);

#endif