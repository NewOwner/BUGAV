using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DynamicAnalyzeCtrl {
    public class ToolResParse_StaticCsharp : IToolResParse {
        public ToolResParse_StaticCsharp(string _ResFname) {
            ResFname = _ResFname;
        }
        public string ResFname { get; set; }
        public bool ParseRes() {
            string text = File.ReadAllText(ResFname);
            if (text.Contains("isn't a .NET")) {
                return false;
            }
            return true;
        }
        public ResContainer ParseResVerbose() {
            return null;
        }
    }
}
