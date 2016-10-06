/*
 * For e-comtech, Beijing. Co.
 *
 * 2015-06-12
 *
 * Author: Fang Yuan
 */
#include "main.h"

int daemon_init(void)
{
	struct sigaction act;
	int i,maxfd;

	if(fork() !=0 )
		exit(0);
	if(setsid() < 0)
		return -1;

	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGHUP, &act, NULL);

	if(fork() != 0)
		exit(0);
	chdir("/");
	umask(0);
	maxfd=sysconf(_SC_OPEN_MAX);
	for(i = 0; i < maxfd; i++)
		close(i);

	open("/dev/null",O_RDWR);
	dup(0);
	dup(1);
	dup(2);
	return 0;
}

