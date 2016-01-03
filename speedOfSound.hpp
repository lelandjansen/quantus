// QUANTUS
// speedOfSound.hpp

#ifndef __SPEEDOFSOUND_HPP__
#define __SPEEDOFSOUND_HPP__

#include <math.h>
#include "globals.hpp"

// Coefficients: Speed of sound in air
const double K0   =  331.5024;
const double K1   =    0.603055;
const double K2   =   -0.000528;
const double K3   =   51.471935;
const double K4   =    0.1495874;
const double K5   =   -0.000782;
const double K6   =   -1.82e-7;
const double K7   =    3.73e-8;
const double K8   =   -2.93e-10;
const double K9   =  -85.20931;
const double K10  =   -0.228525;
const double K11  =    5.91e-5;
const double K12  =   -2.835149;
const double K13  =   -2.15e-13;
const double K14  =   29.179762;
const double K15  =    0.000486;

// Coefficients: Saturation vapor pressure of water vapor in air
const double K16  =    1.2188105e-5;
const double K17  =   -1.9509874e-2;
const double K18  =   34.04926034;
const double K19  =   -6.3536311e3;

// Coefficients: Enhancement factor
const double K20  =    1.00062;
const double K21  =    3.14e-8;
const double K22  =    5.6e-7;



extern uint32_t TEMPERATURE_INITIAL;
extern uint32_t   SPEED_OF_SOUND_INITIAL;
extern uint32_t D_SPEED_OF_SOUND_INITIAL;




// Functions
double   convertCelsiusToKelvin(double temperature);
double   computeEnhncementFactor(double temperature);
double   computeEnhncementFactorDerivative(double temperature);
double   computeH2OSaturationVaporPressure(double temperature);
double   computeH2OSaturationVaporPressureDerivative(double temperature);
double   computeH2OMoleFractionInAir(double temperature);
double   computeH2OMoleFractionInAirDerivative(double temperature);
double   computeSpeedOfSound(double temperature);
double   computeSpeedOfSoundDerivative(double temperature);
uint32_t computeSpeedOfSoundLinearApproximation_fp(uint32_t temperature);



#endif
