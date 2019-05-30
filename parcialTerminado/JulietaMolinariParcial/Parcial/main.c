#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "orquesta.h"
#include "intrumentos.h"
#include "musico.h"
#include "reportes.h"
#include "funciones.h"
#define ORQUESTA_LEN 15
#define MUSICO_LEN 15
#define INSTRUMENTO_LEN 15

int main()
{
    Orquesta orquesta[ORQUESTA_LEN];
    Musico musico[MUSICO_LEN];
    Instrumento instrumento[INSTRUMENTO_LEN];
    initInstrumento(instrumento,INSTRUMENTO_LEN);
    initOrquesta(orquesta,ORQUESTA_LEN);
    initMusico(musico,MUSICO_LEN);
    int opcion = 0;
    int idOrq = 4;
    int idInst = 6;
    int idMus= 7;

    ins_data(instrumento);
    orq_data(orquesta);
    mus_data(musico);

    while(opcion!=12)
    {
        getIntInRange(&opcion,"\n1)Alta orquesta: \n"
                      "2)Modificar datos de orquesta por ID: \n"
                      "3)Baja orquesta: \n"
                      "4)Imprimir orquesta: \n"
                      "5)Agregar Musico: \n"
                      "6)Modificar Musico: \n"
                      "7)Eliminar Musico: \n"
                      "8)Imprimir Musico: \n"
                      "9)Agregar Instrumento: \n"
                      "10)Imprimir Instrumento: \n"
                      "11)INFORMES: \n"
                      "12)Salir\n","ERROR\n",1,13,3);
        switch(opcion)
        {
            case 1:
                {
                    int libre = orq_freeI(orquesta,ORQUESTA_LEN);

                    if(libre >= 0)
                    {
                         printf("\n----Hay lugar----\n");
                         if(orq_add(orquesta,ORQUESTA_LEN,libre,"----Valor invalido----",3)== 0)
                            {
                                orquesta[libre].id = idOrq;
                                printf("\nID: %d\nNombre: %s\nLugar: %s\nTipo: %d\n-------",
                                orquesta[libre].id,orquesta[libre].nombre,orquesta[libre].lugar,orquesta[libre].tipo);
                                idOrq++;
                                break;
                            }
                    }
                    break;
                }
            case 2:
                {
                    if(orq_isEmptyValid(orquesta,ORQUESTA_LEN) != 1)
                    {
                            if(orq_alter(orquesta,ORQUESTA_LEN,"----Orquesta no encontrada----",3)==0)
                        {
                            printf("----Orquesta Actualizada Exitosamente!----");
                        }
                    }else
                    {
                        printf("\n----El listado se encuentra vacio----\n");
                    }

                    break;
                }
            case 3:
                {
                    int id;
                    if(orq_isEmptyValid(orquesta,ORQUESTA_LEN) != 1)
                    {
                       if(orq_remove(orquesta,ORQUESTA_LEN,"----No se encontro----",3,&id)==0)
                       {
                            mus_removeById(musico,id,MUSICO_LEN);
                           printf("----Registro eliminado----");
                       }
                    }else
                    {
                        printf("\n----El listado se encuentra vacio----\n");
                    }
                   break;
                }
            case 4:
                {
                    if(orq_isEmptyValid(orquesta,ORQUESTA_LEN) != 1)
                    {
                        //emp_inform(orquesta,ORQUESTA_LEN,"Valor invalido",3);
                        orq_print(orquesta,ORQUESTA_LEN);
                    }else
                    {
                        printf("\n----El listado se encuentra vacio----\n");
                    }


                    break;
                }
               case 5:
                {
                    int libre = mus_freeI(musico,MUSICO_LEN);

                    if(libre >= 0)
                    {
                         printf("\n----Hay lugar----\n");
                         if(mus_add(musico,orquesta,instrumento,MUSICO_LEN,libre,"----Valor invalido----",3)== 0)
                            {
                                musico[libre].id = idMus;
                                idMus++;
                                break;
                            }
                    }
                case 6:
                {
                    if(mus_isEmptyValid(musico,ORQUESTA_LEN) != 1)
                    {
                            if(mus_alter(musico,MUSICO_LEN,"----Valor invalido----",3)==0)
                        {
                            printf("----Musico Actualizado Exitosamente!----");
                        }
                    }else
                    {
                        printf("\n----El listado se encuentra vacio----\n");
                    }

                    break;
                }
                case 7:
                {
                    if(mus_isEmptyValid(musico,MUSICO_LEN) != 1)
                    {
                        mus_print(musico,instrumento,MUSICO_LEN);
                       if(mus_remove(musico,MUSICO_LEN,"----No se encontro----",3)==0)
                       {
                           printf("----Registro eliminado----");
                       }
                    }else
                    {
                        printf("\n----El listado se encuentra vacio----\n");
                    }
                   break;
                }
             case 8:
                {
                    if(mus_isEmptyValid(musico,MUSICO_LEN) != 1)
                    {
                        //emp_inform(orquesta,ORQUESTA_LEN,"Valor invalido",3);
                        mus_print(musico,instrumento,MUSICO_LEN);
                    }else
                    {
                        printf("\n----El listado se encuentra vacio----\n");
                    }


                    break;
                }
             case 9:
                {
                    int libre = ins_freeI(instrumento,INSTRUMENTO_LEN);

                    if(libre >= 0)
                    {
                         printf("\n----Hay lugar----\n");
                         if(ins_add(instrumento,INSTRUMENTO_LEN,libre,"----Valor invalido----",3)== 0)
                            {
                                instrumento[libre].id = idInst;
                                printf("\nID: %d\nNombre: %s\nTipo: %d\n-------",
                                instrumento[libre].id,instrumento[libre].nombre,instrumento[libre].tipo);
                                idInst++;
                                break;
                            }
                    }
                    break;
                }
             case 10:
                {
                    if(ins_isEmptyValid(instrumento,INSTRUMENTO_LEN) != 1)
                    {
                        //emp_inform(orquesta,ORQUESTA_LEN,"Valor invalido",3);
                        ins_print(instrumento,INSTRUMENTO_LEN);
                    }else
                    {
                        printf("\n----El listado se encuentra vacio----\n");
                    }


                    break;
                }
                case 11:
                {
                    mus_inform(musico,instrumento,orquesta,MUSICO_LEN,"Valor invalido",3);


                    break;
                }
        }


    }
    }

    return 0;
}
