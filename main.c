#include "headers.h"

void main_loop()
{
	do
	{
		getcwd(path, sizeof(path));
		get_pwd();
		printf("%s@%s:%s", user_name, system_name, path );
	}while(0);
}

void initiate()
{
	getlogin_r(user_name, sizeof(user_name));
	gethostname(system_name, sizeof(system_name));
	getcwd(original_path, sizeof(original_path));
	main_loop();
}

int main(int argc, char  *argv[])
{
	initiate();
	return EXIT_SUCCESS;
}