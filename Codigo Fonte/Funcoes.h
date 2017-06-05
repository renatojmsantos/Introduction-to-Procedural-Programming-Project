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
    char data[11]; /* para ter espaço para o \0*/
    char hora[6]; /* para ter espaço para o \0*/
    int lugares;

    Lista Espera;
    Lista Adquiridas;

    Lista_Viagens next;
    Lista_Viagens previous;

} List_Viagens_node;

void inicializa(int *array_esp, int *array_adq);
void le_nome(char *output, char *input, int *start);
void copia_para_array(int *array_dest, char *array_orig, int *start);
int det_tam(Lista_Viagens x);
void imprime_clientes(Lista_Clientes x);
void escreve_array(FILE *fp, int *x);
Lista_Clientes cria_lista_clientes(int *cod);
void escreve_lista_clientes_fich( Lista_Clientes x);
Lista add_Lista_Esp_Adq(int *array_esp_adq, int lugar, Lista_Clientes lista_clien);
void escreve_lista(FILE *fp, Lista x);
void escreve_lista_viagens_fich( Lista_Viagens x);
Lista_Viagens cria_lista_viagens(Lista_Clientes list_clien);
void liberta_listas(Lista_Clientes lista_clien, Lista_Viagens lista_viag);
void atualiza_array(int *array, int codigo_viagem, int modo);

