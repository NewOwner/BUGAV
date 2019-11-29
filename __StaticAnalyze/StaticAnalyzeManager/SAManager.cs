using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace StaticAnalyzeManager {
    public class SAManager {
        public static void RunToolOutCapture(string _targetPath, string _toolpath, string _argflags, string _fext) {
            Process pinProcess = new Process();
            var sb = new StringBuilder();

            try {
                //pinProcess.StartInfo.FileName = @"..\..\..\__LIBS\Manalyze\bin\manalyze.exe";
                pinProcess.StartInfo.FileName = _toolpath;

                // redirect the output
                pinProcess.StartInfo.RedirectStandardOutput = true;
                pinProcess.StartInfo.RedirectStandardError = true;

                // hookup the eventhandlers to capture the data that is received
                pinProcess.OutputDataReceived += (sender, args) => sb.AppendLine(args.Data);
                pinProcess.ErrorDataReceived += (sender, args) => sb.AppendLine(args.Data);

                //Do not receive an event when the process exits.
                pinProcess.EnableRaisingEvents = false;

                // Parameters
                //pinProcess.StartInfo.Arguments = "--output=json --hashes  --plugins=all " + _targetPath;
                pinProcess.StartInfo.Arguments = _argflags + " " + _targetPath; 

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
                using (System.IO.StreamWriter file = new System.IO.StreamWriter(targetName+ _fext)) {
                    file.WriteLine(sb.ToString()); // "sb" is the StringBuilder
                }
            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

    }
}
