#pragma once

#include "../Manalyze/main.h"

#define SUCCESS             0
#define USAGE_ERROR         1
#define BUFFER_SIZE         4096

class StaticAnalyzeCppCtrl {

public:
    StaticAnalyzeCppCtrl();
    ~StaticAnalyzeCppCtrl();

    bool PerformStaticAnalyzeInstance(int argc, char** argv);
};

