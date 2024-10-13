#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Nodo
{
    char *linea;
    struct Nodo *liga;
}NODO;
NODO* creaNodo(char *linea);
void agregarNodo(NODO **cab,char *linea);
NODO* lectArch(const char *nomArch);
void imprimirLista(NODO *cab);
void liberarLista(NODO *cab);
int main()
{
    char nombreArchivo[256];
    NODO *lista = NULL;
    char opcion;
    do {
        printf("\nIngrese el nombre del archivo a leer (incluya al final la extension "".txt""): ");
        scanf("%s",nombreArchivo);
        lista=lectArch(nombreArchivo);
        if (lista==NULL)
                printf("No existe el archivo '%s'\n",nombreArchivo);
         else
            {
                printf("Tu archivo:\n");
                imprimirLista(lista);
                liberarLista(lista);
            }
        printf("Quieres leer otro archivo (s:si/n:no) ");
        scanf(" %c",&opcion);
        } while(opcion=='s'||opcion=='S');
}
NODO* creaNodo(char *linea)
{
    NODO *nvo=(NODO*)malloc(sizeof(NODO));
    if (nvo==NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    nvo->linea=strdup(linea);
    nvo->liga=NULL;
return (nvo);
}
void agregarNodo(NODO **cab,char *linea)
{
NODO *nvoNodo=creaNodo(linea);
    if (*cab==NULL)
    {
        *cab=nvoNodo;
    }
    else
    {
        NODO *nvo=*cab;
        while(nvo->liga!=NULL)
        {
            nvo=nvo->liga;
        }
        nvo->liga=nvoNodo;
    }
}
NODO* lectArch(const char *nomArch)
{
char buffer[256];
NODO *lista=NULL;
FILE *arch=fopen(nomArch,"r");
    if (arch==NULL)
            return NULL;
    while(fgets(buffer,sizeof(buffer),arch)!=NULL)
        {
            buffer[strcspn(buffer,"\n")]=0;
            agregarNodo(&lista,buffer);
        }
    fclose(arch);
return (lista);
}
void imprimirLista(NODO *cab)
{
NODO *nvo=cab;
    while(nvo!= NULL)
        {
            printf("%s\n",nvo->linea);
            nvo=nvo->liga;
        }
}
void liberarLista(NODO *cab)
{
    NODO *nvo;
    while(cab!=NULL)
        {
            nvo=cab;
            cab=cab->liga;
            free(nvo->linea);
            free(nvo);
        }
}
