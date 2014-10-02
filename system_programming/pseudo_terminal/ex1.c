#include <stdio.h>

int main(void)
{
	char login_name[150];
	char password[150];

	//	By default stdin, stdout and stderr are open

	fprintf(stdout, "Login : ");
	if (NULL == fgets(login_name, sizeof(login_name), stdin))
	{
		fprintf(stderr, "No login name\n");
		return 1;
	}

	fprintf(stdout, "Password : ");
	if (NULL == fgets(password, sizeof(password), stdin))
	{
		fprintf(stderr, "No password\n");
		return 1;
	}

	fprintf(stdout, "Result :\n%s%s\n", login_name, password);

	return 0;
}
