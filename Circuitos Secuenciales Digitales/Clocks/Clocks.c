/*FN****************************************************************************
*
*   rising_edge_clock(int prev_clck,int clk);
*
*   Return: Reloj esta en flanco de subida.
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

int rising_edge_clock(int prev_clck,int clk) {
    return (prev_clck == 0 && clk == 1);
}

