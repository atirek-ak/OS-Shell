#include "headers.h"


void main_loop()
{
	do
	{
		//Print directory & user details; Change directory
		getcwd(path, sizeof(path));
		get_pwd();
		printf("%s@%s:%s ", user_name, system_name, displayed_path);
		//Input
		char * input;
		input = get_input();
		store_in_history(input);
		process_input(input);
		//check background processes
		check_background_processes();
	}while(shell_running);
	return;
}

void initiate()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	getlogin_r(user_name, sizeof(user_name));
	gethostname(system_name, sizeof(system_name));
	getcwd(home, sizeof(home));
	number_of_processes = 0;
	main_loop();
	return;
}

int main(int argc, char  *argv[])
{
	shell_running = 1;
	initiate();
	return EXIT_SUCCESS;
}