#include "headers.h"


void sig_handle(int signo){
	if(signo==SIGINT)
		fprintf(stderr,"\n");
	else if (signo == SIGTSTP)
	{
		for(int i=0;i<number_of_processes;i++)
		{
			if(processes[i].id == foreground_process_id)
				processes[i].status = 0;
		}
	}
}
void main_loop()
{
	do
	{
		//Print directory & user details; Change directory
		signal(SIGINT, sig_handle);
		// signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, sig_handle);
		signal(SIGTSTP, sig_handle);


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