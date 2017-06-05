#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int le_linha(FILE *fp, long *num)
{
    int codigo = 0;
    char c='a';  // igual a um caracter qq

    fseek (fp, *num, SEEK_SET); /* vai para o byte num */  // copiado dos powerpoints

    fscanf(fp,"%d", &codigo);
    while (c != '\n')
       {
            fscanf(fp, "%c", &c);
       }

    *num = ftell(fp); // ftell � a posi��o atual no ficheiro

    return codigo;
}

long tamanho_fich(FILE *fp)  // copiado powerpoints
{
    long oldpos = ftell(fp); /* guarda posi��o currente */
    long length;

    if (fseek(fp, 0L, SEEK_END) == -1) /* vai para o fim*/
        return -1;

    length = ftell(fp); /* calcula o tamanho do ficheiro */

    if (fseek(fp, oldpos, SEEK_SET) == -1) /* rep�e file-pointer */
        return -1;
    else return length;
}
