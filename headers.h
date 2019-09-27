//Standard C libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <ctype.h>
#include <locale.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <errno.h>
#include <signal.h>

typedef struct {
	int id;
	char name[100];
	int status;
}process;

//Global variables
process processes[1024];
char user_name[100], system_name[100];
char home[1024], path[1024], displayed_path[1024];
int status;
int redirect_output, redirect_input;
char * redirect_output_descriptor, redirect_input_descriptor, piping_write, piping_read;
int fd1[2], fd2[2];

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
char * refine_parameter(char * parameter);

//cd.c
void change_dir(char * command);

//echo.c
void echo(char * command);

//ls.c
void ls(char * command);
void flag_l(int choice, char * directory);
void without_flag_l(int choice, char * directory);
void open_directory(char * directory);

//processInput.c
void system_command(char * command);
void start_background_process(char * command[]);
void start_process(char * command[]);

//systemCommands.c
void start_process(char * command[]);
void start_background_process(char * command[]);
void system_command(char * command);
void check_background_processes();
void jobs();

//history.c
void store_in_history(char * command);
void display_history(char * command);

//pinfo.c
void find_relative_path(char cwd[],char rwd[]);
void pinfo(char input[]);

//setenv.c
void setenv_function(char * command);
void unsetenv_function(char * command);