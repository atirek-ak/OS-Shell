#include "headers.h"

void output_to_file(char * output, char * file)
{
	FILE * file_pointer = fopen(file, "w");
	if(file_pointer == NULL)
    {
    	printf("Error!");
    	exit(1);
   	}
   	output[strlen(output) - 1] = '\0';
   	fprintf(file_pointer,"%s", output);
    fclose(file_pointer);
}