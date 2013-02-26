/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     socketservidor.c
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Implementacion del socket protocolo TCP lado del servidor.
 * 
 */

#include "socketservidor.h"

 /* Función: abreConexion
    Entrada:
     puerto: Entero que representa el puerto
    Salida:
     descSocket: Entero que almacena el descriptor del socket 
            -1 : Error al abrir el socket
            -2 : Error al hacer bind
            -3 : Error al escuchar
    Función que crea la conexión con un cliente remoto
*/
int abrirConexion(int puerto)
{
    struct sockaddr_in direccion;
    int descriptorS;

    descriptorS = socket (AF_INET, SOCK_STREAM, 0);
    if (descriptorS < 0){      
        return -1;
    }

    direccion.sin_family = AF_INET;
    direccion.sin_port = puerto;
    direccion.sin_addr.s_addr =INADDR_ANY;

    if( bind(descriptorS, (struct sockaddr *)&direccion, sizeof(direccion)) < 0){
        close(descriptorS);
        return -2;
    }

    if (listen(descriptorS, 5) < 0){
        close (descriptorS);
        return -3;
    }

    return descriptorS;
}




 /* Función: abreConexion#include "encomun.h"

    Entrada:
        descriptor: entero que representa el socket del servidor
    Salida:
        dSocket: Entero que almacena el descriptor de la conexion e
            -1 : Error al abrir al aceptar
    Función que acepta la conexion con el cliente
*/
int aceptarConexion(int descriptor)
{
    socklen_t logintudCliente;
    struct sockaddr cliente;
    int dSocket;
    logintudCliente = sizeof(cliente);    
    dSocket = accept(descriptor, &cliente, &logintudCliente);
    if(dSocket < 0) {
        return -1;
    }

    return dSocket;
}

 /* Función: leeSocket
    Entrada:
        descriptor: Descriptor del socket
           datos: Apuntador a menoria del mensaje leido
    Salida:
         TRUE: Si lee el mensaje con exito en el socket
        errno: Si falla al leer el mensaje
    Función que lee un mensaje del socket
*/
int leerSocket(int descriptor, char *datos)
{

    int n;
    bzero(datos,strlen(datos));
    n = read(descriptor,datos,strlen(datos));

    if (n < 0) {
        return errno;
    } else {
        return TRUE;
    }
}

/* Función: escribirSocket
    Entrada:
        descriptor: Descriptor del socket
           datos: Apuntador a menoria del mensaje leido
    Salida:
         TRUE: Si escribe el mensaje con exito en el socket
        errno: Si falla al escribir el mensaje
    Función que escribe un mensaje en el socket
*/
int escribirSocket(int descriptor, char *datos)
{

    int n;
    n =write(descriptor,datos,strlen(datos));

    if (n < 0) {
        return errno;
    } else {
        return TRUE;
    }
}
