#include "../include/oPin.h"

bool oPin::getOutput() const {
    if (inputPins.empty()) return false;
    return inputPins[0]->getOutput();
}