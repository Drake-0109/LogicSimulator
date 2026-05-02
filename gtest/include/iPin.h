#ifndef IPIN_H
#define IPIN_H

#include "device.h"

class iPin : public Device {
private:
    bool input;
public:
    iPin(bool input = false) : input(input) {}
    bool getOutput() const override;
    void setInput(bool value) override;
};

#endif // IPIN_H