#include <stdio.h>
#include <stdlib.h>
#include "adicionar.h"
#include "funcoes.h"
#define max 20

void escreve_fich_cliente(char *p_nome, char *u_nome, int num_cc)
{
    FILE *fp;
    long tam = 0, num = 0;
    int cod = 0;

    fp = fopen("clientes.txt", "r");

    tam = tamanho_fich(fp);

    while (num < tam)
        {
            cod = le_linha(fp, &num); /* para saber codigo a atribuir a novo cliente */
        }
    fclose(fp);

    cod++;

    fp = fopen("clientes.txt", "a");
    fprintf(fp, "%d;%s;%s;%d;0;0;\n", cod, p_nome, u_nome, num_cc); // 0;0 pq é novo cliente -> logo nao tem nenhuma viagem adquirida nem em espera

    fclose(fp);
}

int Adicionar_Clientes()
{
    char primeiro[max], ultimo[max], lixo;
    int n_cc_invalido = 1, numero_cc, adiciona=1;

    while (adiciona ==1)
    {
        printf("Insira o primeiro e ultimo nome do cliente: ");
        scanf("%s %s", primeiro, ultimo);
        while(n_cc_invalido == 1)
        {
            printf("Insira o numero do cartao de cidadao do cliente: ");
            scanf("%d", &numero_cc);
			gets(&lixo);  // proteção contra caracteres
            if (numero_cc < 100000000 || numero_cc > 999999999)  // CC tem 9 digitos
            {
                printf("Inseriu um numero de cartao de cidadao invalido\n Quer voltar a inserir?(0-Nao/1-Sim)\n");
                scanf("%d", &n_cc_invalido);
				gets(&lixo);  // proteçao
				
            }
            else
            {
                n_cc_invalido = 0;
                printf("Cliente adicionado\n");
            }

        }
        escreve_fich_cliente(primeiro, ultimo, numero_cc);
        printf("Deseja inserir mais clientes?(0-Nao/1-Sim)\n");
        scanf("%d", &adiciona);
    }

    return 0;
}
