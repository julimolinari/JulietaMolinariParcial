#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "funciones.h"


/**
* \brief Pide cadena de letras y la valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getString(char* pStr, char* msg, char*msgE)
{
    char bufferStr[20];
    printf("%s",msg);
    fgets(bufferStr,sizeof(bufferStr),stdin);
    bufferStr[strlen(bufferStr)-1] = '\0';
    if(pStr!=NULL)
    {
        strncpy(pStr,bufferStr,sizeof(bufferStr));
    }
    return 0;
}

/*
int getInt (int *pNum, char* msg, char* msgE)

{
    int number;
    int ret=-1;
    printf("%s",msg);
    if(scanf("%d",&number)==1)
    {
        (*pNum)=number;
        ret=0;
    }
    else
    {
        printf("%s",msgE);
        fflush(stdin);
        //fpurge(stdin);
    }
    return ret;
}
*/
/**
* \brief Pide un numero y lo valida
* \param mensaje mensaje para el usuario
* \param mensajeError mesaje mostrado cuaando el ingreso no es valido
* \param maximo tope maximo de validacion
* \param minimo tope minimo de validacion
* \param reintentos cantidad maxima intentos
* \param pResultado variable de salida
* \return Entero 0 correcto, -1 error
**/
int utn_getNumero(int* pResultado,const char *mensaje,const char *mensajeError,int minimo,int maximo,int reintentos)
{
    int ret;
    int num;

    while (reintentos>0)
    {
        printf("%s",mensaje);
        if (getInt(&num)==0)
        {
            if (num<=maximo && num>=minimo)
            {
                break;
            }
        }
        fflush(stdin);
        reintentos--;
        printf("%s\n",mensajeError);
    }
    if(reintentos==0)
    {
        ret=-1;
    }
    else
    {
        ret=0;
        *pResultado = num;
    }
    return ret;
}


/**
* \brief Pide un numero int y lo valida
* \param pResultado variable de salida
* \return Entero 0 correcto, -1 error
**/
int getInt(int *pResultado)
{
    char buffer[64];
    scanf("%s",buffer);

    *pResultado = atoi(buffer);
    return 0;
}


/**
* \brief Pide un numero float y lo valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param pNum variable de salida
* \return Entero 0 correcto, -1 error
**/
int getFloat (float *pNum, char* msg, char* msgE)

{
    float number;
    int ret=-1;
    printf("%s",msg);
    if(scanf("%f",&number)==1)
    {
        (*pNum)=number;
        ret=0;
    }
    else
    {
        printf("%s",msgE);
    }
    return ret;
}


/**
* \brief Pide un numero en un rango determinado lo valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param maximo tope maximo de validacion
* \param minimo tope minimo de validacion
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getIntInRange(  int *pNum,
                    char *msg,
                    char *msgE,
                    int minimo,
                    int maximo,
                    int reintentos)
{
    int retorno = -1;
    char bufferStr[20];
    int bufferInt;
    do
    {

        if((pNum != NULL)&&(!getStringNumeros(bufferStr,msg,msgE,reintentos,-1,-1)))
        {
            bufferInt = atoi(bufferStr);
            if(bufferInt >= minimo && bufferInt <= maximo)
            {
                retorno = 0;
                *pNum = bufferInt;
            }
            else
            {
                printf("El numero esta fuera del rango!\n");
                reintentos--;
            }
        }
        else
        {
            printf("No es un numero valido!\n");
            reintentos--;
        }
    }
    while(retorno==-1 && reintentos>0);
    return retorno;
}
/*
int cargarArraySecuencialInt(int* pArray,int len,char* msg, char* msgE)

{
    int i;
    int buffer;
    int ret;
    for(i=0;i<len;i++)
    {
        ret=getInt(&buffer,msg, msgE);
        if(ret)
        {
            break;
        }
        *(pArray+i)=buffer;
    }
    return 0;
}*/

int cargarArraySecuencialFloat(float* pArray,int len,char* msg, char* msgE)

{
    int i;
    float buffer;
    int ret;
    for(i=0; i<len; i++)
    {
        ret=getFloat(&buffer,msg, msgE);
        if(ret)
        {
            break;
        }
        *(pArray+i)=buffer;
    }
    return 0;
}


