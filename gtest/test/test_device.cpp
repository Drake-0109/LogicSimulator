#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "../include/device.h"
#include "../include/gateAND.h"
#include "../include/gateOR.h"
#include "../include/gateNOT.h"
#include "../include/iPin.h"
#include "../include/oPin.h"

TEST(device, iPin_test) {
    Device *device = new iPin();

    EXPECT_FALSE(device->getOutput());
    device->setInput(true);
    EXPECT_TRUE(device->getOutput());
    device->setInput(false);
    EXPECT_FALSE(device->getOutput());
    delete device;
}

TEST(device, AND_test) {
    Device *device = new gateAND();

    device->addInputPin(new iPin(true));
    EXPECT_TRUE(device->getOutput());
    device->addInputPin(new iPin(true));
    EXPECT_TRUE(device->getOutput());
    device->addInputPin(new iPin(false));
    EXPECT_FALSE(device->getOutput());

    device->freeAllinput();
    delete device;
}

TEST(device, OR_test) {
    Device *device = new gateOR();

    device->addInputPin(new iPin(false));
    EXPECT_FALSE(device->getOutput());
    device->addInputPin(new iPin(false));
    EXPECT_FALSE(device->getOutput() );
    device->addInputPin(new iPin(true));
    EXPECT_TRUE(device->getOutput());

    device->freeAllinput();
    delete device;
}

TEST(device, NOT_test) {
    Device *device = new gateNOT();
    Device *inputPin = new iPin(false);

    device->addInputPin(inputPin);

    EXPECT_TRUE(device->getOutput());
    inputPin->setInput(true);
    EXPECT_FALSE(device->getOutput());
    delete device;
    delete inputPin;
}