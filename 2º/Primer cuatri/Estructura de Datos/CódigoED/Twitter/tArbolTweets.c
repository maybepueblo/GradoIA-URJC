//
// Created by pueblo on 6/9/25.
//

#include "tArbolTweets.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearABVacio(tArbol*arbol) {
    *arbol = NULL;
}

void construirAB(tArbol*arbol, tElemento elem) {
    if (esABVacio(*arbol)) {
        *arbol = (tArbol) malloc(sizeof(tNodo));
        asignar(&((*arbol)->info), elem);
        (*arbol)->izq = NULL;
        (*arbol)->der = NULL;
    } else {
        tElemento r;
        asignar(&(r), (*arbol)->info);
        if (esMenor(r, elem.hashtag)) {
            construirAB(&((*arbol)->der), elem);
        } else {
            construirAB(&((*arbol)->izq), elem);
        }
    }
}

void inorden(tArbol arbol) {
    if (arbol == NULL) return;
    tElemento e = arbol->info;
    inorden(arbol->izq);
    printf("%s \n", e.hashtag);
    inorden(arbol->der);
}

int extraerHashtag(char* tweet, int i){
    int j;
    int longitud = strlen(tweet);
    for (j = 0;i< longitud;i++,j++){
        if (tweet[i] == '\n' ||tweet[i] == '.' ||tweet[i] == ',' ||tweet[i] == '!' ||tweet[i] == '?' ||tweet[i] == ' ' ||tweet[i] == ':' ||tweet[i] == ';'){
            break;
        }
    }
    return j;
}

void incluirTweet(char* hashtag,char* tweet, tArbol arbol ){
    if (esABVacio(arbol)){
        return;
    }
    tElemento* r = &(arbol->info);
    if (SonIguales(r->hashtag,hashtag)){
        construirLista(&(r->listaTweets),tweet);
        return;
    }
    if (esMenor(*r,hashtag)){
        incluirTweet(hashtag,tweet,arbol->der);
    }else{
        incluirTweet(hashtag,tweet,arbol->izq);
    }
}

void analizarTweets(tArbol arbol, tTweet tweet) {
    char destino[140];
    int i,j;
    int longitud = strlen(tweet);
    char caracter;
    for(i = 0;i< longitud;i++){
        caracter = tweet[i];
        if (caracter == '#'){
            j = extraerHashtag(tweet,i);
            memset(destino,0,sizeof(destino));
            strncpy(destino, tweet + i, j);
            incluirTweet(destino,tweet,arbol);
        }
    }
}

void imprimirHashtag(tArbol arbol, tHashtag buscado) {
}

void eliminarHashtag(tArbol*arbol, tHashtag eliminado) {
    tArbol aux;
    if((*arbol != NULL)){
        aux = *arbol;
        if (SonIguales(aux->info.hashtag,eliminado)) {
            if ((*arbol)->izq == NULL) {
                *arbol = (*arbol)->der;
                free(aux);
            } else if ((*arbol)->der == NULL) {
                *arbol = (*arbol)->izq;
                free(aux);
            } else{
                tArbol aux1 = aux->der;
                tArbol aux2 = aux;

                while (aux1->izq != NULL){
                    aux2 = aux1;
                    aux1 = aux1->izq;
                }

                aux->info = aux1->info;

                if (aux2 == aux1){
                    aux2->der = aux1->der;
                }else{
                    aux2->izq = aux1->der;
                }
            }
        }else {
            tElemento r = aux->info;
            if (esMenor(r,eliminado)){
                eliminarHashtag(eliminado,&(aux->der));
            }else
                eliminarHashtag(eliminado,&(aux->izq));
        }
    }else{
        printf("No existe el hashtag");
        return;
    }
}

int esABVacio(tArbol arbol) {
    return arbol == NULL;
}

