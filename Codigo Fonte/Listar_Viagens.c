#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "listar.h"
#include "Adquirir_Viagens.h"
#define max 20

Lista_Viagens_dest cria_lista_viagens_destino(char *destino )
{
    Lista_Viagens_dest lista=NULL, ptr=NULL, node;

    FILE *fp;

    int num, i, cod_anterior = 0;
    char input[max], dest[max];
    char linha[100];

    strcpy(input, destino);

    fp = fopen("viagens.txt", "r");

    while ( !feof(fp) )
    {
        node = malloc(sizeof (Lista_Viagens_node_destino));

        if (node != NULL)
        {
            num = 2; /* para igonrar codigo e ;*/

            fgets(linha, 100, fp);

            node->codigo = atoi( &linha[0] );
            if (node->codigo != cod_anterior)
            {
                cod_anterior = node->codigo;
                le_nome(node->origem, linha, &num);
                le_nome(dest, linha, &num);

                i = strcmp (dest, input);

                if (i==0)
                {
                    strcpy(node->destino, dest);
                    le_nome(node->data, linha, &num);
                    le_nome(node->hora, linha, &num);

                    node->lugares= atoi( &linha[num]);

                    node->previous = NULL;
                    node->next = NULL;

                    if (lista == NULL)
                    {
                        lista = node;
                        ptr = lista;
                    }
                    else
                    {
                        ptr->next = node;
                        node->previous = ptr;
                        ptr = node;
                    }
                }
                else
                {
                    free(node);
                }
            }
            else
            {
                free(node);
            }

        }
        else
        {
            printf("ERRO!\nNao foi possivel alocar memoria.\n");
        }
    }

    /* e necessario libertar o ultimo node pois e uma copia do anterior*/

    fclose(fp);

    if (lista==NULL)
    {
        lista = malloc(sizeof(Lista_Viagens_node_destino));
        lista->codigo = -1; //nao ha lista nenhuma
        lista->next = NULL;
        lista->previous = NULL;
    }

    return lista;
}

void liberta_lista(Lista_Viagens_dest lista)
{
    Lista_Viagens_dest aux;

    while (lista != NULL)
    {
        aux = lista->next;
        free(lista);
        lista = aux;
    }
}

int Listar_Viagens()
{
    Lista_Viagens_dest lista;
    char destino[max];

    printf("Insira o destino da viagem: ");
    scanf("%[^\n]s", destino);
    getchar();

    lista = cria_lista_viagens_destino( destino );

    if (lista->codigo !=-1)
    {
        ordena_lista(lista);
        imprime_lista_viagem(lista);
        getchar(); /*usado para ler \n do buffer*/
        liberta_lista(lista);
    }
    else
	{
		printf("Nao exite esse destino\n");
		getchar();
	}

	getchar(); /* usado para esperar que o utilizador clique nalguma tecla para de seguida voltar ao menu*/
    return 0;
}
