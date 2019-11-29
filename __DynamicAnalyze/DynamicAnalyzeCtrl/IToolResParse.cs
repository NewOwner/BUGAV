using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DynamicAnalyzeCtrl {
    public interface IToolResParse {
        string ResFname { get; set; }
        bool ParseRes();
        ResContainer ParseResVerbose();
    }

    public class ResContainer {
        public ResContainer() {
            isSuspicious = false;
            isMalware = false;
            suspiciousAttr = new List<string>();
            malwareAttr = new List<string>();
        }
        public bool isSuspicious { get; set; }
        public bool isMalware { get; set; }
        public List<string> suspiciousAttr { get; set; }
        public List<string> malwareAttr { get; set; }
    }
}
