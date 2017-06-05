#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"
#include "Adicionar_Clientes.h"
#include "Adicionar_Viagem.h"
#include "Adquirir_Viagens.h"
#include "Cancelar_Viagens.h"
#include "Listar_Clientes.h"
#include "Listar_Viagens.h"
#include "Listar_Viagens_Adq_Clientes.h"

void menu(Lista_Clientes lista_clientes, Lista_Viagens lista_viagens, int cod_max_cliente)
{
    int opcao, escolha;
    char lixo;
    int erro = 1;

    system("cls");

    while(1)
    {
        printf("\t\t\t\t-MENU-\n");
        printf("1- Lista de Viagens\n");
        printf("2- Adicionar Cliente/Viagem\n");
        printf("3- Adquirir Viagens\n");
        printf("4- Cancelar Viagem\n");
        printf("5- Lista de Clientes\n");
        printf("6- Sair\n");
        printf("Insira opcao: ");
        scanf("%d", &opcao);

        gets(&lixo);
        if (opcao>0 && opcao<7)
        {
            switch (opcao)
            {
                case (1):
                {
                    while (opcao == 1)
                    {
                        printf("\n1- Listar Viagens por destino\n2- Listar Viagens por cliente\nOpcao: ");
                        scanf("%d", &escolha);
                        getchar();
                        if (escolha == 1)
                        {
                            printf("\n");
                            Listar_Viagens();
                            opcao = 0;
                        }

                        else if (escolha == 2)
                        {
                            printf("\n");
                            Listar_Viagens_Adq_Clientes();
                            opcao = 0;
                        }
                        else
                        {
                            system("cls");
                            printf("Inseriu uma escolha invalida\n");

                        }
                    }
                    break;
                }
                case (2):
                {
                    while (opcao ==2)
                    {
                        printf("\n1- Adicionar Cliente\n2- Adicionar Viagem\nOpcao: ");
                        scanf("%d", &escolha);
                        getchar();
                        if (escolha == 1)
                        {
                            printf("\n");
                            Adicionar_Clientes();
                            opcao = 0;
                        }

                        else if (escolha == 2)
                        {
                            printf("\n");
                            Adicionar_Viagem();
                            opcao = 0;
                        }
                        else
                        {
                            system("cls");
                            printf("Inseriu uma escolha invalida\n");

                        }
                    }

                    break;
                }
                case (3):
                {
                    printf("\n");
                    Adquirir_Viagens(lista_clientes, lista_viagens, cod_max_cliente);
                    break;
                }
                case (4):
                {
                    printf("\n");
                    Cancelar_Viagens(lista_clientes, lista_viagens, cod_max_cliente);
                    break;
                }
                case (5):
                {
                    printf("\n");
                    Listar_Clientes();
                    break;
                }
                case (6):
                {
                    return;
                }
            }

            system("cls");
        }
        else
        {
            printf("\nERRO: A opcao deve estar entre 1 e 5\n");
            erro = 1;
            while (erro == 1)
            {
                printf("\nPretende regressar ao menu(0-Nao 1-Sim)? ");
                scanf("%d", &opcao);
                gets(&lixo);
                system("cls");
                if (opcao == 0)
				{
					return;
				}
                    
                else if (opcao == 1)
				{
					erro = 0;
				}
                    
                else
				{
					printf("ERRO: Deve introduzir 0 se nao quiser voltar ao menu e 1 caso contrario.\n");
				}
                    
            }
        }
    }

}
int main()
{
	Lista_Clientes lista_clientes; // cria variaveis qe dps vao ficar a info das listas
	Lista_Viagens lista_viagens;
	int cod_max_cliente;

	lista_clientes = cria_lista_clientes(&cod_max_cliente);
	lista_viagens = cria_lista_viagens(lista_clientes);

    menu(lista_clientes, lista_viagens, cod_max_cliente); // assim qe começa o programa sao logo carregadas as listas
	liberta_listas( lista_clientes, lista_viagens );
	return 0;
}
