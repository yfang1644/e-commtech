# For e-comtech, Beijing Co.
# Fang Yuan
#

CC = gcc
TARGET = buttonbox wmctrl main
all: $(TARGET)
LDFLAGS = -lSM -lICE -lX11 -lXmu -lXtst

buttonbox: buttonbox.c 
	$(CC) $^ -o $@ $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs`

wmctrl: wmctrl.c
	$(CC) $^ -o $@ $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs` \
		$(LDFLAGS) -DWMCTRL_STANDALONE -Wall -O3

main: main.c event.c network.c daemon.c wmctrl.c
	$(CC) $^ -o $@ `pkg-config gtk+-2.0 --cflags --libs` $(LDFLAGS)

clean: 
	rm -f $(TARGET) *.o

