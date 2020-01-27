using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DynamicAnalyzeCtrl {
    public class ToolResParse_ConsoleMon : IToolResParse {
        public ToolResParse_ConsoleMon(string _ResFname) {
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
                try {
                    float rate = float.Parse(line);
                    Console.WriteLine("#####################RATE " + rate.ToString());
                    if (rate == 1) { break; }
                    if (rate > 0.2) {
                        resCont.isMalware = true;
                        resCont.suspiciousAttr.Add(line);
                        break;
                    }
                    if (rate > 0.1) {
                        resCont.isSuspicious = true;
                        resCont.suspiciousAttr.Add(line);
                        break;
                    }
                } catch (Exception e) {
                    Console.WriteLine("Exception caught.");
                }
            }
            return resCont;
        }


    }


}
