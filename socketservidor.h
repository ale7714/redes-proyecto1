/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     socketservidor.h
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Implementacion del socket protocolo TCP lado del servidor.
 * 
 */

#ifndef SOCKETSERVIDOR_H
#define SOCKETSERVIDOR_H


#include "encomun.h"

int abrirConexion(int puerto);
int aceptarConexion(int descriptor);
int leerSocket(int descriptor, char *mensaje);
int escribirSocket(int fd, char *datos);

#endif  /* SOCKETSERVIDOR_H */