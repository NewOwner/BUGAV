using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Diagnostics;

namespace DynamicAnalyzeCtrl {
    public class PinToolManager {
        public static void RunTool(string _toolName, string _targetName) {
            Process pinProcess = new Process();

            try {
                pinProcess.StartInfo.FileName = "pin.exe";

                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                // Parameters
                pinProcess.StartInfo.Arguments = "-t " + _toolName + " -unique_logfile" + " -- " + _targetName;

                // Modify the following to hide / show the window
                pinProcess.StartInfo.CreateNoWindow = true;
                pinProcess.StartInfo.UseShellExecute = true;
                pinProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;

                pinProcess.Start();

            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

        public static void RunTool(string _toolName, int _targetPid) {
            Process pinProcess = new Process();

            try {
                pinProcess.StartInfo.FileName = "pin.exe";

                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                // Parameters
                pinProcess.StartInfo.Arguments = "-t " + _toolName + " -unique_logfile" + " -pid " + _targetPid.ToString();

                // Modify the following to hide / show the window
                pinProcess.StartInfo.CreateNoWindow = true;
                pinProcess.StartInfo.UseShellExecute = true;
                pinProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;

                pinProcess.Start();

            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }
    }
}
