#include "headers.h"

void process_single_command(char * parameter)
{
	char command[1000];
	char * save_command;
	char last_character = ' ';
	if(strlen(parameter))
	{
		int index = strlen(parameter) - 1;
		last_character = parameter[index];
		while(last_character == ' ' && index > 0)
		{
			index--;
			last_character = parameter[index];
		}
	}
	strcpy(command, parameter);
	char * word = strtok_r(command, " ", &save_command);
	if(last_character == '&')
		system_command(parameter);
	else if(strcmp("cd", word) == 0)
		change_dir(parameter);
	else if(strcmp("echo", word) == 0)
		echo(parameter);
	else if(strcmp("pwd", word) == 0)
	{
		char str[1024];
		getcwd(str, sizeof(str));
		word = strtok_r(NULL, " ", &save_command);
		if(!(word == NULL))
		{
			word = strtok_r(NULL, " ", &save_command);
			output_to_file(str, word);
			return;
		}
		printf("%s\n", str);
	}
	else if(strcmp("ls", word) == 0)
		ls(parameter);
	else if(strcmp("quit", word) == 0)
		status = 0;
	else if(strcmp("history", word) == 0)
		display_history(parameter);
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