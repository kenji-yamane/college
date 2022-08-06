#ifndef STRINGS_H
#define STRINGS_H

#include <stdbool.h>

// attaches prefix to the beginning of str
char *prepend(char *prefix, char *str);

// counts how many words there are in a string
// word being: a substring with no spaces
int count_words(char *str);

// splits a string into its words
// and stores it into a pointer of pointers
// it stores a null pointer into the end
// of the pointer of pointers to signal end
char **extract_words(char *str);

// copies the given string allocating
// the necessary memory
char *copy_str(char *str);

// returns a pointer to the first non-space character,
// without allocating new memory
char *trim_begin(char *str);

// finds the last non-space character and puts an
// end of string right after it
char *trim_end(char *str);

// checks if string is numeric
bool is_number(char *str);

#endif

