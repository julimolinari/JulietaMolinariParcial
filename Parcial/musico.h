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
int mus_print(Musico* listaMusico,Instrumento* listaInstrumento,int len);
int mus_add(Musico* listaMusico,Orquesta* listaOrquesta,Instrumento* listaInstrumento,int len,int indice,char* msgE,int reintentos);
int mus_freeI(Musico* listaMusico,int len);
int mus_findById(Musico* pMusico, int len, int idE);
int mus_alter(Musico* listaMusico, int len,char* msgE,int tries);
int mus_ordenarAlfa(Musico* listaMusico,Instrumento*listaInstrumento,int len);
int mus_isEmptyValid(Musico* listaMusico,int len);
int mus_totalPromedio(Musico* listaMusico,int len);
int mus_remove(Musico* listaMusico, int len,char* msgE,int tries);
int mus_isOrqIdValid(Orquesta* listaOrquesta,int id,int len);
int mus_isInsIdValid(Instrumento* listaInstrumento,int id,int len);
int mus_getNombreById(Instrumento* listaInstrumento,int id,int len,char* nombre[],char* tipo[]);
int mus_removeById(Musico* listaMusico, int id, int len);
int mus_inform(Musico* listaMusico,Instrumento* listaInstrumento,Orquesta* listaOrquesta, int len,char* msgE,int tries);
int mus_ordenarEdad(Musico* listaMusico,Instrumento*listaInstrumento,int len);
int mus_totalMusicos(Musico* listaMusico,Instrumento*listaInstrumento,int len);
int mus_musicosPorOrquesta(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_data(Musico* musico);
int mus_OrquestaIngresandoNombre(Orquesta*listaOrquesta,int len);
int mus_musicosMenores(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_instorquestaId(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_noInstViento(Musico* listaMusico,Instrumento*listaInstrumento,int len);
int mus_OrqCompleta(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_OrquestaMenosSeis(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_MenosMus(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
