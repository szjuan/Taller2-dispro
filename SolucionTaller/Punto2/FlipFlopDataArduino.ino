/**************************** Symbolic  Constants *****************************/

#define N   60       /* Total number of samples                */
#define R   (N/2)    /* Downsampled size (one sample per cycle) */

/**************** Definition and Initialization of Global Data ****************/

uint8_t clk[N] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
uint8_t clr[N] = {0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
uint8_t pre[N] = {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1};
uint8_t ena[N] = {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1};
uint8_t d[N]   = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0};

/*FN****************************************************************************
*
*   static inline uint8_t rising( uint8_t prev, uint8_t cur )
*
*   Purpose: Detect a rising edge by comparing consecutive clock samples.
*
*   Return:  1 - if a LOW-to-HIGH transition is detected
*            0 - otherwise
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 05/26      Sofia Vega
*
*******************************************************************************/

static inline uint8_t rising(uint8_t prev, uint8_t cur) { return (!prev && cur); }

/*FN****************************************************************************
*
*   static void down2( const uint8_t *in, uint8_t *out )
*
*   Purpose: Downsample a signal array by a factor of 2, keeping even-indexed
*            samples. Used to reduce the clock-rate signal to one sample
*            per full clock cycle for WaveDrom output.
*
*   Return:  Nothing
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 05/26      Sofia Vega
*
*******************************************************************************/

static void down2(const uint8_t *in, uint8_t *out) {
  for (int i = 0; i < R; i++) out[i] = in[2 * i];
}

/*FN****************************************************************************
*
*   static void printClock( const char *name, int n, bool last )
*
*   Purpose: Print a WaveDrom clock signal entry in JSON format to Serial.
*            Uses the 'P' token for a periodic clock wave.
*
*   Return:  Nothing
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 05/26     Sofia Vega
*
*******************************************************************************/

static void printClock(const char *name, int n, bool last) {
  Serial.print("  { \"name\": \""); Serial.print(name); Serial.print("\", \"wave\": \"P");
  for (int i = 1; i < n; i++) Serial.print('.');
  Serial.print("\" }"); Serial.println(last ? "" : ",");
}

/*FN****************************************************************************
*
*   static void printWave( const char *name, int n,
*                          const uint8_t *v, bool last )
*
*   Purpose: Print a WaveDrom signal entry in JSON format to Serial.
*            Emits '0' or '1' on transitions, '.' for unchanged samples.
*
*   Return:  Nothing
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 05/26      Sofia Vega
*
*******************************************************************************/

static void printWave(const char *name, int n, const uint8_t *v, bool last) {
  Serial.print("  { \"name\": \""); Serial.print(name); Serial.print("\", \"wave\": \"");
  uint8_t prev = v[0] & 1;
  Serial.print((char)('0' + prev));
  for (int i = 1; i < n; i++) {
    uint8_t cur = v[i] & 1;
    if (cur == prev) Serial.print('.');
    else { Serial.print((char)('0' + cur)); prev = cur; }
  }
  Serial.print("\" }"); Serial.println(last ? "" : ",");
}

/* ---------------------------------------------------------------------------
 *  Initialise flip-flop state, simulate N samples, downsample, print WaveDrom.
 * --------------------------------------------------------------------------*/

void setup() {
  Serial.begin(115200);

/* Part 1: Initialise flip-flop state and output arrays */

  uint8_t q[N] = {0}, qn[N] = {0};
  uint8_t Q = 0;
  q[0] = Q;
  qn[0] = !Q;

/* Part 2: Simulate DFF behaviour across all N samples */

  for (int i = 1; i < N; i++) {
    if (!clr[i]) Q = 0;
    else if (!pre[i]) Q = 1;
    else if (ena[i] && rising(clk[i - 1], clk[i])) Q = (d[i] != 0);

    q[i] = Q;
    qn[i] = !Q;
  }

/* Part 3: Downsample all signals by factor of 2 */

  uint8_t clk_r[R], clr_r[R], pre_r[R], ena_r[R], d_r[R], q_r[R], qn_r[R];
  down2(clk, clk_r); down2(clr, clr_r); down2(pre, pre_r); down2(ena, ena_r);
  down2(d, d_r);     down2(q, q_r);     down2(qn, qn_r);

/* Part 4: Print WaveDrom JSON to Serial Monitor */

  Serial.println("{ \"signal\": [");
  printClock("clk", R, false);
  printWave("clr", R, clr_r, false);
  printWave("pre", R, pre_r, false);
  printWave("ena", R, ena_r, false);
  printWave("D",   R, d_r,   false);
  printWave("Q",   R, q_r,   false);
  printWave("Qn",  R, qn_r,  true);
  Serial.println("] }");
}

void loop() {

}
