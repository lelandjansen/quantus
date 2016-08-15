#include "initialize_device.h"
#include "standby.h"

InitializeDevice InitializeDevice::state;

void InitializeDevice::HandleInput(Device &device, Input input) {
  std::cout << "InitializeDevice::HandleInput" << std::endl;
}

void InitializeDevice::Update(Device &device) {
  std::cout << "InitializeDevice::HandleInput" << std::endl;

  // do a bunch of work

  device.SetState(&Standby::state);
}
