#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orquesta.h"
#include "intrumentos.h"
#include "musico.h"
#include "funciones.h"



int initInstrumento(Instrumento* list, int len)
{
    int retorno = -1;
    if ( list != NULL && len > 0 )
    {
        int i;
        for( i=0 ; i < len; i++)
        {
            list[i].isEmpty = 1;
        }
        retorno = 0;
    }
    return retorno;
}



int ins_add(Instrumento* listaInstrumento,int len,int indice,char* msgE,int reintentos)
{
    char bufferNombre[50];
    char bufferTipo[3];
    int auxTipo;
    int retorno=-1;

    if((listaInstrumento!=NULL)&&(len>0))
    {
        if( getStringLetras(bufferNombre,"\nIngrese Nombre: ",msgE,reintentos)==0)
        {

                if(getStringNumeros(bufferTipo,"\nIngrese Tipo: ",msgE,reintentos)==0)
                {
                    auxTipo = atoi(bufferTipo);
                    strncpy(listaInstrumento[indice].nombre,bufferNombre,sizeof(bufferNombre));
                    listaInstrumento[indice].tipo = auxTipo;

                    listaInstrumento[indice].isEmpty = 0;
                    retorno=0;
                }
        }
    }
    return retorno;
}

int ins_freeI(Instrumento* listaInstrumento,int len)
{
    int i;
    int retorno=-1;
    for(i=0; i<len; i++)
    {
        if(listaInstrumento[i].isEmpty==1)
        {
            retorno=i;
            break;
        }
    }
    return retorno;
}


int ins_print(Instrumento* listaInstrumento,int len)
{
    int i;
    char *aux;
    int flag=1;
    for(i=0; i<len; i++)
    {
        if(listaInstrumento[i].isEmpty==0)
        {
            switch(listaInstrumento[i].tipo)
        {
            case 1:
                {
                    aux = "Cuerdas";
                }
            case 2:
                {
                    aux = "Viento-madera";
                }
            case 3:
                {
                    aux = "Viento-metal";
                }
            case 4:
                {
                    aux = "Percusion";
                }
        }
            printf("\nID: %d\nNombre: %s\nTipo: %s\n-------",
                   listaInstrumento[i].id,listaInstrumento[i].nombre,aux);
            flag=0;
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}

int ins_isEmptyValid(Instrumento* listaInstrumento,int len)
{
    int i;
    int flag=1;
    for(i=0; i<len; i++)
    {
        if(listaInstrumento[i].isEmpty==0)
        {
            flag=0;
        }
    }
    return flag;
}


int ins_alter(Instrumento* listaInstrumento, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferNombre[50];
    char bufferTipo[3];
    int auxTipo;
    int retorno=-1;

    if((listaInstrumento!=NULL)&&(len>0))
    {
        auxID=ins_getID(listaInstrumento,len,msgE,tries);
        if(auxID>=0)
        {
            posOfID=ins_findById(listaInstrumento,len,auxID);
            if(posOfID!=-1)
            {
                while(opcion!=3)
                {
                    printf("\n1- Modificar Nombre\n");
                    printf("2- Modificar Tipo\n");
                    printf("3- Atras (Menu Principal)\n");
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",msgE,1,5,tries);
                    switch(opcion)
                    {
                    case 1:
                    {
                        if(!getStringLetras(bufferNombre,"\nIngrese NUEVO Nombre: ",msgE,tries))
                        {
                            strncpy(listaInstrumento[posOfID].nombre,bufferNombre,sizeof(bufferNombre));
                            retorno=0;
                        }
                        break;
                    }

                    case 2:
                    {
                        if(!getStringNumeros(bufferTipo,"\nIngrese NUEVO Tipo: ",msgE,tries))
                        {
                            auxTipo=atoi(bufferTipo);
                            listaInstrumento[posOfID].tipo=auxTipo;
                            retorno=0;
                        }
                        break;
                    }
                    }
                }
            }
            else
            {
                printf("\n----No se encontro el ID!-----\n");
            }
        }
    }
    return retorno;
}

int ins_getID (Instrumento* listaInstrumento,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(listaInstrumento!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}
int ins_findById(Instrumento* listaInstrumento, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0; i<len; i++)
    {
        if(listaInstrumento[i].id == idE)
        {
            ret=i;
            break;
        }
    }
    return ret;
}

int ins_remove(Instrumento* listaInstrumento, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(listaInstrumento!=NULL && len>0)
    {
        ins_print(listaInstrumento,len);
        auxID=ins_getID(listaInstrumento,len,msgE,tries);
        if(auxID>=0)
        {
            posOfID=ins_findById(listaInstrumento,len,auxID);
            if(posOfID!=-1)
            {
                listaInstrumento[posOfID].isEmpty=1;
                retorno=0;
            }
        }
    }
    return retorno;
}

