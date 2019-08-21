#include "headers.h"

DIR * directory_stream;
struct dirent * file;

void open_directory(char * directory)
{
	if(directory == NULL)
		directory_stream = opendir(".");
	else
	{
		directory_stream = opendir(directory);
		if(directory_stream == NULL)
		{
			perror("Error:");
			return;
		}
	}
}


void without_flag_l(int choice, char * directory)
{
	open_directory(directory);
	if(directory_stream == NULL)
		return;
	file = readdir(directory_stream);
	while(file != NULL)
	{
		if(choice % 4 == 0 && file->d_name[0] != '.')
		{
			printf("%s\n", file->d_name);
		}	
		else if(choice % 4 == 1)
		{
			printf("%s\n", file->d_name);
		}
		file = readdir(directory_stream);
	}
}

void flag_l(int choice, char * directory)
{
	open_directory(directory);
	if(directory_stream == NULL)
		return;	
	file = readdir(directory_stream);
	while(file != NULL)
	{
		if(choice % 4 == 2 && file->d_name[0] != '.')
		{
			printf("%s\n", file->d_name);
		}	
		else if(choice % 4 == 3)
		{
			printf("%s\n", file->d_name);
		}
		file = readdir(directory_stream);
	}
}

void ls(char * command)
{
	char * save_command;
	char command_copy[1000];
	strcpy(command_copy, command);
	// printf("No\n");
	char * parameter = strtok_r(command_copy, " ", &save_command);
	char * previours_parameter;
	parameter = strtok_r(NULL, " ", &save_command);
	int flag_choice = 0;
	/*
		0 = flagless
		1 = -a
		2 = -l
		3 = -la
		4 = flagless with directory
		5 = -a with directory
		6 = -l with directory
		7 = -la with directory
	*/
	while(parameter != NULL)
	{
		if(strcmp(parameter, "-l") == 0)
		{
			if(flag_choice == 0)
				flag_choice = 2;
			else
				flag_choice = 3;
		}
		else if(strcmp(parameter, "-a") == 0)
		{
			if(flag_choice == 0)
				flag_choice = 1;
			else
				flag_choice = 3;
		}
		else if(strcmp(parameter, "-la") == 0 || strcmp(parameter, "-al") == 0)
			flag_choice = 3;
		else
			flag_choice += 4;
		previours_parameter = parameter;
		parameter = strtok_r(NULL, " ", &save_command);
	}
	switch(flag_choice)
	{
		case 0:
		case 1:
			without_flag_l(flag_choice, NULL);
			break;
		case 2:
		case 3:
			flag_l(flag_choice, NULL);
			break;
		case 4:
		case 5:
			without_flag_l(flag_choice, previours_parameter);
			break;
		case 6:
		case 7:
			flag_l(flag_choice, previours_parameter);
			break;
	}
}