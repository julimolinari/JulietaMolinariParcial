#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orquesta.h"
#include "funciones.h"

/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Orquesta* Pointer to array of orquestas
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

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


/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param listaOrquesta*Orquesta
 * \param len int
 * \param indice int
 * \param msgE char[]
 * \param reintentos int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int orq_add(Orquesta* listaOrquesta,int len,int indice,char* msgE,int reintentos)
{
    char bufferNombre[50];
    char bufferLugar[50];
    char bufferTipo[3];
    int auxTipo=0;
    int retorno=-1;

    if((listaOrquesta!=NULL)&&(len>0))
    {
        if( getStringLetras(bufferNombre,"\nIngrese Nombre: ",msgE,reintentos)==0)
        {
            if(getStringLetras(bufferLugar,"\nIngrese Lugar: ",msgE,reintentos)==0)
            {
                strncpy(listaOrquesta[indice].lugar,bufferLugar,sizeof(bufferLugar));
            }

                //if(utn_getNumero(&auxTipo,"\nIngrese Tipo:","Valor invalido",1,3,3)==0)
                if(getStringNumeros(bufferTipo,"\nIngrese Tipo: ",msgE,reintentos,1,3)==0)
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

/** \brief busca que posicion del array esta libre
 * \param listaOrquesta*Orquesta
 * \param len int
 * \return int return retorna poscicion libre
 **/
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

/** \brief imprime lista de Orquestas
 * \param listaOrquesta*Orquesta
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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


/** \brief permite modificar los datos de orquestas
 * \param listaOrquestas*Orquestas
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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
                        if(!getStringNumeros(bufferTipo,"\nIngrese NUEVO Tipo: ",msgE,tries,1,3))
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


/** \brief busca un ID
 * \param listaOrquesta*Orquesta
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int return el ID buscado
 **/
int orq_getID (Orquesta* listaOrquesta,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(listaOrquesta!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID: ",msgE,tries,-1,-1))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

/** \brief busca posicion de la orquesta pasandole su ID
 * \param listaOrquesta*Orquesta
 * \param len int
 * \param idE int
 * \return int Return devuelve posicion
 **/
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


/** \brief permite elminar registro por ID
 * \param listaOrquesta*Orquesta
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int orq_remove(Orquesta* listaOrquesta, int len,char* msgE,int tries,int* id)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(listaOrquesta!=NULL && len>0)
    {
        orq_print(listaOrquesta,len);
        auxID=orq_getID(listaOrquesta,len,msgE,tries);
        *id=auxID;
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


/** \brief carga datos para pruebas
 * \param orquesta*Orquesta
 * \return int Return 0
 **/
int orq_data(Orquesta* orquesta)
{
    orquesta[0].id = 0;
    orquesta[0].isEmpty = 0;
    orquesta[0].tipo = 3;
    strncpy(orquesta[0].nombre,"La Murga",20);
    strncpy(orquesta[0].lugar,"Mendoza",20);

    orquesta[1].id = 1;
    orquesta[1].isEmpty = 0;
    orquesta[1].tipo = 2;
    strncpy(orquesta[1].nombre,"Zapato",20);
    strncpy(orquesta[1].lugar,"Peru",20);

    orquesta[2].id = 2;
    orquesta[2].isEmpty = 0;
    orquesta[2].tipo = 1;
    strncpy(orquesta[2].nombre,"Avella",20);
    strncpy(orquesta[2].lugar,"Avellaneda",20);

    orquesta[3].id = 3;
    orquesta[3].isEmpty = 0;
    orquesta[3].tipo = 3;
    strncpy(orquesta[3].nombre,"Caramelo",20);
    strncpy(orquesta[3].lugar,"Misiones",20);

    return 0 ;

}
