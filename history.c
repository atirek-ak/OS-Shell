#include "headers.h"

void store_in_history(char * command)
{
	FILE * fPtr;
	fPtr = fopen("./history.txt", "a");
	if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

	if(strlen(command) == 0)
		return; 
	char command_copy[100];
	strcpy(command_copy, command);
	strcat(command_copy, "\n");
	fputs(command_copy, fPtr);
	fclose(fPtr);
	return;
}

void display_history(char * command)
{
	FILE * fp;
	int count = 0;
	char c;
	fp = fopen("./history.txt", "r"); 
    if (fp == NULL) 
    { 
        printf("Could not open file"); 
        return; 
    } 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // 
            count = count + 1; 
    close(fp);    
	char * save_command;
	char command_copy[100];
	strcpy(command_copy, command);
	char * token = strtok_r(command_copy, " ", &save_command);
	token = strtok_r(NULL, " ", &save_command);
	int start, end;
	if(token != NULL)
		sscanf(token, "%d", &end);
	else 
		end = count;
	if(end > count)
		end = count;
	if(end > 20)
		end = 20;
	int difference = count - end, index = 0;
	fp = fopen("./history.txt", "r");
	char * line;
	int i = 0; 
	for (c = getc(fp); c != EOF; c = getc(fp)) 
	{
        if(c == '\n') 
            index = index + 1; 
        if(index >= difference)
        {
        	line[i] = c;
        	i++;
        	if(c == '\n')
        	{
        		line[i] = '\0';
        		if(i != 1)
        			printf("%s", line);
        		i=0;
        	}
        }
	}
	close(fp);	
}