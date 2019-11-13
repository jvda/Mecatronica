
/*
gcc TAD2_2.c -o TAD2_2 -pedantic -Wcomment -Wformat -Wignored-qualifiers -Wmain -Wmissing-braces -Wmissing-include-dirs -Wparentheses -Wsequence-point -Wreturn-type -Wunused-function -Wunused-variable -Wuninitialized -Warray-bounds -Wundef -Wpointer-arith -Wtype-limits -Wcast-qual -Wwrite-strings -Wempty-body -Wsign-compare -Waddress -Wredundant-decls -Winline -Wvla -std=c89

./TAD1_2
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 60
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


void printBinbaryChar (char byte);

int main ( void )
{
    unsigned int x;

    /* Buscar enunciado */

    printf("\nObtén un número nuevo a partir del valor de la variable 'x' haciendo lo siguiente: \n");
    printf("desplaza a la izquierda (y sustituye lo que hubiera en ese lugar) 1 bit(s) el bit nº 1 de x\n");
    printf(", y luego\n"); 
    printf("complementa el bit nº 6 en el resultado\n");

    /* Expresión */

    while (1)
    {
        printf("\nIntroduzca el valor de X:\n");
        scanf("%d",&x);

        x &= 0xFFFF; /*Se supone que un unsigned int ocupa solo 2 byte; En este caso es más facil hacerlo así*/
        printf("%d = 0x%04X = b",x,x);
        printBinbaryChar( (char) (x >> 8) );
        printBinbaryChar( (char) x );
        printf("\n");

        x = ((x | ((x & (1<<1)) << 1)) & (((x | ~(1<<1)) << 1) | ~(1<<2))) ^ (1<<6);

        printf("%d = 0x%04X = b",x,x);
        printBinbaryChar( (char) (x >> 8) );
        printBinbaryChar( (char) x );
        printf("\n");
    }
}

void printBinbaryChar (char byte)
{
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte));
}
