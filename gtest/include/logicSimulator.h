#include "device.h"
#include <string>
#include <vector>

#ifndef LOGIC_SIMULATOR_H
#define LOGIC_SIMULATOR_H

class LogicSimulator {
public:
    std::vector<bool> inputPinValues;

    void load();
    bool checkIfCircuitLoaded();
    void freeSpace();
    std::vector<bool> getSimulationResult();
    std::vector<std::vector<bool>> getTruthTable();
    
    //for unit test
    void loading_lcfFile(std::string);
    bool hasLcfExtension(const std::string&);
    void setCircuitInputPinValues();
    std::vector<bool> simulating();

protected:
    int inputPinNum = 0;
    std::vector<Device*> inputPinsInCircuit;
    std::vector<Device*> outputPinsInCircuit;
    std::vector<Device*> loadedCircuit;

    void findOutputPin(int, const std::vector<Device*>&);
    void defineInputPinsOfCircuit(int, std::vector<std::vector<int>>&, std::vector<Device*>);
    std::vector<Device*> buildingCircuit(std::ifstream&);
    void inputPinDefine();
};

#endif // LOGIC_SIMULATOR_H