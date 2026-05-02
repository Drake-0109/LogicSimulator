#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "../include/logicSimulator.h"

TEST(Simulation__Test, lcfNotLoaded) {
    LogicSimulator* LS = new LogicSimulator();

    std::string filePath = "../../Testing.lcf";
    EXPECT_FALSE(LS->checkIfCircuitLoaded());
    LS->loading_lcfFile(filePath.c_str());
    EXPECT_TRUE(LS->checkIfCircuitLoaded());

    LS->freeSpace();
    delete LS;
}

TEST(Simulation__Test, simulation) {
    LogicSimulator* LS = new LogicSimulator();
    std::string filePath = "../../Testing.lcf";

    LS->loading_lcfFile(filePath.c_str());
    
    LS->inputPinValues = {0, 0, 0};
    LS->setCircuitInputPinValues();
    EXPECT_FALSE(LS->simulating()[0]);

    LS->inputPinValues = {0, 0, 1};
    LS->setCircuitInputPinValues();
    EXPECT_FALSE(LS->simulating()[0]);

    LS->inputPinValues = {0, 1, 0};
    LS->setCircuitInputPinValues();
    EXPECT_FALSE(LS->simulating()[0]);

    LS->inputPinValues = {0, 1, 1};
    LS->setCircuitInputPinValues();
    EXPECT_FALSE(LS->simulating()[0]);

    LS->inputPinValues = {1, 0, 0};
    LS->setCircuitInputPinValues();
    EXPECT_TRUE(LS->simulating()[0]);

    LS->inputPinValues = {1, 0, 1};
    LS->setCircuitInputPinValues();
    EXPECT_TRUE(LS->simulating()[0]);

    LS->inputPinValues = {1, 1, 0};
    LS->setCircuitInputPinValues();
    EXPECT_FALSE(LS->simulating()[0]);

    LS->inputPinValues = {1, 1, 1};
    LS->setCircuitInputPinValues();
    EXPECT_FALSE(LS->simulating()[0]);

    LS->freeSpace();
    delete LS;
}

TEST(Simulation__Test, truthTable) {
    LogicSimulator* LS = new LogicSimulator();
    std::string filePath = "../../Testing.lcf";

    LS->loading_lcfFile(filePath.c_str());
    std::vector<std::vector<bool>> expectedTruthTable = {
        {false},
        {false},
        {false},
        {false},
        {true},
        {true},
        {false},
        {false}
    };
    EXPECT_TRUE(LS->getTruthTable() == expectedTruthTable);

    LS->freeSpace();
    delete LS;
}