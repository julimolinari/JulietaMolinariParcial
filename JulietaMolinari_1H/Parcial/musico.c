#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orquesta.h"
#include "intrumentos.h"
#include "funciones.h"
#include "musico.h"


int initMusico(Musico* list, int len)
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




int mus_add(Musico* listaMusico,Orquesta* listaOrquesta,Instrumento* listaInstrumento,int len,int indice,char* msgE,int reintentos)
{
    char bufferNombre[50];
    char bufferApellido[50];
    char bufferEdad[3];
    int auxEdad;
    char buffeIdOrq[3];
    int auxIdorq;
    char bufferIdInst[3];
    int auxidInst;
    int retorno=-1;

    if((listaMusico!=NULL)&&(len>0))
    {
        if( getStringLetras(bufferNombre,"\nIngrese Nombre: ",msgE,reintentos)==0)
        {
            if(getStringLetras(bufferApellido,"\nIngrese Apellido: ",msgE,reintentos)==0)
            {
                strncpy(listaMusico[indice].apellido,bufferApellido,sizeof(bufferApellido));
            }

                if(getStringNumeros(bufferEdad,"\nIngrese edad: ",msgE,reintentos)==0)
                {
                    if(getStringNumeros(buffeIdOrq,"\nIngrese ID orquesta: ",msgE,reintentos)==0)
                    {

                            auxIdorq = atoi(buffeIdOrq);
                            int aux = mus_isOrqIdValid(listaOrquesta,auxIdorq,len);
                            if(aux != -1 )
                            {
                                listaMusico[aux].idOrq = auxIdorq;
                            }else
                            {
                                printf("\n----El listado de orquesta encuentra vacio----\n");

                            }

                        }
                    if(getStringNumeros(bufferIdInst,"\nIngrese ID instrumento: ",msgE,reintentos)==0)
                    {

                            auxidInst = atoi(bufferIdInst);
                            int aux = mus_isInsIdValid(listaInstrumento,auxidInst,len);
                            if(aux != -1 )
                            {
                                listaMusico[aux].idInst = auxidInst;
                            }else
                            {
                                printf("\n----El listado de orquesta encuentra vacio----\n");

                            }

                        }

                    auxEdad = atoi(bufferEdad);
                    strncpy(listaMusico[indice].nombre,bufferNombre,sizeof(bufferNombre));
                    listaMusico[indice].edad = auxEdad;
                    //listaMusico[indice].id = 0;
                    listaMusico[indice].isEmpty = 0;
                    retorno=0;
                    }
                }
        }

    return retorno;
}


