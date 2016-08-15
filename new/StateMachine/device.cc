#include "device.h"
#include "no_sd_card.h"

void Device::HandleInput(Input input) {
  std::cout << "Device::HandleInput" << std::endl;
  if (!input.sd_card_inserted_) state_ = &NoSdCard::state;
  state_->HandleInput(*this, input);
}

void Device::Update() {
  std::cout << "Device::Update" << std::endl;
  state_->Update(*this);
}

void Device::SetState(DeviceState *state) {
  std::cout << "Device::SetState" << std::endl;
  if (state_) state_ = state;
}
