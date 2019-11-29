using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using Newtonsoft.Json.Linq;

namespace DynamicAnalyzeCtrl {
    public class ToolResParse_StaticCpp : IToolResParse {
        public ToolResParse_StaticCpp(string _ResFname) {
            ResFname = _ResFname;
        }
        public string ResFname { get; set; }
        public bool ParseRes() {
            var logFile = File.ReadAllLines(ResFname);
            var logList = new List<string>(logFile);
            List<string> logListFiltered = new List<string>();
            foreach (var line in logList) {
                if(line.Contains("Warning:") || line.Contains("Error:") || line == "") {
                    continue;
                } else {
                    logListFiltered.Add(line);
                }
            }

            var result = String.Join("\n", logListFiltered.ToArray());
            Console.WriteLine(result);

            dynamic jToken = JToken.Parse(result);
            //string str_summary = jToken.Summary;
            //string str_hashes = jToken.Hashes;
            //string str_plugins = jToken.Plugins;

            if(result.Contains("\"level\": 2")) {
                return true;
            }

            //var myJObject = JObject.Parse(result);
            //string str_summary = myJObject.SelectToken("Summary").Value<string>();
            //string str_hashes = myJObject.SelectToken("Hashes").Value<string>();
            //string str_plugins = myJObject.SelectToken("Plugins").Value<string>();

            return false;
        }

        public ResContainer ParseResVerbose() {
            return null;
        }
    }
}