/**
* \brief Pide cadena de letras y lo valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getStringLetras (char* pStr, char* msg, char* msgE,int reintentos)
{
    char bufferStr[20];
    int ret=-1;
    while(ret==-1 && reintentos>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pStr!=NULL)&&(isLetter(bufferStr)))
        {
            strncpy(pStr,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf(msgE);
            reintentos--;
        }
    }
    return ret;
}


/**
* \brief Pide un numero y lo valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getStringNumeros (char* pStrN, char* msg, char* msgE,int reintentos,int min, int max)
{
    char bufferStrN[20];
    int retorno=-1;
    while(retorno==-1 && reintentos>0)
    {
        if(!getString(bufferStrN,msg,msgE)&&(pStrN!=NULL)&&(isNumber(bufferStrN)))
        {
            if(min!=-1 && max!=-1)
            {
                if(atoi(bufferStrN) >= min && atoi(bufferStrN) <= max)
                {
                    strncpy(pStrN,bufferStrN,sizeof(bufferStrN));
                    retorno=0;
                }
                else
                {
                    printf(msgE);
                    retorno=-1;
                }

            }
            else
            {
                strncpy(pStrN,bufferStrN,sizeof(bufferStrN));
                retorno=0;
            }
        }
        else
        {
            printf(msgE);
            retorno=-1;
        }
    }
    return retorno;
}

/**
* \brief Pide una cadena de numeros float y lo valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getStringNumerosFloat (char* pStr, char* msg, char* msgE,int reintentos)
{
    char bufferStr[20];
    int retorno=-1;
    while(retorno==-1 && reintentos>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pStr!=NULL)&&(isNumberFloat(bufferStr)))
        {

            strncpy(pStr,bufferStr,sizeof(bufferStr));

            retorno=0;
        }
        else
        {
            printf(msgE);
            retorno=-1;
        }
    }
    return retorno;
}


/**
* \brief Pide una cadena alfanumerica y la valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getStringAlphanumeric (char* pStr, char* msg, char* msgE,int reintentos)
{
    char bufferStr[250];
    int ret=-1;
    while(ret==-1 && reintentos>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pStr!=NULL)&&(isAlphanumeric(bufferStr)))
        {
            strncpy(pStr,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf("%s",msgE);
            reintentos--;
        }
    }
    return ret;
}


/**
* \brief Pide un numero de telefono y lo valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getTelephone (char* pStr, char* msg, char* msgE,int reintentos)
{
    char bufferStr[20];
    int ret=-1;
    while(ret==-1 && reintentos>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pStr!=NULL)&&(isTelephone(bufferStr)))
        {
            strncpy(pStr,bufferStr,20);
            ret=0;
        }
        else
        {
            printf("%s",msgE);
            reintentos--;
        }
    }
    return ret;
}


/**
* \brief Pide un numero de DNI y lo valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getDni (char* pStr, char* msg, char* msgE,int reintentos)
{
    char bufferStr[20];
    int ret=-1;
    while(ret==-1 && reintentos>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pStr!=NULL)&&(isDni(bufferStr)))
        {
            strncpy(pStr,bufferStr,20);
            ret=0;
        }
        else
        {
            printf("%s",msgE);
            reintentos--;
        }
    }
    return ret;
}

/**
* \brief Pide una edad y la valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getAge (char* pStr, char* msg, char* msgE,int reintentos)
{
    char bufferStr[3];
    int ret=-1;
    while(ret==-1 && reintentos>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pStr!=NULL))
        {
            if(atoi(bufferStr)>0 && atoi(bufferStr)<150)
            {
                strncpy(pStr,bufferStr,3);
                ret=0;
            }
        }
        else
        {
            printf("%s",msgE);
            reintentos--;
        }
    }
    return ret;
}


/**
* \brief Pide un numero de cuit y lo valida
* \param msg mensaje para el usuario
* \param msgE mesaje mostrado cuaando el ingreso no es valido
* \param reintentos cantidad maxima intentos
* \param pStr variable de salida
* \return Entero 0 correcto, -1 error
**/
int getCuit (char* pStr, char* msg, char* msgE,int reintentos)
{
    char bufferStr[20];
    int ret=-1;
    while(ret==-1 && reintentos>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pStr!=NULL)&&(isCuit(bufferStr)))
        {
            strncpy(pStr,bufferStr,20);
            ret=0;
        }
        else
        {
            printf("%s",msgE);
            reintentos--;
        }
    }
    return ret;
}

int findEmptyPlace (char pArray[][20],int* pIndex,int len)
{
    int i;
    int ret=-1;
    for(i=0; i<len; i++)
    {
        if(pArray[i][0]=='\0')
        {
            *pIndex=i;
            ret=0;
            break;
        }
    }
    return ret;
}

int findName(char* name, char parray[][20], int len, int* pIndex)
{
    int i;
    int ret=-1;
    for(i=0; i<len; i++)
    {
        if(strcmp(name,parray[i])==0)
        {
            *pIndex=i;
            ret=0;
            break;
        }
    }
    return ret;
}

int ordenarArrayMayorMenor (char* pArray, int len,int limit)
{
    int i;
    int j;
    char buffer[limit];
    for(i=0; i<len-1; i++)
    {
        for(j=i+1; j<len; j++)
        {
            if(pArray[i]>pArray[j])
            {
                buffer[i]=pArray[i];
                pArray[i]=pArray[j];
                pArray[j]=buffer[i];
            }
        }
    }
    return 0;
}

int showArrayInt(int* pArray,int len)

{
    int i;
    for(i=0; i<len; i++)
    {
        printf("%d\n",pArray[i]);
    }
    return 0;
}

int showArrayChar(char* pArray,int len)

