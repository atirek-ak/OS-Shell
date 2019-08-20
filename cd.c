#include "headers.h"

void change_dir(char * command)
{
	char * save_command;
	// printf("%s\n", command);
	char * parameter = strtok_r(command, " ", &save_command);
	parameter = strtok_r(NULL, " ", &save_command);
	// printf("%s\n", parameter);
	if(parameter == NULL || strcmp(parameter,"~") == 0)
	{
		int returned_value = chdir(home);
		// printf("Null parameter\n");
	}
	else if(chdir(parameter) == -1)
		perror("Error");
	return;
}