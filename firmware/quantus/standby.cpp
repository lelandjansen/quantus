// QUANTUS
// standby.cpp

#include "standby.hpp"


// Standby state
void standby() {

  sdInserted() ? measureTemperature_float() : NEXT_STATE = STATE_NO_SD;

} // End of standby
