/*
 * For e-comtech, Beijing. Co.
 *
 * 2015-06-12
 *
 * Author: Fang Yuan
 */

#include "event.h"

Display *display;
int event_init(void)
{
	display = XOpenDisplay(NULL);
	if (!display)
		return -2;
	else
		return 0;
}

void mouseMove(int x, int y, unsigned long mdelay)
{
	XTestFakeMotionEvent(display, -1, x, y, mdelay);
	XFlush(display);
}

void buttonEvent(unsigned int button, Boolean pressed, unsigned long mdelay)
{
	XTestFakeButtonEvent(display, button, pressed, mdelay);
	XFlush(display);
}

void keyEvent(unsigned int keycode, Boolean pressed, unsigned long mdelay)
{
	XTestFakeKeyEvent(display, keycode, pressed, mdelay);
	XFlush(display);
}

