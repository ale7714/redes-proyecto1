/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     centro.h
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Programa que permite invocar el servidor
 * 
 */

#ifndef CENTRO_H
#define CENTRO_H

#include "encomun.h"
#include "socketservidor.h"

char usoCentro[720]="\nUso: \t$./centro -n nombreCentro -cp capacidadMaxima \n\
    \t-i inventario -t tiempo -s suministro -p puerto\n\
    Donde:\n\
    \t1) nombreCentro: es una cadena de caracteres sin espacio que \
    indica el nobre del centro de distribucion.\n\
    \t2) capacidadMaxima: entero entre 38.000 y 3.800.000 que indica la capacidad\
    maxima.\n\
    \t3) inventario: entero entre 0 y capacidadMaxima que indica el \
    inventario actual de la bomba.\n\
    \t4) tiempo: entero entre 0 y 180 que indica el tiempo de respuesta.\n\
    \t5) suministro: entero entre 0 y 10.000 que representa el suministro promedio en\
    litros por minuto.\n\
    \t6) puerto: entero que representa el puerto por el cual escuchara las peticiones.\n";
char *nombreCentro = NULL;
int capacidadMaxima;
int inventario;
int tiempo;
int suministro;
int puerto;
int tiempoEjecucion;
FILE *logServer;
char entryLog[256];
int solicitando;
typedef struct centro{
    char nombre[52];    
    int capacidad;    
    int inventario;
    int suministro;
    int tiempo;
    int puerto;
} centro;

typedef struct datos {
    char bomba[52];
    int socket;
} datos;

void verificarArgs(int cantArg,char*args[]);
void inicializarCentro(char* nombreC, int capacidadC, int inventarioC, int tiempoC, int suministroC,
         int puertoC, centro* c);
void aumentarGasolina(int i);
int tanqueVacio(centro* estacion);
int tanqueFull(centro* estacion);
void *ejecucionCentro();

#endif  /* CENTRO_H */
