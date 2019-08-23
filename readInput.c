#include "headers.h"

char * get_input()
{
	char * buffer = malloc(sizeof(char) * 1024);
	int size = 1024, i=0;
	char c;
	if(!buffer)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		c = getchar();
		if(c == EOF)
		{
			buffer[i++] = '\0';
			return buffer;
		}
		else if(c == '\n')
		{
			buffer[i++] = '\0';
			return buffer;
		}
		else
			buffer[i++] = c;
		if(i >= 1024)
		{
			size += 1024;
			buffer = realloc(buffer, size);
			if(!buffer)
			{
				perror("Error");
				exit(EXIT_FAILURE);
			}
		}
	}
}
