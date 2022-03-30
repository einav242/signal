#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler1(int sig)
{
	printf("I am in sighandler 1\n");
	sleep(1);
	fflush(stdout);
	raise(SIGUSR1); //secode signal: SIGUSR1
}
void sig_handler2(int sig)
{
	printf("I am in sighandler 2\n");
	sleep(1);
	fflush(stdout);
	int i = 5;
	int j = 0;
	int k;
	k = i / j; //third signl: SIGFPRE
	fflush(stdout);
}
void sig_handler3(int sig)
{
	printf("I am in sighandler 3\n");
	sleep(1);
	fflush(stdout);
	{
		char *ptr = 0;
		*ptr = 0; //fourth signal: SIGSEGV
	}
}
void sig_handler4(int sig)
{
	printf("I am in sighandler 4\n");
	abort(); //fifth signal: SIGABRT
}
void sig_handler5(int sig)
{
	printf("I am in sighandler 5\n");
	printf("I am goin to sleep...\n");
	while (1)
	{
		printf("To wake me up press ctrl+c\n"); // after press ctrl+c we make signal number six: SIGINT
		sleep(1);
	}
}
void sig_handler6(int sig)
{
	printf("I am in sighandler6\n");
	printf("bye bye...\n");
	exit(1);
}

int main()
{
	int status;
	signal(SIGCHLD, sig_handler1);
	signal(SIGUSR1, sig_handler2);
	signal(SIGFPE, sig_handler3);
	signal(SIGSEGV, sig_handler4);
	signal(SIGABRT, sig_handler5);
	signal(SIGINT, sig_handler6);
	if (!(fork())) //first signal:SIGCHILD
	{
		exit(1);
	}
	wait(&status);
}