/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     centro.c
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Programa que permite invocar el servidor
 * 
 */

#include "centro.h"

pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;

/*  Función: verificarArgs  
    Entrada:
        cantArg: Cantidad de parametros introducidos.
           args: Arreglo con los parametros introducidos.
    Salida:
        N/A 
    Función que permite verificar los parametros de entrada al llamar
    el programa. En caso de diferencias con el formato de 
    entrada se muestra el mensaje de uso del progama
*/
void verificarArgs(int cantArg,char*args[]){
    int opt;

    struct option longopts[] = {
       { "cp", required_argument, NULL, 'm'},
       { 0, 0, 0, 0}
    };

    if(cantArg == 13){

        /* Ciclo que toma los arguemtos de cada uno de los flags sin importar el orden en
           el cual son colocado los flags al invocar el programa */
        while ((opt = getopt_long_only(cantArg, args, "n:m:i:t:s:p:",longopts,NULL)) != -1){

            switch (opt) {
                case 'n':
                    // Nombre del Centro
                    if (nombreCentro != NULL) 
                        free(nombreCentro);
                    if (asprintf(&nombreCentro, "%s", optarg) == -1) {
                            fatalerror("Error copiando string para manejo de argumentos",
                                EXIT_BAD_ARG);
                    }
                    //printf("Nombre: %s\n",nombreCentro);
                    break;

                case 'm':
                    // Capacidad Máxima
                    capacidadMaxima = atoi(optarg);
                    //printf("Capacidad: %d\n",capacidadMaxima);
                    break;

                case 'i':
                    // Inventario
                    inventario = atoi(optarg);
                    //printf("Inventario: %d\n",inventario);
                    break;

                case 't':
                    // Tiempo de respuesta
                    tiempo = atoi(optarg);
                    //printf("Tiempo: %d\n",tiempo);
                    break;

                case 's':
                    // Suministro
                    suministro = atoi(optarg);
                    //printf("Suministro: %d\n",suministro);
                    break;

                case 'p':
                    // Suministro
                    puerto = atoi(optarg);
                    //printf("Puerto: %d\n",puerto);
                    break;

                default:
                       fatalerror(usoCentro,EXIT_BAD_ARG);
            }

        }
        if(capacidadMaxima < 38000 || capacidadMaxima > 3800000){
            fatalerror(usoCentro,EXIT_BAD_ARG);
        }
        if(inventario < 0 || inventario > capacidadMaxima){
            fatalerror(usoCentro,EXIT_BAD_ARG);
        }
        if(suministro < 0 || suministro > 10000){
            fatalerror(usoCentro,EXIT_BAD_ARG);
        }
        if(puerto < 0){
            fatalerror(usoCentro,EXIT_BAD_ARG);
        }
        if(tiempo < 0 || tiempo > 180){
            fatalerror(usoCentro,EXIT_BAD_ARG);
        }
    }else{
        fatalerror(usoCentro,EXIT_BAD_ARG);
    } 
}


/*  Función: inicializarCentro
    Entrada:
            nombreC: Apuntador al nombre de la bomba
         capacidadC: Entero que representa la capacidad maxima
        inventarioC: Entero que representa el inventario
            tiempoC: Entero que representa el tiempo de respuesta
        suministroC: Entero que representa el suministro promedio
                  c: Apuntador a la dirección en memoria de la bomba
    Salida:
        N/A 
    Función que inicializa al tipo centro
*/
void inicializarCentro(char* nombreC, int capacidadC, int inventarioC, int tiempoC, int suministroC,
         int puertoC, centro* c){
    strcpy(c->nombre,nombreC);
    c->capacidad = capacidadC; 
    c->inventario = inventarioC;      
    c->suministro = suministroC;
    c->tiempo = tiempoC;
    c->puerto = puertoC;
}


/*  Función: aumentarGasolina
    Entrada:
        estacion: Apuntador a la dirección en memoria de la centro
    Salida:
        N/A
    Función que aumenta el inventario de gasolina de centro
*/
void aumentarGasolina(int i){
    if((i = i + suministro) >= capacidadMaxima){
        i = capacidadMaxima;
    }

}

