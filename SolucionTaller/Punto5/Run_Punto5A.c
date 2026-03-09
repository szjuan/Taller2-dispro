/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h> /* Due to: printf, putchar */

/* ------------------------ Inclusion of Own Headers ------------------------ */

/**************************** Symbolic  Constants *****************************/

/* ----------------- Predefined Sizes of Arrays and Strings ----------------- */

#define MAX     34      /* Number of samples along time   */
#define HALF    (MAX/2) /* Downsampled signal length       */

/************************** Prototypes of Functions ***************************/

/* ----------------- Public Functions defined after main() ------------------ */

static void Print_Wave    ( const char *, int, const int *, float, int );
static void Print_Wave_X  ( const char *, int, const int *, float, int );
static void Print_Clock   ( const char *, int, const int *, float, int );
static void Downsample2   ( const int *, int, int * );
static int  Rising_Edge   ( int, int );
static void DFF           ( int *, int, int, int, int, int * );

/******************************* Main Function ********************************/

/*FN****************************************************************************
*
*   int main( void )
*
*   Purpose: Simulate the 74HC595 shift register and output WaveDrom JSON.
*
*   Plan:
*       Part 1: Define input signals
*       Part 2: Initialize state arrays
*       Part 3: Simulate for all timesteps
*       Part 4: Downsample all signals
*       Part 5: Print WaveDrom output
*
*   Register of Revisions:
*   DATE        RESPONSIBLE  COMMENT
*   ----------  -----------  -------------------------
*   MAR 04/26   Sofia V      Initial implementation
*
*******************************************************************************/

int main( void )
{

/* Part 1: Define input signals */

int srclk[MAX] = {
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0
};
int rclk[MAX] = {
    0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
    1,0,0,0,1,0,0,0,0,0,1,0,0,0
};
int ser[MAX] = {
    0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,0,0,0,0,0,0,0,0
};
int srclr[MAX] = {
    0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,1
};
int oe[MAX] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,1,1,0,0,0,0,0,0,0,0,0
};

/* Part 2: Initialize state arrays */

int sh[8][MAX]={{0}}, st[8][MAX]={{0}}, q[8][MAX]={{0}};
int SH[8]={0}, ST[8]={0};

for( int b = 0; b < 8; b++ ) { sh[b][0]=SH[b]; st[b][0]=ST[b]; }

/* Part 3: Simulate for all timesteps */

for( int i = 1; i < MAX; i++ ) {

    DFF( &SH[0], srclk[i-1], srclk[i], srclr[i], ser[i],           &sh[0][i] );
    for( int b = 1; b < 8; b++ )
        DFF( &SH[b], srclk[i-1], srclk[i], srclr[i], sh[b-1][i-1], &sh[b][i] );
    for( int b = 0; b < 8; b++ )
        DFF( &ST[b], rclk[i-1],  rclk[i],  1,        sh[b][i-1],   &st[b][i] );
    for( int b = 0; b < 8; b++ )
        q[b][i] = oe[i] ? -1 : st[b][i];

}

/* Part 4: Downsample all signals */

int _ser[HALF], _srclr[HALF], _oe[HALF], _sh7[HALF];
Downsample2( ser,   MAX, _ser   );
Downsample2( srclr, MAX, _srclr );
Downsample2( oe,    MAX, _oe    );
Downsample2( sh[7], MAX, _sh7   );

int _sh[8][HALF], _st[8][HALF], _q[8][HALF];
for( int b = 0; b < 8; b++ ) {
    Downsample2( sh[b], MAX, _sh[b] );
    Downsample2( st[b], MAX, _st[b] );
    Downsample2( q[b],  MAX, _q[b]  );
}

/* Part 5: Print WaveDrom output */

static const char *shn[8] = {"SH0","SH1","SH2","SH3","SH4","SH5","SH6","SH7"};
static const char *stn[8] = {"ST0","ST1","ST2","ST3","ST4","ST5","ST6","ST7"};
static const char *qn[8]  = {"QA", "QB", "QC", "QD", "QE", "QF", "QG", "QH"};

