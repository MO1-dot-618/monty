#include "monty.h"

int rmonty(FILE *file);
void free_stack(stack_t *head);
int push(stack_t **head, int n);
void pall(stack_t *head);

void pall(stack_t *head)
{
	stack_t *temp = head;

	while(temp->next)
		temp = temp->next;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->prev;
	}
}
void free_stack(stack_t *head)
{
	stack_t *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

int push(stack_t **head, int n)
{
	stack_t *new = (stack_t*) malloc(sizeof(stack_t));
	stack_t *temp;

	new->n = n;
	new->next = NULL;
	if (!*head)
	{
		new->prev = NULL;
		*head = new;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	return(0);
}

int rmonty(FILE *file)
{
	char *line;
	char *opcode, *num_push;
	int i = 0, j = 0, line_num = 0;
	stack_t *stack_head = NULL;

	line = malloc(100);
	if (line == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
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
		{
			num_push = malloc(10);
			j = 0;
			while (line[i] >= '9' || line[i] <= '0')
				i++;
			while (line[i] != '\0' && line[i] != ' ' && line[i] != '\n' && line[i] <= '9' && line[i] >= '0')
				num_push[j++] = line[i++];
			num_push[j] = '\0';
			if (num_push[0] != '\0')
				push(&stack_head, atoi(num_push));
			else
				fprintf(stderr, "L%d: usage: push integer\n", line_num);
			free(num_push);
		}
		else if(strcmp(opcode, "pall") == 0)
		{
			pall(stack_head);
		}
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_num, opcode);
			free(opcode);
			free(line);
			free_stack(stack_head);
			return(EXIT_FAILURE);
		}
		free(opcode);
		free(line);
		line = malloc(100);
	}
	free(line);
	free_stack(stack_head);
	return(0);
}

int main(int argc, char **argv)
{
	FILE *file;
	int return_;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return_ = rmonty(file);

	fclose(file);
	return (return_);
}
