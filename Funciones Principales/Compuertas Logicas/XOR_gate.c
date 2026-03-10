#include "LogicGates.h"

/*FN****************************************************************************
*
*   XOR_Gate(int A, int B);
*
*   Return: Retorna el resultado entre de la operacion XOR entre A y B.
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

int XOR_Gate(int A, int B) {
    return (A && !B) || (!A && B);
}