printf( "{ \"signal\": [\n" );

printf( " [\"Control\"],\n" );
Print_Clock( "SRCLK",  MAX,  srclk,  0.0f, 0 );
Print_Wave ( "SER",    HALF, _ser,   0.5f, 0 );
Print_Clock( "RCLK",   MAX,  rclk,   0.5f, 0 );
Print_Wave ( "SRCLR#", HALF, _srclr, 0.0f, 0 );
Print_Wave ( "OE#",    HALF, _oe,    0.5f, 0 );

printf( " {},\n [\"Shift Register (SH)\"],\n" );
for( int b = 0; b < 8; b++ ) Print_Wave( shn[b], HALF, _sh[b], 0.0f, 0 );

printf( " {},\n [\"Storage Register (ST)\"],\n" );
for( int b = 0; b < 8; b++ ) Print_Wave( stn[b], HALF, _st[b], 0.0f, 0 );

printf( " {},\n [\"Output (Q)\"],\n" );
for( int b = 0; b < 8; b++ ) Print_Wave_X( qn[b], HALF, _q[b], 0.5f, 0 );
Print_Wave( "QH'", HALF, _sh7, 0.0f, 1 );

printf( "] }\n" );

return 0;

} /* main */

/*FN****************************************************************************
*
*   static int Rising_Edge( int prev_clk, int clk )
*
*   Purpose: Detect a rising edge on a clock signal.
*
*   Parameters:
*       prev_clk - Previous clock sample
*       clk      - Current clock sample
*
*   Return: 1 if rising edge detected, 0 otherwise
*
*   Register of Revisions:
*   DATE        RESPONSIBLE  COMMENT
*   ----------  -----------  -------------------------
*   MAR 04/26   Sofia V      Initial implementation
*
*******************************************************************************/

static int
Rising_Edge( int prev_clk, int clk )
{
return !prev_clk && clk;

} /* Rising_Edge */

/*FN****************************************************************************
*
*   static void DFF( int *s, int pc, int c, int clr, int d, int *q )
*
*   Purpose: Simulate a D flip-flop with async active-low clear.
*
*   Parameters:
*       s   - Internal state (persistent across calls)
*       pc  - Previous clock sample
*       c   - Current clock sample
*       clr - Async clear, active low
*       d   - Data input
*       q   - Output
*
*   Register of Revisions:
*   DATE        RESPONSIBLE  COMMENT
*   ----------  -----------  -------------------------
*   MAR 04/26   Sofia V      Initial implementation
*
*******************************************************************************/

static void
DFF( int *s, int pc, int c, int clr, int d, int *q )
{
if( !clr )
    *s = 0;
else if( Rising_Edge( pc, c ) )
    *s = d;

*q = *s;

} /* DFF */

/*FN****************************************************************************
*
*   static void Downsample2( const int *in, int n, int *out )
*
*   Purpose: Downsample a signal by 2, keeping even-indexed samples.
*            Used to convert 2x-rate simulation arrays to 1x for WaveDrom.
*
*   Parameters:
*       in  - Input array at 2x rate
*       n   - Length of input array
*       out - Output array at 1x rate (length n/2)
*
*   Register of Revisions:
*   DATE        RESPONSIBLE  COMMENT
*   ----------  -----------  -------------------------
*   MAR 04/26   Sofia V      Initial implementation
*
*******************************************************************************/

static void
Downsample2( const int *in, int n, int *out )
{
for( int i = 0; i < n/2; i++ ) out[i] = in[2*i];

} /* Downsample2 */

