#include "monty.h"

int main(int argc, char **argv)
{
	char* line;
	char* opcode;
	FILE *file;
	int i = 0, j = 0, line_num = 0;

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
	line = malloc(100);
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
			exit(EXIT_FAILURE);
		}
		free(opcode);
		free(line);
		line = malloc(100);
	}
	free(line);
	fclose(file);
	return 0;
}
