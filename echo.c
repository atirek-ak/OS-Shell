#include "headers.h"

char * filter_parameter(char * parameter)
{
	int j=0;
	char c;
	char * filtered_parameter = malloc(sizeof(char) * 1024);
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
	FILE * file_pointer;
	char * file_name;
	char * save_command;
	char command_copy[1000];
	strcpy(command_copy, command);
	char * parameter = strtok_r(command_copy, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	while(parameter)
	{
		char * filtered_parameter = filter_parameter(parameter);
		printf("%s ", filtered_parameter);
		parameter = strtok_r(NULL, " ", &save_command);
	}
	printf("\n");
	return;
}
