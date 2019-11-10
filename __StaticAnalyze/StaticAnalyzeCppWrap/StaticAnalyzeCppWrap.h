#pragma once

#include "../StaticAnalyzeCppCtrl/StaticAnalyzeCppCtrl.h"
#include <string>

using namespace System;

public ref class StaticAnalyzeCppWrap {
    StaticAnalyzeCppCtrl* ptr_StaticAnalyzeCppCtrl;

public:
    StaticAnalyzeCppWrap();
    ~StaticAnalyzeCppWrap();

    bool WRAP_PerformStaticAnalyzeInstance(std::string fname);
};
