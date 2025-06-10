#include <stdio.h>

#include "tArbolTweets.h"


int main(void) {
    FILE *hashtags = fopen("hashtags.txt","r");
    FILE *tweets = fopen("tweets.txt","r");
    tHashtag hashtag;
    tElemento elemento;
    tArbol arbol;
    crearABVacio(&arbol);
    while (fgets(hashtag,sizeof hashtag,hashtags)){
        crearElemento(&elemento, hashtag);
        construirAB(&arbol,elemento);
    }
    fclose(hashtags);
    tTweet tweet;

    while (fgets(tweet,sizeof tweet,tweets)){
        analizarTweets(tweet,arbol);
    }
    fclose(tweets);


    inorden(arbol);


    int buscar;
    printf("Quieres buscar algun hashtag? \n  1 = Si \n 2 = No\n");
    scanf("%i[^\n]",&buscar);

    while (buscar == 1){
        char buscado[140];
        printf("Introduzca el hashtag que quiere buscar\n");
        scanf("%s",&buscado);
        imprimirHashtag(buscado,arbol);
        printf("Quieres buscar algun hashtag mas? \n  1 = Si \n 2 = No\n");
        scanf("%i",&buscar);
    }

    int eliminar;
    printf("Quieres eliminar algun nodo?\n 1 = Si \n 2 = No \n");
    scanf("%i",&eliminar);

    // Para eliminar el arbol --> eliminar la lista, eliminar izq y der antes de eliminar el nodo
    while (eliminar == 1){
        char eliminado[140];
        printf("Introdzca el hashtag que quiere eliminar\n");
        scanf("%s",&eliminado);
        eliminarHashtag(eliminado,&arbol);
        printf("Quieres eliminar otro hashtag? \n,1 = Si \n 2 = No \n");
        scanf("%i",&eliminar);
    }

    inorden(arbol);

    return 0;
}
