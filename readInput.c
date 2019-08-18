#include "headers.h"

#define BUFFER_SIZE 1024

char * getInput()
{
	int size = BUFFER_SIZE;
	char * buffer = malloc(sizeof(char) * BUFFER_SIZE);
	int i=0;
	if(!buffer)
	{
		printf("Could not load buffer\n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		char c = getchar();
		if(c == EOF || c == '\n')
		{
			buffer[i++] = '\0';
			return buffer;
		}
		else
		{
			buffer[i++] = c;
		}
		if(i >= BUFFER_SIZE)
		{
			size += BUFFER_SIZE;
			buffer = realloc(buffer, size);
			if(!buffer)
			{
				printf("Could not load buffer\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
