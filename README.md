# Arduino signals library

Functions for common system identification signals. Currently includes sinusoids and logarithmic chirps.

## Installation

Clone or unzip this repository into the Arduino libraries folder, or any other folder which is part of the Arduino build path. Normally this is under `~/Documents/Arduino/libraries/`.

## How to use

### Sine

Sine waves are defined by an amplitude, a frequency (Hz), and an offset. The function prototype is as follows:
```c++
void configure_sine(const int amp, const double freq, const int offset = 0);
int sine(unsigned long t);
```
Before calling the `sine` function, it must be configured using `configure_sine`. By default, the amplitude, frequency, and offset are all set to zero, so calling the sine wave without configuring it will result in a zero signal. 

The following example configures a sinusoid which oscillates between 10 and 20 at a frequency of 8 times per second
```c++
int min_value = 10;
int max_value = 20;
int amp = (max_value - min_value)/2;
double freq = 8;
int offset = (max_value + min_value)/2;

configure_sine(amp, freq, offset);
```
The sine function can now be called by
```c++
unsigned long t = micros();
int x = sine(t);
```

### Logarithmic chirp

A chirp signal is a sinusoid whose frequency varies over time, often periodically, with the instantaneous frequency of a sinusoid defined as the derivative of its argument. Many types of chirp signals exist are they defined by form of their instantaneous frequency. This library implements a logarithmic chirp, where the logarithm of the instantaneous frequency is proportional to time. 

The implementation in this library includes a logarithmic chirp which sweeps a given frequency band in a given period. This signal is defined by an amplitude, a starting frequency (rad/s), a stopping frequency (rad/s), a period (s), and an offset. The function prototype is as follows
```c++
void configure_chirp(const int amp, const double start_freq, const double stop_freq, const int per, const int offset = 0);
int chirp(unsigned long t);
```
Before calling the `chirp` function, it must be configured using `configure_chirp`. By default, the amplitude and offset are set to zero, and both frequencies are set to one, and the period is set to 32767. 

The following example configures a logarithmic chirp which sweeps from 0.1 rad/s to 10 rad/s in 15 seconds, oscillating between 10 and 20
```c++
int min_value = 10;
int max_value = 20;
int amp = (max_value - min_value)/2;
double start_freq = 0.1;
double stop_freq = 10;
int per = 15;
int offset = (max_value + min_value)/2;

configure_chirp(amp, start_freq, stop_freq, per, offset);
```
The chirp function can now be called by
```c++
unsigned long t = micros();
int x = chirp(t);
```

