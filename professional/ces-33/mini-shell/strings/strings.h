#ifndef STRINGS_H
#define STRINGS_H

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

#endif

