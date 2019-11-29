using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DynamicAnalyzeCtrl {
    public class ToolResParse_ImageLoad : IToolResParse {
        public ToolResParse_ImageLoad(string _ResFname) {
            ResFname = _ResFname;
        }
        public string ResFname { get; set; }
        public bool ParseRes() {
            int thrcnt = File.ReadLines(ResFname).Count() / 2;
            if (thrcnt > 5) {
                return true;
            } else {
                return false;
            }
        }
        public ResContainer ParseResVerbose() {
            return null;
        }
    }
}
