#include "headers.h"

void process_input(char * input)
{
	char * save_single_command;
	char * command = strtok_r(input,";",&save_single_command);
	while(command != NULL)
	{
		// printf("%s\n", command);
		command = strtok_r(NULL,";",&save_single_command);
	}
}