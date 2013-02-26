CC = gcc
CFLAGS = -g
LIBS =  -Wall -lpthread -lm 
all : bomba centro

encomun.o : encomun.h encomun.c 
	$(CC) $(CFLAGS) -c encomun.c

listaservidor.o : listaservidor.h listaservidor.c 
	$(CC) $(CFLAGS) -c listaservidor.c

socketcliente.o : socketcliente.h socketcliente.c
	$(CC) $(CFLAGS) -c socketcliente.c

socketservidor.o : socketservidor.h socketservidor.c
	$(CC) $(CFLAGS) -c socketservidor.c

bomba : encomun.o listaservidor.o socketcliente.o bomba.h bomba.c 
	$(CC) $(CFLAGS) encomun.o listaservidor.o socketcliente.o bomba.h bomba.c $(LIBS) -o bomba

centro : encomun.o socketservidor.o centro.h centro.c 
	$(CC) $(CFLAGS) encomun.o socketservidor.o centro.h centro.c  $(LIBS) -o centro
clean :
	rm *.o
	rm bomba
	rm centro