/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     bomba.h
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Programa que permite invocar el cliente
 * 
 */

#ifndef BOMBA_H
#define	BOMBA_H

#include "encomun.h"
#include "listaservidor.h"

char usoBomba[720]="\nUso: \t$./bomba -n nombreBomba -cp capacidadMaxima \n\
	\t-i inventario -c consumo -fc ficheroCentros\n\
	Donde:\n\
	\t1) nombreBomba: es una cadena de caracteres sin espacio que \
	indica el nobre de la bomba.\n\
	\t2) capacidadMaxima: entero entre 38.000 y 380.000 que indica la capacidad\
	maxima.\n\
	\t3) inventario: entero entre 0 y capacidadMaxima que indica el \
	inventario actual de la bomba.\n\
	\t4) consumo: entero entre 0 y 1.000 que indica el consumo promedio en\
	litros por minutos.\n\
	\t5) ficheroCentros: nombre del fichero que contiene el listado de los\
	centros de distribucion.\n";
char *ficheroCentros = NULL;
char *nombreBomba = NULL;
int inventario;
int consumo;
int capacidadMaxima;
int tiempoEjecucion;
FILE *logClient;
char entryLog[256];
int solicitando;
typedef struct bomba{
    char nombre[52];    
    int capacidad;    
    int inventario;
    int consumo;
} bomba;


void verificarArgs(int cantArg,char*args[]);
void crearListaCentros(servidor* lista, char* nFichero);
void inicializarBomba(char* nombreB, int capacidadB, int inventarioB, int consumoB, bomba* estacion);
int tanqueVacio(bomba* estacion);
int tanqueFull(bomba* estacion);
void disminuirGasolina(bomba* estacion);
void aumentarGasolina(bomba* estacion, int gasolina);

#endif	/* BOMBA_H */

