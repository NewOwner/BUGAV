using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DynamicAnalyzeCtrl {
    public class ToolResParse_StaticCpp : IToolResParse {
        public ToolResParse_StaticCpp(string _ResFname) {
            ResFname = _ResFname;
        }
        public string ResFname { get; set; }
        public bool ParseRes() {
            //int thrcnt = File.ReadLines(ResFname).Count() / 2;
            return false;
        }
    }
}