{
    int i;
    for(i=0; i<len; i++)
    {
        printf("%d\n",pArray[i]);
    }
    return 0;
}


/**
* \brief Validacion de numeros
* \param char*pStr cadena ingresada
* \return Entero 0 correcto, 1 error
**/
int isNumber (char* pStr)
{
    int i=0;
    while(pStr[i]!='\0')
    {
        if(pStr[i]<'0' || pStr[i]>'9')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/**
* \brief Validacion del numero float
* \param char*pStr cadena ingresada
* \return Entero 0 correcto, 1 error
**/
int isNumberFloat (char* pStr)
{
    int i=0;
    int contadorPuntos=0;
    while(pStr[i]!='\0')
    {
        if((pStr[i]<'0' || pStr[i]>'9')&&(pStr[i]!='.'))
        {
            return 0;
        }
        if(pStr[i]=='.')
        {
            contadorPuntos++;
            if(contadorPuntos>1)
            {
                return 0;
            }
        }
        i++;
    }
    return 1;
}

/**
* \brief Validacion de letra
* \param char*pStr cadena ingresada
* \return Entero 0 correcto, 1 error
**/
int isLetter (char* pStr)
{
    int i=0;
    while(pStr[i]!='\0')
    {
        if((pStr[i]!=' ')&&(pStr[i]<'a'||pStr[i]>'z')&&(pStr[i]<'A'||pStr[i]>'Z'))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/**
* \brief Validacion de caracteres alfanumericos
* \param char*pStr cadena ingresada
* \return Entero 0 correcto, 1 error
**/
int isAlphanumeric (char* pStr)
{
    int i=0;
    while(pStr[i]!='\0')
    {
        if((pStr[i]!=' ')&&(pStr[i]!='.')&&(pStr[i]<'a'||pStr[i]>'z')&&(pStr[i]<'A'||pStr[i]>'Z')
                &&(pStr[i]<'0' || pStr[i]>'9'))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/**
* \brief Validacion de telefono
* \param char*pStr cadena ingresada
* \return Entero 0 correcto, 1 error
**/
int isTelephone (char* pStr)
{
    int i=0;
    int contadorGuion=0;
    while(pStr[i]!='\0')
    {
        if((pStr[i]!=' ')&&(pStr[i]!='-')&&(pStr[i]<'0' || pStr[i]>'9'))
        {
            return 0;
        }
        if(pStr[i]=='-')
        {
            contadorGuion++;
        }
        i++;
    }
    if(contadorGuion==1)
    {
        return 1;
    }
    return 0;
}


/**
* \brief Validacion del numero de dni
* \param char*pStr cadena ingresada
* \return Entero 0 correcto, 1 error
**/
int isDni (char* pStr)
{
    int i=0;
    while(pStr[i]!='\0')
    {
        if(!isNumber(pStr))
        {
            return 0;
        }
        if(strlen(pStr)<7 || strlen(pStr)>8)
        {
            return 0;
        }
        i++;
    }
    return 1;
}


/**
* \brief Validacion del numero de cuit
* \param char*pStr cadena ingresada
* \return Entero 0 correcto, 1 error
**/
int isCuit (char* pStr)
{
    int ret=0;
    int i=0;
    while(pStr[i]!='\0')
    {
        if((pStr[i]!='-')&&(pStr[i]<'0' || pStr[i]>'9'))
        {
            return 0;
        }
        else if((pStr[2]=='-')&&(pStr[10]=='-' || pStr[11]=='-'))
        {
            ret=1;
        }
        i++;
    }
    return ret;
}

/**
* \brief Validacion del sexo
* \param char*pStr cadena ingresada
* \return Entero 0 correcto, 1 error
**/
int isValidSex(char letra, char maximo, char minimo)
{
    int retorno = 1;

    if((letra != 'f') && (letra != 'F') && (letra != 'm') && (letra != 'M'))
    {
        retorno = 0;
    }
    return retorno;
}




int getSex(char *mensaje, char *mensajeError, char minimo, char maximo, int reintentos, char *resultado)
{
    char buffer;
    int retorno = -1;
    int control;

    if(mensaje != NULL && mensajeError != NULL && resultado != NULL && maximo >= minimo && reintentos >= 0)
    {
        do
        {
            fflush(stdin);
            printf("%s", mensaje);
            scanf("%c", &buffer);

            printf("Lo ingresado es: %c\n\n", buffer);

            control = isValidSex(buffer, maximo, minimo);
            printf("isValidSex: %d\n\n", control);
            if(isValidSex(buffer, maximo, minimo))
            {
                *resultado = buffer;
                retorno = 0;
                break;
            }
            else
            {
                printf("%s", mensajeError);
            }
        }
        while(reintentos--);
    }
    return retorno;
}

//getSex("\n\nIngrese el sexo F o M: ", "\n\n Error! Ingrese una opcion valida", 1, 2, 2, &sexo);

// printf("El sexo ingresado es : %c" , sexo);
