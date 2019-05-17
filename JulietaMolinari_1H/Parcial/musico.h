#ifndef MUSICO_H_INCLUDED
#define MUSICO_H_INCLUDED
#include <string.h>
#include "orquesta.h"
#include "intrumentos.h"


typedef struct
{
 int id;
 char nombre[51];
 char apellido[51];
 int edad;
 int idOrq;
 int idInst;
 int isEmpty;
}Musico;
#endif


int initMusico(Musico* list, int len);
int mus_print(Musico* listaMusico,int len);
int mus_add(Musico* listaMusico,Orquesta* listaOrquesta,Instrumento* listaInstrumento,int len,int indice,char* msgE,int reintentos);
int mus_freeI(Musico* listaMusico,int len);
int mus_findById(Musico* pMusico, int len, int idE);
int mus_alter(Musico* listaMusico, int len,char* msgE,int tries);
int mus_ordenarAlfa(Musico* listaMusico,int len);
int mus_isEmptyValid(Musico* listaMusico,int len);
int mus_totalPromedio(Musico* listaMusico,int len);
int mus_inform(Musico* listaMusico, int len,char* msgE,int tries);
int mus_remove(Musico* listaMusico, int len,char* msgE,int tries);
int mus_isOrqIdValid(Orquesta* listaOrquesta,int id,int len);
int mus_isInsIdValid(Instrumento* listaInstrumento,int id,int len);
