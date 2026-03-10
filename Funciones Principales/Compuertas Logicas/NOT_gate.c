#include "LogicGates.h"

/*FN****************************************************************************
*
*   int NOT_Gate(int A);
*
*   Return: Retorna el resultado de la operacion Not de A.
*
*   Registro de Versiones:
*
*   DATE       RESPONSABLE           COMENTARIO
*   -----------------------------------------------------------------------
*   Marz 8/26  Juan Andres Sanchez   Implemntacion Inicial
*
*   REVISADO
*   -----------------------------------------------------------------------
*   Sofia Vega, Andres Trujillo
*
*******************************************************************************/

int NOT_Gate(int A) {
    int result = !A;
    return result ;
}