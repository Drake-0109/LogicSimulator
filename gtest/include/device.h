#ifndef DEVICE_H
#define DEVICE_H
#include <vector>

class Device {
protected:
    std::vector<Device*> inputPins;
    bool isOutputPin = true;
public:
    virtual bool getOutput() const = 0;
    virtual void addInputPin(Device* input);
    virtual void setInput(bool value) {};
    void setNotOutputPin();
    bool getIsOutputPin() const;
    void freeAllinput();  //for testing
    virtual ~Device() = default;
};

#endif // DEVICE_H