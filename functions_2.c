#include "monty.h"

/**
 * get_int - get int from string
 * @line_number: line number of opcode
 * Return: return int
*/

int get_int(int line_number)
{
	int num, i;

	if (!commandv[1])
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	for (i = 0; commandv[1][i]; i++)
	{
		if (commandv[1][i] < 48 || commandv[1][i] > 57)
		{
			if (i == 0 && commandv[1][i] == '-')
				continue;
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}
	num = atoi(commandv[1]);
	return (num);
}

/**
 * _swap - swap top two nodes
 * @stack: bottom node
 * @line_number: line number of opcode
*/

void _swap(stack_t **stack, unsigned int line_number)
{
	int tmp;
	stack_t *previous, *current = *stack;

	if (!current->next)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	while (current->next)
	{
		previous = current;
		current = current->next;
	}
	tmp = current->n;
	current->n = previous->n;
	previous->n = tmp;
}
