CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = main.c auth.c menu.c contact.c input.c

ict-cms: $(SRC) contact.h input.h auth.h menu.h
	$(CC) $(CFLAGS) -o ict-cms $(SRC)

clean:
	rm -f ict-cms
