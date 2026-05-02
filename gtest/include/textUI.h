#include <vector>
#include "../include/logicSimulator.h"

#ifndef TEXTUI_H
#define TEXTUI_H

class TextUI {
public:
    LogicSimulator* LS;
    TextUI() { LS = new LogicSimulator(); };
    void displayMenu();
    void processCommand(int);

    //for unit test
    void printResults(std::vector<bool>);
    void printTruthTable(std::vector<std::vector<bool>>);
    ~TextUI() { delete LS; };

private:
    void Exit();
    void printFormat(std::vector<bool>);
};

#endif // TEXTUI_H