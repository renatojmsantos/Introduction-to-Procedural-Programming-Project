#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define max 20

int verifica_viagem(Lista_Viagens lista, char *orig, char *dest, int *array_cod)
{
    int h, i, total=0;
    Lista_Viagens aux = lista;

    while ( aux!=NULL )
        {

            if ( (h=strcmp(aux->destino, dest))== 0 && (i = strcmp(aux->origem, orig)) ==0) /*h==0 significa que sao iguais*/
            {
                printf("%d %s %s %s %s\n", aux->codigo, aux->origem, aux->destino, aux->data, aux->hora);
                *(array_cod +total) = aux->codigo;
                total++;
				if (total==max) /* o array nao tem mais espaço alucado */
                {
                    printf("Nao e possivel verificar mais viagens\n");
                    return total;
                }
            }

        aux = aux->next;
        }

    return total;
}

int in_array(int *array_cod, int cod)
{
    int i = 0;

    while(array_cod[i]!=0 && i<max)
    {
        if (array_cod[i] == cod)
            return 1;
        i++;
    }
    return 0;
}


int verifica_vagas(Lista x, int total_lugares)
{
    int i=0;
    while(x!=NULL)
    {
        x = x->next;
        i++;
        if (i>=total_lugares)
            return 0;
    }
    return 1;
}

void add_reserva(Lista lista_adq_esp, Lista_Clientes lista_clien)  // carregar as listas criadas em funcoes.c
{
    Lista aux, node=NULL;
    while(lista_adq_esp != NULL)
    {
        aux = lista_adq_esp;
        lista_adq_esp = lista_adq_esp->next;    /* procura a primeira vaga (fim da lista) */
    }

    if (aux->cod_cliente==0) /* quer dizer que nao ha nenhum cliente em lista adquiridos/espera */
    {
        aux->cod_cliente = lista_clien->codigo;
    }
    else
    {
        while (node==NULL)
        {
            node = malloc(sizeof(Lista_node)); // aloca a memória solicitada
            if (node !=NULL)
            {
                node->next = NULL;
                node->cod_cliente = lista_clien->codigo;

                aux->next = node;
                aux = aux->next;
            }
        }
    }

}


void adquire(Lista_Viagens lista_viagens, int cod_viagem, Lista_Clientes lista_Client, int cod_cliente)
{
    int i, vaga, pretende, opcao = 1;
    Lista_Viagens aux_viagens = lista_viagens;
    Lista_Clientes aux_cliente = lista_Client;

    /* procura na lista viagem
	pergunta se quer ir adquiridos ou espera
	se adquiridos
		verifica se existe vagas
		se sim
			add reserva
		se nao pergunta se quer ir para espera
            add espera */

    for (i=1; i<cod_viagem; i++)
    {
        aux_viagens =aux_viagens->next;   /* vai para o node da viagem pretendida */
    }

	for (i=1; i<cod_cliente; i++)
	{
		aux_cliente = aux_cliente->next;   /* vai para o node do cliente introduzido */
	}

    while (opcao == 1) // 1 pq é Verdadeira ??????
    {
        printf("Deseja ir para:\n 1- Lista de espera\n 2- Lista de adquiridos \n");
        scanf("%d", &opcao);
        if (opcao==1)
        {
            add_reserva(aux_viagens->Espera, aux_cliente);
            atualiza_array(aux_cliente->espera, cod_viagem, 1);   // 1 = modo (adicionar info) -> ver funcoes.c / modo 0 -> elimina info
            opcao = 0;   // sair
        }
        else if (opcao == 2)
        {
            vaga = verifica_vagas(aux_viagens->Adquiridas, aux_viagens->lugares);
            if (vaga==1) /* existe vagas */
            {

                add_reserva(aux_viagens->Adquiridas, aux_cliente);
                atualiza_array(aux_cliente->adquiridos, cod_viagem, 1);
				opcao = 0;

            }
            else
            {
                printf("Nao existem vagas nessa viagem.\n Pretende ir para a lista de espera? (0-Nao, 1-Sim)\n");
                scanf("%d", &pretende);
                if (pretende == 1)
                {

                    add_reserva(aux_viagens->Espera, aux_cliente);
                    atualiza_array(aux_cliente->espera, cod_viagem, 1);
					opcao = 0;
                }
            }
        }
        else
        {
			while (opcao != 1)
			{
				printf("Inseriu uma opcao invalida\nDesja recomecar(0-Nao, 1-Sim)\n");
				scanf("%d", &opcao);
				if (opcao == 0)
					return;
			}
        }
    }


}

