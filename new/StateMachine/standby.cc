#include "standby.h"
#include "data.h"

Standby Standby::state;

void Standby::HandleInput(Device &device, Input input) {
  std::cout << "Standby::HandleInput" << std::endl;
  if (input.button_pressed_) device.SetState(&Data::state);
}

void Standby::Update(Device &device) {
  std::cout << "Standby::Update" << std::endl;

  // do stuff in standby mode
}
