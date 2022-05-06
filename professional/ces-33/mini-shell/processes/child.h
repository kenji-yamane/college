#ifndef CHILD_H
#define CHILD_H

#include <sys/types.h> // pid_t

// represents a single child process
typedef struct {
	int num_arg;
	char **argv;
	int num_env;
	char **envp;
	char *input_file;
	char *output_file;
	int pipe_in;
	int pipe_out;
} childp;

// creates empty child,
// allocating only its pointers
// and setting the end of argc and
// envp to NULL
// it also sets program, input file
// and output file to empty strings
childp new_child();

// adds arg to child's arguments
childp add_argument(childp p, char *arg);

// sets input_file
void set_input_file(childp p, char *in);

// sets output_file
void set_output_file(childp p, char *out);

/*
 * creates a new process by forking and executing
 *
 * at first it attempts to execute a program locally
 * if it is not found locally, it tries on the /bin folder
 * if none is found, it terminates itself
 */
pid_t childp_create(childp p);

// frees every field from childp
// dynamically allocated
void free_child(childp p);

#endif // child

