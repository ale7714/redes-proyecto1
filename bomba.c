/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     bomba.c
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Programa que permite invocar el cliente
 * 
 */

#include "bomba.h"
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
       { "fc", required_argument, NULL, 'f'},
       { 0, 0, 0, 0}
    };

	if(cantArg == 11){
         int long_index =0;
        /* Ciclo que toma los arguemtos de cada uno de los flags sin importar el orden en
           el cual son colocado los flags al invocar el programa */
        while ((opt = getopt_long_only(cantArg, args, "n:i:c:m:f:",longopts,&long_index)) != -1){
            switch (opt) {
                case 'n':
                    // Nombre de la bomba
                    if (nombreBomba != NULL) 
                        free(nombreBomba);
                    if (asprintf(&nombreBomba, "%s", optarg) == -1) {
                            fatalerror("Error copiando string para manejo de argumentos",
                                EXIT_BAD_ARG);
                    }
                    //printf("Nombre bomba:%s\n",nombreBomba);
                    break;

                case 'm':
                    // Capacidad Máxima
                    capacidadMaxima = atoi(optarg);
                    //printf("Capacidad:%d\n",capacidadMaxima);
                    break;

                case 'i':
                    // Inventario
                    inventario = atoi(optarg);
                    //printf("Inventario:%d\n",inventario);
                    break;

                case 'c':
                    // Consumo
                    consumo = atoi(optarg);
                    //printf("Consumo:%d\n",consumo);
                    break;

                case 'f':
                    // Fichero de los Centros de distribución
                    if (ficheroCentros != NULL) 
                        free(ficheroCentros);
                    if (asprintf(&ficheroCentros, "%s", optarg) == -1) {
                            fatalerror("Error copiando string para manejo de argumentos",
                                EXIT_BAD_ARG);
                    }
                    //printf("Fichero Centros: %s\n",ficheroCentros);
                    break;


                default:
                       fatalerror(usoBomba,EXIT_BAD_ARG);
            }

        }

        if(capacidadMaxima < 38000 || capacidadMaxima > 380000){
            fatalerror(usoBomba,EXIT_BAD_ARG);
        }
        if(inventario < 0 || inventario > capacidadMaxima){
            fatalerror(usoBomba,EXIT_BAD_ARG);
        }
        if(consumo < 0 || consumo > 1000){
            fatalerror(usoBomba,EXIT_BAD_ARG);
        }
	}else{
		fatalerror(usoBomba,EXIT_BAD_ARG);
	}
}

/*  Función: inicializarBomba
    Entrada:
             nombre: Apuntador al nombre de la bomba
         capacidadB: Entero que representa la capacidad maxima
        inventarioB: Entero que representa el inventario
           consumoB: Entero que representa el consumo promedio
           estacion: Apuntador a la dirección en memoria de la bomba
    Salida:
        N/A 
    Función que inicializa al tipo bomba
*/
void inicializarBomba(char* nombreB, int capacidadB, int inventarioB, int consumoB, bomba* estacion){

    bzero(estacion->nombre,52);
    strcpy(estacion->nombre,nombreB);
    estacion->capacidad = capacidadB; 
    estacion->inventario = inventarioB;      
    estacion->consumo = consumoB;
}


/*  Función: crearListaCentros
    Entrada:
        lista: Apuntador a la dirección en memoria de la lista de centros de distribución
     nFichero: Nombre del fichero que contiene los datos de los  centro
    Salida:
        N/A 
    Función que crea la lista de los centros distribución
*/
void crearListaCentros(servidor* lista, char* nFichero){
    char contenido[256];
    char* datos= NULL;
    char nombre[52];
    char dns[52];
    int puerto;
    servidor *aux = (servidor *) malloc(sizeof(servidor));

    FILE *file = fopen(nFichero, "rt");

    if(file==NULL){
        fatalerror("Error al abrir el fichero",EXIT_OPEN_FILE);
    } 

    while (fgets(contenido, 256, file) != NULL) {
        //printf("contenido %s\n",contenido);    
        datos = strtok (contenido,"&");
        //printf("datos %s\n",datos);
        strcpy(nombre, trim(datos));
        //printf("Lectura centros\n");
        //printf("Nombre centro: %s\n",nombre);
        datos = strtok (NULL, "&");
        strcpy(dns,trim(datos));
        //printf("DNS: %s\n",dns);
        datos = strtok( NULL, "&" );        
        puerto=atoi(trim(datos));
        //printf("Puerto: %d\n",puerto);
        crear(aux);
        inicializar(nombre,dns,puerto,aux);
        insertar(lista,aux);
        //imprimir(lista);
        //printf("ciclo\n");    
    }
    
    fclose(file); 
}

