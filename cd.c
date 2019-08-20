#include "headers.h"

void change_dir(char * command)
{
	char * save_command;
	char command_copy[1000];
	strcpy(command_copy, command);
	// printf("%s\n", command);
	char * parameter = strtok_r(command, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	// printf("%s\n", parameter);
	if(parameter == NULL || strcmp(parameter,"~") == 0)
	{
		int returned_value = chdir(home);
		// printf("Null parameter\n");
	}
	else if(strcmp(parameter,".") == 0)
		return;
	else if(strcmp(parameter,"..") == 0)
	{
		// printf("Yes\n");
		if(strcmp(home, path) == 0)
			printf("Error: cannot go below home directory\n");
		else
		{
			int i;
			for(i=strlen(path)-1;path[i]!= '/';i--)
			path[i] = '\0';
			chdir(path);
		}
	}
	else if(chdir(parameter) == -1)
		perror("Error");
	return;
}