#include "headers.h"

char * filter_parameter(char * parameter)
{
	int j=0;
	char c;
	char * filtered_parameter = malloc(sizeof(char) * 1024);
	// printf("%d\n", strlen(parameter));
	for(int i=0; i<strlen(parameter);i++)
	{
		c = parameter[i];
		if(!(c == '\"' || c == '\''))
		{
			filtered_parameter[j++] = c;
		}
	}
	return filtered_parameter;
}

void echo(char * command)
{
	int output_redirect = 0;
	char file_name[100];
	char * save_command;
	char command_copy[1000], command_copy2[100];
	strcpy(command_copy, command);
	char * parameter = strtok_r(command_copy, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	while(parameter)
	{
		if(strcmp(parameter, ">") == 0)
		{
			output_redirect = 1;
			parameter = strtok_r(NULL, " ", &save_command);
			parameter = strtok_r(NULL, " ", &save_command);
			file_name = strtok_r(NULL, " ", &save_command);
			dup2(1, file_name);
		}
		parameter = strtok_r(NULL, " ", &save_command);
	}
	strcpy(command_copy2, command);
	parameter = strtok_r(command_copy2, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	while(parameter)
	{
		char * filtered_parameter = filter_parameter(parameter);
		printf("%s ", filter_parameter);
		parameter = strtok_r(NULL, " ", &save_command);
	}
	if(output_redirect)
		dup2(file_name, 1);		
	return;
}
