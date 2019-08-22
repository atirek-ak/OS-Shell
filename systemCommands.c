#include "headers.h"

long long int backid[100];

void start_process(char * command[])
{
	pid_t child_id;
	child_id = fork();
	if(child_id==0)
	{
		execvp(command[0],command);
		perror("Error:");
		_exit(0);
	}
	else
		wait(NULL);
	return;
}

void start_background_process(char * command[])
{
	pid_t child_id;
	child_id = fork();
	if(child_id == 0)
	{
		execvp(command[0],command);
		perror("Error:");
		_exit(0);
	}
	int i;
	for(i=0; i<100; i++)
	{
		if(backid[i]==-1)
		{
			backid[i]=child_id;
			break;
		}
	}
	return;
}

void system_command(char * command)
{
	char * input[100];
	char command_copy[100];
	char * save_command;
	strcpy(command_copy, command);
	char * token = strtok_r(command_copy, " ", &save_command);
	int i = 0;
	while(token != NULL)
	{
		input[i] = token;
		token = strtok_r(NULL, " ", &save_command);
		i++;
	}
	if(input[i-1][strlen(input[i-1]) - 1] == '&')
	{
		input[i-1][strlen(input[i-1]) - 1] = '\0';
		start_background_process(input);
	}
	else
	{
		printf("%s\n", );
		start_process(input);
	}
}