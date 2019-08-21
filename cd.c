#include "headers.h"

void change_dir(char * command)
{
	char * save_command;
	char command_copy[1000];
	strcpy(command_copy, command);
	char * parameter = strtok_r(command_copy, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	if(parameter == NULL || strcmp(parameter,"~") == 0)
	{
		int i;
		for(i=0;i<strlen(home);i++)
			path[i] = home[i];
		path[i] = '\0';		
		int returned_value = chdir(home);
	}
	else if(strcmp(parameter,".") == 0)
		return;
	else if(strcmp(parameter,"..") == 0)
	{
		// printf("%s\n", path);
		int i;
		for(i=strlen(path)-1;path[i]!= '/';i--){;}
		path[i] = '\0';
		chdir(path);
		// printf("%s\n", path);
	}
	else if(chdir(parameter) == 0)
	{
		//update path variable
		// printf("%s\n", path);
		path[strlen(path)] = '/';
		int i = strlen(path);
		for(int j=0;j < strlen(parameter);i++, j++)
			path[i] = parameter[j];
		path[i] = '\0';
		// printf("%s\n", path);
	}
	else	
		perror("Error");
	// get_pwd();
	return;
}