// QUANTUS
// speedOfSound.cpp

/* REFERENCE for speed of sound in air equation
 * O.Cramer, "The variation of the specific heat ratio and the speed of sound in
 *   air with temperature, pressure, humidity, and CO2 concentration,"
 *   J. Acoust. Soc. Am. 93, 2510-2516 (1993).
 */


#include "speedOfSound.hpp"

uint32_t TEMPERATURE_INITIAL;
uint32_t SPEED_OF_SOUND_INITIAL;
uint32_t D_SPEED_OF_SOUND_INITIAL;





// Convert temperature from degrees Celsius to Kelvin
double convertCelsiusToKelvin(double temperature) {
    return temperature + 273.15;
} // End of convertCelsiusToKelvin





// Compute enhancement factor
double computeEnhncementFactor(double temperature) {

    double f;                     // Enhancement factor
    double p = SETTINGS.pressure; // Pressure (Pascales)
    double t = temperature;       // Temperature (Celsius)

    f    =  K20;
    f   +=  K21 * p;
    f   +=  K22 * t   * t;

    return f;

} // End of computeEnhncementFactor


// Compute enhancement factor derivative
double computeEnhncementFactorDerivative(double temperature) {

    double d_f;             // Enhancement factor
    double t = temperature; // Temperature (Celsius)

    d_f = 2 * K22 * t;

    return d_f;

} // End of computeEnhncementFactorDerivative





// Compute saturation vapor pressure of water vapor in air
double computeH2OSaturationVaporPressure(double temperature) {

    double psv; // Saturation vapor pressure of water vapor in air
    double T = convertCelsiusToKelvin(temperature); // Temperature (Kelvin)

    psv  =  K16  * T   * T;
    psv +=  K17  * T;
    psv +=  K18;
    psv +=  K19  / T;
    psv  =  exp(psv);

    return psv;

} // End of computeH2OSaturationVaporPressure


// Compute saturation vapor pressure of water vapor in air
double computeH2OSaturationVaporPressureDerivative(double temperature) {

    double d_psv; // Saturation vapor pressure of water vapor in air derivative
    double psv = computeH2OSaturationVaporPressure(temperature); // Saturation vapor pressure of water vapor in air
    double T = convertCelsiusToKelvin(temperature); // Temperature (Kelvin)

    d_psv  = (2 * K16 * T) + K17 - (K19 / (T * T));
    d_psv *= psv;

    return d_psv;

} // End of computeH2OSaturationVaporPressureDerivative





// Compute mole fraction of water vapor in air (fraction)
double computeH2OMoleFractionInAir(double temperature) {

    double xw;                             // Water vapor mole fraction (fraction)
    double h = SETTINGS.humidity;          // Humidity (fraction)
    double p = SETTINGS.pressure;          // Pressure (Pascales)
    double f = computeEnhncementFactor(temperature); // Enhancement factor
    double psv = computeH2OSaturationVaporPressure(temperature); // Saturation
    // vapor pressure of water vapor in air

    xw =  h * f * psv / p;

    return xw;

} // End of computeH2OMoleFractionInAir


// Compute mole fraction of water vapor in air (fraction)
double computeH2OMoleFractionInAirDerivative(double temperature) {

    double d_xw; // Water vapor mole fraction derivative
    double h     = SETTINGS.humidity; // Humidity (fraction)
    double p     = SETTINGS.pressure; // Pressure (Pascales)
    double f     = computeEnhncementFactor(temperature); // Enhancement factor
    double d_f   = computeEnhncementFactorDerivative(temperature); // Enhancement factor derivative
    double psv   = computeH2OSaturationVaporPressure(temperature);
    double d_psv = computeH2OSaturationVaporPressureDerivative(temperature);

    d_xw  = d_f  * psv  + d_psv * f;
    d_xw *= h    / p;

    return d_xw;

} // End of computeH2OMoleFractionInAirDerivative





// Compute speed of sound in air based on temperature, atmospheric pressure,
//  relative humidity, and carbon dioxide mole fraction
double computeSpeedOfSound(double temperature) {

    // Constant variables
    double t  = temperature;              // Temperature (degrees Celsius)
    double p  = SETTINGS.pressure;        // Atmospheric pressure (Pascales)
    double xc = SETTINGS.CO2MoleFraction; // Carbon dioxide mole fraction (fraction)

    // Computed variables
    double c;    // Speed of sound in air (metres per second)
    double xw = computeH2OMoleFractionInAir(t); // Water vapor mole fraction (fraction)

    // Speed of sound in air (metres per second)
    c    =  K0  + K1  * t   + K2  * t   * t;
    c   += (K3  + K4  * t   + K5  * t   * t) * xw;
    c   += (K6  + K7  * t   + K8  * t   * t) * p;
    c   += (K9  + K10 * t   + K11 * t   * t) * xc;
    c   +=  K12 * xw  * xw;
    c   +=  K13 * p   * p;
    c   +=  K14 * xc  * xc;
    c   +=  K15 * xw  * p   * xc;

    return c;

} // End of computeSpeedOfSound


// Compute first derivative of speed of sound in air with respect to temperature
double computeSpeedOfSoundDerivative(double temperature) {

    // Constant variables
    double t    = temperature;              // Temperature (degrees Celsius)
    double p    = SETTINGS.pressure;        // Atmospheric pressure (Pascales)
    double xc   = SETTINGS.CO2MoleFraction; // Carbon dioxide mole fraction (fraction)

    // Computed variables
    double d_c; // Speed of sound in air derivative
    double xw   = computeH2OMoleFractionInAir(t); // Water vapor mole fraction (fraction)
    double d_xw = computeH2OMoleFractionInAirDerivative(t); // Water vapor mole fraction derivative

    d_c  =  K1  + 2   * K2  * t;
    d_c += (K4  + 2   * K5  * t) * xw;
    d_c += (K3  + K4  * t   + K5 * t   * t) * d_xw;
    d_c += (K7  * 2   * K8  * t) * p;
    d_c += (K10 + 2   * K11 * t) * xc;
    d_c +=  2   * K12 * xw  * d_xw;
    d_c +=  K15 * p   * xc  * d_xw;

    return d_c;

} // End of computeSpeedOfSoundDerivative





// Compute the speed of sound in air using a linear approximation (fiexed point)
uint32_t computeSpeedOfSoundLinearApproximation_fp(uint32_t temperature) {

    // Linear approximation:
    // L(x) = f(a) + f'(a)(x-a)

    uint32_t speedOfSound;

    if (temperature == TEMPERATURE_INITIAL) {
        speedOfSound = SPEED_OF_SOUND_INITIAL;
    }
    else if (temperature > TEMPERATURE_INITIAL) {
        speedOfSound  = (temperature - TEMPERATURE_INITIAL) / 10000;
        speedOfSound *= D_SPEED_OF_SOUND_INITIAL;
        speedOfSound += SPEED_OF_SOUND_INITIAL;
    }
    else if (temperature < TEMPERATURE_INITIAL) {
        speedOfSound  = (TEMPERATURE_INITIAL - temperature) / 10000;
        speedOfSound *= D_SPEED_OF_SOUND_INITIAL;
        speedOfSound  = SPEED_OF_SOUND_INITIAL - speedOfSound;
    }

    return speedOfSound;

} // End of speedOfSoundLinearApproximation_fp
