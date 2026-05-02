#include "../include/gateOR.h"

bool gateOR::getOutput() const {
    if (inputPins.empty()) return false;

    for (Device* dev : inputPins) {
        if (dev->getOutput() == true) {
            return true;
        }
    }
    return false;
}
