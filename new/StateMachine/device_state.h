#ifndef STATEMACHINE_DEVICE_STATE_H_
#define STATEMACHINE_DEVICE_STATE_H_

#include "device.h"
#include "input.h"

class Device;

class DeviceState {
 public:
  virtual void HandleInput(Device &device, Input input);
  virtual void Update(Device &device);
};

#endif //STATEMACHINE_DEVICE_STATE_H_
