#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 20

typedef struct Lnode_Clientes *Lista_Clientes;

typedef struct Lnode_Clientes
{
    int codigo;
    char primeiro_nome[max];
    char ultimo_nome[max];
    int num_cc;
    int adquiridos[max];
    int espera[max];

    Lista_Clientes next;
    Lista_Clientes previous;

} Lista_Clientes_node;

typedef struct L_node_Lista *Lista;

typedef struct L_node_Lista
{
    int cod_cliente;

    /*Lista_Clientes ptr;*/

    Lista next;
} Lista_node;

typedef struct Lnode_Viagens *Lista_Viagens;

typedef struct Lnode_Viagens
{
    int codigo;
    char origem[max];
    char destino[max];
    char data[11]; /* para ter espaço para o \0 */   // \0 = fim da string
    char hora[6]; /* para ter espaço para o \0 */
    int lugares;

    Lista Espera;
    Lista Adquiridas;

    Lista_Viagens next;
    Lista_Viagens previous;

} List_Viagens_node;

void inicializa(int *array_esp, int *array_adq)
{
    int i;

    for (i=0; i<max; i++)
    {
        *(array_adq +i)=0;
        *(array_esp +i)=0;
    }
}

void le_nome(char *output, char *input, int *start) // só é usada pra ler 1º e ultimo nome do cliente. E ler destino e origem das viagens
{
    int i=0;


    while ( *( input + *start) !=';' && *( input + *start) != '\n') // lê nome até encontrar ; e \n
    {
        *(output +i) = *(input + *start); //
        i++; // Vai incrementando i (posição do array onde guarda a informação) até chegar a max, ou ; ou \n
        if (i == max)
            break;

        *start = *start + 1; // incrementa a posiçao do array de entrada
    }
    output[i]='\0'; /* fim da string*/
    *start = *start +1;
}

void copia_para_array(int *array_dest, char *array_orig, int *start)   // ?????
{
    int i=0;

    while ( *( array_orig + *start) !=';' && *( array_orig + *start) != '\n')
    {
        if ( *( array_orig + *start) !='|')  //  ' | ' separa os códigos dos clientes. Se a encontrar a encontrar nao faz nada
        {
            *(array_dest +i) =  atoi( &(*(array_orig + *start))  );  //atoi -> converte um caracter num inteiro
            i++;
        }
        *start = *start + 1;

        if (i == max-1)
            break;
    }
    *(array_dest + i) = 0;
}

int det_tam(Lista_Viagens x)
{
    int i=0;
    while(x!=NULL)
    {
        x = x->next;
        i++;
    }

    return i;
}

void imprime_clientes(Lista_Clientes x)
{
    while(x!=NULL)
    {
        printf("%d %s %s %d\n", x->codigo, x->primeiro_nome, x->ultimo_nome, x->num_cc);
        x = x->next;
    }
}

void escreve_array(FILE *fp, int *x)
{
    int i=0;
    while (*(x + i) != 0)
    {
        fprintf(fp, "%d|", *(x +i));
        i++;
    }
    if (i==0)
        fprintf(fp, "00");  // 00 se nao tiver la info nenhuma
    fseek(fp, -1, SEEK_CUR); // SEEK_CUR -> da posiçao atual anda 1 byte para tras
    fprintf(fp,";");  // Anda sempre 1 byte para trás . escreve a info e | até nao haver mais info no array
    // coloca ; se ja nao houver mais info a escrever no ficheiro
}

Lista_Clientes cria_lista_clientes(int *cod)
{
    Lista_Clientes lista=NULL, ptr=NULL, node;
    FILE *fp;

    int array_adquiridos[max], array_espera[max], num;

    char linha[100];

    inicializa(array_adquiridos, array_espera);

    fp = fopen("clientes.txt", "r");

    while ( !feof(fp))  // fim do ficheiro
    {
        node = malloc(sizeof (Lista_Clientes_node));  // aloca memoria

        if (node != NULL)
        {
            num = 2; /* para ignorar codigo e ; começa a ler nome do cliente */

            fgets(linha, 100, fp);

            node->codigo = atoi( &linha[0] );
            le_nome(node->primeiro_nome, linha, &num);
            le_nome(node->ultimo_nome, linha, &num);

            node->num_cc = atoi( &linha[ num ] );  // converte um caracter num inteiro

            num = num + 10; /* pois cartao cidadao tem 9 numeros */

            copia_para_array(node->adquiridos, linha, &num);
            num++;
            copia_para_array(node->espera, linha, &num);

            node->previous = NULL;
            node->next = NULL;

            if (lista == NULL)    /* A lista nao aponta pra nada. É criada uma variavel aux e apontada pra o node da info do cliente */
            {
                lista = node;
                ptr = lista;
            }
            else
            {
                ptr->next = node; // como ja exite um primeiro elemento da lista faz as ligaçoes necessarias pra ficar tudo ordenado
                node->previous = ptr;
                ptr = node;
            }
            inicializa(array_adquiridos, array_espera);
        }
        else
        {
            printf("ERRO!\n Nao foi possivel alocar memoria.\n");  // só pra verificar se está a alocar bem as memorias
        }

    }

    *cod = node->codigo;

    /* e necessario libertar o ultimo node pois e uma copia do anterior*/
    ptr->previous->next = NULL;
    free(ptr);

    fclose(fp);

    return lista;

}

void escreve_lista_clientes_fich( Lista_Clientes x)
{
    FILE *fp;

    fp = fopen("clientes.txt", "w");

    while(x != NULL)
    {
        fprintf(fp,"%d;%s;%s;%d;", x->codigo, x->primeiro_nome, x->ultimo_nome, x->num_cc);
        escreve_array(fp, x->adquiridos);
        escreve_array(fp, x->espera);
        fprintf(fp,"\n");
        x = x->next;

    }

    fclose(fp);

}

