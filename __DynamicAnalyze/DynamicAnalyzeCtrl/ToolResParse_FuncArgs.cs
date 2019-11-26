using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DynamicAnalyzeCtrl {
    public class ToolResParse_FuncArgs : IToolResParse {
        public ToolResParse_FuncArgs(string _ResFname) {
            ResFname = _ResFname;
        }
        public string ResFname { get; set; }
        public bool ParseRes() {
            string ftext = File.ReadAllText(ResFname);
            foreach (string line in File.ReadLines(@"inp_tool_funcargs.txt")) {
                if (ftext.Contains(line)) {
                    Console.WriteLine(line);
                } else {
                    return false;
                }
            }
            return false;
        }
    }
}
