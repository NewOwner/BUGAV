using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DynamicAnalyzeCtrl {
    public class ToolResParse_StaticYara : IToolResParse {
        public ToolResParse_StaticYara(string _ResFname) {
            ResFname = _ResFname;
        }
        public string ResFname { get; set; }
        public bool ParseRes() {
            var logFile = File.ReadAllLines(ResFname);
            return false;
        }
    }
}
