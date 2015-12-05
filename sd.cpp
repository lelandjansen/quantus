// QUANTUS
// sd.cpp


#include "sd.h"

// Initialize file type
File dataFile;
char dataFileName[13];



void sdSetup() {

  Serial.println("Initializing SD card.");

  // Try to initialize SD card
  // If initialization fails, print error to serial monitor
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Initialization failed!");
    // Loop indefinitely
    // Blink status LED red
    while (1) {
      redLED();
      delay(1000);
      offLED();
      delay(1000);
    }
  }

  // If initialization succeeds
  Serial.println("Initialization done.");

} // End of sdSetup





double getConstantsFromSD(char constantName) {

  // Possible values for constantName:
  // pressure (P), pressureError (p), humidity (H), humidityError (h)
  // !!! Implement error in pressure and humidity later

  char*  fileName;
  double defaultValue, minimum, maximum;
  double fileValue;
  double value;


  // Values stored in globals.h
  switch (constantName) {
    case 'H':
      fileName     = "humidity.txt";
      defaultValue = defaultHumidity; // Fraction
      minimum      = minimumHumidity; // Fraction
      maximum      = maximumHumidity; // Fraction
      break;
    case 'P':
      fileName     = "pressure.txt";
      defaultValue = defaultAtmosphericPressure; // Pascales
      minimum      = minimumAtmosphericPressure; // Pascales
      maximum      = maximumAtmosphericPressure; // Pascales
      break;
    default:
      return -1;
  } // End of switch


  // !!! Remove when File I/O is implemented
  value = defaultValue;

  return value;

} // End of getPressureFromSD



void dataFileSetup(int frequency, double humidity, double pressure) {

  // format          012345678901
  // dataFileName = "QNTS_000.csv";


  int fileCount;

  for (fileCount =  999; fileCount > 0; fileCount--) {
    sprintf(dataFileName, "QNTS_%03i.csv", fileCount);

    if (SD.exists(dataFileName)) {
      Serial.print("file: ");
      Serial.println(dataFileName);
      fileCount++;
      sprintf(dataFileName, "QNTS_%03i.csv", fileCount);
      Serial.print("new: ");
      Serial.println(dataFileName);
      break;
    }

  }

  dataFile = SD.open(dataFileName, FILE_WRITE);

  dataFile.println("QUANTUS,Distance-time measurements");
  dataFile.println("Computed by,QUANTUS UNO");
  dataFile.println("Version,0.0.7"); // !!! Implement proper versioning later
  dataFile.print("Frequency (Hz),");
  dataFile.println(frequency);
  dataFile.print("Relative humidity (fraction),");
  dataFile.println(humidity);
  dataFile.print("Pressure (Pa),");
  dataFile.println(pressure);
  dataFile.println(",");
  dataFile.println("time (s),distance (m)");

  dataFile.close();

  Serial.println("QUANTUS,Distance-time measurements");
  Serial.println("Computed by,QUANTUS UNO");
  Serial.println("Version,0.0.7"); // !!! Implement proper versioning later
  Serial.print("Frequency (Hz),");
  Serial.println(frequency);
  Serial.print("Relative humidity (percent),");
  Serial.println(humidity);
  Serial.print("Pressure (Pa),");
  Serial.println(pressure);
  Serial.println(",");
  Serial.println(",");
  Serial.println("time (s),distance (m)");

}


// Accepts time in microseconds, distance in centimetres
// Converts values to seconds and metres
void writeDataToFile(double pointTime, double distance) {



  dataFile = SD.open(dataFileName, FILE_WRITE);

  if (dataFile) {
    dataFile.print(pointTime, 6);
    dataFile.print(",");
    dataFile.print(distance, 3);
    dataFile.println();
    dataFile.close();

    Serial.print(pointTime, 6);
    Serial.print(",");
    Serial.print(distance, 3);
    Serial.println();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    while (1) {
      redLED();
      delay(1000);
      offLED();
      delay(1000);
    }
  }

}