/*  Función: tanqueVacio
    Entrada:
        estacion: Apuntador a la dirección en memoria de centro
    Salida:
        FALSE: Si el tanque no esta vacio
         TRUE: Cuando el tanque esta vacio 
    Función que verfica si el tanque esta o no vacio 
*/
int tanqueVacio(centro* estacion){
    if(estacion->inventario != 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/*  Función: tanqueFull
    Entrada:
        estacion: Apuntador a la dirección en memoria de la centro
    Salida:
        FALSE: Si el tanque no esta full
         TRUE: Cuando el tanque esta full
    Función que verfica si el tanque esta o no full
*/
int tanqueFull(centro* estacion){
    if(estacion->inventario != estacion->capacidad) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/*  Función: finHilo
    Entrada:
        signal: Entero que representa la señal de retorno del hilo
    Salida:
        N/A
    Función que verfica si el tanque esta o no full
*/
static void finHilo(int signal){

    if (fclose(logServer) == 0){

        printf("Termino actividad del servidor.\n");

    }

    exit(0);

}

/*  Función: ejecucionCentro
    Entrada:
        N/A
    Salida:
        N/A
    Función que se encarga de hacer la simulación del tiempo. 
    Verifica que el tanque este lleno o vacío y hace el aumento de gasolina, cuando sea necesario. 
*/
void *ejecucionCentro(){

    while(tiempoEjecucion<=480){
        if(inventario == capacidadMaxima){
            sprintf(entryLog, "Tanque full: %d\n", tiempoEjecucion);
            fprintf(logServer,"%s",entryLog);
            fflush(logServer);
        }

        if(inventario <= 0){
            sprintf(entryLog, "Tanque vacio: %d\n", tiempoEjecucion);
            fprintf(logServer,"%s",entryLog);
            fflush(logServer);
        }

        tiempoEjecucion++;
        if((inventario = inventario + suministro) > capacidadMaxima){
            inventario = capacidadMaxima;
        }
        usleep(100*1000);
    }

    raise(SIGUSR1);
}

/*  Función: enviarTiempoRespuesta
    Entrada:
        Apuntador a la dirección en memoria del tipo datos
    Salida:
        N/A
    Función que se encarga de escribir en un socket cual es el tiempo de respuesta del centro. 
*/
void *enviarTiempoRespuesta(void *d){

    datos *datosHilo = (datos *) d;

    int socket = (int) datosHilo->socket;
    int n;

    char bufferOut[256];
    bzero(bufferOut, 256);

    sprintf(bufferOut, "%d", tiempo);

    n = write(socket, bufferOut, sizeof (bufferOut));

    if (n < 0) printf("Error: escribiendo en el socket\n");

}

/*  Función: enviarGasolina
    Entrada:
        Apuntador a la dirección en memoria del tipo datos
    Salida:
        N/A
    Función que se encarga de enviar un string al socket, indicando si procede o no la petición, dependiendo de si tiene gasolina en el inventario o no. 
*/
void *enviarGasolina(void *d){

    //pthread_detach(pthread_self());

    datos *datosHilo = (datos *) d;

    int socket = datosHilo->socket;
    char nombreB[52];
    int n;
    char bufferOut[256];
    bzero(bufferOut, 256);   
    //bzero(nombreB, 256);   
    strcpy(nombreB, datosHilo->bomba);
    printf("datosHilo->bomba %s\n",datosHilo->bomba);
    printf("datosHilo->socket %d\n",datosHilo->socket);
    printf("nombreB %s\n",nombreB);
    int envio=FALSE;

    /*
        Se coloca un semaforo pues inicia la zona critica
    */
    pthread_mutex_lock(&mute);

    if (inventario >= 38000) {
        printf("Enviando gasolina: si\n"); 
        sprintf(bufferOut, "si");
        inventario = inventario - 38000;

        // Escribir el resultado de la peticion en log
        sprintf(entryLog, "Suministro incial: %d, %s, enviado, inventario: %d\n", tiempoEjecucion, nombreB,inventario);
        fprintf(logServer,"%s",entryLog);
        fflush(logServer);
        printf("bufferOut: %s\n",bufferOut);   
        n = write(socket, bufferOut, sizeof(bufferOut));
        printf("n: %d\n",n);

        if (n < 0) printf("Error: escribiendo en el socket\n");

        envio = TRUE;

    }

    pthread_mutex_unlock(&mute);
    /*
        Se quita semaforo pues termina la zona critica
    */
    if(envio == FALSE){
        sprintf(bufferOut, "no");

        // Escribir el resultado de la peticion en log
        sprintf(entryLog, "Suministro incial: %d, %s, inventario insuficiente, inventario: %d\n", tiempoEjecucion, nombreB, inventario);
        fprintf(logServer,"%s",entryLog);
        fflush(logServer);

        n = write(socket, bufferOut, sizeof(bufferOut));
        if (n < 0) printf("Error: escribiendo en el socket\n");

        printf("No envie nada\n");

    }

}

/*  Función: iniciarServidor
    Entrada:
        Apuntador a la dirección en memoria del tipo datos
    Salida:
        N/A
    Función que se encarga de manejar las conexiones, es decir, abrir el socket, escucha las conexiones y las acepta. Por cada conexión que acepta crea un hilo y lee lo que manda el cliente. Si es solicitud lo redirige a enviarGasolina, si es tiempo lo redirige a enviarTiempoRespuesta.
*/
void iniciarServidor(){

    int socketServidor, socketCliente, lenCliente;
    struct sockaddr_in direccionServ, direccionCliente;

    socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServidor < 0) fatalerror("Error abriendo el socket", EXIT_SOCKET);

    bzero((char *) &direccionServ, sizeof (direccionServ));

    direccionServ.sin_family = AF_INET;
    direccionServ.sin_addr.s_addr = INADDR_ANY;
    direccionServ.sin_port = htons(puerto);

    if (bind(socketServidor, (struct sockaddr *) &direccionServ, sizeof(direccionServ)) < 0){
        fatalerror("Error durante el bind", EXIT_BIND);
    }
    
    
    listen(socketServidor, 5);

    lenCliente = sizeof(direccionCliente);
    
    while (TRUE) {
        socketCliente = accept(socketServidor, (struct sockaddr *)&direccionCliente, &lenCliente);
        if (socketCliente < 0)  fatalerror("Error en el accept",EXIT_ACCEPT);


        pthread_t hiloCliente;
        
        datos *datosHilo = (datos *) malloc(sizeof(datos));
        datosHilo->socket = socketCliente;
                                        printf("socketCliente %d\n",socketCliente);
        int n;

        char buffer[256];
        bzero(buffer, 256);

        n = read(socketCliente, buffer, 255);
        printf("mensaje %s\n",buffer);

        if(strcmp(buffer, "tiempo") == 0){
            printf("solicitud de tiempo \n");
            pthread_create(&hiloCliente, NULL, enviarTiempoRespuesta, (void*)datosHilo);

        } else{
            char *bomba = strtok(buffer, "&");

            if(strcmp(buffer, "solicitud") == 0){

                bomba = strtok(NULL,"&");
                strcpy(datosHilo->bomba,bomba);
                pthread_create(&hiloCliente, NULL, enviarGasolina, (void*)datosHilo);

            }else {

                n = write(socketCliente, "Error en solicitud: tiempo` o `solicitud&nombre` \n", 256);
                if (n < 0) fatalerror("Error escribiendo en el socket", EXIT_WRITE);
                printf("Error en solicitud: `tiempo` o `solicitud&nombre`` \n");

            }

        }

        if(n < 0) fatalerror("Error leyendo del socket", EXIT_READ);

    }
}

/*
 * Programa principal para el centro de servicio
 */
int main(int argc, char** argv) {

    pthread_t threadPrincipal = (pthread_t *) malloc(sizeof (pthread_t));

    struct sigaction accion;
    memset(&accion,'\0',sizeof(accion));
    accion.sa_handler = &finHilo;

    tiempoEjecucion = 0;

    programname = argv[0]; // Guardar nombre del programa para errores

    if(sigaction(SIGUSR1, &accion, NULL) < 0) {
        fatalerror("Manejando la señal",EXIT_ERROR);
        return 1;
    }

    verificarArgs(argc,argv);

    // Crear y abrir archivo en modo de escritura
    char log_name[128];
    sprintf(log_name, "log_%s.txt", nombreCentro);
    logServer = fopen(log_name, "w");
    fprintf(logServer, "\0");
    fclose(logServer);
    logServer = fopen(log_name, "a+");

    // Escribir estado inicial del centro en el log
    sprintf(entryLog, "Estado incial: %d\n", inventario);
    fprintf(logServer,"%s",entryLog);
    fflush(logServer);

    int tError;
    if((tError=pthread_create(&threadPrincipal,NULL,ejecucionCentro,NULL)) < 0)
        fatalerror("Error al crear el thread",tError); 

    iniciarServidor();

    exit(EXIT_SUCCESS);
}
