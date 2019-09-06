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

//Global variables
char user_name[100], system_name[100];
char home[1024], path[1024], displayed_path[1024];
int status;

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

//echo.c
void echo(char * command);
char * filter_parameter(char * parameter);

//ls.c
void ls(char * command);
void flag_l(int choice, char * directory, char * target_file);
void without_flag_l(int choice, char * directory, char * target_file);
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

//history.c
void store_in_history(char * command);
void display_history(char * command);

//pinfo.c
void find_relative_path(char cwd[],char rwd[]);
void pinfo(char input[]);

//output.c
void output_to_file(char * output, char * file);