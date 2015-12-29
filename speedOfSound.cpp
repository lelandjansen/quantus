// QUANTUS
// speedOfSound.cpp

/* REFERENCE for speed of sound calculation
 * O.Cramer, "The variation of the specific heat ratio and the speed of sound in
 *   air with temperature, pressure, humidity, and CO2 concentration,"
 *   J. Acoust. Soc. Am. 93, 2510-2516 (1993).
 */

#include "speedOfSound.hpp"


double computeSpeedOfSound(double temperature) {

  // DELETE
  // return 344.66;

  // Input variables
  double t  = temperature;              // Temperature (degrees Celsius)
  double p  = settings.pressure;        // Atmospheric pressure (Pascales)
  double h  = settings.humidity;        // Relative humidity (fraction)
  double xc = settings.CO2MoleFraction; // Carbon dioxide mole fraction (fraction)

  // Computed variables
  double c;    // Speed of sound in air (metres per second)
  double T;    // Temperature in (Kelvin)
  double xw;   // Water vapor mole fraction (fraction)
  double f;    // Enhancement factor
  double psv;  // Saturation vapor pressure of water vapor in air (Aascales)

  // Coefficients: Speed of sound in air
  const double a0   =  331.5024;
  const double a1   =    0.603055;
  const double a2   =   -0.000528;
  const double a3   =   51.471935;
  const double a4   =    0.1495874;
  const double a5   =   -0.000782;
  const double a6   =   -1.82e-7;
  const double a7   =    3.73e-8;
  const double a8   =   -2.93e-10;
  const double a9   =  -85.20931;
  const double a10  =   -0.228525;
  const double a11  =    5.91e-5;
  const double a12  =   -2.835149;
  const double a13  =   -2.15e-13;
  const double a14  =   29.179762;
  const double a15  =    0.000486;

  // Coefficients: Saturation vapor pressure of water vapor in air
  const double a16  =    1.2188105e-5;
  const double a17  =   -1.9509874e-2;
  const double a18  =   34.04926034;
  const double a19  =   -6.3536311e3;

  // Coefficients: Enhancement factor
  const double a20  =    1.00062;
  const double a21  =    3.14e-8;
  const double a22  =    5.6e-7;


  // Temperature (Kelvin)
  T = t + 273.15;


  // Enhancement factor
  f    =  a20;
  f   +=  a21 * p;
  f   +=  a22 * t   * t;


  // Saturation vapor pressure of water vapor in air (Pascales)
  psv  =  a16  * T   * T;
  psv +=  a17  * T;
  psv +=  a18;
  psv +=  a19  / T;
  psv  =  exp(psv);


  // Mole fraction of water vapor in air (fraction)
  xw   =  h   * f   * psv / p;


  // Speed of sound in air (metres per second)
  c    =  a0  + a1  * t   + a2  * t   * t;
  c   += (a3  + a4  * t   + a5  * t   * t) * xw;
  c   += (a6  + a7  * t   + a8  * t   * t) * p;
  c   += (a9  + a10 * t   + a11 * t   * t) * xc;
  c   +=  a12 * xw  * xw;
  c   +=  a13 * p   * p;
  c   +=  a14 * xc  * xc;
  c   +=  a15 * xw  * p * xc;


  return c;


} // End of computeSpeedOfSound
