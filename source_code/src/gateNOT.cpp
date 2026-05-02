#include "../include/gateNOT.h"

bool gateNOT::getOutput() const {
    if (inputPins.empty()) return false;
    return !inputPins[0]->getOutput();
}