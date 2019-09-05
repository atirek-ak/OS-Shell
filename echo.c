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
	char * save_command;
	char command_copy[1000];
	strcpy(command_copy, command);
	char * parameter = strtok_r(command_copy, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	char output[1024];
	// printf("%d\n", strlen(output));
	int flag = 1;
	while(parameter)
	{
		char * filtered_parameter = filter_parameter(parameter);
			// printf("ENcountered\n");
		// printf("%s\n", filtered_parameter);
		if(strcmp(filtered_parameter, ">") == 0)
		{
			parameter = strtok_r(NULL, " ", &save_command);
			output_to_file(output, parameter);
			return;
		}
		if(flag)
		{
			strcpy(output, filtered_parameter);
			flag = 0;
		}
		else
			strcat(output, filtered_parameter);
		// printf("%s\n", output);
		strcat(output, " ");
		// printf("%s\n", output);
		parameter = strtok_r(NULL, " ", &save_command);
	}
	printf("%s\n", output);
	output[0] = '\0';
	return;
}
