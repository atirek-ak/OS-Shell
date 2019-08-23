#include "headers.h"

char * history[20];
int pointer = 0, size = 0;


void store_in_history(char * command)
{
	history[pointer] = command;
	pointer++;
	if(pointer == 20)
		pointer = 0;
	size++;
	if(size == 21)
		size--;
}

void display_history(char * command)
{
	char * save_command;
	char command_copy[100];
	strcpy(command_copy, command);
	char * token = strtok_r(command_copy, " ", &save_command);
	token = strtok_r(NULL, " ", &save_command);
	int start = pointer, end;
	if(token != NULL)
		sscanf(token, "%d", &end);
	else 
		end = size;
	if(end > size)
		end = size;
	start -= end;
	if(start < 0)
		start += size;		 
	while(end)
	{
		if(start == size)
			start = 0;
		printf("%s\n", history[start]);
		start++;
		end--;
	}
}