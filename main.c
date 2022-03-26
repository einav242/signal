#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int signum)
{
	int i = 5;
	int j = 0;
	int k;
	switch (signum)
	{
	case SIGCHLD:
		printf("I am in sighandler1\n");
		fflush(stdout);
		raise(SIGUSR1);
	case SIGUSR1:
		printf("I am in sighandler3\n");
		fflush(stdout);
		k = i / j;
		fflush(stdout);
		break;
	case SIGFPE:
		printf("I am in sighandler2\n");
		fflush(stdout);
		{
			char *ptr = 0;
			*ptr = 0;
		}

	case SIGSEGV:
	{
		printf("I am in sighandler4\n");
		abort();
	}
	case SIGABRT:
	{
		printf("I am in sighandler5\n");
		exit(1);
	}
	}
}

int main()
{
	int status;
	signal(SIGCHLD, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGFPE, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGABRT, sig_handler);
	if (!(fork()))
	{
		exit(1);
	}
	wait(&status);
	// script(1);
}