/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     encomun.h
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Funciones que usan en común el programa cliente y el servidor
 * 
 */

#ifndef ENCOMUN_H
#define	ENCOMUN_H
#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
 
#define FALSE 0
#define TRUE 1
#define EXIT_BAD_ARG -1
#define EXIT_OPEN_FILE -2
#define EXIT_NO_HOST -3
#define EXIT_ERROR -4
#define EXIT_SOCKET -5
#define EXIT_BIND -6
#define EXIT_ACCEPT -7
#define EXIT_READ -8
#define EXIT_WRITE -8
extern char *programname;

extern void fatalerror(char *message, int errortype);
extern void leerFichero(char* nFichero,char* cFichero);
extern char* trim(char *cadena);

#endif	/* ENCOMUN_H */

