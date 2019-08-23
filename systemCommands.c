#include "headers.h"

typedef struct {
	int id;
	char * name;
}process;

process processes[100];
int number_of_processes = 0;

void start_process(char * command[])
{
	// for(int i=0;command[i] != NULL;i++)
		// printf("%s\n", command[i]);
	pid_t child_id;
	child_id = fork();
	// printf("**%d\n", child_id);
	if(child_id < 0)
	{
		perror("Error:");
		_exit(0);
	}
	else if(child_id == 0)
		execvp(command[0],command);
	else
		wait(NULL);
	return;
}

void start_background_process(char * command[])
{
	// for(int i=0;command[i] != NULL;i++)
		// printf("%s\n", command[i]);
	// printf("No\n");
	pid_t child_id;
	child_id = fork();
	// printf("**%d\n", child_id);
	if(child_id < 0)
	{
		perror("Error:");
		_exit(0);
	}
	else if(child_id == 0)
		execvp(command[0],command);
	else if(child_id > 0)
	{
		processes[number_of_processes].name = command[0];
		processes[number_of_processes].id = child_id;
		number_of_processes++;
	}
	// printf("%d\n", number_of_processes);
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
		// printf("%s\n", token);
		input[i] = token;
		token = strtok_r(NULL, " ", &save_command);
		i++;
	}
	input[i] = NULL;
	if(input[i-1][0] == '&')
	{
		input[i-1] = NULL;
		start_background_process(input);
	}
	else
	{
		// printf("%s\n", );
		start_process(input);
	}
}

void check_background_processes()
{
	// printf("%d\n", number_of_processes);
	int temp_number_of_processes = 0;
	process temp_processes[100];
	for(int i=0;i<number_of_processes;i++)
	{
		int status;
		if(waitpid(processes[i].id, &status, WNOHANG) != 0)
			printf("%s with pid %d exited normally\n", processes[i].name, processes[i].id);
		else
		{
			temp_processes[temp_number_of_processes].name = processes[i].name;
			temp_processes[temp_number_of_processes].id = processes[i].id;
			temp_number_of_processes++;
			// printf("No\n");
		}
	}
	number_of_processes = temp_number_of_processes;
	for(int i=0;i<number_of_processes;i++)
	{
		processes[i].name = temp_processes[i].name;
		processes[i].id = temp_processes[i].id;
	}
}