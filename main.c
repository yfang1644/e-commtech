/*
 * For e-comtech, Beijing. Co.
 *
 * 2015-06-12
 *
 * Author: Fang Yuan
 */

#include "main.h"

int main(int argc, char *argv[])
{
	int listenfd, connfd, on, nready, maxfdp1, len;
	struct sockaddr_in  cliaddr;
	pid_t pid;
	fd_set rset;

/*
	if(daemon_init() < 0) {
		fprintf(stderr, "daemon init error\n");
		exit(-1);
	}
*/
	if((listenfd = net_init()) < 0) {
		fprintf(stderr, "network init error\n");
		exit(-2);
	}

	if(event_init() < 0) {
		fprintf(stderr, "event init error\n");
		exit(-3);
	}

	FD_ZERO(&rset);
	maxfdp1 = listenfd + 1;

	for(;;) {
		FD_SET(listenfd, &rset);

		if((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
			if(errno == EINTR)
				continue;
			else {
				fprintf(stderr, "select err\n");
				exit(-1);
			}
		}

		if(FD_ISSET(listenfd, &rset)) {
			len = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
			if((pid = fork()) == 0) {
				close(listenfd);
				talk_to_net(connfd);
				exit(0);
			} else
				close(connfd);
		}
	}
	return 0;
}

