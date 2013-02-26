/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     socketcliente.h
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Implementacion del socket protocolo TCP lado del cliente.
 * 
 */

#ifndef SOCKETCLIENTE_H
#define SOCKETCLIENTE_H


#include "encomun.h"

int crearConexion(char *nombre_host, int puerto);
int escribeSocket(int descriptor, char *mensaje);
int leerSocket(int descriptor, char *mensaje);
int escribirSocket(int fd, char *datos);

#endif  /* SOCKETCLIENTE_H */