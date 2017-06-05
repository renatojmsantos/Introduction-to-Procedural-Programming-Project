#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define max 20


int verifica_se_tem_viagens(int *x, int *y){
    int i=0;
    while (i<max)
    {
        if (*(x+i)!=0) // se encontrar alguma coisa em x[i] ( viagem) quer dizer qe tem viagens
        {
            return 1;
        }
        i++;
    }

    i=0;
    while(i<max)
    {
        if(*(y+i)!=0)  // mesma coisa pra a lista de espera
        {
            return 1;
        }
        i++;
    }
    return 0;
}

Lista_Clientes cria_lista_clientes_listar()
{
    Lista_Clientes lista=NULL, ptr=NULL, node;
    FILE *fp;
    int i,cod_anterior=0;
    int array_adquiridos[max], array_espera[max], num;

    char linha[100];

    inicializa(array_adquiridos, array_espera); // mete os arrays igual a 0

    fp = fopen("clientes.txt", "r");

    while ( !feof(fp))  // enquanto for diferente do fim de ficheiro
    {
        node = malloc(sizeof (Lista_Clientes_node));

        if (node != NULL)
        {
            num = 2; /* para igonrar codigo e ;*/

            fgets(linha, 100, fp);  // le a linha toda de um ficheiro

            node->codigo = atoi( &linha[0] );
            if (node->codigo != cod_anterior){  // certificar que nao lê 2 vezes a mesma linha ( != ). Se nao estiver executa o if
                cod_anterior = node ->codigo;
                le_nome(node->primeiro_nome, linha, &num);
                le_nome(node->ultimo_nome, linha, &num);

                node->num_cc = atoi( &linha[ num ] );

                num = num + 10; /* pois cartao cidadao tem 9 numeros e ignorar ;*/

                copia_para_array(node->adquiridos, linha, &num);
                num++;
                copia_para_array(node->espera, linha, &num);

                i = verifica_se_tem_viagens(node->adquiridos, node->espera);
                if (i==1){
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

                    inicializa(array_adquiridos, array_espera);
                }
                else{
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

    fclose(fp);

    return lista;
}

void libertar ( Lista_Clientes x)
{
	Lista_Clientes aux;

	while (x!=NULL)
	{
		aux = x->next;
		free (x);
		x = aux;
	}
}
int Listar_Clientes()
{
    Lista_Clientes clientes;
    clientes = cria_lista_clientes_listar();
    printf("Lista de todos os clientes com viagens adquiridas/espera\n\n");
    imprime_clientes( clientes );
	libertar ( clientes );
    getchar();

    return 0;
}
