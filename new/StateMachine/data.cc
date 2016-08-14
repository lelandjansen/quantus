#include "data.h"
#include "standby.h"

Data Data::state;

void Data::HandleInput(Device &device, Input input) {
  std::cout << "Data::HandleInput" << std::endl;
  if (input.button_pressed_) device.SetState(&Standby::state);
}

void Data::Update(Device &device) {
  std::cout << "Data::Update" << std::endl;

  // setup

  // countdown
  // abort if countdown interrupted

  int data_points = 0;
  unsigned long time = 0;
  while (/*device.CurrentState() == &Date::state && */ data_points < 5 /* max data */) {
    if (/* it's time to take a measurement */ time < 1) {
      // collect ping measurement
      // collect temperature measurement

      // compute speed of sound in air
      // compute distance

      // log data

      std::cout << "Collect data" << std::endl;

      ++data_points;
    }
  }

  // teardown

  device.SetState(&Standby::state);
}