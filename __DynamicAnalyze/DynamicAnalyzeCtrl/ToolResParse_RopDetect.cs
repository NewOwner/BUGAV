using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;


namespace DynamicAnalyzeCtrl {
    public class ToolResParse_RopDetect : IToolResParse {
        public ToolResParse_RopDetect(string _ResFname) {
            ResFname = _ResFname;
        }
        public string ResFname { get; set; }
        public bool ParseRes() {
            string ftext = File.ReadAllText(ResFname);
            if (ftext.Contains("ROP DETECTED")) {
                return true;
            } else {
                return false;
            }
        }
    }
}
