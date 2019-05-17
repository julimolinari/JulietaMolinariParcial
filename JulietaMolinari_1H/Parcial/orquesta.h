#ifndef ORQUESTA_H_INCLUDED
#define ORQUESTA_H_INCLUDED
#include <string.h>

typedef struct
{
 int id;
 char nombre[50];
 char lugar[50];
 int tipo;
 int isEmpty;
}Orquesta;
#endif


int initOrquesta(Orquesta* list, int len);
int orq_print(Orquesta* listaOrquesta,int len);
int orq_add(Orquesta* listaOrquesta,int len,int indice,char* msgE,int tries);
int orq_freeI(Orquesta* listaOrquesta,int len);
int orq_findById(Orquesta* pOrquesta, int len, int idE);
int orq_alter(Orquesta* listaOrquesta, int len,char* msgE,int tries);
int orq_ordenarAlfa(Orquesta* listaOrquesta,int len);
int orq_isEmptyValid(Orquesta* listaOrquesta,int len);
int orq_totalPromedio(Orquesta* listaOrquesta,int len);
int orq_inform(Orquesta* listaOrquesta, int len,char* msgE,int tries);
int orq_remove(Orquesta* listaOrquesta, int len,char* msgE,int tries);
int orq_getID (Orquesta* listaOrquesta,int len,char* msgE,int tries);

