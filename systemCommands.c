#include "headers.h"
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
		strcpy(processes[number_of_processes].name, command[0]);
		processes[number_of_processes].id = child_id;
		processes[number_of_processes].status = 1;
		number_of_processes++;
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
	// int temp_number_of_processes = 0;
	// process temp_processes[1024];
	for(int i=0;i<number_of_processes;i++)
	{
		int status;
		if(waitpid(processes[i].id, &status, WNOHANG) != 0 && processes[i].status == 1)
		{
			printf("%s with pid %d exited normally\n", processes[i].name, processes[i].id);
			processes[i].status = 0;
		}
	}
		// temp_processes[temp_number_of_processes].name = processes[i].name;
		// temp_processes[temp_number_of_processes].id = processes[i].id;
		// temp_number_of_processes++;
	// }
	// number_of_processes = temp_number_of_processes;
	// for(int i=0;i<number_of_processes;i++)
	// {
		// processes[i].name = temp_processes[i].name;
		// processes[i].id = temp_processes[i].id;
	// }
}

void jobs_function()
{
	for(int i=number_of_processes - 1;i >= 0;i--)
	{
		if(processes[i].status)
			printf("[%d] Running %s [%d]\n", number_of_processes-i, processes[i].name, processes[i].id);
		else	
			printf("[%d] Stopped %s [%d]\n", number_of_processes-i, processes[i].name, processes[i].id);
	}
	// char proc[100];
	// proc[0]='\0';
	// strcpy(proc,"/proc/");
	// char string_id[10];
	// sprintf(string_id,"%lld",backid[i]);
	// strcat(proc,string_id);
	// strcat(proc,"/stat");
	// FILE * statfile;
	// if(!(statfile = fopen(proc,"r")))
		// return;
	// long long int pid;
	// char status;
	// char name[20];
	// fscanf(statfile,"%lld %s %c",&pid,name,&status);
	// fclose(statfile);
	// printf("%s[%lld]\n",name,backid[i]);
}

void kjob_function(char * command)
{
	char * input[100];
	char command_copy[100];
	char * save_command;
	strcpy(command_copy, command);
	char * token = strtok_r(command_copy, " ", &save_command);
	token = strtok_r(NULL, " ", &save_command);
	int job_number = atoi(token);
	token = strtok_r(NULL, " ", &save_command);
	int signal = atoi(token);
	for(int i=0;i<number_of_processes;i++)
	{
		if(job_number == number_of_processes-i)
		{
			kill(processes[i].id, signal);
			printf("%s with pid %d killed\n", processes[i].name, processes[i].id);
			processes[i].status = 0;
			return;
		}
	}
}

void overkill_function(char * command)
{
	char * input[100];
	char command_copy[100];
	char * save_command;
	strcpy(command_copy, command);
	char * token = strtok_r(command_copy, " ", &save_command);
	token = strtok_r(NULL, " ", &save_command);
	int job_number = atoi(token);
	token = strtok_r(NULL, " ", &save_command);
	int signal = atoi(token);
	for(int i=0;i<number_of_processes;i++)
	{
		if(job_number == number_of_processes-i)
		{
			kill(processes[i].id, signal);
			printf("%s with pid %d killed\n", processes[i].name, processes[i].id);
			processes[i].status = 0;
			return;
		}
	}
}

void fg_function(char * command)
{
	char * input[100];
	char command_copy[100];
	char * save_command;
	strcpy(command_copy, command);
	char * token = strtok_r(command_copy, " ", &save_command);
	token = strtok_r(NULL, " ", &save_command);
	int job_number = atoi(token);
	for(int i=0;i<number_of_processes;i++)
	{
		if(job_number == number_of_processes-i)
		{
			kill(processes[i].id, SIGCONT);
			processes[i].status = 1;
			waitpid(-1,NULL,WUNTRACED);
			return;
		}
	}
}

void bg_function(char * command)
{
	char * input[100];
	char command_copy[100];
	char * save_command;
	strcpy(command_copy, command);
	char * token = strtok_r(command_copy, " ", &save_command);
	token = strtok_r(NULL, " ", &save_command);
	int job_number = atoi(token);
	for(int i=0;i<number_of_processes;i++)
	{
		if(job_number == number_of_processes-i)
		{
			kill(processes[i].id, SIGCONT);
			processes[i].status = 1;
			return;
		}
	}
}