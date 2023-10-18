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
	char *full_path, *lineptr = NULL;
	size_t n;
	pid_t pid;
	char **command;
	unsigned int args, i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);

		if (getline(&lineptr, &n, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\nexit\n", 6);

			free(lineptr);
			lineptr = NULL;
			exit(0);
		}

		args = get_args(lineptr);
		command = malloc(sizeof(char *) * (args + 1));
		i = 0;
		command[i] = strtok(lineptr, " \n\t\r");

		while (command[i] != NULL)
		{
			i++;
			command[i] = strtok(NULL, " \n\t\r");
		}

		if (command[0] == NULL)
		{
			free(lineptr);
			free(command);
			lineptr = NULL;
			continue;
		}

		if (access(command[0], X_OK))
		{
			full_path = get_full_path(command[0], env);

			if (full_path == NULL)
			{
				perror(argv[0]);
				continue;
			}

			command[0] = full_path;
		}

		pid = fork();

		if (pid == 0)
		{
			if (execve(command[0], command, env) == -1)
			{
				perror(argv[0]);

				free(lineptr);
				free(command);
				lineptr = NULL;
				exit(0);
			}
		}
		else
		{
			wait(NULL);
		}

		free(lineptr);
		free(command);
		lineptr = NULL;
	}

	return (0);
}


/**
 * get_args - Extracts and returns an unsigned 
 * integer from a given string.
 *
 * @str: A pointer to the input string to parse.
 *
 * Return: 0 if no valid integer is found.
 */
unsigned int get_args(char *str)
{
	unsigned int args = 0;
	char *new_str = _strdup(str);
	char *token;

	token = strtok(new_str, " \n\t\r");

	while (token != NULL)
	{
		token = strtok(NULL, " \n\t\r");
		args++;
	}

	free(new_str);

	return (args);
}

/**
 * _strdup - Duplicates a string and returns a 
 * dynamically allocated copy.
 * Responsible for freeing the memory when it is no
 * longer needed.
 *
 * @str: A pointer to the null-terminated string 
 * to duplicate.
 *
 * Return: A pointer to a newly allocated 
 * duplicate of the input string,
 * or NULL if memory allocation fails.
 */
char *_strdup(char *str)
{
	unsigned int len = _strlen(str);
	char *new_str = malloc(sizeof(char) * (len + 1));
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		new_str[i] = str[i];
	}

	new_str[i] = '\0';

	return (new_str);
}

/**
 * _strlen - Check the length of a null-terminated 
 * string.
 *
 * @str: A pointer to the null-terminated string to.
 *
 * Return: The length of the input string as an 
 * unsigned integer.
 */
unsigned int _strlen(char *str)
{
	unsigned int len = 0;

	for (; str[len] != '\0'; len++)
		;

	return (len);
}
/**
 * _strncmp - Compares first character of two strings
 * str1 and str2.
 *
 * @str1 - A pointer to the first input string.
 * @str2 - A pointer to the second input string.
 *
 * Return: 0 if the first n characters of str1 
 * and str2 are identical.
 * A non-zero value indicating the difference 
 * between the two strings if they are not equal.
 */
unsigned int _strncmp(char *str1, char *str2, unsigned int n)
{
	unsigned int i = 0;

	if (_strlen(str1) < n || _strlen(str2) < n)
		return (1);

	while (i < n)
	{
		if (str1[i] != str2[i])
			return (1);
	
		i++;
	}

	return (0);
}
/**
 * build_path - This function takes two input strings, 
 * dir (directory) and file (file), and combines them 
 * to create a complete file path.
 *
 * @dir - A pointer to the directory portion of the path.
 * @file - A pointer to the filename or file portion of 
 * the path.
 *
 * Return: A pointer to a character string (char*): 
 * The resulting file path created by concatenating dir and file.
 */
char *build_path(char *dir, char *file)
{
	int i = 0, j = 0;
	unsigned int len = _strlen(dir) + _strlen(file) + 2;
	char *full_path = malloc(sizeof(char) * len);

	while (dir[i] != '\0')
	{
		full_path[j] = dir[i];
		i++, j++;
	}

	full_path[j] = '/';
	i = 0;
	j++;

	while (file[i] != '\0')
	{
		full_path[j] = file[i];
		i++, j++;
	}

	full_path[j] = '\0';
	
	return (full_path);
}
/**
 * get_full_path - This function takes two inputs,
 * file and env, and attempts to locate the full
 * path to the specified file within the environment
 * variables provided in env.
 *
 * @file - A pointer to the string representing the
 * file or executable to be located.
 * @env - A pointer to an array of environment
 * variables (as strings) that contain directory
 * paths to search for the specified file.
 *
 * Return: A pointer to a character string (char*):
 * The full path to the specified file if it is found
 * within one of the directories specified in env.
 * If the file is not found, the function may return NULL
 * or a special value to indicate the absence of the file.
 */  
char *get_full_path(char *file, char **env)
{
	char *path, *full_path, *dir;

	path = get_path(env);

	if (path == NULL)
		return (NULL);

	strtok(path, "=:");
	dir = strtok(NULL, "=:");

	while (dir != NULL)
	{
		full_path = build_path(dir, file);

		if (access(full_path, X_OK) == 0)
			return (full_path);

		dir = strtok(NULL, "=:");
	}

	return (NULL);
}
/**
 * get_path - This function takes an array of
 * environment variables (env) and retrieves
 * the value associated with the "PATH"
 * environment variable.
 *
 * @env - A pointer to an array of environment
 * variables, where the "PATH" variable is to be
 * retrieved.
 *
 * Return: A pointer to a character string (char*):
 * The value of the PATH environment variable,
 * which consists of a colon-separated list of
 * directory paths.
 */
char *get_path(char **env)
{
	unsigned int j = 0;
	char *path;

	while (env[j] != NULL)
	{
		if (_strncmp("PATH", env[j], 4) == 0)
		{
			path = _strdup(env[j]);	
			return (path);
		}

		j++;
	}

	return (NULL);
}
