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
 * get_args - Extracts and returns an unsigned integer from a given string.
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
 * _strdup - Duplicates a string and returns a dynamically allocated copy.
 * Responsible for freeing the memory when it is no
 * longer needed.
 *
 * @str: A pointer to the null-terminated string to duplicate.
 *
 * Return: A pointer to a newly allocated duplicate of the input string,
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
 * _strlen - Calculate the length of a null-terminated string.
 *
 * @str: A pointer to the null-terminated string to measure.
 *
 * Return: The length of the input string as an unsigned integer.
 */
unsigned int _strlen(char *str)
{
	unsigned int len = 0;

	for (; str[len] != '\0'; len++)
		;

	return (len);
}

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
