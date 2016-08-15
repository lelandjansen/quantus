#include "sd_card_setup.h"
#include "standby.h"

SdCardSetup SdCardSetup::state;

void SdCardSetup::HandleInput(Device &device, Input input) {
  std::cout << "SdCardSetup::HandleInput" << std::endl;
}

void SdCardSetup::Update(Device &device) {
  std::cout << "SdCardSetup::Update" << std::endl;

  // set up sd card

  device.SetState(&Standby::state);
}
