#include "headers.h"

void process_single_command(char * parameter)
{
	// printf("%s\n", parameter);
	char command[1000];
	char * save_command;
	strcpy(command, parameter);
	// printf("Pass\n");
	// printf("%s\n", parameter);
	char * word = strtok_r(command, " ", &save_command);
	if(strcmp("cd", word) == 0)
	{
		// printf("Yes\n");
		// printf("%s\n", parameter);
		change_dir(parameter);
	}
}

void process_input(char * input)
{
	char * save_single_command;
	char input_copy[1000];
	strcpy(input_copy, input);
	// printf("Yes\n");
	char * command = strtok_r(input_copy, ";", &save_single_command);
	while(command != NULL)
	{
		process_single_command(command);
		command = strtok_r(NULL,";",&save_single_command);
	}
}