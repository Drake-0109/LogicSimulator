#ifndef OPIN_H
#define OPIN_H
#include "device.h"

class oPin : public Device {
public:
    oPin() = default;
    bool getOutput() const override;
};

#endif // OPIN_H