int Adquirir_Viagens(Lista_Clientes list_client, Lista_Viagens list_viag, int cod_max)
{
    int erro, v, escolha=1, o_viagem=1 ,e_cliente=1, op_adquirir=1, cod_cliente=0, cod_via=0, i=0;
    char destino[max], origem[max] , lixo;
    int cod_existentes[max];

    for(i=0; i<max; i++)
        cod_existentes[i]=0; /* inicializar array que vai todos os codigos das viagens*/

    while (op_adquirir==1)
    {
        e_cliente=1;
        o_viagem =1;
        escolha = 1;

        while(escolha==1)
        {
            printf("Insira a origem da viagem: ");
			scanf("%[^\n]s", origem); /* para ler varias palavras ate \n */
			getchar();			/* para ler \n do scanf acima */  // lê um caracter e retorna um inteiro que é o código do caracter
			printf("Insira o destino da viagem: ");
            scanf("%[^\n]s", destino);
            getchar();  // só lê o \n

            v = verifica_viagem(list_viag, origem, destino, cod_existentes); /* ao verificar viagens se encontar viagens que satisfacam
																				input vai pondo em cod_existentes o codigo delas */
            if (v!=0)
            {
                while(o_viagem == 1)
                {
                    printf("Insira codigo da viagem pretendida: ");
                    scanf("%d", &cod_via);
                    getchar();
                    if ( (i = in_array(cod_existentes, cod_via)) == 1)
                    {
                        while (e_cliente == 1)
                        {
                            imprime_clientes(list_client);
                            printf("Insira codigo do cliente: ");
                            scanf("%d", &cod_cliente);
                            gets(&lixo);  // proteção contra caracteres
                            if (cod_cliente>=1 && cod_cliente <=cod_max)
                            {
                                adquire( list_viag, cod_via, list_client, cod_cliente );
								escreve_lista_clientes_fich( list_client );
								escreve_lista_viagens_fich( list_viag );
                                e_cliente = 0;    // igual a zero para sair
                                o_viagem = 0;
                                escolha = 0;
                            }
                            else
                            {
                                erro = 1;
                                printf("Inseriu um codigo de cliente errado");
                                while (erro==1)
                                {
                                    printf("\nDeseja voltar a escrever o codigo do cliente?(0-Nao, 1-Sim)\n");
                                    scanf("%d", &e_cliente);
                                    gets(&lixo);
                                    if (e_cliente==0)
                                        return 0;
                                    else if (o_viagem!=1)
                                    {
                                        system("cls");
                                        printf("ERRO! Inseriu opcao invalida.");
                                    }
                                    else
                                    {
                                        erro = 0;   // opção válida
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        erro = 1;
                        printf("Inseriu um codigo de viagem errado");
                        while (erro == 1)
                        {
                            printf("\n Deseja voltar a escrever o codigo da viagem?(0-Nao, 1-Sim)\n");
                            scanf("%d", &o_viagem);
                            gets(&lixo);
                            if (o_viagem==0)
                                return 0;
                            else if (o_viagem!=1)
                            {
                                system("cls");
                                printf("ERRO!Inseriu opcao invalida.");
                            }
                            else
                            {
                                erro =0;
                            }
                        }
                    }

                }

            }
            else
            {
                erro = 1;
                printf("Nao existe esse viagem");
                while (erro == 1)
                {
                    printf("\nDeseja recomecar?(0-Nao, 1-Sim)\n");
                    scanf("%d", &escolha);
                    gets(&lixo);
                    if (escolha==0)
                        return 0;
                    else if (escolha!=1)
                    {
                        system("cls");
                        printf("ERRO!Inseriu opcao invalida.");
                    }
                    else
                    {
                        erro =0;
                    }
                }

            }

        }

        printf("Deseja adquirir mais viagens? (0-Nao, 1-Sim)\n");
        scanf("%d", &op_adquirir);
        getchar();
        if (op_adquirir == 0)
        {
            return 0;
        }
        else if (op_adquirir != 1)
        {
            printf("ERRO! Inseriu uma opcao invalida\n");
            op_adquirir =1;
        }
    }

    return 0;
}
