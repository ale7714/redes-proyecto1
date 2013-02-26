/* 
 * Universidad Simón Bolivar
 * CI4835 - Redes de Computadoras
 * Proyecto 1 
 * 
 * Archivo:     listaservidor.c
 * Autor:       Alexandra Paredes 05-38680
 *              Javier Rodriguez  05-38838
 * Descripción: Implementacion de la estructura servidor, la cual consiste en el nombre, 
 * la dirección DNS, el puerto y un apuntador al proximo servidor.
 * 
 */

#include "listaservidor.h"

/*  Función: crear
    Entrada:
        lista: Apuntador a la dirección en memoria de la lista
    Salida:
        N/A 
    Función que crea la lista que almacena tipo servidor
*/
void crear(servidor* lista){
    //bzero(lista->nombre,128);
    strcpy(lista->nombre,"NIL");
    //bzero(lista->dns,128);
    strcpy(lista->dns,"NIL"); 
    lista->puerto = 0; 
    lista->tiempoRespuesta = 0; 
    lista->siguiente = NULL; 
}

/*  Función: inicializar
    Entrada:
        nombre: Apuntador al nombre del servidor 
           dns: Apuntador al dns del servidor
        puerto: Entero que representa el puerto
         lista: Apuntador a la dirección en memoria de la lista
    Salida:
        N/A 
    Función que inicializa la lista que almacena tipo servidor
*/
void inicializar(char* nombre, char* dns, int puerto, servidor* lista){
    //bzero(lista->nombre,128);
    strcpy(lista->nombre,nombre);
    //bzero(lista->dns,128);
    strcpy(lista->dns,dns); 
    lista->puerto = puerto; 
    lista->tiempoRespuesta = 0; 
    lista->siguiente = NULL;   
}


/*  Función: insertar
    Entrada:
            lista: Apuntador a la dirección en memoria de la lista
        servNuevo: Apuntador a la dirección en memoria del servidor a insertar en la lista
    Salida:
        N/A 
    Función que inserta a la lista del tipo servidor, el servidor indicado en servNuevo
*/
void insertar(servidor* lista, servidor* servNuevo){
    servidor *temp = lista;
    if(strcmp(temp->nombre,"NIL")!=0){
        while(temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        servidor *ele =  (servidor *) malloc(sizeof(servidor));
        inicializar(servNuevo->nombre,servNuevo->dns,servNuevo->puerto,ele);
        temp->siguiente = ele;
    }else{
        inicializar(servNuevo->nombre,servNuevo->dns,servNuevo->puerto,lista);
    }
}

/*  Función: liberar
    Entrada:
        lista: Apuntador a la dirección en memoria de la lista
    Salida:
        N/A 
    Función que limpia en memoria la lista que almacena tipo servidor
*/
void liberar(servidor* lista){
    servidor *aux; 
    while(lista != NULL){
        aux = lista;    
        strcpy(aux->nombre,""); 
        strcpy(aux->dns,""); 
        aux->puerto = 0;      
        aux->siguiente = NULL;
        free(aux);
        lista = lista->siguiente;
    }
}

/*  Función: imprimir
    Entrada:
        lista: Apuntador a la dirección en memoria de la lista
    Salida:
        N/A 
    Función que imprime la lista que almacena tipo servidor
*/
void imprimir(servidor* lista){
    servidor *aux = lista;
    printf("Lista de Centros de Servicio:\n");
    while(aux != NULL){   
        printf("Nombre centro: %s\n",aux->nombre);
        printf("DNS: %s\n",aux->dns);
        printf("Puerto: %d\n",aux->puerto);   
        printf("Tiempo de Respuesta: %d\n",aux->tiempoRespuesta); 
        printf("\n"); 
        aux = aux->siguiente; 
    }
}
/*  Función: ordenarPorTiempo
    Entrada:
        lista: Apuntador a la dirección en memoria de la lista
    Salida:
        N/A 
    Función que ordena por tiempo de respuesta los elementos de la lista
*/
void ordenarPorTiempo(servidor* lista){
    
    servidor *aux = lista;
    servidor *cont;

    for(; aux->siguiente != NULL; aux = aux->siguiente){

        for(cont = aux->siguiente; cont != NULL; cont = cont->siguiente){
            
            if(aux->tiempoRespuesta > cont->tiempoRespuesta){
                servidor *temp;
                inicializar(aux->nombre,aux->dns,aux->puerto,temp);
                temp->tiempoRespuesta = aux->tiempoRespuesta;
                strcpy(aux->nombre,cont->nombre); 
                strcpy(aux->dns,cont->dns); 
                aux->puerto = cont->puerto;
                aux->tiempoRespuesta = cont->tiempoRespuesta;
                strcpy(cont->nombre,temp->nombre); 
                strcpy(cont->dns,temp->dns); 
                cont->puerto = temp->puerto;
                cont->tiempoRespuesta = temp->tiempoRespuesta;

            }

        }

    }


}

