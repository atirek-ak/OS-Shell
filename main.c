#include "headers.h"

void main_loop()
{
	int i=0;
	do
	{
		//Print directory & user details; Change directory
		getcwd(path, sizeof(path));
		// printf("%s\n", path);
		get_pwd();
		printf("%s@%s:%s ", user_name, system_name, displayed_path );
		//Input
		char * input;
		input = get_input();
		process_input(input);
		i++;
	}while(i<10);
}

void initiate()
{
	getlogin_r(user_name, sizeof(user_name));
	gethostname(system_name, sizeof(system_name));
	getcwd(home, sizeof(home));
	// printf("%s\n", home);
	main_loop();
}

int main(int argc, char  *argv[])
{
	initiate();
	return EXIT_SUCCESS;
}