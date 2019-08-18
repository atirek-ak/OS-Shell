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
	else
	{
		int len = strlen(original_path);
		char str[1024];
		for(int i=len, j=1; i<strlen(path);i++, j++)
			str[j] = path[i];
		str[strlen(path) - len + 1] = '\0';
		str[0] = '~';
		for(int i=0;i<strlen(str);i++)
			path[i] = str[i];
	}
}