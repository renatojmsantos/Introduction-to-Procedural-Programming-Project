#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define max 20


void imprime_viagens( Lista_Viagens x)
{
    while(x != NULL)
    {
        printf("%d %s %s %s %s\n", x->codigo, x->origem, x->destino, x->data, x->hora);
        x=x->next;
    }
}


int verifica_cliente_em_viagem(int *array, int cod_via)
{
    int i;

    for (i=0; i<max && *(array +i)!=0; i++)
    {
        if ( *(array +i) == cod_via) // cod_via = codigo da viagem
            return 1;
    }
    return 0;
}

Lista cancela(Lista lista, int cod_cliente)
{
    Lista aux = lista, anterior=lista;  // lista é a lista de todos os clientes que estao na lista de espera ou de espera
    int i=0;

    while(aux->cod_cliente != cod_cliente)  // vai pra a info da lista onde esta o codigo do cliente
    {
        anterior = aux;
        aux = aux->next;
        i++;
    }

    if (i!=0)
    {
        anterior->next = aux->next;
        free(aux);
		return lista;
    }
    else
    {
        aux = aux->next;
        free(anterior);
		return aux; /* pois passa a ser primeiro node da lista */
    }
}

Lista atualiza_adquiridos_espera(Lista lista_adquiridas, Lista lista_espera)
{
    while (lista_adquiridas->next != NULL)
        lista_adquiridas = lista_adquiridas->next; // vai pra o fim da lista. O último a comprar é o último a ser servido

	if (lista_espera->cod_cliente !=0)  // Se houver alguem na lista de espera passa para o último lugar na lista de adquiridos
    {
        lista_adquiridas->next = lista_espera;
        lista_adquiridas = lista_adquiridas->next;
        lista_espera = lista_espera->next;
        lista_adquiridas->next = NULL;
    }

    return lista_espera;
}
int Cancelar_Viagens(Lista_Clientes lista_clientes, Lista_Viagens lista_viagens, int cod_max_cliente)
{
    Lista_Clientes aux_cliente;
    Lista_Viagens aux_viagem;
    int opcao, erro, escolha=1, cod_cliente=0, cod_via=0, i=0;
    char lixo;


    while (escolha==1)  // verdade
    {
        aux_cliente = lista_clientes; // variaveis auxiliares a apontar pra as listas
        aux_viagem = lista_viagens;

        system("cls");
        printf("Insira que tipo de cancelamento quer:\n 1- Cancelar de viagens adquiridas\n 2- Cancelar de lista de espera\nOpcao: ");
        scanf("%d", &opcao);
        gets(&lixo);
        if (opcao == 1 || opcao == 2)
        {
            imprime_clientes(lista_clientes);
            printf("Insira codigo do cliente: ");
            scanf("%d", &cod_cliente);
            gets(&lixo);
            if (cod_cliente>=1 && cod_cliente <=cod_max_cliente)
            {
                while (aux_cliente->codigo != cod_cliente)
                    aux_cliente = aux_cliente->next;
                /* aux tem o node do cliente introduzido */

                imprime_viagens(lista_viagens);
                printf("Insira o codigo da viagem que o cliente quer cancelar: ");
                scanf("%d", &cod_via);
                getchar();  // ler \n

                while (aux_viagem->codigo != cod_via && aux_viagem!=NULL)
                    aux_viagem = aux_viagem->next;   // verificar se tem a viagem

                if ( aux_viagem == NULL )
                {
                    printf("ERRO!\n O codigo da viagem inserido e invalido");
                    getchar();
                    return 0;
                }

                if (opcao == 1)
                {
                    i = verifica_cliente_em_viagem(aux_cliente->adquiridos, cod_via);

                    if (i==1)
                    {
                        aux_viagem->Adquiridas = cancela(aux_viagem->Adquiridas, cod_cliente);
                        aux_viagem->Espera = atualiza_adquiridos_espera(aux_viagem->Adquiridas, aux_viagem->Espera);
                        atualiza_array(aux_cliente->adquiridos, cod_via, 0);
                        printf("Viagem Cancelada\n");
                    }
                    else
                    {
                        printf("ERRO!\nO cliente nao tem essa viagem adquirida\n");
                        gets(&lixo);
                    }
                }
                else
                {
                    i = verifica_cliente_em_viagem(aux_cliente->espera, cod_via);  // ve se cliente esta na fila de espera
                    if (i==1) // caso seja verdade
                    {
                        aux_viagem->Espera = cancela(aux_viagem->Espera, cod_cliente);
                        atualiza_array(aux_cliente->espera, cod_via, 0);
                        printf("Viagem Cancelada\n");
                    }
                    else
                    {
                        printf("ERRO!\nO cliente nao esta na lista de espera dessa viagem");
                        gets(&lixo);
                    }
                }
                escreve_lista_clientes_fich(lista_clientes);
                escreve_lista_viagens_fich(lista_viagens);
                escolha = 0;
            }
            else
            {
                printf("Inseriu um codigo de cliente errado\n");
                gets(&lixo);
            }
        }
        else
        {
            printf("Inseriu uma opcao invalida");
            erro = 1;  // há erro
            while (erro==1)
            {
                printf("\n Deseja voltar a escrever a opcao?(0-Nao, 1-Sim)\n");
                scanf("%d", &escolha);
                gets(&lixo);
                if (escolha==0)
                {
                    escreve_lista_clientes_fich(lista_clientes);
                    escreve_lista_viagens_fich(lista_viagens);
                    return 0;
                }
                else if ( escolha == 1)
                {
                    erro = 0;
                }
                else
                {
                    system("cls");
                    printf("Inseriu uma opcao invalida.");
                }
            }
        }

    }
    getchar();
    return 0;
}