int mus_print(Musico* listaMusico,int len)
{
    int i;
    int flag=1;
    for(i=0; i<len; i++)
    {
        if(listaMusico[i].isEmpty==0)
        {
            printf("\nID: %d\nNombre: %s\nApellido: %s\nEdad: %d\nID orquesta: %d\nID instrumento: %d\n-------",
                   listaMusico[i].id,listaMusico[i].nombre,listaMusico[i].apellido,listaMusico[i].edad,listaMusico[i].idOrq,listaMusico[i].idInst);
            flag=0;
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}



int mus_freeI(Musico* listaMusico,int len)
{
    int i;
    int retorno=-1;
    for(i=0; i<len; i++)
    {
        if(listaMusico[i].isEmpty==1)
        {
            retorno=i;
            break;
        }
    }
    return retorno;
}




int mus_getID (Musico* listaMusico,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(listaMusico!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}


/*

int mus_alter(Musico* listaMusico, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferNombre[50];
    char bufferApellido[50];
    char bufferEdad[10];
    char bufferSector[3];
    float auxSalario;
    int auxSector;
    int retorno=-1;

    if((listaMusico!=NULL)&&(len>0))
    {
        auxID=mus_getID(listaMusico,len,msgE,tries);
        if(auxID>=0)
        {
            posOfID=mus_findById(listaMusico,len,auxID);
            if(posOfID!=-1)
            {
                while(opcion!=5)
                {
                    printf("\n1- Modificar Nombre\n");
                    printf("2- Modificar Apellido\n");
                    printf("3- Modificar Salario\n");
                    printf("4- Modificar Sector\n");
                    printf("5- Atras (Menu Principal)\n");
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",msgE,1,5,tries);
                    switch(opcion)
                    {
                    case 1:
                    {
                        if(!getStringLetras(bufferNombre,"\nIngrese NUEVO Nombre: ",msgE,tries))
                        {
                            strncpy(listaMusico[posOfID].nombre,bufferNombre,sizeof(bufferNombre));
                            retorno=0;
                        }
                        break;
                    }
                    case 2:
                    {
                        if(!getStringLetras(bufferApellido,"\nIngrese NUEVO Apellido: ",msgE,tries))
                        {
                            strncpy(listaMusico[posOfID].apellido,bufferApellido,sizeof(bufferApellido));
                            retorno=0;
                        }
                        break;
                    }
                    case 3:
                    {
                        if(!getStringNumerosFloat(bufferSalario,"\nIngrese NUEVO Salario: ",msgE,tries))
                        {
                            auxSalario=atof(bufferSalario);
                            listaMusico[posOfID].salario=auxSalario;
                            retorno=0;
                        }
                        break;
                    }
                    case 4:
                    {
                        if(!getStringNumeros(bufferSector,"\nIngrese NUEVO Sector: ",msgE,tries))
                        {
                            auxSector=atoi(bufferSector);
                            listaMusico[posOfID].sector=auxSector;
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




int mus_findById(Musico* listaMusico, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0; i<len; i++)
    {
        if(listaMusico[i].id == idE)
        {
            ret=i;
            break;
        }
    }
    return ret;
}



int mus_remove(Musico* listaMusico, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(listaMusico!=NULL && len>0)
    {
        auxID=mus_getID(listaMusico,len,msgE,tries);
        if(auxID>=0)
        {
            posOfID=mus_findById(listaMusico,len,auxID);
            if(posOfID!=-1)
            {
                listaMusico[posOfID].isEmpty=1;
                retorno=0;
            }
        }
    }
    return retorno;
}



int mus_inform(Musico* listaMusico, int len,char* msgE,int tries)
{
    int opcion=0;
    int retorno=-1;

            if((listaMusico!=NULL)&&(len>0))
            {
                while(opcion!=3)
                {
                    printf("\n1- Empleados ordenados alfabeticamente por Apellido y Sector\n");
                    printf("2- Total y promedio de los salarios\n");
                    printf("3- Salir\n");
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",msgE,1,3,tries);
                    switch(opcion)
                    {
                        case 1:
                        {
                            mus_ordenarAlfa(listaMusico,len);
                            break;
                        }
                        case 2:
                        {
                            mus_totalPromedio(listaMusico,len);
                            break;
                        }
                    }
                }
            }

    return retorno;
}



int mus_ordenarAlfa(Musico* listaMusico,int len)
{
    int retorno = -1;
    Musico auxMusico;
    int i;
    int j;
    for(i=0; i < len -1 ; i ++)
    {
        for(j=i+1; j<len  ; j++)
        {
            if(stricmp(listaMusico[i].apellido,listaMusico[j].apellido) > 0)
            {
                auxMusico = listaMusico[i];
                listaMusico[i] = listaMusico[j];
                listaMusico[j] = auxMusico;
                retorno = 0;
            } else if(stricmp(listaMusico[i].apellido,listaMusico[j].apellido) == 0)
            {
                if(listaMusico[i].sector>listaMusico[j].sector)
                {
                    auxMusico = listaMusico[i];
                    listaMusico[i] = listaMusico[j];
                    listaMusico[j] = auxMusico;
                    retorno = 0;
                }
            }
        }
    }
    mus_print(listaMusico,len);
    return retorno;
}



int mus_totalPromedio(Musico* listaMusico,int len)
{
    float auxSalario = 0;
    int auxCantidadEmpleados = 0;
    float promedio;
    int cont = 0;
    int i;
    int j;
    for(i=0; i < len  ; i ++)
    {
        if(listaMusico[i].isEmpty == 0)
        {
            auxSalario = listaMusico[i].salario + auxSalario;
            auxCantidadEmpleados ++;
        }
    }
    promedio = auxSalario / auxCantidadEmpleados;

    printf("\n-Total Salarios:  %.2f\n",auxSalario);
    printf("-Promedio de los Salarios: %.2f\n",promedio);

    for(j=0; j < len ; j ++)
    {
        if(listaMusico[j].salario>promedio)
        {
            cont++;
        }
    }
    printf("-De los %d empleados, %d superan el salario promedio\n",auxCantidadEmpleados,cont);
    return 0;
}


*/
int mus_isOrqIdValid(Orquesta* listaOrquesta,int id,int len)
{
    int i;
    int flag=1;
    for(i=0; i<len; i++)
    {
        if(listaOrquesta[i].id == id)
        {
            flag=id;
        }
    }
    return flag;
}
int mus_isInsIdValid(Instrumento* listaInstrumento,int id,int len)
{
    int i;
    int flag=1;
    for(i=0; i<len; i++)
    {
        if(listaInstrumento[i].id == id)
        {
            flag=id;
        }
    }
    return flag;
}
int mus_isEmptyValid(Musico* listaMusico,int len)
{
    int i;
    int flag=-1;
    for(i=0; i<len; i++)
    {
        if(listaMusico[i].isEmpty==0)
        {
            flag=0;
        }
    }
    return flag;
}
