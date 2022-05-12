#ifndef OUTPUT_H
#define OUTPUT_H

// message that is printed on startup of application
void welcome_message();

// message that is printed for each line the user inputs
void prompt();

// generic error message for a syscall
void syscall_error(char *program);

// error of a function being used incorrectly
// by another part of code
void developer_error(char *message);

// error on parsing, due to user confusion
void syntax_error(char *message);

#endif

