#include "monty.h"

/**
 * get_function - get function of opcode
 * @line: opcode
 * Return: function associated with opcode
*/

void (*get_function(char *line))(stack_t **, unsigned int)
{
	int i;
	instruction_t instruct[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop}
	};

	for (i = 0; instruct[i].opcode; i++)
	{
		if (!strcmp(instruct[i].opcode, line))
		{
			return (instruct[i].f);
		}
	}
	return (NULL);
}

/**
 * _push - push number on top of stack
 * @stack: bottom of stack
 * @line_number: line number of opcode
*/

void _push(stack_t **stack, unsigned int line_number)
{
	int num, i;
	stack_t *new = malloc(sizeof(stack_t)), *temp;

	if (!commandv[1])
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	for (i = 0; commandv[1][i]; i++)
	{
		if (commandvcommandv[1][i] < 48 || commandv[1][i] > 57)
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}
	num = atoi(commandv[1]);
	if (!new)
	{
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	new->n = num;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		new->prev = temp;
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		new->prev = NULL;
		new->next = NULL;
		*stack = new;
	}
}

/**
 * _pall - print stack from top
 * @stack: bottom of stack
 * @line_number: line number of opcode
*/

void _pall(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	stack_t *tmp = *stack;

	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		while (tmp)
		{
			printf("%d\n", tmp->n);
			tmp = tmp->prev;
		}
	}
}

/**
 * _pint - print top node of stack
 * @stack: bottom node of stack
 * @line_number: line number of opcode
*/

void _pint(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (!tmp)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	while (tmp->next)
		tmp = tmp->next;
	printf("%d\n", tmp->n);
}

/**
 * _pop - remove top node of stack
 * @stack: bottom node of stack
 * @line_number: line number of opcode
*/

void _pop(stack_t **stack, unsigned int line_number)
{
	stack_t *rm, *tmp = *stack;

	if (!tmp)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	while (tmp->next)
		tmp = tmp->next;
	rm = tmp;
	if (tmp->prev)
	{
		tmp = tmp->prev;
		tmp->next = rm->next;
	}
	else
		*stack = NULL;
	free(rm);
}
