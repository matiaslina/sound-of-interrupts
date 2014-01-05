TARGET=play
FILES=main.c \
	  proc_parser.c
CFLAGS=`pkg-config --cflags libpulse libpulse-simple` \
	   -g -Wextra -Werror -Wall -Wunused-but-set-variable
LIBS=`pkg-config --libs libpulse libpulse-simple` \
	 -lm
CC=gcc

.PHONY: clean

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(FILES) $(LIBS)

clean:
	rm -r $(TARGET)
