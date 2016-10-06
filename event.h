/*
 * For e-comtech, Beijing. Co.
 *
 * 2015-06-12
 *
 * Author: Fang Yuan
 */

#ifndef	_EVENT_H_
#define	_EVENT_H_

#include <X11/extensions/XTest.h>       //the xlib extension lib

typedef int     Boolean;
#define true        ((Boolean) 1)
#define false       ((Boolean) 0)

#define	MOUSEMOVE	1
#define	LBUTTONDN	2
#define	LBUTTONUP	3
#define	RBUTTONDN	4
#define	RBUTTONUP	5

int event_init(void);

void mouseMove(int x, int y, unsigned long mdelay);

void buttonEvent(unsigned int button, Boolean pressed, unsigned long mdelay);

void keyEvent(unsigned int keycode, Boolean pressed, unsigned long mdelay);

#endif	// _EVENT_H_

