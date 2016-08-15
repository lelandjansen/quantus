#ifndef STATEMACHINE_NO_SD_CARD_H_
#define STATEMACHINE_NO_SD_CARD_H_

#include <iostream>
#include "device_state.h"
#include "device.h"
#include "input.h"

class NoSdCard : public DeviceState {
 public:
  static NoSdCard state;
  virtual void HandleInput(Device &device, Input input);
  virtual void Update(Device &device);
};

#endif //STATEMACHINE_NO_SD_CARD_H_
