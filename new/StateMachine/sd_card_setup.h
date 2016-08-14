#ifndef STATEMACHINE_SD_CARD_SETUP_H_
#define STATEMACHINE_SD_CARD_SETUP_H_

#include <iostream>
#include "device_state.h"
#include "device.h"
#include "input.h"

class SdCardSetup : public DeviceState {
 public:
  static SdCardSetup state;
  virtual void HandleInput(Device &device, Input input);
  virtual void Update(Device &device);
};

#endif //STATEMACHINE_SD_CARD_SETUP_H_
