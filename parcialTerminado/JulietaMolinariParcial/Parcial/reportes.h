#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orquesta.h"
#include "intrumentos.h"
#include "funciones.h"
#include "musico.h"


int mus_promedio(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_OrquestaIngresandoNombre(Orquesta*listaOrquesta,int len);
int mus_musicosMenores(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_instorquestaId(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_noInstViento(Musico* listaMusico,Instrumento*listaInstrumento,int len);
int mus_OrqCompleta(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_OrquestaMenosSeis(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
int mus_MenosMus(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len);
