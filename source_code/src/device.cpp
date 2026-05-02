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

