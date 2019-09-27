#include "headers.h"

void setenv_function(char * command)
{
	char * save_command;
	char command_copy[1000], variable[1000], value[1000];
	strcpy(command_copy, command);
	char * parameter = strtok_r(command_copy, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	if(!parameter)
		perror("Too less arguments");
	else
		strcpy(variable, parameter);
	parameter = strtok_r(NULL, " ", &save_command);
	if(!parameter)
	{
		value[0]=' ';
		value[1]='\0';
	}
	else
		strcpy(value, parameter);
	parameter = strtok_r(NULL, " ", &save_command);
	if(parameter)
		perror("Too many arguments");
	if(setenv(variable, value, 1) != 0)
		perror("Error:");
	else
		printf("Environment variable %s set to value %s successfully\n", variable, value	);
}

void unsetenv_function(char * command)
{
	char * save_command;
	char command_copy[1000], variable[1000];
	strcpy(command_copy, command);
	char * parameter = strtok_r(command_copy, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	if(!parameter)
		perror("Too less arguments");
	else
		strcpy(variable, parameter);
	parameter = strtok_r(NULL, " ", &save_command);
	if(parameter)
		perror("Too many arguments");
	if(unsetenv(variable) != 0)
		perror("Error:");
	else
		printf("Environment variable %s deleted.\n", variable);
}