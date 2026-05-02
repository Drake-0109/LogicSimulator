#include <cstdio>
#include <cstdlib>

#include "../include/textUI.h"
#include "../include/logicSimulator.h"

enum class CommandType {
    Loadlcf = 1,
    Simulation = 2,
    DisplayTruthTable = 3,
    Exit = 4
};

void TextUI::Exit() {
    printf("Goodbye, thanks for using LS.\n\n");
    delete LS;
    exit(0);
}

void TextUI::displayMenu() {
    printf("1. Load logic circuit file\n");
    printf("2. Simulation\n");
    printf("3. Display truth table\n");
    printf("4. Exit\n");
    printf("Command: ");
}

void TextUI::printFormat(std::vector<bool> result) {
    for(int i = 0; i < LS->inputPinValues.size(); i++) printf("i ");
    printf("| ");
    for(int i = 0; i < result.size(); i++) printf("o ");
    printf("\n");
    for(int i = 0; i < LS->inputPinValues.size(); i++) printf("%d ", i+1);
    printf("| ");
    for(int i = 0; i < result.size(); i++) printf("%d ", i+1);
    printf("\n");
    for(int i = 0; i < LS->inputPinValues.size(); i++) printf("--");
    printf("+");
    for(int i = 0; i < result.size(); i++) printf("--");
    printf("\n");
}

void TextUI::printResults(std::vector<bool> result) {
    printFormat(result);
    for(int j = 0; j < LS->inputPinValues.size(); j++) printf("%d ", static_cast<int>(LS->inputPinValues[j]));
    printf("| ");
    for(int j = 0; j < result.size(); j++) printf("%d ", static_cast<int>(result[j]));
    printf("\n\n");
}

void TextUI::printTruthTable(std::vector<std::vector<bool>> truthTable) {
    int count = 0;
    int inputCount = LS->inputPinValues.size();

    printFormat(truthTable[0]);
    for (const auto& row : truthTable) {
        for(int j = 0; j < inputCount; j++) {
            printf("%d ", (count >> (inputCount-1-j)) & 1);
        }
        count++;
        printf("| ");
        for(int j = 0; j < row.size(); j++) printf("%d ", static_cast<int>(row[j]));
        printf("\n");
    }
    printf("\n");
}

void TextUI::processCommand(int command) {
    CommandType cmd = static_cast<CommandType>(command);
    switch (cmd){
    case CommandType::Loadlcf:
        LS->load(); break;
        
    case CommandType::Simulation:
        if(!LS->checkIfCircuitLoaded()) break;
        printf("Simulation result: \n");
        printResults(LS->getSimulationResult()); break;

    case CommandType::DisplayTruthTable:
        if(!LS->checkIfCircuitLoaded()) break;
        printf("Truth table: \n");
        printTruthTable(LS->getTruthTable());
        break;

    case CommandType::Exit:
        LS->freeSpace();
        Exit(); break;
    default:
        printf("Invalid command. Please try again.\n");
        break;
    }
}