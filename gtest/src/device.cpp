#include "../include/device.h"

void Device::addInputPin(Device* input) { 
    inputPins.push_back(input);
};

void Device::setNotOutputPin() { 
    isOutputPin = false; 
};

bool Device::getIsOutputPin() const {
    return isOutputPin; 
};

void Device::freeAllinput() {   //for testing
    for (Device* device : inputPins) {
        delete device;
    }
}