#include "headers.h"

//function to calculate Relative path
void find_relative_path(char cwd[],char rwd[])
{
	int i, flag;
	if(strlen(cwd) < strlen(home))
	{
		if(strlen(cwd) == 1 && cwd[0] == '/')
		{
			strcpy(rwd,"/");
			return;
		}
		char copy_cwd[1000], cur_dir[1000];
		strcpy(copy_cwd,cwd);
		for(char * token = strtok(copy_cwd, "/"); token != NULL; token = strtok(NULL,"/"))
		{
			strcpy(cur_dir, token);
		}
		rwd[0]='/';
		strcpy(&rwd[1], cur_dir);
	}
	else
	{
		for(i=0; i < strlen(home); i++)
		{
			if(home[i] != cwd[i])
			{
				flag = 1;
				break;
			}			
		}
		if(flag != 1)
		{
			strcpy(rwd, "~");
			strcpy(&rwd[1], &cwd[i]);
			
		}
		else
		{
			char copy_cwd[1000], cur_dir[1000];
			strcpy(copy_cwd,cwd);
			char * token = strtok(copy_cwd, "/");
			while(token != NULL)
			{
				strcpy(cur_dir, token);
				token = strtok(NULL,"/");
			}
			rwd[0] = '/';
			strcpy(&rwd[1], cur_dir);
		}
	}
	
}

//main pinfo function
void pinfo(char input[])
{
	char * saveptr;
	char base_directory[100];
	char stat_directory[100];
	FILE * statfile;
	int pid, size;
	char status, name[20], rwd[100], path[100];
	// proc[0]='\0';
	strcpy(base_directory,"/proc/");
	char * token = strtok_r(input, " ", &saveptr);
	token = strtok_r(NULL, " ", &saveptr);
	if(token == NULL)
		strcat(base_directory, "self");
	else
		strcat(base_directory, token);
	strcpy(stat_directory, base_directory);
	strcat(stat_directory , "/stat");
	if(!(statfile = fopen(stat_directory, "r")))
	{
		perror("Error:\n");
		return;
	}
	fscanf(statfile,"%d %s %c",&pid,name,&status);
	printf("pid -- %d\n",pid);
	printf("Process Status -- %c\n",status);
	strcpy(stat_directory, base_directory);
	fclose(statfile);
	strcat(stat_directory, "/statm");
	if(!(statfile = fopen(stat_directory,"r")))
		printf("Error finding info on process : %d\n",getpid());
	//scanning size in virtual memory
	fscanf(statfile,"%d",&size);
	fclose(statfile);
	printf("%d {Virtual Memory}\n",size);
	strcpy(stat_directory,base_directory);
	strcat(stat_directory,"/exe");
	ssize_t path_len = readlink(stat_directory, path, sizeof(path));
    if(path_len < 0) 
    {
        printf("Error reading symbolic link %s\n", stat_directory);
        return;
    }
    find_relative_path(path, rwd);
    printf("%s\n", rwd);
	

}


