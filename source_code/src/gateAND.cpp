#include "../include/gateAND.h"

bool gateAND::getOutput() const {
    if (inputPins.empty()) return false;
        
    for (Device* dev : inputPins) {
        if (dev->getOutput() == false) return false;
    }
    return true;
}
