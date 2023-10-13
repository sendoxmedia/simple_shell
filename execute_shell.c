#include "new_shell.h"



void execute_command(const char *command) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        sen_print("Error forking process.\n");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
	
        char *args[128];
        int arg_count = 0;

        char *token = strtok((char *)command, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        execve(args[0], args, NULL);

        sen_print("No such file or directory.\n");
        exit(EXIT_FAILURE);
    } else {

        wait(NULL);
    }
}
