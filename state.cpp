// QUANTUS
// state.cpp

#include "state.hpp"


// Run the function of the next state
void state() {

  switch (NEXT_STATE) {

    case STATE_NO_SD:
      STATE = STATE_NO_SD;
      noSD();
      break;

    case STATE_SD_SETUP:
      STATE = STATE_SD_SETUP;
      sdSetup();
      break;

    case STATE_STANDBY:
      STATE = STATE_STANDBY;
      // function
      break;

    case STATE_DATA_SETUP:
      STATE = STATE_DATA_SETUP;
      dataSetup();
      break;

    case STATE_DATA_COLLECT:
      STATE = STATE_DATA_COLLECT;
      // dataCollect();
      dataCollect_fp();
      break;

    case STATE_DATA_CONCLUDE:
      STATE = STATE_DATA_CONCLUDE;
      dataConclude();
      break;

    case STATE_WARNING:
      STATE = STATE_WARNING;
      // function
      break;

    case STATE_ERROR:
      STATE = STATE_ERROR;
      // function
      break;

  } // End of switch

} // End of state



// Advance to next state
void nextState() {

  if (STATE == NEXT_STATE) {
    switch (STATE) {

      case STATE_NO_SD:
        // Do not advance to next state
        NEXT_STATE = STATE_NO_SD;
        break;

      case STATE_SD_SETUP:
        // Do not advance to next state
        NEXT_STATE = STATE_SD_SETUP;
        break;

      case STATE_STANDBY:
        NEXT_STATE = STATE_DATA_SETUP;
        break;

      case STATE_DATA_SETUP:
        NEXT_STATE = STATE_DATA_CONCLUDE;
        break;

      case STATE_DATA_COLLECT:
        NEXT_STATE = STATE_DATA_CONCLUDE;
        break;

      case STATE_DATA_CONCLUDE:
        // Do not advance to next state
        NEXT_STATE = STATE_DATA_CONCLUDE;
        break;

      case STATE_WARNING:
        NEXT_STATE = STATE_STANDBY;
        break;

      case STATE_ERROR:
        // Do not advance to next state
        NEXT_STATE = STATE_ERROR;
        break;

    } // End of switch
  } // End of if

} // End of nextState
