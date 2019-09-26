#include "headers.h"

void echo(char * command)
{
	char * save_command;
	char command_copy[1000];
	strcpy(command_copy, command);
	char * parameter = strtok_r(command_copy, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	while(parameter)
	{
		printf("%s ", parameter);
		parameter = strtok_r(NULL, " ", &save_command);
	}
	printf("\n");
	return;
}
