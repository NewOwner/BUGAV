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
    char* arr[] = { (char*)dir, (char*)file, "--output=json", "--hashes", "--plugins=all" };
    int argc = 5;
    ptr_StaticAnalyzeCppCtrl->PerformStaticAnalyzeInstance(argc, arr);
    return true;
}

//byte[] bytes_dir = Encoding.ASCII.GetBytes(System.Environment.CurrentDirectory + "\\bugav.exe");
                //byte[] bytes_file = Encoding.ASCII.GetBytes(_target);
                //unsafe {
                //    sbyte* sp_dir;
                //    sbyte* sp_file;
                //    fixed (byte* p_dir = bytes_dir) { sp_dir = (sbyte*)p_dir; }
                //    fixed (byte* p_file = bytes_file) { sp_file = (sbyte*)p_file; }
                //    _StaticAnalyzeCppWrapInst.WRAP_PerformStaticAnalyzeInstance(sp_dir, sp_file);
                //}