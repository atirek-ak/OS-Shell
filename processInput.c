#include "headers.h"

void process_single_command(char * parameter)
{
	char * command;
	char * save_command;
	strcpy(command, parameter);
	char * word = strtok_r(command, " ", &save_command);
	if(strcmp("cd", word) == 0)
	{
		change_dir(command);
	}
}

void process_input(char * input)
{
	char * save_single_command;
	char * command = strtok_r(input, ";", &save_single_command);
	while(command != NULL)
	{
		command = strtok_r(NULL,";",&save_single_command);
		process_single_command(command);
	}
}