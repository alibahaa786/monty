#include "monty.h"

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
		if (is_blank(command))
			continue;
		command[strlen(command) - 1] = '\0';
		commandv = tokenize(command);
		if (!commandv)
			continue;
		get_function(command, line_num)(&stack, line_num);
	}
	free_stack(stack);
	fclose(f);
	exit(EXIT_SUCCESS);
}

/**
 * tokenize - split command into words
 * @command: full command
 * Return: array of words of the command
*/

char **tokenize(char *command)
{
	size_t i, j = 0;
	char *cmd = malloc(sizeof(char *));

	commandv = malloc(sizeof(char *) * 3);
	if (!commandv || !cmd)
	{
		fprintf(stderr, "USAGE: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; command[i]; i++)
	{
		if (command[i] != ' ' && command[i - 1] == ' ' && j)
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
	for (i = 0; cmd[i]; i++)
		command[i] = cmd[i];
	for (; command[i]; i++)
		command[i] = '\0';
	if (!cmd)
		return (NULL);
	commandv[0] = strtok(cmd, " ");
	commandv[1] = strtok(NULL, " ");
	return (commandv);
}

/**
 * is_blank - check if line of opcode is blank
 * @line: opcode
 * Return: 1 if blank else 0
*/

int is_blank(char *line)
{
	size_t i;

	if (strlen(line) < 2)
		return (1);
	for (i = 0; i < strlen(line) - 1; i++)
	{
		if (line[i] != ' ')
			return (0);
	}
	return (1);
}

/**
 * free_stack - free stack
 * @stack: stack
*/

void free_stack(stack_t *stack)
{
	stack_t *tmp;

	while (stack)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
	}
}

/**
 * free_array - free array
 * @array: array
*/

void free_array(char **array)
{
	int i;

	for (i = 0; array[i]; i++)
		free(array);
}
