cmake_minimum_required(VERSION 3.6)
project(StateMachine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cc
        data.cc data.h
        device.cc device.h
        device_state.cc device_state.h
        initialize_device.cc initialize_device.h
        input.h input.cc
        no_sd_card.cc no_sd_card.h
        sd_card_setup.cc sd_card_setup.h
        standby.cc standby.h
        state_machine.cc state_machine.h)

add_executable(StateMachine ${SOURCE_FILES})
