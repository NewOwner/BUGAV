using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DynamicAnalyzeCtrl {
    public class ToolResParse_ApiMon : IToolResParse {
        public ToolResParse_ApiMon(string _ResFname) {
            ResFname = _ResFname;
        }
        public string ResFname { get; set; }
        public bool ParseRes() {
            var logFile = File.ReadAllLines(ResFname);
            return false;
        }
        public ResContainer ParseResVerbose() {
            ResContainer resCont = new ResContainer();
            var logFile = File.ReadAllLines(ResFname);

            foreach (var line in logFile) {
                if (line.Contains("LoadLibraryExW")) {
                    resCont.isSuspicious = true;
                }
                if (line.Contains("WinExec")) {
                    resCont.isSuspicious = true;
                }
                if (line.Contains("ReadProcessMemory")) {
                    resCont.isSuspicious = true;
                }
                if (line.Contains("WriteProcessMemory")) {
                    resCont.isSuspicious = true;
                }
                if (line.Contains("SetWindowsHookExA")) {
                    resCont.isSuspicious = true;
                }
                if (line.Contains("IsDebuggerPresent")) {
                    resCont.isMalware = true;
                }
                if (line.Contains("CreateServiceA")) {
                    resCont.isSuspicious = true;
                }
                if (line.Contains("GetSystemDirectoryW")) {
                    resCont.isSuspicious = true;
                }
                if (line.Contains("GetSystemTime")) {
                    resCont.isSuspicious = true;
                }

            }
            return resCont;
        }
    }
}