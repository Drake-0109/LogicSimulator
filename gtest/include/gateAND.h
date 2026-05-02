#ifndef GATEAND_H
#define GATEAND_H

#include "device.h"

class gateAND : public Device {
public:
    gateAND() = default;
    bool getOutput() const override;
};

#endif // GATEAND_H