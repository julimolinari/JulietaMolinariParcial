#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orquesta.h"
#include "intrumentos.h"
#include "musico.h"
#include "funciones.h"

/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Instrumento* Pointer to array of instrumentos
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
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


/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param listaInstrumento*Instrumentos
 * \param len int
 * \param indice int
 * \param msgE char[]
 * \param reintentos int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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
                strncpy(listaInstrumento[indice].nombre,bufferNombre,sizeof(bufferNombre));
                if(getStringNumeros(bufferTipo,"\nIngrese Tipo: ",msgE,reintentos,1,4)==0)
                {
                    auxTipo = atoi(bufferTipo);

                    listaInstrumento[indice].tipo = auxTipo;

                    listaInstrumento[indice].isEmpty = 0;
                    retorno=0;
                }
        }
    }
    return retorno;
}

/** \brief busca que posicion del array esta libre
 * \param listaInstrumento*Instrumentos
 * \param len int
 * \return int return retorna poscicion libre
 **/
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

/** \brief imprime lista de Instrumentos
 * \param listaInstrumento*Instrumentos
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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
                    break;
                }
            case 2:
                {
                    aux = "Viento-madera";
                    break;
                }
            case 3:
                {
                    aux = "Viento-metal";
                    break;
                }
            case 4:
                {
                    aux = "Percusion";
                    break;
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

/** \brief permite modificar los datos de instrumentos
 * \param listaInstrumentos*Instrumentos
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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
                        if(!getStringNumeros(bufferTipo,"\nIngrese NUEVO Tipo: ",msgE,tries,1,3))
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


/** \brief busca un ID
 * \param listaInstrumento*Instrumentos
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int return el ID buscado
 **/
int ins_getID (Instrumento* listaInstrumento,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(listaInstrumento!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID: ",msgE,tries,-1,-1))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

/** \brief busca posicion del instrumento pasandole su ID
 * \param listaInstrumento*Instrumento
 * \param len int
 * \param idE int
 * \return int Return devuelve posicion
 **/
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


/** \brief permite elminar registro por ID
 * \param listaInstrumento*Instrumento
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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


/** \brief carga datos para pruebas
 * \param instrumentos*Instrumentos
 * \return int Return 0
 **/
int ins_data(Instrumento* instrumento)
{
    instrumento[0].id = 1;
    instrumento[0].isEmpty = 0;
    instrumento[0].tipo = 1;
    strncpy(instrumento[0].nombre,"Instrum1",20);

    instrumento[1].id = 2;
    instrumento[1].isEmpty = 0;
    instrumento[1].tipo = 2;
    strncpy(instrumento[1].nombre,"Instrum2",20);

    instrumento[2].id = 3;
    instrumento[2].isEmpty = 0;
    instrumento[2].tipo = 2;
    strncpy(instrumento[2].nombre,"Instrum3",20);

    instrumento[3].id = 4;
    instrumento[3].isEmpty = 0;
    instrumento[3].tipo = 3;
    strncpy(instrumento[3].nombre,"Instrum4",20);

    instrumento[4].id = 5;
    instrumento[4].isEmpty = 0;
    instrumento[4].tipo = 4;
    strncpy(instrumento[4].nombre,"Instrum5",20);

    return 0;
}
