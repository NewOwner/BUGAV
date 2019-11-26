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
                pinProcess.StartInfo.FileName = @"..\..\..\__LIBS\pin_dbi\pin.exe";

                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                // Parameters
                pinProcess.StartInfo.Arguments = "-t " + _toolName + " -unique_logfile" + " -- " + _targetName;

                // Modify the following to hide / show the window
                pinProcess.StartInfo.CreateNoWindow = true;
                pinProcess.StartInfo.UseShellExecute = true;
                //pinProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;

                pinProcess.Start();

            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

        public static void RunToolOutCapture(string _toolName, string _targetName) {
            Process pinProcess = new Process();
            var sb = new StringBuilder();

            try {
                pinProcess.StartInfo.FileName = @"..\..\..\__LIBS\pin_dbi\pin.exe";
                
                // redirect the output
                pinProcess.StartInfo.RedirectStandardOutput = true;
                pinProcess.StartInfo.RedirectStandardError = true;

                // hookup the eventhandlers to capture the data that is received
                pinProcess.OutputDataReceived += (sender, args) => sb.AppendLine(args.Data);
                pinProcess.ErrorDataReceived += (sender, args) => sb.AppendLine(args.Data);

                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                // Parameters
                //pinProcess.StartInfo.Arguments = "-t " + _toolName + " -unique_logfile" + " -- " + _targetName;
                pinProcess.StartInfo.Arguments = "-t " + _toolName + " -- " + _targetName;

                // Modify the following to hide / show the window
                pinProcess.StartInfo.CreateNoWindow = true;
                pinProcess.StartInfo.UseShellExecute = false;
                //pinProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;

                pinProcess.Start();

                // start our event pumps
                pinProcess.BeginOutputReadLine();
                pinProcess.BeginErrorReadLine();

                // until we are done
                pinProcess.WaitForExit();
            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

        public static void RunToolCmd(string _toolName, string _targetName) {
            Process pinProcess = new Process();

            try {
                pinProcess.StartInfo.FileName = "CMD.EXE";

                // hookup the eventhandlers to capture the data that is received
                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                pinProcess.StartInfo.Arguments = "/K F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\__LIBS\\pin_dbi\\pin.exe -t " + _toolName + " -- " + _targetName;

                pinProcess.Start();

                pinProcess.WaitForExit();
            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

        

        public static void RunTool(string _toolName, int _targetPid) {
            Process pinProcess = new Process();

            try {
                pinProcess.StartInfo.FileName = "CMD.EXE";

                // hookup the eventhandlers to capture the data that is received
                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                pinProcess.StartInfo.Arguments = "/K F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\__LIBS\\pin_dbi\\pin.exe" + " -pid " + _targetPid.ToString() + " -t " + _toolName;

                pinProcess.Start();

                pinProcess.WaitForExit();
            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }


    }
}
