#include "pch.h"

#include "StaticAnalyzeCppWrap.h"

#pragma comment(lib, "boost_filesystem-vc142-mt-x64-1_71.lib")
//#pragma comment(lib, "boost_program_options-vc142-mt-x64-1_71.lib")
#include <boost/program_options.hpp>

StaticAnalyzeCppWrap::StaticAnalyzeCppWrap() :ptr_StaticAnalyzeCppCtrl(new StaticAnalyzeCppCtrl()) {}

StaticAnalyzeCppWrap::~StaticAnalyzeCppWrap() {
    delete ptr_StaticAnalyzeCppCtrl;
}

bool StaticAnalyzeCppWrap::WRAP_PerformStaticAnalyzeInstance(std::string fname) {
    char* arr[] = { "abc","abc2" };
    ptr_StaticAnalyzeCppCtrl->PerformStaticAnalyzeInstance(1, arr);
    return true;
}