/*  Función: tanqueVacio
    Entrada:
        estacion: Apuntador a la dirección en memoria de la bomba
    Salida:
        FALSE: Si el tanque no esta vacio
         TRUE: Cuando el tanque esta vacio 
    Función que verfica si el tanque esta o no vacio 
*/
int tanqueVacio(bomba* estacion){
    if(estacion->inventario != 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/*  Función: tanqueFull
    Entrada:
        estacion: Apuntador a la dirección en memoria de la bomba
    Salida:
        FALSE: Si el tanque no esta full
         TRUE: Cuando el tanque esta full
    Función que verfica si el tanque esta o no full
*/
int tanqueFull(bomba* estacion){
    if(estacion->inventario != estacion->capacidad) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/*  Función: disminuirGasolina
    Entrada:
        estacion: Apuntador a la dirección en memoria de la bomba
    Salida:
        N/A
    Función que disminuye el inventario de gasolina de la bomba
*/
void disminuirGasolina(bomba* estacion){
    if( (estacion->inventario = estacion->inventario  - estacion->consumo) < 0){
        estacion->inventario = 0;
    }
}

/*  Función: disminuirGasolina
    Entrada:
        estacion: Apuntador a la dirección en memoria de la bomba
    Salida:
        N/A
    Función que aumenta el inventario de gasolina de la bomba
*/
void aumentarGasolina(bomba* estacion, int gasolina){
    if((estacion->inventario = estacion->inventario + gasolina) > estacion->capacidad){
        estacion->inventario = estacion->capacidad;
    }

}

/*  Función: manejadorCliente
    Entrada:
       Apuntador,a una dirección de memoria, de una estructura de tipo servidor.
    Salida:
        N/A
    Función que se encarga de mandar el mensaje de solicitud al servidor y si la respuesta es afirmativa, se aumenta el inventario de gasolina. 
*/
void* manejadorCliente(void *lista){

    servidor *aux = (servidor *) malloc(sizeof(servidor));
    inicializar(((servidor *)lista)->nombre,((servidor *)lista)->dns,((servidor *)lista)->puerto,aux);
    aux->siguiente = ((servidor *)lista)->siguiente;

    char pedido[100];
    sprintf(pedido, "solicitud&%s", nombreBomba);

    while(aux != NULL) {
        int sock;
        int n;
        int numPuerto;
        struct sockaddr_in dirServer;
        struct hostent *server;        
        numPuerto = aux->puerto;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            sprintf(entryLog, "Peticion: %d, %s, no disponible\n", tiempoEjecucion, aux->nombre);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);           
            continue;
        }

        server = gethostbyname(aux->dns);
        
        if (server == NULL) {
            sprintf(entryLog, "Peticion: %d, %s, no disponible\n", tiempoEjecucion, aux->nombre);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);           
            continue;
        }

        bzero((char *) &dirServer, sizeof (dirServer));
        dirServer.sin_family = AF_INET;
        bcopy((char *) server->h_addr, (char *) &dirServer.sin_addr.s_addr, server->h_length);
        dirServer.sin_port = htons(numPuerto);

        if (connect(sock, (struct sockaddr *) &dirServer, sizeof (dirServer)) < 0) {
            sprintf(entryLog, "Peticion: %d, %s, no disponible\n", tiempoEjecucion, aux->nombre);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);           
            continue;
        }

        n = write(sock, pedido, strlen(pedido));
        if (n < 0) {
            sprintf(entryLog, "Peticion: %d, %s, no disponible\n", tiempoEjecucion, aux->nombre);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);           
            printf("\nError escribiendo en el socket\n");
            continue;
        }

        char buffer[256];
        bzero(buffer, 256);
        pthread_mutex_lock(&mute);
        n = read(sock, buffer, 255);
        if (n < 0) {
            sprintf(entryLog, "Peticion: %d, %s, no disponible\n", tiempoEjecucion, aux->nombre);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);           
            continue;
        }

        if (strcmp(buffer, "si") == 0) {
            sprintf(entryLog, "Peticion: %d, %s, exitosa\n", tiempoEjecucion, aux->nombre);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);


            printf("inventario before: %d\n",inventario);
            if( (inventario = inventario  + 38000) > capacidadMaxima){
                inventario = capacidadMaxima;
            } 
             printf("inventario after: %d\n",inventario);
      
            pthread_mutex_unlock(&mute);
            printf("gasolina recibida\n");
            break;
        }
        if (strcmp(buffer,"no") == 0) {
            sprintf(entryLog, "Peticion: %d, %s, fallida\n", tiempoEjecucion, aux->nombre);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);       
            printf("inventario insuficiente\n");
            continue;
        }
        aux = aux->siguiente;
        close(sock);
    }
    solicitando = FALSE;
    //exit(EXIT_SUCCESS);    
}

