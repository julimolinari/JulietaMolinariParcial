#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "orquesta.h"
#include "intrumentos.h"
#include "funciones.h"
#include "musico.h"

/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Musico* Pointer to array of musicos
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
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



/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param listaMusicoo*Musico
 * \param len int
 * \param indice int
 * \param msgE char[]
 * \param reintentos int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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
    int i;
    if((listaMusico!=NULL)&&(len>0))
    {
        if( getStringLetras(bufferNombre,"\nIngrese Nombre: ",msgE,reintentos)==0)
        {
            if(getStringLetras(bufferApellido,"\nIngrese Apellido: ",msgE,reintentos)==0)
            {
                strncpy(listaMusico[indice].apellido,bufferApellido,sizeof(bufferApellido));
            }
            if(getStringNumeros(bufferEdad,"\nIngrese edad: ",msgE,reintentos,1,99)==0)
            {
                auxEdad = atoi(bufferEdad);
                listaMusico[indice].edad = auxEdad;
                while(retorno== -1 && reintentos>0)
                {
                    if(getStringNumeros(buffeIdOrq,"\nIngrese ID orquesta: ",msgE,reintentos,0,len)==0)
                    {

                        auxIdorq = atoi(buffeIdOrq);
                        int aux = mus_isOrqIdValid(listaOrquesta,auxIdorq,len);
                        if(aux != -1 )
                        {
                            int i;

                            for(i=0;  len > i; i++)
                            {
                                if(aux == listaOrquesta[i].id && listaOrquesta[i].isEmpty==0)
                                {
                                    listaMusico[indice].idOrq = auxIdorq;
                                    retorno=0;
                                    break;

                                }
                            }


                        }
                        else
                        {
                            printf("\n----ID invalido----\n");
                            reintentos--;

                        }
                    }
                }
                retorno = -1;
                while(retorno== -1 && reintentos>0)
                {
                    if(getStringNumeros(bufferIdInst,"\nIngrese ID instrumento: ",msgE,reintentos,0,len)==0)
                    {
                        auxidInst = atoi(bufferIdInst);
                        int aux = mus_isInsIdValid(listaInstrumento,auxidInst,len);
                        if(aux != -1 )
                        {
                            for(i=0;  len > i; i++)
                            {
                                if(aux == listaInstrumento[i].id && listaInstrumento[i].isEmpty==0)
                                {
                                    listaMusico[indice].idInst = auxidInst;
                                    retorno = 0;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            printf("\n----ID invalido----\n");
                            reintentos--;

                        }

                    }
                }


                strncpy(listaMusico[indice].nombre,bufferNombre,sizeof(bufferNombre));
                //listaMusico[indice].id = 0;
                listaMusico[indice].isEmpty = 0;
                retorno=0;
            }
        }
    }

    return retorno;
}

/** \brief imprime lista de musicos
 * \param listaMusico*Musico
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_print(Musico* listaMusico,Instrumento* listaInstrumento,int len)
{
    int i;
    int flag=1;
    char tipo[20];
    int posOfID;
    //char nombre[20];
    //char tipo[20];
    for(i=0; i<len; i++)
    {
        if(listaMusico[i].isEmpty==0)
        {
            int auxId = listaMusico[i].idInst;
            posOfID = ins_findById(listaInstrumento,len,auxId);

            //mus_getNombreById(listaInstrumento,listaMusico[i].id,len,&nombre,&tipo);
            switch(listaInstrumento[posOfID].tipo)
            {
            case 1:
            {
                strcpy(tipo, "Cuerdas");
                break;
            }
            case 2:
            {
                strcpy(tipo, "Viento-madera");
                break;
            }
            case 3:
            {
                strcpy(tipo, "Viento-metal");
                break;
            }
            case 4:
            {
                strcpy(tipo, "Percusion");
                break;
            }
            }
            printf("\nID: %d\nNombre: %s\nApellido: %s\nEdad: %d\nInstrumento: %s\nTipo Instrumento: %s\n-------",
                   listaMusico[i].id,listaMusico[i].nombre,listaMusico[i].apellido,listaMusico[i].edad,listaInstrumento[posOfID].nombre,tipo);
            flag=0;
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}


/** \brief busca que posicion del array esta libre
 * \param listaMusico*Musico
 * \param len int
 * \return int return retorna poscicion libre
 **/
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



/** \brief busca un ID
 * \param listaMusico*Musico
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int return el ID buscado
 **/
int mus_getID (Musico* listaMusico,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(listaMusico!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID: ",msgE,tries,-1,-1))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

/** \brief permite modificar los datos de musicos
 * \param listaMusico*Musico
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_alter(Musico* listaMusico, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferNombre[50];
    char bufferApellido[50];
    char bufferEdad[10];
    int auxEdad;
    char bufferIdOrq[3];
    char bufferIdIns[3];
    int auxIdOrq;
    int auxIdIns;
    int retorno=-1;

    if((listaMusico!=NULL)&&(len>0))
    {
        auxID=mus_getID(listaMusico,len,msgE,tries);
        if(auxID>=0)
        {
            posOfID=mus_findById(listaMusico,len,auxID);
            if(posOfID!=-1)
            {
                while(opcion!=6)
                {
                    printf("\n1- Modificar Nombre\n");
                    printf("2- Modificar Apellido\n");
                    printf("3- Modificar Edad\n");
                    printf("4- Modificar ID Orquesta\n");
                    printf("5- Modificar ID Instrumento\n");
                    printf("6- Atras (Menu Principal)\n");
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",msgE,1,6,tries);
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
                        if(!getStringNumeros(bufferEdad,"\nIngrese NUEVA Edad: ",msgE,tries,1,99))
                        {
                            auxEdad=atof(bufferEdad);
                            listaMusico[posOfID].edad=auxEdad;
                            retorno=0;
                        }
                        break;
                    }
                    case 4:
                    {
                        if(!getStringNumeros(bufferIdOrq,"\nIngrese NUEVO ID Orquesta: ",msgE,tries,0,len))
                        {
                            auxIdOrq=atoi(bufferIdOrq);
                            listaMusico[posOfID].idOrq=auxIdOrq;
                            retorno=0;
                        }
                        break;
                    }
                    case 5:
                    {
                        if(!getStringNumeros(bufferIdIns,"\nIngrese NUEVO Sector: ",msgE,tries,0,len))
                        {
                            auxIdIns=atoi(bufferIdIns);
                            listaMusico[posOfID].idInst=auxIdIns;
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


/** \brief busca posicion del musico pasandole su ID
 * \param listaMusico*Musico
 * \param len int
 * \param idE int
 * \return int Return devuelve posicion
 **/
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


/** \brief permite elminar registro por ID
 * \param listaMusico*Musico
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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


/** \brief permite elminar registro por ID como parametro
 * \param listaMusico*Musico
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
int mus_removeById(Musico* listaMusico, int id, int len)
{
    int retorno=-1;
    int i;
    if(listaMusico!=NULL && len>0)
    {
        for(i=0; i<len; i++)
        {
            if(listaMusico[i].idOrq == id)
            {
                listaMusico[i].isEmpty=1;
                retorno=0;
                break;
            }
        }
    }
    return retorno;
}
/*


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
/** \brief valida el ID de orquesta ingresado en musico
 * \param listaOrquesta*Orquesta
 * \param len int
 * \param msgE char[]
 * \param tries int
 * \return int Return id o -1 si salio mal
 **/
int mus_isOrqIdValid(Orquesta* listaOrquesta,int id,int len)
{
    int i;
    int flag=-1;
    for(i=0; i<len; i++)
    {
        if(listaOrquesta[i].id == id)
        {
            flag=id;
            break;
        }
    }
    return flag;
}

/** \brief valida el ID de instrumentos ingresado en musico
 * \param listaInstrumentos*Intreumentos
 * \param msgE char[]
 * \param tries int
 * \return int Return id o -1 si salio mal
 **/
int mus_isInsIdValid(Instrumento* listaInstrumento,int id,int len)
{
    int i;
    int flag=-1;
    for(i=0; i<len; i++)
    {
        if(listaInstrumento[i].id == id)
        {
            flag=id;
        }
    }
    return flag;
}

/** \brief valida si las posiciones estan vacias - isEmpty==0
 * \param listaMusico*Musico
 * \param msgE char[]
 * \param tries int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 **/
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

/*int mus_getNombreById(Instrumento* listaInstrumento,int id,int len,char *nombre[20],char *tipo[20])
{
    int i;
    int flag=-1;
    //char bufferTipo[20];
    for(i=0; i<len; i++)
    {
        if(listaInstrumento[i].id == id)
        {
            strncpy(&nombre,listaInstrumento[i].nombre,sizeof(listaInstrumento[i].nombre));

            flag = 0;

        }
    }
    return flag;
}*/


/** \brief carga datos para pruebas
 * \param musico*Musico
 * \return int Return 0
 **/
int mus_data(Musico* musico)
{
    musico[0].id = 1;
    musico[0].isEmpty = 0;
    musico[0].edad = 30;
    musico[0].idInst=2;
    musico[0].idOrq=1;
    strncpy(musico[0].nombre,"Mus1",20);
    strncpy(musico[0].apellido,"AMus1",20);

    musico[1].id = 2;
    musico[1].isEmpty = 0;
    musico[1].edad = 20;
    musico[1].idInst=5;
    musico[1].idOrq=2;
    strncpy(musico[1].nombre,"Mus2",20);
    strncpy(musico[1].apellido,"AMus2",20);

    musico[2].id = 3;
    musico[2].isEmpty = 0;
    musico[2].edad = 25;
    musico[2].idInst=2;
    musico[2].idOrq=4;
    strncpy(musico[2].nombre,"Mus3",20);
    strncpy(musico[2].apellido,"AMus3",20);

    musico[3].id = 4;
    musico[3].isEmpty = 0;
    musico[3].edad = 27;
    musico[3].idInst=1;
    musico[3].idOrq=4;
    strncpy(musico[3].nombre,"Mus4",20);
    strncpy(musico[3].apellido,"AMus4",20);

    musico[4].id = 5;
    musico[4].isEmpty = 0;
    musico[4].edad = 22;
    musico[4].idInst=3;
    musico[4].idOrq=1;
    strncpy(musico[4].nombre,"Mus5",20);
    strncpy(musico[4].apellido,"AMus5",20);

    musico[5].id = 6;
    musico[5].isEmpty = 0;
    musico[5].edad = 35;
    musico[5].idInst=4;
    musico[5].idOrq=3;
    strncpy(musico[5].nombre,"Mus6",20);
    strncpy(musico[5].apellido,"AMus6",20);



    return 0;
}

