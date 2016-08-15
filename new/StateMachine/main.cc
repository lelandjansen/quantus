#include <iostream>
#include "device.h"
#include "input.h"
#include "initialize_device.h"
#include "standby.h"

int main() {
  Device device;
  Input input;
  input.button_pressed_ = false;
  input.sd_card_inserted_ = true;

  std::cout << "\nSet state\n" << std::endl;
  device.SetState(&InitializeDevice::state);

  std::cout << "\nUpdate\n" << std::endl;
  device.Update();

  std::cout << "\nUpdate\n" << std::endl;

  device.Update();
  device.Update();
  device.Update();

  std::cout << "\nHandle Input\n" << std::endl;
  input.button_pressed_ = true;
  device.HandleInput(input);
  input.button_pressed_ = false;

  std::cout << "\nUpdate\n" << std::endl;
  device.Update();
  device.Update();
  device.Update();
  device.Update();
  device.Update();

  std::cout << "\nHandle Input\n" << std::endl;
  input.sd_card_inserted_ = false;
  device.HandleInput(input);

  std::cout << "\nUpdate\n" << std::endl;
  device.Update();
  device.Update();
  device.Update();
  device.Update();
  device.Update();

  std::cout << "\nHandle Input\n" << std::endl;
  input.sd_card_inserted_ = true;
  device.HandleInput(input);

  std::cout << "\nUpdate\n" << std::endl;
  device.Update();
  device.Update();
  device.Update();
  device.Update();
  device.Update();

  return 0;
}