#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "../include/textUI.h"

TEST(TextUI__Test, printResult) {
    TextUI* UI = new TextUI();
    LogicSimulator* LS = UI->LS;

    std::vector<bool> result = {true};
    testing::internal::CaptureStdout();
    LS->inputPinValues = {true, false, true}; // Set input pin values for the test
    UI->printResults(result);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput = "i i i | o \n1 2 3 | 1 \n------+--\n1 0 1 | 1 \n\n";
    EXPECT_TRUE(output == expectedOutput);

    LS->freeSpace();
    delete UI;
}

TEST(TextUI__Test, printTruthTable) {
    TextUI* UI = new TextUI();
    LogicSimulator* LS = UI->LS;
    std::vector<std::vector<bool>> truthTable = {
        {false},
        {true}
    };

    testing::internal::CaptureStdout();
    LS->inputPinValues = {false}; // Set input pin values for the test
    UI->printTruthTable(truthTable);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput = "i | o \n1 | 1 \n--+--\n0 | 0 \n1 | 1 \n\n";
    EXPECT_TRUE(output == expectedOutput);

    LS->freeSpace();
    delete UI;
}