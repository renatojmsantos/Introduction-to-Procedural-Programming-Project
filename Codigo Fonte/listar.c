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

} Lista_Viagens_node_dest;

int determinar_tam(Lista_Viagens_dest x)
{
    int i=0;
    while(x!=NULL)
    {
        x = x->next;
        i++;
    }

    return i;
}
void ordena_lista(Lista_Viagens_dest lista)
{
    int trocou=1 ;
	Lista_Viagens_dest aux_1, aux_2, temp;
    int n, j, i, h;

    temp = malloc(sizeof(Lista_Viagens_node_dest));

    aux_1 = lista;
    aux_2 = aux_1->next;

    n = determinar_tam(lista);

    /* BUBBLE SORT para datas*/
    for (i=0; i< n-1 && trocou ; i++)
    {
        trocou = 0;
        for(j=0; j< n-i-1; j++)
        {

            h = strcmp( aux_1->data, aux_2->data );
            if(h > 0) // 1» maior qe a 2»
            {
                trocou = 1;
                temp->codigo = aux_1->codigo;
                strcpy(temp->origem, aux_1->origem);
                strcpy(temp->data, aux_1->data);
                strcpy(temp->destino, aux_1->destino);
                strcpy(temp->hora, aux_1->hora);
                temp->lugares = aux_1->lugares;

                aux_1->codigo = aux_2->codigo;
                strcpy(aux_1->origem, aux_2->origem);
                strcpy(aux_1->data, aux_2->data);
                strcpy(aux_1->destino, aux_2->destino);
                strcpy(aux_1->hora, aux_2->hora);
                aux_1->lugares = aux_2->lugares;

                aux_2->codigo = temp->codigo;
                strcpy(aux_2->origem, temp->origem);
                strcpy(aux_2->data, temp->data);
                strcpy(aux_2->destino, temp->destino);
                strcpy(aux_2->hora, temp->hora);
                aux_2->lugares = temp->lugares;

            }
            else if( h == 0) // datas iguais
            {
                h = strcmp(aux_1->hora, aux_2->hora); // compara horas
                if (h>0) // aux1 > aux2
                {
                    trocou = 1;
                    temp->codigo = aux_1->codigo;
                    strcpy(temp->origem, aux_1->origem);
                    strcpy(temp->destino, aux_1->destino);
                    strcpy(temp->data, aux_2->data);
                    strcpy(temp->hora, aux_1->hora);
                    temp->lugares = aux_1->lugares;
                    /*  a data porque e igual */

                    aux_1->codigo = aux_2->codigo;
                    strcpy(aux_1->origem, aux_2->origem);
                    strcpy(aux_1->data, aux_2->data);
                    strcpy(aux_1->destino, aux_2->destino);
                    strcpy(aux_1->hora, aux_2->hora);
                    aux_1->lugares = aux_2->lugares;

                    aux_2->codigo = temp->codigo;
                    strcpy(aux_2->origem, temp->origem);
                    strcpy(aux_2->data, temp->data);
                    strcpy(aux_2->destino, temp->destino);
                    strcpy(aux_2->hora, temp->hora);
                    aux_2->lugares = temp->lugares;
                }
            }

            aux_1 = aux_1->next;
            aux_2 = aux_2->next;
        }
        aux_1 = lista;
        aux_2 = aux_1->next;

    }

    lista = aux_1;

    free(temp);

}

void imprime_lista_viagem( Lista_Viagens_dest x)
{
    while(x != NULL)
    {
        printf("%d %s -> %s %s %s %d\n", x->codigo, x->origem, x->destino, x->data, x->hora, x->lugares);
        x=x->next;
    }
}
