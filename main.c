#include "header.h"

/**
 * main - main shell loop
 * @argc: the argc parameter is not used
 * @argv: an array of command-line arguments
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main(int __attribute__((unused)) argc, char *argv[], char **env)
{
	char *lineptr, **command;
	pid_t pid;
	unsigned int is_command_valid, commands_executed = 1;
	int wstatus;
	int exit_code = EXIT_SUCCESS;

	while (1)
	{
		lineptr = get_lineptr();
		if (lineptr == NULL)
			break;
		command = get_command(lineptr);
		if (command == NULL)
		{
			free(lineptr);
			break;
		}
		is_command_valid  = validate_command(command, argv[0], env, &exit_code);
		if (is_command_valid == COMMAND_NOT_VALID)
		{
			_free(lineptr, command, is_command_valid);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(command[0], command, env) == -1)
				print_error(argv[0], command[0]);
		}
		else
		{
			wait(&wstatus);
			if (WIFEXITED(wstatus))
				exit_code = WEXITSTATUS(wstatus);
		}
		_free(lineptr, command, is_command_valid);
		commands_executed++;
	}

	return (exit_code);
}
