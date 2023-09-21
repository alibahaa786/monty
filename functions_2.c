#include "monty.h"

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
