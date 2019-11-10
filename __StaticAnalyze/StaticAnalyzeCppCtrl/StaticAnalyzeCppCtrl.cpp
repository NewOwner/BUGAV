#include "pch.h"
#include "StaticAnalyzeCppCtrl.h"

StaticAnalyzeCppCtrl::StaticAnalyzeCppCtrl() {}

StaticAnalyzeCppCtrl::~StaticAnalyzeCppCtrl() {}

bool StaticAnalyzeCppCtrl::PerformStaticAnalyzeInstance(int argc, char** argv) {
    bool res = true;
    PerformAnalyze(argc, argv);
    return res;
}
