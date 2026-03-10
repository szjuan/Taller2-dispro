#include "LogicGates.h"

/*FN****************************************************************************
*
*   AND_Gate(int A, int B) ;
*
*   Return: Retorna el resultado de la operacion AND entre A y B.
*
*   Registro de Versiones:
*
*   DATE       RESPONSABLE           COMENTARIO
*   -----------------------------------------------------------------------
*   Marzo  8/26  Juan Andres Sanchez   Implementación Inicial
*
*   REVISADO
*   -----------------------------------------------------------------------
*   Sofia Vega, Andres Trujillo
*
*******************************************************************************/


int AND_Gate(int A, int B) {
    int result = A && B;
    return result;
}


