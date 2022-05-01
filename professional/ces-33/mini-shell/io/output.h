#ifndef OUTPUT_H
#define OUTPUT_H

// message that is printed on startup of application
void welcome_message();

// message that is printed for each line the user inputs
void prompt();

// echoes what the user is writing to help him
void echo(char c);

// generic error message for a syscall
void syscall_error(char *program);

#endif

