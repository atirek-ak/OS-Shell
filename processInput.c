#include "headers.h"

void process_single_command(char * parameter)
{
	char command[1000];
	char * save_command;
	strcpy(command, parameter);
	char * word = strtok_r(command, " ", &save_command);
	if(strcmp("cd", word) == 0)
		change_dir(parameter);
	else if(strcmp("echo", word) == 0)
		echo(parameter);
	else if(strcmp("pwd", word) == 0)
	{
		char str[1000];
		getcwd(str, sizeof(str));
		printf("%s\n", str);
	}
	else if(strcmp("ls", word) == 0)
		ls(parameter);
	else if(strcmp("quit", word) == 0)
		status = 0;
	else if(strcmp("pinfo", word) == 0)
		pinfo(parameter);
	else
		system_command(parameter);
	return;
}

void process_input(char * input)
{
	char * save_single_command;
	char input_copy[1000];
	strcpy(input_copy, input);
	// printf("Yes\n");
	char * command = strtok_r(input_copy, ";", &save_single_command);
	while(command != NULL && status)
	{
		process_single_command(command);
		command = strtok_r(NULL,";",&save_single_command);
	}
	return;
}