/*
 * Programa principal para la Bomba
 */
int main(int argc, char** argv) {

    int tError;

    programname = argv[0]; // Guardar nombre del programa para errores

    verificarArgs(argc,argv); 

    // Crear y abrir archivo en modo de escritura
    char log_name[128];
    sprintf(log_name, "log_%s.txt", nombreBomba);
    logClient = fopen(log_name, "w");
    fprintf(logClient, "\0");
    fclose(logClient);
    logClient = fopen(log_name, "a+");

    // Escribir estado inicial del centro en el log
    sprintf(entryLog, "Estado incial: %d\n", inventario);
    fprintf(logClient,"%s",entryLog);
    fflush(logClient);

    tiempoEjecucion = 0;
    solicitando = FALSE;

    servidor *listaCentros = (servidor *) malloc(sizeof(servidor));
    crear(listaCentros); 
    crearListaCentros(listaCentros,ficheroCentros);
    //imprimir(listaCentros);

    while(tiempoEjecucion<=480){


        if(inventario == capacidadMaxima){
            sprintf(entryLog, "Tanque full: %d\n", tiempoEjecucion);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);
        }

        if(inventario == 0){
            sprintf(entryLog, "Tanque vacio: %d\n", tiempoEjecucion);
            fprintf(logClient,"%s",entryLog);
            fflush(logClient);
        }

        if( ((capacidadMaxima - inventario) >= 38000) && (solicitando == FALSE)){
            pthread_t threadSolicitud = (pthread_t *) malloc(sizeof (pthread_t));
            solicitando = TRUE;
            if((tError=pthread_create(&threadSolicitud,NULL,manejadorCliente,(void *)listaCentros)) < 0)
                fatalerror("Error al crear el thread",tError);

        }
        //imprimir(listaCentros);
        tiempoEjecucion++;
        if( (inventario = inventario  - consumo) < 0){
            inventario = 0;
        }
        usleep(100*1000);
    }

    if (fclose(logClient) == 0){

        printf("Termino actividad del cliente.\n");

    }
    //liberar(listaCentros);
    // Agarramos cada elemento de la lista, nos conectamos a ese servidor,
    // preguntamos el tiempo de respuesta, guardamos el tiempo... 
    // Ordenamos la lista por tiempo de respuesta

    // Si el tanque full entonces debo guardar el tiempo en el que esta full
    // Si esta vacio escribimos en el record el momento que queda vacio
    // Llamamos al servidor para solicitar gasolina. (Se toma el primer elemento de la
    // lista, si la respuesta es negativa se continua con el siguiente)

    exit(EXIT_SUCCESS);
}

