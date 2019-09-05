#include "headers.h"

DIR * directory_stream;
struct dirent * file;

void open_directory(char * directory)
{
	if(directory == NULL)
		directory_stream = opendir(".");
	else
	{
		directory_stream = opendir(directory);
		if(directory_stream == NULL)
		{
			perror("Error:");
			return;
		}
	}
}


void without_flag_l(int choice, char * directory)
{
	char output[1024*1024];
	int flag = 1;
	open_directory(directory);
	if(directory_stream == NULL)
		return;
	file = readdir(directory_stream);
	while(file != NULL)
	{
		if((choice % 4 == 0 && file->d_name[0] != '.') || choice % 4 == 1)
		{
			if(flag)
			{
				flag = 0;
				strcpy(output, file->d_name);
			}
			else
				strcat(output, file->d_name);
			strcat(output, "\n");
			// printf("%s\n", file->d_name);
		}
		file = readdir(directory_stream);
		// printf("%s\n", file);
		if(file == NULL)
			break;
		if(strcmp(file, ">") == 0)
		{
			file = readdir(directory_stream);
			printf("%s\n", file);
			output_to_file(output, file);
			return;
		}
	}
	printf("%s", output);
	output[0] = '\0';
}

void flag_l(int choice, char * directory)
{
	open_directory(directory);
	if(directory_stream == NULL)
		return;	
	file = readdir(directory_stream);
	while(file != NULL)
	{
		if(!((choice % 4 == 2 && file->d_name[0] != '.') || choice % 4 == 3))
		{
			file = readdir(directory_stream);
			continue;
		}
		struct stat file_details;
		stat(file->d_name,&file_details);
		//print file permissions
		printf( (S_ISDIR(file_details.st_mode)) ? "d" : "-");
    	printf( (file_details.st_mode & S_IRUSR) ? "r" : "-");
    	printf( (file_details.st_mode & S_IWUSR) ? "w" : "-");
    	printf( (file_details.st_mode & S_IXUSR) ? "x" : "-");
    	printf( (file_details.st_mode & S_IRGRP) ? "r" : "-");
    	printf( (file_details.st_mode & S_IWGRP) ? "w" : "-");
    	printf( (file_details.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (file_details.st_mode & S_IROTH) ? "r" : "-");
    	printf( (file_details.st_mode & S_IWOTH) ? "w" : "-");
    	printf( (file_details.st_mode & S_IXOTH) ? "x\t" : "-\t");
    	//number of hard links to the file
  		printf(" %3d", (int)file_details.st_nlink);
    	//owner
    	struct passwd * uname = getpwuid(file_details.st_uid);
  		printf(" %s",uname->pw_name);
    	//group
  		struct group * ugroup = getgrgid(file_details.st_gid);
  		printf(" %s",ugroup->gr_name);
    	//number of bytes
  		printf(" %10d", (int)file_details.st_size);
    	//time lasst modified & file name
		struct tm *time;
		char datestring[256];
    	time = localtime(&file_details.st_mtime);
    	strftime(datestring, sizeof(datestring), "%b %d %H:%M", time);
    	printf(" %s %s\n", datestring, file->d_name);
		file = readdir(directory_stream);
	}
}

void ls(char * command)
{
	char * save_command;
	char command_copy[1000];
	strcpy(command_copy, command);
	char * parameter = strtok_r(command_copy, " ", &save_command);
	char * previours_parameter;
	parameter = strtok_r(NULL, " ", &save_command);
	int flag_choice = 0;
	/*
		0 = flagless
		1 = -a
		2 = -l
		3 = -la
		4 = flagless with directory
		5 = -a with directory
		6 = -l with directory
		7 = -la with directory
	*/
	while(parameter != NULL)
	{
		if(strcmp(parameter, "-l") == 0)
		{
			if(flag_choice == 0)
				flag_choice = 2;
			else
				flag_choice = 3;
		}
		else if(strcmp(parameter, "-a") == 0)
		{
			if(flag_choice == 0)
				flag_choice = 1;
			else
				flag_choice = 3;
		}
		else if(strcmp(parameter, "-la") == 0 || strcmp(parameter, "-al") == 0)
			flag_choice = 3;
		else
			flag_choice += 4;
		previours_parameter = parameter;
		parameter = strtok_r(NULL, " ", &save_command);
	}
	switch(flag_choice)
	{
		case 0:
		case 1:
			without_flag_l(flag_choice, NULL);
			break;
		case 2:
		case 3:
			flag_l(flag_choice, NULL);
			break;
		case 4:
		case 5:
			without_flag_l(flag_choice, previours_parameter);
			break;
		case 6:
		case 7:
			flag_l(flag_choice, previours_parameter);
			break;
	}
}