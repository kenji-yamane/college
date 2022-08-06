#ifndef CHILD_H
#define CHILD_H

#include <sys/types.h> // pid_t

#include <stdbool.h>

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
	int status;
	int pid;
	bool stopped;
	bool completed;
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

// sets status and interprets it
childp set_status(childp p, int status);

// duplicates if possible pipes and input
// and output files
void define_ends(childp p);

// handles job control signals and sets
// its own group in foreground if it is the case
void position_itself(childp p, pid_t pgid, bool foreground);

/*
 * creates a new process by forking and executing
 *
 * at first it attempts to execute a program locally
 * if it is not found locally, it tries on the /bin folder
 * if none is found, it terminates itself
 */
pid_t instantiate(childp p, pid_t pgid, bool foreground);

// frees every field from childp
// dynamically allocated
void free_child(childp p);

#endif // child
