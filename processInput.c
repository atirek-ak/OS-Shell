#include "headers.h"

char * refine_parameter(char * parameter)
{
	char * result = malloc(4096 * sizeof(char));
	int flag = 1;
	int i = 0;
	char command[1000];
	char * save_command;
	strcpy(command, parameter);
	char * word = strtok_r(command, " ", &save_command);
	while(word)
	{
		if(strcmp(word,">") != 0 && strcmp(word,"|") != 0 && strcmp(word,"<") != 0 && strcmp(word,">>") != 0)
		{
			if(flag)
			{
				strcpy(result, word);
				strcat(result, " ");
				flag = 0;
			}
			else
			{
				strcat(result, word);
				strcat(result, " ");
			}
		}
		else
			word = strtok_r(NULL, " ", &save_command);
		word = strtok_r(NULL, " ", &save_command);
	}
	return result;
}

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
	// printf("Yes\n");
	char * refined_parameter = refine_parameter(parameter);
	// printf("%s\n", refined_parameter);
	redirect_output = 0;
	redirect_input = 0;
	int default_output = dup(1);
	int default_input = dup(0);
	char * word = strtok_r(command, " ", &save_command);
	char * arguments = strtok_r(NULL, " ", &save_command);
	while(arguments)
	{
		if(strcmp(arguments,">") == 0)
		{
			char * file_name = strtok_r(NULL, " ", &save_command);
			redirect_output_descriptor = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(redirect_output_descriptor < 0)
			{
				perror("Error:");
				break;
			}
			dup2(redirect_output_descriptor, 1);
			close(redirect_output_descriptor);
			redirect_output = 1;
		}
		else if(strcmp(arguments,">>") == 0)
		{
			char * file_name = strtok_r(NULL, " ", &save_command);
			redirect_output_descriptor = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if(redirect_output_descriptor < 0)
			{
				perror("Error:");
				break;
			}
			dup2(redirect_output_descriptor, 1);
			close(redirect_output_descriptor);
			redirect_output = 1;
		}
		else if(strcmp(arguments,"<") == 0)
		{
			char * file_name = strtok_r(NULL, " ", &save_command);
			redirect_input_descriptor = open(file_name, O_RDONLY, 0644);
			if(redirect_input_descriptor < 0)
			{
				perror("Error:");
				break;
			}
			dup2(redirect_input_descriptor, 0);
			close(redirect_input_descriptor);
			redirect_input = 1;
		}
		arguments = strtok_r(NULL, " ", &save_command);
	}
	if(last_character == '&')
		system_command(refined_parameter);
	else if(strcmp("cd", word) == 0)
		change_dir(refined_parameter);
	else if(strcmp("echo", word) == 0)
		echo(refined_parameter);
	else if(strcmp("pwd", word) == 0)
	{
		char str[1000];
		getcwd(str, sizeof(str));
		printf("%s\n", str);
	}
	else if(strcmp("ls", word) == 0)
		ls(refined_parameter);
	else if(strcmp("quit", word) == 0)
		status = 0;
	else if(strcmp("history", word) == 0)
		display_history(refined_parameter);
	else if(strcmp("pinfo", word) == 0)
		pinfo(refined_parameter);
	else
		system_command(refined_parameter);
	if(redirect_input)
	{
		dup2(default_input, 0);
		close(default_input);
		redirect_input = 0;
	}
	if(redirect_output)
	{
		dup2(default_output, 1);
		close(default_output);
		redirect_output = 0;
	}
	return;
}

void process_pipe(char * command)
{
	// if (pipe(fd1)==-1) 
    // { 
        // perror("Pipe failed:");
        // return; 
    // } 
    // if (pipe(fd2)==-1) 
    // { 
        // perror("Pipe failed:");
        // return; 
    // } 
    // pid_t pid = fork();
    piping_write = open("randadfafom.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    piping_read = open("randadfafom.txt", O_RDONLY, 0644);
	char command_copy[1000];
	int flag = 0;
	char * save_command;
	strcpy(command_copy, command);
	char * word = strtok_r(command_copy, "|", &save_command);
	char * next_word = strtok_r(NULL, "|", &save_command);
	int default_output = dup(1);
	int default_input = dup(0);
	// if(pid < 0)
	// {
		// perror("Fork failed:");
		// return;
	// }
	// else if(pid > 0)

	while(1)
	{
		if(flag)
		{
			dup2(piping_read, 0);
		}
		if(next_word)
		{
			dup2(piping_write, 1);
		}
		process_single_command(word);
		dup2(default_output, 1);
		dup2(default_input, 0);
		if(!next_word)
		{
			close(piping_write);
			close(piping_read);
			break;
		}
		word = next_word;
		next_word = strtok_r(NULL, "|", &save_command);
		flag = 1;
	}
}

void process_input(char * input)
{
	char * save_single_command;
	char input_copy[1000];
	strcpy(input_copy, input);
	char * command = strtok_r(input_copy, ";", &save_single_command);
	redirect_output_descriptor = NULL;
	redirect_input_descriptor = NULL;
	while(command != NULL && status)
	{
		process_pipe(command);
		command = strtok_r(NULL,";",&save_single_command);
	}
	return;
}