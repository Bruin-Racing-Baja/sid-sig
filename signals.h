/* signals.h
 *
 * Functions for common system identification signals, assumed to run on microsecond timesteps
 *
 * author: Tyler McCown (tylermccown@engineering.ucla.edu)
 * created: 15 March 2020
 */

// sine signal
int sine_amp(0); // [pot counts]
int sine_off(0); // [pot counts]
double sine_freq(0);

// logarithmic chirp signal
int chirp_amp = 0;
double chirp_w1(1); // [2pi*Hz]
double chirp_w2(1); // [2pi*Hz]
int chirp_per = -1+(2^15); // [s]
double chirp_alpha = 1./chirp_per*log(chirp_w2/chirp_w1);
int chirp_off(0);

void configure_sine(const int amp, const double freq, const int offset = 0) {
    /* sets the parameters of the sinusoid
     *
     * amp: sinusoid amplitude in whatever units
     * freq: sinusoid frequency in [Hz]
     * offset: sinusoid offset in whatever units
     */
    sine_amp = amp;
    sine_off = offset;
    sine_freq = freq;
}

void configure_chirp(const int amp, const double start_freq, const double stop_freq, const int per, const int offset = 0) {
    /* sets the parameters of the logarithmic chirp
     * 
     * amp: chirp amplitude in whatever units
     * start_freq: chirp starting frequency in [rad/s]
     * stop_freq: chirp stop frequency in [rad/s]
     * per: chirp period in [s]
     * offset: chirp offset in whatever units
     */
    chirp_amp = amp;
    chirp_w1 = start_freq;
    chirp_w2 = stop_freq;
    chirp_per = per;
    chirp_alpha = 1./chirp_per*log(chirp_w2/chirp_w1);
    chirp_off = offset;
}

int sine(unsigned long t) {
  return sine_off + sine_amp*sin(2*PI*sine_freq*t/1.e3);
}

int chirp(unsigned long t) {
  t = t % (1000000*chirp_per);
  double f = chirp_w1/chirp_alpha*(exp(chirp_alpha*t/1.0e6) - 1);
  return chirp_off + chirp_amp*sin(f);
}

