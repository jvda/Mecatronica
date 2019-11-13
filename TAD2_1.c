/*
gcc TAD2_1.c -o TAD2_1 -pedantic -Wcomment -Wformat -Wignored-qualifiers -Wmain -Wmissing-braces -Wmissing-include-dirs -Wparentheses -Wsequence-point -Wreturn-type -Wunused-function -Wunused-variable -Wuninitialized -Warray-bounds -Wundef -Wpointer-arith -Wtype-limits -Wcast-qual -Wwrite-strings -Wempty-body -Wsign-compare -Waddress -Wredundant-decls -Winline -Wvla -std=c89

./TAD1_1
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


char xorWord(char * word);
void printBinbaryChar (char byte);
void printDesgloseChar (char * nameVar, char c);
void printDesgloseWord (char * word);
void textTxFromMx (char * tx, char mx);

int main ( void )
{
    char name[MAX], surnames[MAX], dni[MAX], dni1[MAX], dni2[MAX], ta[MAX], tb[MAX];
    char n1a, n2a, ma, pa, qa;
    char n1b, n2b, mb, pb, qb;
    char c;
    unsigned int x;

    /* Buscar enunciado */

    printf("Introduzca su nombre de pila:\n");
    scanf("%s",name);
    n1a = xorWord(name);
    printDesgloseWord (name);
    printDesgloseChar ("N1A", n1a);

    printf("Introduzca sus apellidos:\n");
    scanf("%s",surnames);
    n2a = xorWord(surnames);
    printDesgloseWord (surnames);
    printDesgloseChar ("N2A", n2a);
    
    ma = n1a & ((1<<1)|(1<<0));
    printDesgloseChar ("MA", ma);

    pa = ((n1a & ((1<<2)|(1<<3)|(1<<4))) >> 2) + 1;
    printDesgloseChar ("PA", pa);

    qa = n2a & ((1<<0)|(1<<1)|(1<<2));
    printDesgloseChar ("QA", qa);



    printf("Introduzca sus DNI:\n");
    scanf("%s",dni);

    strncpy(dni1, dni, 4);
    strncpy(dni2, &dni[4], 4);

    n1b = xorWord(dni1);
    printDesgloseWord (dni1);
    printDesgloseChar ("N1B", n1b);

    n2b = xorWord(dni2);
    printDesgloseWord (dni2);
    printDesgloseChar ("N2B", n2b);
    
    mb = n1b & ((1<<1)|(1<<0));
    printDesgloseChar ("MB", mb);

    pb = ((n1b & ((1<<2)|(1<<3)|(1<<4))) >> 2) + 1;
    printDesgloseChar ("PB", pb);

    qb = n2b & ((1<<0)|(1<<1)|(1<<2));
    printDesgloseChar ("QB", qb);

    if (ma == 3 && mb == 3)
    {
        ma = 0;
    }
    else if (ma != 3 && mb != 3)
    {
        if (ma <= mb) ma = 3;
        else mb = 3;
    }
    
    textTxFromMx (ta, ma);
    textTxFromMx (tb, mb);

    printf("\nObtén un número nuevo a partir del valor de la variable 'x' haciendo lo siguiente: ");
    printf("\n%s",ta);
    if (ma == 3) printf(" %d bit(s)",pa);
    printf(" el bit nº %d de x\n",qa);
    printf(", y luego ");
    printf("\n%s",tb);
    if (mb == 3) printf("%d bit(s)",pb);
    printf(" el bit nº %d en el resultado\n\n",qb);

    /* Expresión */

    while (1)
    {
        printf("Introdux¡zca el valor de X:\n");
        scanf("%d",&x);

        x &= 0xFFFF; /*Se supone que un unsigned int ocupa solo 2 byte; En este caso es más facil hacerlo así*/
        printf("%d = %04X = ",x,x);
        printBinbaryChar( (char) (x >> 8) );
        printBinbaryChar( (char) x );
        printf("\n");

        x = (x | ((x & (1<<1)) << 1)) & (((x | ~(1<<1)) << 1) | ~(1<<2)) ^ (1<<6);

        printf("%d = %04X = ",x,x);
        printBinbaryChar( (char) (x >> 8) );
        printBinbaryChar( (char) x );
        printf("\n");
    }
}

char xorWord (char * word)
{
    static char xor;
    static int i;

    i = 1;
    xor = word[0];
    while (word[i]!=0)
    {
        xor ^= word[i];
        ++i;
    }

    return xor;
}

void printBinbaryChar (char byte)
{
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte));
}

void printDesgloseWord (char * word)
{
    int i;

    i = 0;
    while (word[i]!=0)
    {
        printf("%C = %02X = ",word[i],word[i]);
        printBinbaryChar(word[i]);
        printf("\n");

        /*printDesgloseChar ( word[i], word[i]);*/
        
        ++i;
    }

}

void printDesgloseChar (char * nameVar, char c)
{
    printf("%s = %02X = ",nameVar,c);
    printBinbaryChar(c);
    printf("\n");
}

void textTxFromMx (char * tx, char mx)
{
    switch (mx)
    {
        case 0:
        {   
            strcpy(tx,"pon a cero");
            break;
        }
        case 1:
        {   
            strcpy(tx,"pon a uno"); 
            break;
        }
        case 2:
        {   
            strcpy(tx,"complementa"); 
            break;
        }
        default:
        {   
            strcpy(tx,"desplaza a la izquierda (y sustituye lo que hubiera en ese lugar)");
            break;
        }
    }
}
