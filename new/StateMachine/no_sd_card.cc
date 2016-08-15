#include "no_sd_card.h"
#include "sd_card_setup.h"

NoSdCard NoSdCard::state;

void NoSdCard::HandleInput(Device &device, Input input) {
  std::cout << "NoSdCard::HandleInput" << std::endl;
  if (input.sd_card_inserted_) device.SetState(&SdCardSetup::state);
}

void NoSdCard::Update(Device &device) {
  std::cout << "NoSdCard::Update" << std::endl;

  // do stuff while there is no card
}
