#ifndef listar
#define listar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 20

typedef struct Lnode_Viagens_dest *Lista_Viagens_dest;

typedef struct Lnode_Viagens_dest
{
    int codigo;
    char origem[max];
    char destino[max];
    char data[11]; /* para ter espaço para o \0*/
    char hora[6]; /* para ter espaço para o \0*/
    int lugares;

    Lista_Viagens_dest next;
    Lista_Viagens_dest previous;

} Lista_Viagens_node_destino;
#endif


void ordena_lista(Lista_Viagens_dest lista);
void imprime_lista_viagem( Lista_Viagens_dest x);
