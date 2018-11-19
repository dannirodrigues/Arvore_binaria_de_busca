#ifndef _ABB_PRIV_H
#define _ABB_PRIV_H

#include "abb_interface.h"

struct nodearv{
    void* info;
    /*vários outros dados*/
    node_t* esquerda;
    node_t* direita;
};

struct arvorebb{
    long tamanho;
    node_t* raiz;
    void (*destroi)(void **data);
    void (*imprime)(const void *data);
    int (*compara)(const void *key1, const void* key2); //0=igual; >0 key2 maior e key 1 menor; <0 key1 maior e key2 menor
};

#endif