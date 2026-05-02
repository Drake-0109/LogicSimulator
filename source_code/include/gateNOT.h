#ifndef GATENOT_H
#define GATENOT_H

#include "device.h"

class gateNOT : public Device {
public:
    gateNOT() = default;
    bool getOutput() const override;
};

#endif // "GATE_NOT_H"