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
char home[1024], path[1024], displayed_path[1024];

//Functions
//main.c
void initiate();
void main_loop();

//pwd.c
void get_pwd();

//readInput.c
char * get_input();

//processInput.c
void process_input(char * input);
void process_single_command(char * parameter);

//cd.c
void change_dir(char * command);