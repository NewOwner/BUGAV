using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace StaticAnalyzeManager {
    public class SAManager {
        public static void RunSAUtil(string _targetName) {
            Process pinProcess = new Process();

            try {
                pinProcess.StartInfo.FileName = "CMD.EXE";

                // hookup the eventhandlers to capture the data that is received
                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                pinProcess.StartInfo.Arguments = "/K F:\\UNIVER\\9_sem\\TISUIB\\2\\STAGED\\static_analysis\\Manalyze\\bin\\manalyze.exe --output=json --hashes  --plugins=all " + _targetName;

                pinProcess.Start();

                pinProcess.WaitForExit();
            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

        public static void RunTool(string _targetPath) {
            Process pinProcess = new Process();

            try {
                pinProcess.StartInfo.FileName = @"..\..\..\__LIBS\Manalyze\bin\manalyze.exe";

                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;
                string targetName = Path.GetFileName(_targetPath);
                //+ " >"+ targetName+".cpp.res.txt"

                // Parameters
                pinProcess.StartInfo.Arguments = "--output=json --hashes  --plugins=all " + _targetPath ;

                // Modify the following to hide / show the window
                pinProcess.StartInfo.CreateNoWindow = true;
                pinProcess.StartInfo.UseShellExecute = true;
                //pinProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;

                pinProcess.Start();
                pinProcess.WaitForExit();

            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }


        public static void RunToolOutCapture(string _targetPath) {
            Process pinProcess = new Process();
            var sb = new StringBuilder();

            try {
                pinProcess.StartInfo.FileName = @"..\..\..\__LIBS\Manalyze\bin\manalyze.exe";

                // redirect the output
                pinProcess.StartInfo.RedirectStandardOutput = true;
                pinProcess.StartInfo.RedirectStandardError = true;

                // hookup the eventhandlers to capture the data that is received
                pinProcess.OutputDataReceived += (sender, args) => sb.AppendLine(args.Data);
                pinProcess.ErrorDataReceived += (sender, args) => sb.AppendLine(args.Data);

                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                // Parameters
                pinProcess.StartInfo.Arguments = "--output=json --hashes  --plugins=all " + _targetPath;

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

                string targetName = Path.GetFileName(_targetPath);
                using (System.IO.StreamWriter file = new System.IO.StreamWriter(targetName+ ".cpp.res.txt")) {
                    file.WriteLine(sb.ToString()); // "sb" is the StringBuilder
                }
            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

    }
}
