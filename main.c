#include "main.h"
#include <sys/wait.h>

char **commandv = NULL;

/**
 * main - monty interpeter
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: SUCCESS or FAILURE
*/

int main(int argc, char *argv[])
{
	stack_t *stack = NULL;
	FILE *f;
	char *command;
	int line_num = 0;
	void (*func)(stack_t**, unsigned int);

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	f = fopen(argv[1], "r");
	if (!f)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	command = malloc(sizeof(char) * 1024);
	if (!command)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	while (fgets(command, 1024, f))
	{
		line_num++;
		command[strlen(command) - 1] = '\0';
		commandv = tokenize(command);
		if (!commandv)
			continue;
		func = get_function(commandv[0]);
		func(&stack, line_num);
	}
	exit(EXIT_SUCCESS);
}

char **tokenize(char *command)
{
	size_t i, j = 0;
	char *cmd = malloc(sizeof(char *));

	commandv = malloc(sizeof(char **));
	if (!commandv || !cmd)
	{
		fprintf(stderr, "USAGE: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; command[i]; i++)
	{
		if (command[i] != ' ' && command[i - 1] == ' ')
		{
			cmd[j] = ' ';
			j++;
			cmd[j] = command[i];
			j++;
		}
		else if (command[i] != ' ')
		{
			cmd[j] = command[i];
			j++;
		}
	}
	if (!cmd)
		return (NULL);
	commandv[0] = strtok(cmd, " ");
	for (i = 1; ; i++)
	{
		commandv[i] = strtok(NULL, " ");
		if (!commandv[i])
			break;
	}
	return (commandv);
}
