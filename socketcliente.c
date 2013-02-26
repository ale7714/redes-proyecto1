/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     socketcliente.c
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Implementacion del socket protocolo TCP lado del cliente.
 * 
 */

 #include "socketcliente.h"
 
 /* Función: crearConexion
    Entrada:
       host: Apuntador a la dirección en memoria del host
     puerto: Entero que representa el puerto
    Salida:
     descSocket: Entero que almacena el descriptor del socket 
            -1 : Error con el host
            -2 : Error al abrir el socket
            -3 : Error al conectar
    Función que crea la conexión con un servidor remoto
*/
int crearConexion(char *nombre_host, int puerto){

    struct sockaddr_in direccionHost;
    struct hostent *host;
    int descSocket;

    host = NULL;
    printf("intentando conectarme\n");
    host = gethostbyname (nombre_host);
    if (host == NULL) { 
        return -1;
    }
    printf("intentando conectarme 1: %d\n",host);    

    direccionHost.sin_family = AF_INET;
    direccionHost.sin_addr.s_addr = ((struct in_addr *)(host->h_addr))->s_addr;
    direccionHost.sin_port = puerto;
    
    descSocket = socket (AF_INET, SOCK_STREAM, 0);
    if (descSocket < 0){
        return -2;       
    }
    printf("intentando conectarme 2\n"); 
    if (connect (descSocket,(struct sockaddr *)&direccionHost, sizeof (direccionHost)) < 0){
        return -3;
    }
    printf("conexion %d\n",descSocket);
    return descSocket;
}


 /* Función: escribeSocket
    Entrada:
     descriptor: Descriptor del socket
        mensaje: Mensaje a escribir
    Salida:
         TRUE: Si escribe el mensaje con exito en el socket
        FALSE: Si falla al escribir el mensaje
    Función que escribe un mensaje en el socket
*/
int escribeSocket(int descriptor, char *mensaje){

    int n;

    n = write(descriptor,mensaje,strlen(mensaje));
    if (n < 0) {
        return FALSE;
    } else {
        return TRUE;
    }

}


 /* Función: leeSocket
    Entrada:
        descriptor: Descriptor del socket
           mensaje: Apuntador a menoria del mensaje leido
    Salida:
         TRUE: Si lee el mensaje con exito en el socket
        errno: Si falla al leer el mensaje
    Función que lee un mensaje del socket
*/
int leerSocket(int descriptor, char *mensaje){

    int n;
    bzero(mensaje,256);
    n = read(descriptor,mensaje,strlen(mensaje));

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