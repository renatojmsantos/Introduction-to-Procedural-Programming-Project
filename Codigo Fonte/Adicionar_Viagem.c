#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adicionar.h"
#define max 20

typedef struct data {
    int dia, mes, ano;
    } Data;


int dataValida(Data data) {

    switch (data.mes) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if ((data.dia>=1) && (data.dia<=31))
            return 1;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if ((data.dia>=1) && (data.dia<=30))
            return 1;
            break;
        case 2:
            if ((data.dia>=1) && (data.dia<=28))
            return 1;
            else
                if ((data.dia==29) && ((data.ano%4)==0))
                return(1);
                break;
        }
        return 0;
}

void escreve_fich_viagem(char *origem, char *destino, Data data, int hora, int minutos, int lugares)
{
    FILE *fp;
    long tam = 0, num = 0;
    int cod = 0;
    char orig[max], dest[max];

    strcpy(orig, origem); /* tentar fazer funcao sem auxilio destes strcpy */ // copia a string origem pra orig
    strcpy(dest, destino);

    fp = fopen("viagens.txt", "r");

    tam = tamanho_fich(fp);

    while (num < tam)
        {
            cod = le_linha(fp, &num); /*para saber codigo a atribuir a novo cliente*/
        }
    fclose(fp);

    cod++;

    fp = fopen("viagens.txt", "a");

    fprintf(fp, "%d;%s;%s;%d/", cod, orig, dest, data.ano);

    if (data.mes<10)
        fprintf(fp, "0%d/", data.mes);
    else
        fprintf(fp, "%d/", data.mes);
    if (data.dia<10)
        fprintf(fp, "0%d;", data.dia);
    else
        fprintf(fp, "%d;", data.dia);
    if (hora < 10)
        fprintf(fp, "0%d:", hora);
    else
        fprintf(fp, "%d:", hora);

    if (minutos < 10)
        fprintf(fp, "0%d;%d;0;0;\n", minutos, lugares);

    else
        fprintf(fp, "%d;%d;0;0;\n", minutos, lugares);

    fclose(fp);
}

int Adicionar_Viagem()
{
    Data data;
    char origem[max], destino[max], c, c1, c2, lixo;
    int lugares, opcao, horas, minutos, invalido=1, recomecar=1;

    while (invalido == 1)
    {
        printf("Insira origem viagem:\n");
        scanf("%[^\n]s", origem);  // vai ler a string até encontrar um \n
        getchar();
        printf("Insira destino viagem:\n");
        scanf("%[^\n]s", destino);
        getchar();
        if ( (strcmp(origem, destino) == 0)) // compara a string apontada, por origem para a string apontada por destino
        {
            printf("Inseriu origem e destinos iguais\n");
            while ( recomecar == 1)
            {
                printf("Deseja recomecar?(0-Nao/1-Sim)\n");
                scanf("%d", &opcao);
                gets(&lixo);
                if (opcao == 0 )
                {
                    return 0;
                }
                else if (opcao == 1)
                {
                    recomecar = 0;
                }
                else
                {
                    printf("Inseriu uma opcao invalida\n");
                }
            }

        }
        else
        {
            invalido = 0;
            opcao = 1;
        }

    }

    while (opcao == 1)
    {
        printf("Insira a data viagem (aaaa/mm/dd):\n");
        scanf("%d%c%d%c%d", &data.ano, &c1, &data.mes, &c2, &data.dia);
        gets(&lixo);

        if ( dataValida(data) && c1=='/' && c2=='/')
        {
            while (opcao == 1)
            {
                printf("Insira a hora viagem(hh:mm):\n");
                scanf("%d%c%d", &horas, &c, &minutos);
                gets(&lixo);
                if (c == ':' && horas>=0 && horas<24 && minutos>=0 && minutos<60)
                {
                    while (opcao == 1)
                    {
                        printf("Insira o total de lugares da viagem:\n");
                        scanf("%d", &lugares);
                        gets(&lixo);  // proteção
                        if (lugares > 0)
                        {
                            escreve_fich_viagem(origem, destino, data, horas, minutos, lugares);
                            printf("Viagem adicionada! \n");
                            opcao = 0;
                        }
                        else
                        {
                            opcao = 0;
                            printf("Inseriu numero de lugares invalido");
                            while (opcao != 1)
                            {
                                printf("\n Deseja voltar o numero de lugares? (0-Nao / 1-Sim)\n");
                                scanf("%d", &opcao);
                                gets(&lixo);
                                if (opcao == 0)
                                    return 0;
                                else if( opcao != 1)
                                {
                                    system("cls");
                                    printf("Inseriu uma opcao invalida");
                                }

                            }
                        }

                    }
                }
                else
                {
                    opcao = 0;
                    printf("Inseriu uma hora invalida\n");
                    while (opcao != 1)
                    {
                        printf("\n Deseja voltar a escrever a hora? (0-Nao / 1-Sim)\n");
                        scanf("%d", &opcao);
                        gets(&lixo);
                        if (opcao == 0)
                            return 0;
                        else if( opcao != 1)
                        {
                            system("cls");
                            printf("Inseriu uma opcao invalida");
                        }

                    }
                }
            }
        }
        else
        {
            opcao =0;
            printf("Inseriu uma data invalida");
            while (opcao != 1)
            {
                printf("\n Deseja voltar a escrever a data? (0-Nao / 1-Sim)\n");
                scanf("%d", &opcao);
                gets(&lixo);
                if (opcao == 0)
                    return 0;
                else if( opcao != 1)
                    printf("Inseriu uma opcao invalida");

            }
        }
    }
    getchar();

    return 0;
}
