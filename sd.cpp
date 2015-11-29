// QUANTUS
// sd.cpp

#include "sd.h"

// Initialize file type
File dataFile;

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


  // !!! Finish File I/O later
  /*
  // Check to see if file pressure.txt exists
  // If pressure.txt exists
  if (SD.exists(fileName)) {
    Serial.print(fileName);
    Serial.println(" exists");


    // Open the file
    // FILE_WRITE enables read/write access to the file
    dataFile = SD.open(fileName, FILE_WRITE);

    // If the file is available
    if (dataFile) {
      // Read file contents
      // atoi converts a string to a double floating point number
      fileValue = atoi(myFile.read());
      Serial.print("fileValue: ");
      Serial.println(fileValue);

    }
    // If the file is not available
    else {
      Serial.println("Cannot open file!");
      // Loop indefinitely
      // Blink status LED red
      while (1) {
        redLED();
        delay(1000);
        offLED();
        delay(1000);
      }
    }

    // Check to see if file value is in range
    // If the file's value is within the permitted range
    if (fileValue >= minimum && fileValue <= maximum) {
      // Set value to the file's value
      value = fileValue;
    }
    // If the file's content is not within the range (or not a valid value)
    else {
            // Close the current file
      dataFile.close();

      // Remove the file
      SD.remove(fileName);

      // Create new file
      dataFile = SD.open(fileName);

      dataFile.print(defaultValue);

      // Set value to the default value
      value = defaultValue;


    }

    // Convert the string to a double floating point number
    // Check to see if value makes sense
    // If value makes sense
      // Set "pressure" to that value
    // If value does not make sense
      // Overwrite current file data with standard pressure value
      // Set "pressure" to standard value
    // Close file

    dataFile.close;
  }
  // If pressure.txt does not exist
  else {
    Serial.println("example.txt doesn't exist.");
    // Create file "pressure.txt"
    // Open file
    // Add standard pressure value to "pressure.txt file"
    // Set "pressure" to standard value
    // Close file
  }


  */


  // !!! Remove when File I/O is implemented
  value = defaultValue;

  return value;

} // End of getPressureFromSD



void dataFileSetup(int frequency, double humidity, double pressure) {

  if (!SD.exists("QUANTUS.csv")) {
    dataFile = SD.open("QUANTUS.csv", FILE_WRITE);
  }
  else {
    SD.remove("QUANTUS.csv");
    dataFile = SD.open("QUANTUS.csv", FILE_WRITE);
  }

  dataFile.println("QUANTUS,Distance-time measurements");
  dataFile.println("Computed by,QUANTUS EDISON");
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
  Serial.println("Computed by,QUANTUS EDISON");
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



  dataFile = SD.open("QUANTUS.csv", FILE_WRITE);

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
