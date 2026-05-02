#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "../include/logicSimulator.h"

TEST(loading_lcf__Test, hasLcfExtension) {
    LogicSimulator* LS = new LogicSimulator();
    std::string filePath = "hasNoLcfExtension";

    EXPECT_FALSE(LS->hasLcfExtension(filePath.c_str()));
    filePath = "123";
    EXPECT_FALSE(LS->hasLcfExtension(filePath.c_str()));
    filePath = "filenotfound.lcf";
    EXPECT_TRUE(LS->hasLcfExtension(filePath.c_str()));

    LS->freeSpace();
    delete LS;
}

TEST(loading_lcf__Test, load_lcf) {
    LogicSimulator* LS = new LogicSimulator();
    std::string filePath = "../../Testing.lcf";
    
    LS->loading_lcfFile(filePath.c_str());
    
    LS->freeSpace();
    delete LS;
}