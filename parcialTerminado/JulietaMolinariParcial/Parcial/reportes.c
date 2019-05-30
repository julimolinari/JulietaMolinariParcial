#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orquesta.h"
#include "intrumentos.h"
#include "funciones.h"
#include "musico.h"
#include "reportes.h"



/** \brief muestra informes, con distintos filtros
 * \param listaMusico*Musico
 * \param listaInstrumento*Instrumento
 * \param listaOrquesta*Orquesta
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_inform(Musico* listaMusico,Instrumento* listaInstrumento,Orquesta* listaOrquesta, int len,char* msgE,int tries)
{
    int opcion=0;
    int retorno=-1;

    if((listaMusico!=NULL)&&(len>0))
    {
        while(opcion!=9)
        {
            printf("\n1- Buscar orquesta por lugar\n");
            printf("2- Musicos por edad (menores a 25)\n");//insercion
            printf("3- Orquestas con menos de 6 musicos\n");
            printf("4- Instrumentos de Orquestas y musico\n");
            printf("5- Informar orquestas completas\n");
            printf("6- Orquesta con menos musicos\n");
            printf("7- Promedio de musico por orquesta\n");
            printf("8- Musicos que NO tocan instrumentos de viento\n");
            printf("9- Salir\n");
            getIntInRange(&opcion,"\n   INGRESE OPCION: ",msgE,1,9,tries);
            switch(opcion)
            {
            case 1:
            {
                mus_OrquestaIngresandoNombre(listaOrquesta, len);
                break;
            }
            case 2:
            {
                mus_musicosMenores(listaMusico,listaInstrumento,listaOrquesta,len);
                break;
            }
            case 3:
            {
                mus_OrquestaMenosSeis(listaMusico,listaInstrumento,listaOrquesta,len);
                break;
            }
            case 4:
            {
                mus_instorquestaId(listaMusico,listaInstrumento,listaOrquesta,len);
                break;
            }
            case 5:
            {
                mus_OrqCompleta(listaMusico,listaInstrumento,listaOrquesta,len);
                break;
            }
             case 6:
            {
                mus_MenosMus(listaMusico,listaInstrumento,listaOrquesta,len);
                break;
            }
             case 7:
            {
                mus_promedio(listaMusico,listaInstrumento,listaOrquesta,len);
                break;
            }
            case 8:
            {
                mus_noInstViento(listaMusico,listaInstrumento, len);
                break;
            }


            }
        }
    }

    return retorno;
}


/** \brief busca orquestas por nombre del lugar al que pertenecen
 * \param listaOrquesta*Orquesta
 * \param len int tamnaño lista
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_OrquestaIngresandoNombre(Orquesta*listaOrquesta,int len)
{
    int retorno = -1;
    int i;
    char lugarOrq[20];

    if(!getString(lugarOrq,"\nIngrese Lugar de la Orquesta: ","Lugar invalido"))
    {
        retorno=0;
    }

    for (i = 0; i < len; i++)
    {
        if(stricmp(lugarOrq,listaOrquesta[i].lugar) == 0 )
        {
            printf("\nID: %d\nNombre: %s\nLugar: %s\nTipo: %d\n-------",
                   listaOrquesta[i].id,listaOrquesta[i].nombre,listaOrquesta[i].lugar,listaOrquesta[i].tipo);
        }
    }
    return retorno;
}


/** \brief muestra los musicos menores de 25
 * \param listaMusico*Musico
 * \param listaInstrumento*Instrumento
 * \param listaOrquesta*Orquesta
 * \param len int tamaño lista
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_musicosMenores(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len)
{
    int retorno = -1;
    int i;
    int PosIdIns;
    int posIdOrq;
    for (i = 0; i < len; i++)
    {
        if(listaMusico[i].edad < 25 && listaMusico[i].isEmpty==0)
        {
            PosIdIns = ins_findById(listaInstrumento,len,listaMusico[i].idInst);
            posIdOrq = orq_findById(listaOrquesta,len,listaMusico[i].idOrq);
            printf("\nID: %d\nNombre: %s\nApellido: %s\nEdad: %d\nInstrumento: %s\nOrquesta: %s\n-------",
                   listaMusico[i].id,listaMusico[i].nombre,listaMusico[i].apellido,listaMusico[i].edad,listaInstrumento[PosIdIns].nombre,listaOrquesta[posIdOrq].nombre);
            retorno = 0;
        }
    }
    return retorno;
}


/** \brief ingresando el id, muestra la orquesta y sus musico
 * \param listaMusico*Musico
 * \param listaInstrumento*Instrumento
 * \param listaOrquesta*Orquesta
 * \param len int tamaño lista
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_instorquestaId(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len)
{
    int i;
    char bufferIdOrq[3];
    int PosIdIns;
    int retorno = -1;
    if(!getStringNumeros(bufferIdOrq,"\nIngrese ID Orquesta: ","valor invalido",3,0,len))
    {
        for (i = 0; i < len; i++)
        {
            if(listaMusico[i].idOrq == atoi(bufferIdOrq))
            {
                PosIdIns = ins_findById(listaInstrumento,len,listaMusico[i].idInst);

                printf("\nNombre: %s\nTipo de instrumento: %d\nMusico: %s\n-------",
                       listaInstrumento[PosIdIns].nombre,listaInstrumento[PosIdIns].tipo,listaMusico[i].nombre);
                retorno = 0;
            }
        }



    }
    return retorno;
}


/** \brief muestra los musicos que no tocan instrumentos de viento
 * \param listaMusico*Musico
 * \param listaInstrumento*Instrumento
 * \param len int tamaño lista
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_noInstViento(Musico* listaMusico,Instrumento*listaInstrumento,int len)
{
    int i;
    int PosIdIns;
    int retorno = -1;
    char aux[20];
    for (i = 0; i < len; i++)
    {
        if(listaMusico[i].idInst >= 0 && listaMusico[i].isEmpty == 0)
        {
            PosIdIns = ins_findById(listaInstrumento,len,listaMusico[i].idInst);
            if(listaInstrumento[PosIdIns].tipo == 1 || listaInstrumento[PosIdIns].tipo == 4)
            {

                if(listaInstrumento[PosIdIns].tipo == 1)
                {
                    strcpy(aux,"Cuerdas");
                }
                else
                {
                    strcpy(aux,"Percusion");
                }
                printf("\nID: %d\nNombre: %s\nApellido: %s\nEdad: %d\nInstrumento: %s\n-------",
                       listaMusico[i].id,listaMusico[i].nombre,listaMusico[i].apellido,listaMusico[i].edad,aux);
                retorno = 0;
            }
        }
    }
    return retorno;
}

/** \brief muestra las orquestas con menos de 6 musicos
 * \param listaMusico*Musico
 * \param listaInstrumento*Instrumento
 * \param listaOrquesta*Orquesta
 * \param len int tamaño lista
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_OrquestaMenosSeis(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len)
{
    int idOrquesta[len];
    int contMusicosOrq[len];
    int retorno = -1;
    int i;
    int j;
    for(i = 0; i < len; i++)
    {
        idOrquesta[i]=0;
        contMusicosOrq[i]=0;
    }
    for (i = 0; i < len; i++)
    {
        if(listaOrquesta[i].isEmpty == 0)
        {
            idOrquesta[i] = listaOrquesta[i].id;
            for (j = 0; j < len; j++)
            {
                if(listaMusico[j].idOrq == idOrquesta[i])
                {
                    contMusicosOrq[i]++;
                }
            }
            retorno = 0;
        }

    }
    for(i = 0; i < len; i++)
    {
        if(contMusicosOrq[i]<6)
        {
            j = orq_findById(listaOrquesta,len,idOrquesta[i]);
            if(listaOrquesta[j].isEmpty == 0)
            {
                printf("\nID: %d\nNombre: %s\nLugar: %s\nTipo: %d\n-------",
                       idOrquesta[i],listaOrquesta[j].nombre,listaOrquesta[j].lugar,listaOrquesta[j].tipo);
            }

        }
    }

    return retorno;
}

/** \brief muestra el promedio de musicos por orquesta
 * \param listaMusico*Musico
 * \param listaInstrumento*Instrumento
 * \param listaOrquesta*Orquesta
 * \param len int tamaño lista
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_promedio(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len)
{
    int retorno = -1;
    int i;
    int j;
    float contMus;
    float contOrq;
    float promedio;
    for(i = 0; i < len; i++)
    {
        if(listaMusico[i].isEmpty == 0)
        {
                contMus++;
                retorno = 0;
        }
    }
    for(j = 0; j < len; j++)
    {
        if(listaOrquesta[j].isEmpty == 0)
        {
                contOrq++;
        }
    }
    promedio = contMus/contOrq;
    printf("\nPromedio de musicos por orquesta: %.2f\n-------",promedio);

    return retorno;
}

/** \brief muestra las orquestas que estan completas
 * \param listaMusico*Musico
 * \param listaInstrumento*Instrumento
 * \param listaOrquesta*Orquesta
 * \param len int tamaño lista
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_OrqCompleta(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len)
{
    int retorno = -1;
    int i;
    int j;
    int posIdInst;
    int contPer;
    int contCuer;
    int contVient;

    for (i = 0; i < len; i++)
    {
        if(listaOrquesta[i].isEmpty == 0)
        {
            for (j = 0; j < len; j++)
            {
                if(listaMusico[j].idOrq == listaOrquesta[i].id)
                {
                        posIdInst = ins_findById(listaInstrumento,len,listaMusico[j].idInst);

                        switch(listaInstrumento[posIdInst].tipo)
                    {
                    case 1:
                    {
                        contCuer++;
                        break;
                    }
                    case 2:
                    case 3:
                    {
                        contVient++;
                        break;
                    }
                    case 4:
                    {
                        contPer++;
                        break;
                    }
                    }

                }
            }
    if(contCuer>= 4 && contVient >= 4 && contPer>=1)
    {
        printf("\nID: %d\nNombre: %s\nLugar: %s\nTipo: %d\n-------",
        listaOrquesta[i].id,listaOrquesta[i].nombre,listaOrquesta[i].lugar,listaOrquesta[i].tipo);
    }
            retorno = 0;
        }

    }
    return retorno;
}

/** \brief muestra las orquestas con menos musicos
 * \param listaMusico*Musico
 * \param listaInstrumento*Instrumento
 * \param listaOrquesta*Orquesta
 * \param len int tamaño lista
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_MenosMus(Musico* listaMusico,Instrumento*listaInstrumento,Orquesta*listaOrquesta,int len)
{
    int idOrquesta[len];
    int contMusicosOrq[len];
    int retorno = -1;
    int i;
    int j;
    int musMin = 1000;
    for(i = 0; i < len; i++)
    {
        idOrquesta[i]=0;
        contMusicosOrq[i]=0;
    }
    for (i = 0; i < len; i++)
    {
        if(listaOrquesta[i].isEmpty == 0)
        {
            idOrquesta[i] = listaOrquesta[i].id;
            for (j = 0; j < len; j++)
            {
                if(listaMusico[j].idOrq == idOrquesta[i])
                {
                    contMusicosOrq[i]++;
                }
            }
            retorno = 0;
        }

    }
    for(i = 0; i < len; i++)
    {
        if(contMusicosOrq[i] < musMin && contMusicosOrq[i] != 0)
        {
            musMin = contMusicosOrq[i];
        }
    }
    for(i = 0; i < len; i++)
    {
        if(contMusicosOrq[i] == musMin)
        {
     printf("\nID: %d\nNombre: %s\nLugar: %s\nTipo: %d\nCantidad de musicos: %d\n-------",
     listaOrquesta[i].id,listaOrquesta[i].nombre,listaOrquesta[i].lugar,listaOrquesta[i].tipo,musMin);
     }
    }

    return retorno;
}


