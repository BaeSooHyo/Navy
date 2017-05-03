CC = gcc
CDFLAGS = -Wall -g -std=c99
LDFLAGS = -g
TARGETS = ivanGetTheKatyusha

all : $(TARGETS)

$(TARGETS) : navy.o command.o intel.o
	$(CC) $(LDFLAGS) $^ -o $@

navy.o : navy.c
		$(CC) -c $(CDFLAGS) $< -o $@

command.o : command.c command.h
		$(CC) -c $(CDFLAGS) $< -o $@

intel.o : intel.c intel.h
		$(CC) -c $(CDFLAGS) $< -o $@

mrproper :
		rm -f $(TARGETS)

clean :
		rm -f *.o
