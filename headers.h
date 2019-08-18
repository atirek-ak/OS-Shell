//Standard C libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/wait.h>
#include <fcntl.h> 

//Global variables
char user_name[100], system_name[100];
char original_path[1024], path[1024];

//Functions
//main.c
void initiate();
void main_loop();

//pwd.c
void get_pwd();
