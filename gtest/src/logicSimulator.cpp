#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>

#include "../include/logicSimulator.h"
#include "../include/device.h"
#include "../include/gateAND.h"
#include "../include/gateOR.h"
#include "../include/gateNOT.h"
#include "../include/iPin.h"
#include "../include/oPin.h"

enum class GateType {
    AND = 1,
    OR = 2,
    NOT = 3
};


bool LogicSimulator::hasLcfExtension(const std::string& fileName) {
    if (fileName.length() >= 4) {
        return (0 == fileName.compare(fileName.length() - 4, 4, ".lcf"));
    }
    return false;
}

void LogicSimulator::findOutputPin(int gateNum, const std::vector<Device*>& gates) {
    int outputPinCount = 0;
    Device *device;
    std::vector<Device*> outputPins;

    for (int i = 0; i < gateNum; i++) {
        if (gates[i]->getIsOutputPin()) {
            device = new oPin();
            device->addInputPin(gates[i]);
            outputPins.push_back(device);
        }
    }
    outputPinsInCircuit = outputPins;
    return;
}

void LogicSimulator::defineInputPinsOfCircuit(int gateNum,std::vector<std::vector<int>>& allGateInputsIndex, std::vector<Device*> gates) {
    for (int i = 0; i < gateNum; i++) {
        for(int j = 0; j < allGateInputsIndex[i].size(); j++) {
            int pinIndex = allGateInputsIndex[i][j];
            if (pinIndex > 0) {
                gates[i]->addInputPin(gates[pinIndex - 1]);
                gates[pinIndex - 1]->setNotOutputPin();
            } else {
                gates[i]->addInputPin(inputPinsInCircuit[-pinIndex - 1]);
            }
        }
    }
}

Device* createGate(std::ifstream& in, std::vector<std::vector<int>>& allGateInputsIndex) {
    Device* newDevice;
    std::vector<int> gateInputs;
    std::string input;
    in >> input;
    GateType gateType = static_cast<GateType>(std::stoi(input));

    while(in >> input && input != "0") {
        int pinIndex = std::stoi(input);
        gateInputs.push_back(pinIndex);
    }
    allGateInputsIndex.push_back(gateInputs);
    
    switch (gateType) {
        case GateType::AND:
            newDevice = new gateAND();
            break;
        case GateType::OR:
            newDevice = new gateOR();
            break;
        case GateType::NOT:
            newDevice = new gateNOT();
            break;
        default:
            throw std::runtime_error("Invalid gate type in file.");
            return nullptr;
    }
    return newDevice;
}

std::vector<Device*> LogicSimulator::buildingCircuit(std::ifstream& in) {
    std::vector<Device*> gates;
    std::vector<std::vector<int>> allGateInputsIndex;
    int gateNum;
    in >> inputPinNum >> gateNum;
    inputPinsInCircuit.assign(inputPinNum, nullptr);
    loadedCircuit.assign(gateNum, nullptr);

    for(int i = 0; i < inputPinNum; ++i) {
        inputPinsInCircuit[i] = new iPin(false);
    }
    for(int i = 0; i < gateNum; ++i) {
        gates.push_back(createGate(in, allGateInputsIndex));
    }

    defineInputPinsOfCircuit(gateNum, allGateInputsIndex, gates);
    findOutputPin(gateNum, gates);
    printf("Circuit: %d input pins, %d output pins and %d gates\n\n", inputPinNum, outputPinsInCircuit.size(), gateNum);
    return gates;
}

void LogicSimulator::loading_lcfFile(std::string filePath) {
    std::ifstream in;
    std::ofstream out;

    in.open(filePath);
    if (in.is_open() && hasLcfExtension(filePath)) {
        loadedCircuit = buildingCircuit(in);
    } else {
        printf("File not found or file format error!!\n\n");
    }
    in.close();
    return;
}

void LogicSimulator::load() {
    freeSpace();

    std::string filePath;
    printf("Please key in a file path: ");
    std::cin >> filePath;

    loading_lcfFile(filePath.c_str());
}

// --------------------------------------------------------------------------

bool LogicSimulator::checkIfCircuitLoaded() {
    if (loadedCircuit.empty()) {
        printf("Please load an lcf file, before using this operation.\n\n");
        return false;
    }
    return true;
}

void LogicSimulator::setCircuitInputPinValues() {
    for (int i = 0; i < inputPinNum; i++) {
        inputPinsInCircuit[i]->setInput(inputPinValues[i]);
    }
}

void LogicSimulator::inputPinDefine() {
    inputPinValues.assign(inputPinNum, false);
    int inputValue;

    for (int i = 0; i < inputPinNum; i++) {
        while(true) {
            printf("Please key in the value of input pin %d: ", i+1);
            if (scanf("%d", &inputValue) == 1 && (inputValue == 0 || inputValue == 1)) {
                inputPinValues[i] = inputValue;
                break;
            } else {
                printf("The value of input pin must be 0/1\n");
                while (getchar() != '\n'); // Clear the input buffer
            }
        }
    }
    setCircuitInputPinValues();
}

std::vector<bool> LogicSimulator::simulating() {
    std::vector<bool> results;
    for (int i = 0; i < outputPinsInCircuit.size(); i++) {
        results.push_back(outputPinsInCircuit[i]->getOutput());
    }
    return results;
}

std::vector<bool> LogicSimulator::getSimulationResult() {
    inputPinDefine();
    return simulating();
}

// --------------------------------------------------------------------------

std::vector<std::vector<bool>> LogicSimulator::getTruthTable() {
    std::vector<std::vector<bool>> truthTable;
    inputPinValues.assign(inputPinNum, false);
    int runtimes = 1 << inputPinNum;

    for (int i = 0; i < runtimes; i++) {
        for (int j = 0; j < inputPinNum; j++) {
            bool value = (i >> j) & 1;
            inputPinsInCircuit[inputPinNum-1-j]->setInput(value);
        }
        truthTable.push_back(simulating());
    }
    return truthTable;
}

// --------------------------------------------------------------------------

void LogicSimulator::freeSpace() {

    for (Device* device : inputPinsInCircuit) {
        delete device;
    }
    for (Device* device : loadedCircuit) {
        delete device;
    }
    for (Device* device : outputPinsInCircuit) {
        delete device;
    }
    
    inputPinsInCircuit.clear();
    loadedCircuit.clear();
    outputPinsInCircuit.clear();
    inputPinValues.clear();
}
