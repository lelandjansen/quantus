#ifndef STATEMACHINE_DEVICE_H_
#define STATEMACHINE_DEVICE_H_

#include <iostream>
#include "device_state.h"
#include "input.h"

class DeviceState;

class Device {
 public:
  virtual void HandleInput(Input input);
  virtual void Update();
  void SetState(DeviceState *state);

 private:
  DeviceState *state_;
};

#endif //STATEMACHINE_DEVICE_H_
