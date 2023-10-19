#include "header.h"
/**
 * validate_command - function that is used to validate
 * and process a command provided as input to a shell or a
 * similar program. This function takes multiple arguments
 *
 * @command: A pointer to a pointer to characters (char **)
 * representing the command to be validated
 *
 * @shell: A pointer to a character array (char *) indicating
 * the name or identifier of the shell or program.
 *
 * @env: A pointer to a pointer to characters (char **)
 * representing the environment variables for the shell
 * or program.
 *
 * @exit_code: A pointer to an integer (int *) used to store an
 * exit code or error code.
 *
 * Return: (VALID_COMMAND).
 */

unsigned int validate_command(char **command, char *shell, char **env,
		int *exit_code)
{
	char *full_path;
	struct stat file_info = {0};


	if (command[0] == NULL)
		return (COMMAND_NOT_VALID);

	stat(command[0], &file_info);
	if (S_ISDIR(file_info.st_mode))
	{
		write(2, shell, _strlen(shell));
		write(2, ": line 1: ", 10);
		write(2, command[0], _strlen(command[0]));
		write(2, ": Is a directory\n", 17);
		*exit_code = 126;
		return (COMMAND_NOT_VALID);
	}

	if (access(command[0], X_OK))
	{
		full_path = get_full_path(command[0], env, shell);

		if (full_path == NULL)
		{
			*exit_code = 127;
			return (COMMAND_NOT_VALID);
		}

		command[0] = full_path;

		return (COMMAND_VALIDATED);
	}

	return (VALID_COMMAND);
}
