#include "monty.h"

/**
 * get_function - get function of opcode
 * @line: opcode
 * @line_number: line number of opcode
 * Return: function associated with opcode
*/

void (*get_function(char *line, int line_number))(stack_t **, unsigned int)
{
	int i;
	instruction_t instruct[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add}
	};

	for (i = 0; i < 6; i++)
	{
		if (!strcmp(instruct[i].opcode, commandv[0]))
		{
			return (instruct[i].f);
		}
	}
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, line);
	exit(EXIT_FAILURE);
}

/**
 * _push - push number on top of stack
 * @stack: bottom of stack
 * @line_number: line number of opcode
*/

void _push(stack_t **stack, unsigned int line_number)
{
	int num;
	stack_t *new = malloc(sizeof(stack_t)), *temp;

	num = get_int(line_number);
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