/*FN****************************************************************************
*
*   static void Print_Wave( const char *name, int n, const int *v,
*                            float phase, int last )
*
*   Purpose: Print a 0/1 signal as a WaveDrom wave string.
*            Appends phase field if phase != 0.
*
*   Parameters:
*       name  - Signal name
*       n     - Number of samples
*       v     - Signal array
*       phase - WaveDrom phase offset (0 = none)
*       last  - 1 if this is the last signal (no comma)
*
*   Register of Revisions:
*   DATE        RESPONSIBLE  COMMENT
*   ----------  -----------  -------------------------
*   MAR 04/26   Sofia V      Initial implementation
*
*******************************************************************************/

static void
Print_Wave( const char *name, int n, const int *v, float phase, int last )
{
printf( "  { \"name\": \"%s\", \"wave\": \"", name );

int prev = v[0] & 1;
putchar( prev ? '1' : '0' );
for( int i = 1; i < n; i++ ) {
    int cur = v[i] & 1;
    putchar( cur == prev ? '.' : (cur ? '1' : '0') );
    prev = cur;
}

if( phase != 0.0f ) {
    putchar( '.' );
    printf( "\", \"phase\": %.1f }%s\n", phase, last ? "" : "," );
} else
    printf( "\" }%s\n", last ? "" : "," );

} /* Print_Wave */

/*FN****************************************************************************
*
*   static void Print_Wave_X( const char *name, int n, const int *v,
*                              float phase, int last )
*
*   Purpose: Print a 0/1/x signal as a WaveDrom wave string.
*            Values of -1 are rendered as 'x' (high impedance).
*
*   Parameters:
*       name  - Signal name
*       n     - Number of samples
*       v     - Signal array (-1 = high-Z)
*       phase - WaveDrom phase offset (0 = none)
*       last  - 1 if this is the last signal (no comma)
*
*   Register of Revisions:
*   DATE        RESPONSIBLE  COMMENT
*   ----------  -----------  -------------------------
*   MAR 04/26   Sofia V      Initial implementation
*
*******************************************************************************/

static void
Print_Wave_X( const char *name, int n, const int *v, float phase, int last )
{
printf( "  { \"name\": \"%s\", \"wave\": \"", name );

int prev = v[0];
putchar( prev == -1 ? 'x' : (prev ? '1' : '0') );
for( int i = 1; i < n; i++ ) {
    int cur = v[i];
    if( cur == prev ) putchar( '.' );
    else putchar( cur == -1 ? 'x' : (cur ? '1' : '0') );
    prev = cur;
}

if( phase != 0.0f ) {
    putchar( '.' );
    printf( "\", \"phase\": %.1f }%s\n", phase, last ? "" : "," );
} else
    printf( "\" }%s\n", last ? "" : "," );

} /* Print_Wave_X */

/*FN****************************************************************************
*
*   static void Print_Clock( const char *name, int n_raw, const int *v,
*                             float phase, int last )
*
*   Purpose: Print a clock signal as WaveDrom wave string.
*            Reads even-indexed samples: 1 -> 'P' (pulse), 0 -> '0' (missed).
*
*   Parameters:
*       name  - Signal name
*       n_raw - Length of raw (2x rate) array
*       v     - Raw signal array
*       phase - WaveDrom phase offset (0 = none)
*       last  - 1 if this is the last signal (no trailing comma)
*
*   Register of Revisions:
*   DATE        RESPONSIBLE  COMMENT
*   ----------  -----------  -------------------------
*   MAR 04/26   Sofia V      Initial implementation
*
*******************************************************************************/

static void
Print_Clock( const char *name, int n_raw, const int *v, float phase, int last )
{
printf( "  { \"name\": \"%s\", \"wave\": \"", name );

for( int i = 0; i < n_raw; i += 2 ) putchar( v[i] ? 'P' : '0' );

if( phase != 0.0f ) {
    putchar( '.' );
    printf( "\", \"phase\": %.1f }%s\n", phase, last ? "" : "," );
} else
    printf( "\" }%s\n", last ? "" : "," );

} /* Print_Clock */
