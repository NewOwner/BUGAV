#include "pch.h"

#include "StaticAnalyzeCppWrap.h"

#ifdef _DEBUG
#pragma comment(lib, "boost_filesystem-vc142-mt-gd-x64-1_71.lib")
#else
#pragma comment(lib, "boost_filesystem-vc142-mt-x64-1_71.lib")
#endif
#include <boost/program_options.hpp>

StaticAnalyzeCppWrap::StaticAnalyzeCppWrap() :ptr_StaticAnalyzeCppCtrl(new StaticAnalyzeCppCtrl()) {}

StaticAnalyzeCppWrap::~StaticAnalyzeCppWrap() {
    delete ptr_StaticAnalyzeCppCtrl;
}

bool StaticAnalyzeCppWrap::WRAP_PerformStaticAnalyzeInstance(const char* dir, const char* file) {
    char* arr[2] = { (char*)dir, (char*)file };
    ptr_StaticAnalyzeCppCtrl->PerformStaticAnalyzeInstance(2, arr);
    return true;
}
