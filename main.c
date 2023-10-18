#include "monty.h"

int rmonty(FILE *file);
stack_t *init_stack(int n, stack_t *prev, stack_t *next);

int rmonty(FILE *file)
{
	char* line;
	char* opcode;
	int i = 0, j = 0, line_num = 0;
	stack_t *stack_head = init_stack(0, NULL, NULL);

	line = malloc(100);
	if (line == NULL)
	{
		printf("Error: malloc failed\n");
		return(EXIT_FAILURE);
	}
	while (fgets(line, 100, file) != NULL)
	{
		line_num++;
		j = 0;
		i = 0;
		
		opcode = malloc(10);

		while (line[i] != '\0' && line[i] == ' ')
			i++;
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '\n' && j < 9)
			opcode[j++] = line[i++];
		opcode[j] = '\0';
		if(strcmp(opcode, "push") == 0)
			printf("you wanna push\n"); /* write code to run opcode */
		else if(strcmp(opcode, "pall") == 0)
			printf("you wanna print\n"); /* write code to run opcode */
		else
		{
			printf("L%d: unknown instruction %s\n", line_num, opcode);
			free(opcode);
			free(line);
			fclose(file);
			return(EXIT_FAILURE);
		}
		free(opcode);
		free(line);
		line = malloc(100);
	}
	free(line);
	return(0);
}

stack_t *init_stack(int n, stack_t *prev, stack_t *next)
{
	stack_t *stack_head = (stack_t*) malloc(sizeof(stack_t));
	stack_head->prev = prev;
	stack_head->next = next;
	stack_head->n = n;

	return stack_head;
}

int main(int argc, char **argv)
{
	FILE *file;
	int return_;

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return_ = rmonty(file);

	fclose(file);
	return (return_);
}
