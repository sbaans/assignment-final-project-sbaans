CFLAGS = -g -Wall -Werror
LDFLAGS = -pthread
LDLIBS += -lasound

all: audio_app

default: audio_app

audio_app.o: audio_app.c
	$(CC) $(CFLAGS) -c audio_app.c

audio_app: audio_app.o
	$(CC) $(LDFLAGS) audio_app.o $(LDLIBS) -o audio_app

clean :
	rm -f audio_app audio_app.o
