#ifndef GATEOR_H
#define GATEOR_H

#include "device.h"

class gateOR : public Device {
public:
    gateOR() = default;
    bool getOutput() const override;
};

#endif // GATEOR_H