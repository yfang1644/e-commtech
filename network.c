/*
 * For e-comtech, Beijing. Co.
 *
 * 2015-06-12
 *
 * Author: Fang Yuan
 */

#define	SERV_PORT	10086
#define	MAXLINE		1024

#include "main.h"
#include "event.h"

extern Display *display;

void sig_child(sig_num)
{
	pid_t pid;
	int stat;

	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		fprintf(stderr, "child %d terminated\n", pid);
	return;
}

int move_windows(int windowID)
{
	int i;
	char *argmain[] = {"x", "-r", "Button Boxes", "-e", "0,0,0,310,116"};
	char *argwin1[] = {"x", "-r", "new dialog", "-a", "new dialog",
					"-e", "0,0,150,100,120"};
	int ret;

	return 0;
	switch(windowID) {
		case 0:
			ret = wmctrl(5, argmain, display); 
			break;
		case 1:
			ret = wmctrl(7, argwin1, display); 
			break;
		default:
			break;
	}
}

void talk_to_net(int fd)
{
	ssize_t n;
	char line[MAXLINE];
	int actionID, x, y, type;

	move_windows(0);
	for(;;) {
		if((n = read(fd, line, MAXLINE)) == 0)
			return;
		line[n] = '\0';
		sscanf(line, "%d,%d,%d,%d\n", &actionID, &x, &y, &type);
//		fprintf(stderr, "%d %d %d %d\n", actionID, x, y, type);

		switch(actionID) {
			case MOUSEMOVE:
				mouseMove(x, y, 0);
				break;
			case LBUTTONDN:
				buttonEvent(1, true, 0);
				break;
			case LBUTTONUP:
				buttonEvent(1, false, 0);
				break;
			default:
				break;
		}

		if(type == 1)
			move_windows(1);
	}
}

int net_init(void)
{
	int listenfd, on;
	struct sockaddr_in addr, cliaddr;
	int sin_size;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	// sock addr reuse
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERV_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(listenfd,(struct sockaddr *)&addr, sizeof(addr));
	listen(listenfd, 5);

	signal(SIGCHLD, sig_child);

	return listenfd;
}

