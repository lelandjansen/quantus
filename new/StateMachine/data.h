#ifndef STATEMACHINE_DATA_H_
#define STATEMACHINE_DATA_H_

#include <iostream>
#include "device_state.h"
#include "device.h"
#include "input.h"

class Data : public DeviceState {
 public:
  static Data state;
  virtual void HandleInput(Device &device, Input input);
  virtual void Update(Device &device);
};

#endif //STATEMACHINE_DATA_H_
