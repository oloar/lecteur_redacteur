# Ce Makefile peut etre utilisé comme ceci
# > make all
# pour compiler et obtenir tous les exécutables listés dans PROGS
# ou alors
# > make <nom d'1 executable>

.PHONY: all, clean, dist

# Disable implicit rules
.SUFFIXES:

CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS =

LIBS += -lpthread

# mettre les .h
INCLUDE = lecteur_redacteur.h fifo.h
# mettre des .o 
OBJS = lecteur_redacteur.o  fifo.o
INCLDIR = -I.

# mettre les noms des exécutables à créer
PROGS = test_lr_fifo

all: $(PROGS)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(INCLDIR) -c -o $@ $<

%: %.o $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -f $(PROGS) *.o

dist : clean all
	mv $(PROGS) ../dist/
