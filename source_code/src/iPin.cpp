#include "../include/iPin.h"

bool iPin::getOutput() const {
    return input;
}

void iPin::setInput(bool value) {
    input = value;
}