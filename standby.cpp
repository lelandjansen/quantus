// QUANTUS
// standby.cpp

#include "standby.hpp"


// Standby state
void standby() {

  if (sdInserted()) measureTemperature_float();
  else  NEXT_STATE = STATE_NO_SD;

} // End of standby
