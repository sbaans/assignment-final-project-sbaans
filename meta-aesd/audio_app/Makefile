CFLAGS = -g -Wall -Werror
LDFLAGS = -pthread

all: audio_app

default: audio_app

aesdsocket.o: audio_app.c
	$(CC) $(CFLAGS) -c audio_app.c

audio_app: audio_app.o
	$(CC) $(LDFLAGS) audio_app.o -o audio_app

clean :
	rm -f audio_app audio_app.o
