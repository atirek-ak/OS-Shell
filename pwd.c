#include "headers.h"

void get_pwd()
{
	if(strcmp(home, path) == 0)
	{
		displayed_path[0] = '~';
		displayed_path[1] = '\0';
	}
	else
	{
		int len = strlen(home);
		char str[1024];
		for(int i=len, j=1; i<strlen(path);i++, j++)
			str[j] = path[i];
		str[strlen(path) - len + 1] = '\0';
		str[0] = '~';
		for(int i=0;i<strlen(str);i++)
			displayed_path[i] = str[i];
	}
}