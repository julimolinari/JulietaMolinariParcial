#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orquesta.h"
#include "funciones.h"



int initOrquesta(Orquesta* list, int len)
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



int orq_add(Orquesta* listaOrquesta,int len,int indice,char* msgE,int reintentos)
{
    char bufferNombre[50];
    char bufferLugar[50];
    char bufferTipo[3];
    int auxTipo;
    int retorno=-1;

    if((listaOrquesta!=NULL)&&(len>0))
    {
        if( getStringLetras(bufferNombre,"\nIngrese Nombre: ",msgE,reintentos)==0)
        {
            if(getStringLetras(bufferLugar,"\nIngrese Lugar: ",msgE,reintentos)==0)
            {
                strncpy(listaOrquesta[indice].lugar,bufferLugar,sizeof(bufferLugar));
            }

                if(getStringNumeros(bufferTipo,"\nIngrese Tipo: ",msgE,reintentos)==0)
                {
                    auxTipo = atoi(bufferTipo);
                    strncpy(listaOrquesta[indice].nombre,bufferNombre,sizeof(bufferNombre));
                    listaOrquesta[indice].tipo = auxTipo;

                    listaOrquesta[indice].isEmpty = 0;
                    retorno=0;
                }
        }
    }
    return retorno;
}

int orq_freeI(Orquesta* listaOrquesta,int len)
{
    int i;
    int retorno=-1;
    for(i=0; i<len; i++)
    {
        if(listaOrquesta[i].isEmpty==1)
        {
            retorno=i;
            break;
        }
    }
    return retorno;
}


int orq_print(Orquesta* listaOrquesta,int len)
{
    int i;
    int flag=1;
    for(i=0; i<len; i++)
    {
        if(listaOrquesta[i].isEmpty==0)
        {
            printf("\nID: %d\nNombre: %s\nLugar: %s\nTipo: %d\n-------",
                   listaOrquesta[i].id,listaOrquesta[i].nombre,listaOrquesta[i].lugar,listaOrquesta[i].tipo);
            flag=0;
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}

int orq_isEmptyValid(Orquesta* listaOrquesta,int len)
{
    int i;
    int flag=1;
    for(i=0; i<len; i++)
    {
        if(listaOrquesta[i].isEmpty==0)
        {
            flag=0;
        }
    }
    return flag;
}


int orq_alter(Orquesta* listaOrquesta, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferNombre[50];
    char bufferLugar[50];
    char bufferTipo[3];
    int auxTipo;
    int retorno=-1;

    if((listaOrquesta!=NULL)&&(len>0))
    {
        auxID=orq_getID(listaOrquesta,len,msgE,tries);
        if(auxID>=0)
        {
            posOfID=orq_findById(listaOrquesta,len,auxID);
            if(posOfID!=-1)
            {
                while(opcion!=4)
                {
                    printf("\n1- Modificar Nombre\n");
                    printf("2- Modificar Lugar\n");
                    printf("3- Modificar Tipo\n");
                    printf("4- Atras (Menu Principal)\n");
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",msgE,1,5,tries);
                    switch(opcion)
                    {
                    case 1:
                    {
                        if(!getStringLetras(bufferNombre,"\nIngrese NUEVO Nombre: ",msgE,tries))
                        {
                            strncpy(listaOrquesta[posOfID].nombre,bufferNombre,sizeof(bufferNombre));
                            retorno=0;
                        }
                        break;
                    }
                    case 2:
                    {
                        if(!getStringLetras(bufferLugar,"\nIngrese NUEVO Lugar: ",msgE,tries))
                        {
                            strncpy(listaOrquesta[posOfID].lugar,bufferLugar,sizeof(bufferLugar));
                            retorno=0;
                        }
                        break;
                    }

                    case 3:
                    {
                        if(!getStringNumeros(bufferTipo,"\nIngrese NUEVO Tipo: ",msgE,tries))
                        {
                            auxTipo=atoi(bufferTipo);
                            listaOrquesta[posOfID].tipo=auxTipo;
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

int orq_getID (Orquesta* listaOrquesta,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(listaOrquesta!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}
int orq_findById(Orquesta* listaOrquesta, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0; i<len; i++)
    {
        if(listaOrquesta[i].id == idE)
        {
            ret=i;
            break;
        }
    }
    return ret;
}

int orq_remove(Orquesta* listaOrquesta, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(listaOrquesta!=NULL && len>0)
    {
        orq_print(listaOrquesta,len);
        auxID=orq_getID(listaOrquesta,len,msgE,tries);
        if(auxID>=0)
        {
            posOfID=orq_findById(listaOrquesta,len,auxID);
            if(posOfID!=-1)
            {
                listaOrquesta[posOfID].isEmpty=1;
                retorno=0;
            }
        }
    }
    return retorno;
}
