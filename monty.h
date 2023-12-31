#ifndef __LISTS_H
#define __LISTS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **commandv;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void (*get_function(char *line, int line_number))(stack_t **stack, unsigned int line_number);
void _push(stack_t **stack, unsigned int line_number);
int get_int(int line_number);
char **tokenize(char *command);
void _pall(stack_t **stack, unsigned int __attribute__((unused)) line_number);
void _pint(stack_t **stack, unsigned int line_number);
void _pop(stack_t **stack, unsigned int line_number);
void _swap(stack_t **stack, unsigned int line_number);
void _add(stack_t **stack, unsigned int line_number);
void _nop(stack_t __attribute__((unused)) **stack, unsigned int __attribute__((unused)) line_number);
void free_stack(stack_t *stack);
void free_array(char **array);
int is_blank(char *line);
#endif /*__LISTS_H*/
