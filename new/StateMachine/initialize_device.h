#ifndef STATEMACHINE_INITIALIZE_DEVICE_H_
#define STATEMACHINE_INITIALIZE_DEVICE_H_

#include <iostream>
#include "device_state.h"
#include "device.h"
#include "input.h"

class InitializeDevice : public DeviceState {
 public:
  static InitializeDevice state;
  virtual void HandleInput(Device &device, Input input);
  virtual void Update(Device &device);
};

#endif //STATEMACHINE_INITIALIZE_DEVICE_H_
