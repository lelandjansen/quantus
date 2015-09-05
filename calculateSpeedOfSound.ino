/*
  Quantus
  calculateSpeedOfSound.ino
  Copyright (c) Leland Jansen 2015. All rights reserved.
*/


#include <math.h>


// Calculate the speed of sound in the given conditions
// Accepts three parameters: T, H, and P
// T is the air temperature (measured in degrees Celsius)
// H is the relative humidity (measured as a fraction)
// P is the ambient pressure (measured in Pascales)
// Returns the speed of sound in metres per second
double calculateSpeedOfSound(double T, double H, double P) {

    // Convert temperature from degrees Celsius to kelvin
    T += 273.15;
      
    // Constants
    // Universal gas constant (J/(mol K))
    double R = 8.3145e3;
    // Molar mass of dry air (g/mol)
    double mmAir = 28.96;
    // Molar mass of water (g/mol)
    double mmH2O = 18.03;
    // A (from 1 to 100 Celsius) (mmHg)
    double A = 8.07131;
    // B (from 1 to 100 Celsius) (mmHg)
    double B = 1730.63;
    // C (from 1 to 100 Celsius) (mmHg)
    double C = 233.426;


    // Vapor pressure (Pa)
    double V = pow(10, A - B/(C + T - 273.15)) * 1.01325e5/760.;

    // Fraction of molecules that are water
    double h = (H * V) / (100. * P);

    // Mean molecular weight of moist air
    double M = mmAir - (mmAir - mmH2O) * h;

    // Adiabatic constant of moist air
    double y = (7. + h) / (5. + h);


    // Speed of sound (m/s)
    double speedOfSound = sqrt(y * R * T / M);

    /*
    Serial.print("speedOfSound: \t");
    Serial.print(speedOfSound, 4);
    Serial.println(" m/s");
    */
    
    return speedOfSound;

}
