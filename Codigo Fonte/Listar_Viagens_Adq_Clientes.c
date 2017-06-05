#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "listar.h"
#include "Listar_Viagens.h"
#include "Adquirir_Viagens.h"
#define max 20

Lista_Clientes cria_lista_cliente(char *primeiro, char *ultimo)
{
    Lista_Clientes lista=NULL, ptr=NULL, node;
    FILE *fp;

    int array_adquiridos[max], array_espera[max], num, i;

    char linha[100];

    inicializa(array_adquiridos, array_espera);

    fp = fopen("clientes.txt", "r");

    while ( !feof(fp))
    {
        node = malloc(sizeof (Lista_Clientes_node));

        if (node != NULL)
        {
            num = 2; /* para igonrar codigo e ;*/

            fgets(linha, 100, fp);

            node->codigo = atoi( &linha[0] );
            le_nome(node->primeiro_nome, linha, &num);
            i = strcmp(node->primeiro_nome, primeiro);
            if (i == 0)
            {
                le_nome(node->ultimo_nome, linha, &num);
                i = strcmp(node->ultimo_nome, ultimo);
                if (i == 0)
                {
                    node->num_cc = atoi( &linha[ num ] );

                    num = num + 10; /* pois cartao cidadao tem 9 numeros e ignora-se o ";" */

                    copia_para_array(node->adquiridos, linha, &num);
                    num++; /* para ignorar o ";" */
                    copia_para_array(node->espera, linha, &num);

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

    if (lista==NULL)
    {
        lista = malloc(sizeof(Lista_Clientes));
        lista->codigo = -1;
        lista->next = NULL;
        lista->previous = NULL;
    }

    return lista;
}

void copia_array(int *destino, int *origem)
{
    int i;

    for (i = 0; i<max; i++)
    {
        *(destino +i) = *(origem +i);
    }
}

Lista_Viagens_dest cria_lista_viagens_cliente(Lista_Clientes lista_clientes)
{
    Lista_Viagens_dest lista=NULL, ptr=NULL, node=NULL;
    char linha[100];
    int array_adq[max], array_esp[max], array_codigos[max], i=0, j, num=2, h=0, k;
    FILE *fp;

    inicializa(array_codigos, array_adq);

    copia_array(array_adq, lista_clientes->adquiridos);
    copia_array(array_esp, lista_clientes->espera);

    fp = fopen("viagens.txt", "r");

    while ( *(array_adq +i) !=0 && i<max )
    {
        num = 2;
        j=1;
        fseek(fp, 0L, SEEK_SET);    /* poe fp a apontar para inicio ficheiro */
        while (j< *(array_adq +i))  /* procura no ficheiro codigo viagem*/
        {
            fgets(linha, 100, fp);
            j++;
        }
        fgets(linha, 100, fp);

        node = malloc(sizeof (Lista_Viagens_node_destino));
        if (node != NULL)
        {
            node->codigo = atoi( &linha[0] );
            if ( (k = in_array(array_codigos, node->codigo) ) == 0 )  /*significa que nao esta viagem ainda nao esta na lista e e necessario adicionar*/
            {
                node->codigo = atoi( &linha[0] );
                array_codigos[h] = node->codigo;
                h++;
                le_nome(node->origem, linha, &num);
                le_nome(node->destino, linha, &num);

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
            i--;
        }
        i++;
    }

    num = 2;
    i=0;
    while ( array_esp[i] !=0 && i<max)
    {
        j=1;
        fseek(fp, 0L, SEEK_SET);    /* poe fp a apontar para inicio ficheiro */
        while ( j < array_esp[i] )  /* procura no ficheiro codigo viagem*/
        {
            fgets(linha, 100, fp);
            j++;
        }

        fgets(linha, 100, fp);

        node = malloc(sizeof (Lista_Viagens_node_destino));
        if (node != NULL)
        {
            node->codigo = atoi( &linha[0] );
            if ( (k = in_array(array_codigos, node->codigo) ) == 0 )  /*significa que nao esta viagem ainda nao esta na lista e e necessario adicionar*/
            {
                array_codigos[h] = node->codigo;
                h++;
                le_nome(node->origem, linha, &num);
                le_nome(node->destino, linha, &num);

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
            i--;
        }

        i++;
    }
    fclose( fp );

    if (lista == NULL)
    {
        lista = malloc(sizeof(Lista_Viagens_node_destino));
        lista->next = NULL;
        lista->previous = NULL;

        lista->codigo = -1;
    }

    return lista;
}

void liberta(Lista_Clientes x, Lista_Viagens y)
{
    Lista_Clientes aux_1;
    Lista_Viagens aux_2;
    while (x!=NULL)
    {
        aux_1 = x->next;
        free(x);
        x = aux_1;
    }

    while (y!=NULL)
    {
        aux_2 = y->next;
        free(y);
        y = aux_2;
    }
}

void libertar_listas_dest(Lista_Clientes lista_cliente, Lista_Viagens_dest lista_viagens)
{
    Lista_Clientes aux_1;
    Lista_Viagens_dest aux_2;
    while(lista_cliente!=NULL)
    {
        aux_1 = lista_cliente->next;
        free(lista_cliente);
        lista_cliente = aux_1;
    }

    while(lista_viagens != NULL)
    {
        aux_2 = lista_viagens->next;
        free(lista_viagens);
        lista_viagens = aux_2;
    }
}
int Listar_Viagens_Adq_Clientes()
{
    Lista_Clientes lista_cliente;
    Lista_Viagens_dest lista_viagens;
    char primeiro[max], ultimo[max];
    int recomecar = 1;

    while (recomecar == 1)
    {
        system("cls");
        printf("Insira o primeiro nome seguido do ultimo nome do cliente:\n");
        scanf("%s %s", primeiro, ultimo);

        lista_cliente = cria_lista_cliente(primeiro, ultimo);
        if (lista_cliente->codigo == -1)  // nao existe esse cliente
        {
            printf("Nao existe esse cliente");
            while (recomecar == 1)
            {
                printf("\nDeseja recomecar? (0- Nao / 1-Sim)\n");
                scanf("%d", &recomecar);
                if (recomecar == 0)
                {
                    free( lista_cliente );
                    return 0;
                }
                else if ( recomecar != 1)
                {
                    recomecar = 1;
                    printf("Inseriu uma opcao invalida.");
                }
                recomecar = 0;
            }
            recomecar = 1;
        }
        else
        {
            recomecar = 0;
            lista_viagens = cria_lista_viagens_cliente ( lista_cliente );
            if (lista_viagens->codigo != -1)
            {
                ordena_lista(lista_viagens); // Buble sort
                imprime_lista_viagem( lista_viagens );
                libertar_listas_dest(lista_cliente, lista_viagens);
            }
            else
            {
                printf("O cliente inserido nao tem nenhuma viagem adquirida\n");
            }


        }
    }
    getchar();
	getchar(); /* espera input para voltar ao menu */

    return 0;
}
