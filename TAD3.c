/*
gcc -pedantic -Wcomment -Wformat -Wignored-qualifiers -Wmain -Wmissing-braces -Wmissing-include-dirs -Wparentheses -Wsequence-point -Wreturn-type -Wunused-function -Wunused-variable -Wuninitialized -Warray-bounds -Wundef -Wpointer-arith -Wtype-limits -Wcast-qual -Wwrite-strings -Wempty-body -Wsign-compare -Waddress -Wlogical-op -Wredundant-decls -Winline -Wvla -std=c89 -c TAD3.c -o TAD3.o

gcc -o TAD3 TAD3.o -lm.

./TAD3
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENT 100
#define MAX_MANUFACTURER 32

struct ComponentType
{
    unsigned int            code;
    float                   price;
    int                     availability;
    char                    manufacturer[MAX_MANUFACTURER];
};

struct ComponentType    components[MAX_COMPONENT];
unsigned            lenghtlist;

enum BoolType {TRUE = 1, FALSE = 0};

struct ComponentType * initializeList (void);
int printMenu (void);
void addToList (struct ComponentType * lista, const struct ComponentType * component);
void deleteFromList (struct ComponentType * list, unsigned pos);
struct ComponentType * getFromList(struct ComponentType * list, unsigned pos);
void printList (void);
void printComponent(struct ComponentType * comp);
double getVariance (double * samples, unsigned nsamples);

int main ( void )
{
    unsigned option, i, n;
    struct ComponentType *  list;
    struct ComponentType *  gcomp;
    struct ComponentType    comp;
    double jitter[MAX_COMPONENT];
    double variance;
    clock_t t0, t1;
    enum BoolType bool;

    bool = TRUE; 

    printf("%d",CLOCKS_PER_SEC);

    list = initializeList();

    n = 0;

    while(bool)
    {   

        printf("\n%d\n",lenghtlist);
        option = printMenu();

        switch (option)
        {
            case 1:
            {
                printf("\nInserte [codigo] [precio] [fabricante] [disponibilidad 1/0]\n");
                scanf("%d %f %s %d",&comp.code, &comp.price, (char *) &comp.manufacturer, &comp.availability);
                addToList(list, &comp);
                break;
            }
            case 2:
            {   
                printf("\nInserte la posición que desea borrar\n");
                scanf("%d",&i);
                deleteFromList (list, i);
                break;
            }
            case 3:
            {   
                printf("\nInserte la posición que desea imprimir\n");
                scanf("%d",&i);
                gcomp = getFromList(list,i);

                printf("%d",i);
                printComponent(gcomp);

                break;
            }
            case 4:
            {
                list = initializeList();
                break;
            }
            case 5:
            {   
                
                comp.price = 0;
                strcpy(comp.manufacturer,"Auto");
                comp.availability = 0;
                for (i = lenghtlist; i < MAX_COMPONENT; ++i)
                {   
                    t0 = clock();
                    comp.code = i;
                    addToList(list, &comp);
                    t1 = clock();
                    jitter[i] = (double) (t1 - t0) ;
                    printf("\n%f",jitter[i]);
                }
                variance = getVariance(jitter, MAX_COMPONENT);
                printf("\nJitter = %f\n\n",variance);
                break;
            }
            case 6:
            {
                printList();
                break;
            }
            default:
                break;
        }
        
    }
}

struct ComponentType * initializeList (void)
{   
    lenghtlist = 0;

    return components;
}

int printMenu (void)
{
    int option;

    printf("1. Añadir componente a la lista,\n");
    printf("2. Borrar componente de la lista,\n");
    printf("3. Imprimir en pantalla el componente enésimo,\n");
    printf("4. Vaciar completamente la lista (borrar todos los componentes),\n");
    printf("5. Rellenar la lista con 100 elementos definidos con cualquier contenido\n");

    scanf("%d",&option);

    return option;
}

void addToList (struct ComponentType * list, const struct ComponentType * component)
{
    if (lenghtlist < 100)
    {
        list[lenghtlist].code = component->code;
        list[lenghtlist].price = component->price;
        list[lenghtlist].availability = component->availability;
        strcpy(list[lenghtlist].manufacturer,component->manufacturer);
        ++lenghtlist;
    }
}

void deleteFromList (struct ComponentType * list, unsigned pos)
{
    unsigned i;
    unsigned lenghtend, lenghtrest;
    struct ComponentType * listRest;

    listRest = &list[pos+1];

    lenghtend = lenghtlist - 1;
    lenghtrest = lenghtlist - (pos + 1);
    lenghtlist = pos; 

    printf("%d %d",lenghtlist, pos);

    i = 0;
    while (i < lenghtrest)
    {
        addToList(list, &listRest[i]);
        ++i;
    }
}

struct ComponentType * getFromList(struct ComponentType * list, unsigned pos)
{
    return &list[pos];
}

void printList (void)
{
    unsigned int i;

    printf("\n");
    for (i=0;i<lenghtlist;++i)
    {
        /*printf("%d -> %d %f€ %d %s\n",i+1,components[i].code,components[i].price, components[i].availability, components[i].manufacturer);*/
        printf("%d",i+1);
        printComponent(&components[i]);
    }
    printf("\n");
}

void printComponent(struct ComponentType * comp)
{
    printf(" -> %d %f€ %d %s\n",comp->code,comp->price, comp->availability, comp->manufacturer);
}


double getVariance (double * samples, unsigned nsamples)
{
    unsigned i;
    double media, v;
    double variance;

    media = samples[0];
    for (i=1;i<nsamples;++i)
    {
        media += samples[i];
    }
    media /= nsamples;

    v = (samples[0]) - media ;
    v *= v;
    variance = v;
    for (i=1;i<nsamples;++i)
    {
        v = (samples[i]) - media ;
        v *= v;
        variance += v;
    }
    variance /= (nsamples - 1);

    return media;
}
