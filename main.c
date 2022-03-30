#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int sig)
{
	switch (sig)
	{
	case SIGCHLD:
		printf("I am in sighandler1\n");
		sleep(1);
		fflush(stdout);
		raise(SIGUSR1); //secode signal: SIGUSR1
	case SIGUSR1:
		printf("I am in sighandler2\n");
		sleep(1);
		fflush(stdout);
		int i = 5;
		int j = 0;
		int k;
		k = i / j; //third signl: SIGFPRE
		fflush(stdout);
		break;
	case SIGFPE:
		printf("I am in sighandler3\n");
		sleep(1);
		fflush(stdout);
		{
			char *ptr = 0;
			*ptr = 0; //fourth signal: SIGSEGV
		}

	case SIGSEGV:
	{
		printf("I am in sighandler4\n");
		abort(); //fifth signal: SIGABRT
	}
	case SIGABRT:
	{
		printf("I am in sighandler5\n");
		printf("I am goin to sleep...\n");
		while (1)
		{
			printf("To wake me up press ctrl+c\n"); // after press ctrl+c we make signal number six: SIGINT
			sleep(1);
		}
	}
	case SIGINT:
	{
		printf("I am in sighandler6\n");
		printf("bye bye...");
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
	signal(SIGINT, sig_handler);
	if (!(fork())) //first signal:SIGCHILD
	{
		exit(1);
	}
	wait(&status);
}