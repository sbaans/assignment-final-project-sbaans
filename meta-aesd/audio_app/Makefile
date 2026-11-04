CFLAGS = -g -Wall -Werror
LDFLAGS = -pthread
LDLIBS += -lasound

ifdef CI_SYSROOT
CFLAGS += -I$(CI_SYSROOT)/usr/include
LDFLAGS += -L$(CI_SYSROOT)/usr/lib
endif

all: audio_app

default: audio_app

audio_app.o: audio_app.c
	$(CC) $(CFLAGS) -c audio_app.c

audio_app: audio_app.o
	$(CC) $(LDFLAGS) audio_app.o $(LDLIBS) -o audio_app

clean :
	rm -f audio_app audio_app.o
