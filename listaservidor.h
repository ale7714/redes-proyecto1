/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     listaservidor.h
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Implementacion de la estructura servidor, la cual consiste en el nombre, 
 * la dirección DNS, el puerto y un apuntador al proximo servidor.
 * 
 */


#ifndef LISTASERVIDOR_H
#define LISTASERVIDOR_H


#include "encomun.h"

typedef struct servidor{
    char nombre[128];    
    char dns[128];    
    int puerto;
    int tiempoRespuesta;
    struct servidor *siguiente;
} servidor;

extern void crear(servidor* lista);
extern void inicializar(char* nombre, char* dns, int puerto, servidor* lista);
extern void insertar(servidor* lista, servidor* servNuevo);
extern void ordenarPorTiempo(servidor* lista);
extern void liberar(servidor* lista);
extern void imprimir(servidor* lista);

#endif  /* LISTASERVIDOR_H */