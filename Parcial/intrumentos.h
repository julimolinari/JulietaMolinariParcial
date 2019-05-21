#ifndef INTRUMENTO_H_INCLUDED
#define INTRUMENTO_H_INCLUDED
#include <string.h>

typedef struct
{
 int id;
 char nombre[50];
 int tipo;
 int isEmpty;
}Instrumento;
#endif


int initInstrumento(Instrumento* list, int len);
int ins_print(Instrumento* listaInstrumento,int len);
int ins_add(Instrumento* listaInstrumento,int len,int indice,char* msgE,int tries);
int ins_freeI(Instrumento* listaInstrumento,int len);
int ins_findById(Instrumento* pInstrumento, int len, int idE);
int ins_alter(Instrumento* listaInstrumento, int len,char* msgE,int tries);
int ins_ordenarAlfa(Instrumento* listaInstrumento,int len);
int ins_isEmptyValid(Instrumento* listaInstrumento,int len);
int ins_totalPromedio(Instrumento* listaInstrumento,int len);
int ins_inform(Instrumento* listaInstrumento, int len,char* msgE,int tries);
int ins_remove(Instrumento* listaInstrumento, int len,char* msgE,int tries);
int ins_getID (Instrumento* listaInstrumento,int len,char* msgE,int tries);
int ins_data(Instrumento* instrumento);
