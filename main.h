/*
 * For e-comtech, Beijing. Co.
 *
 * 2015-06-12
 *
 * Author: Fang Yuan
 */

#ifndef	_MAIN_H_
#define	_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdarg.h>
#include <syslog.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <X11/extensions/XTest.h>       //the xlib extension lib

int daemon_init(void);
int network_init(void);
void talk_to_net(int fd);
int wmctrl(int argc, char *argv[], Display *disp);

#endif	// _MAIN_H_
