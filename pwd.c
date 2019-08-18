#include "headers.h"


// extern char original_path[1024];
// extern char path[1024];



void get_pwd()
{
	if(strcmp(original_path, path) == 0)
	{
		path[0] = '~';
		path[1] = '\0';
	}
}