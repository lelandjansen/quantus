#ifndef STATEMACHINE_STANDBY_H_
#define STATEMACHINE_STANDBY_H_

#include <iostream>
#include "device_state.h"
#include "device.h"
#include "input.h"

class Standby : public DeviceState {
 public:
  static Standby state;
  virtual void HandleInput(Device &device, Input input);
  virtual void Update(Device &device);
};

#endif //STATEMACHINE_STANDBY_H_