Lista add_Lista_Esp_Adq(int *array_esp_adq, int lugar, Lista_Clientes lista_clien)
{
    Lista node=NULL, lista=NULL, temp=NULL;
    Lista_Clientes aux = lista_clien;

    int i, j;

    for (i=0; i<lugar && *(array_esp_adq + i) != 0; i++)
    {

        node = malloc( sizeof (Lista_node));

        if (node!=NULL)
        {
            for (j=1; j< *(array_esp_adq +i); j++)
            {
                lista_clien = lista_clien->next;
            }

            node->cod_cliente = lista_clien->codigo;
            /*printf("node->cod_cliente %d\n", node->cod_cliente);
            node->ptr = lista_clien;*/

            node->next = NULL;

            if (lista==NULL)
            {
                lista = node;
                temp = lista;
            }
            else
            {
                temp->next = node;
                temp = temp->next;
            }
        }
        lista_clien = aux;
    }

    if (i==0)
    {
        while (lista == NULL)
        {
            lista = malloc(sizeof (Lista_node ) );
            if (lista!=NULL)
            {
                lista->cod_cliente = 0;
                lista->next = NULL;
            }
        }
    }
    return lista;
}

void escreve_lista(FILE *fp, Lista x)
{
    int i=0;

    while (x!= NULL)
    {
        fprintf(fp, "%d|", x->cod_cliente);
        i++;
        x=x->next;
    }
    if (i==0)    // parecido a escreve_array
        fprintf(fp, "00");

    fseek(fp, -1, SEEK_CUR);
    fprintf(fp,";");
}

void escreve_lista_viagens_fich( Lista_Viagens x)
{
    FILE *fp;

    fp = fopen("viagens.txt", "w");

    while(x != NULL)
    {
        fprintf(fp, "%d;%s;%s;%s;%s;%d;", x->codigo, x->origem, x->destino, x->data, x->hora, x->lugares);
        escreve_lista(fp, x->Adquiridas);
        escreve_lista(fp, x->Espera);
        fprintf(fp, "\n");
        x=x->next;
    }
    fclose(fp);
}

Lista_Viagens cria_lista_viagens(Lista_Clientes list_clien)  // parecido a criar lista_clientes
{
    Lista_Clientes aux = list_clien;
    Lista_Viagens lista=NULL, ptr=NULL, node;

    FILE *fp;

    int num, lugar;
    int array_adq[max], array_esp[max];

    char linha[100];

    inicializa(array_adq, array_esp);

    fp = fopen("viagens.txt", "r");

    while ( !feof(fp) )
    {
        aux = list_clien;
        node = malloc(sizeof (List_Viagens_node));

        if (node != NULL)
        {
            num = 2; /* para igonrar codigo e ; */

            fgets(linha, 100, fp);

            node->codigo = atoi( &linha[0] );
            le_nome(node->origem, linha, &num);
            le_nome(node->destino, linha, &num);
            le_nome(node->data, linha, &num);
            le_nome(node->hora, linha, &num);

            lugar = atoi( &linha[num]);
            node->lugares= lugar;

            num = num+2;
            copia_para_array(array_adq ,linha, &num);
            num++;
            copia_para_array(array_esp ,linha, &num);

            node->Adquiridas = add_Lista_Esp_Adq(array_adq, lugar, aux);
            node->Espera = add_Lista_Esp_Adq(array_esp, max, aux);

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
                (ptr->next)->previous = ptr;
                ptr = ptr->next;
            }

            inicializa(array_adq, array_esp);

        }
        else
        {
            printf("ERRO!\nNao foi possivel alocar memoria.\n");
        }
    }
    /* e necessario libertar o ultimo node pois e uma copia do anterior*/
    ptr->previous->next = NULL;
    free(ptr);

    fclose(fp);
    return lista;
}

void liberta_listas(Lista_Clientes lista_clien, Lista_Viagens lista_viag)  //liberta as 2 listas
{
    Lista_Clientes aux_1;
    Lista_Viagens aux_2;
    Lista aux_3;
    while(lista_clien!=NULL)
    {
        aux_1 = lista_clien->next;
        free(lista_clien);
        lista_clien = aux_1;
    }

    while(lista_viag != NULL)
    {
        aux_2 = lista_viag->next;
        while (lista_viag->Espera!=NULL) /* liberta lista espera*/
        {
            aux_3 = lista_viag->Espera->next;
            free(lista_viag->Espera);
            lista_viag->Espera = aux_3;
        }
        while (lista_viag->Adquiridas!=NULL) /* liberta lista adquiridas*/
        {
            aux_3 = lista_viag->Adquiridas->next;
            free(lista_viag->Adquiridas);
            lista_viag->Adquiridas = aux_3;
        }
        free(lista_viag);
        lista_viag = aux_2;
    }
}

void atualiza_array(int *array, int codigo_viagem, int modo)
{
    int i=0;

    if ( modo == 0 )  /* elimina info */
    {
        while ( *(array +i) != codigo_viagem )/* procura a viagem a eliminar*/
        {
            i++;
            if (i==max-1)
                break;
        }
        while (i<max-1)
        {
            *(array +i) = *(array +i+1); /* copia a restante info do array eliminando o cod_viagem que foi cancelada*/
            i++;
        }
		*(array + max-1) = 0;	/* caso o array estive-se "cheio" o ultimo elemento passa a ser zero*/
    }
    else /*add info*/
    {
        while ( *(array +i)!=0 )
        {
            i++;
            if (i==max)
                break;
        }
        *(array +i) = codigo_viagem;
        *(array +i+1) = 0;  // medida de segurança: certificar que nao ha mais info
    }
}
