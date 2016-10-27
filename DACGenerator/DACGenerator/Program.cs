using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DACGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            Random rnd = new Random();
            int n = 1000;
            using (StreamWriter sw = new StreamWriter(new FileStream("graphData.txt", FileMode.Create)))
            {
                sw.WriteLine(n);
                for (int i = 0; i < n; i++)
                {
                    sw.Write($"{rnd.Next(1,100)}");
                    if (rnd.NextDouble() > 0.95 && i!=n-1)
                    {
                        sw.Write($" {rnd.Next(i + 1, n)}");
                    }
                    if (rnd.NextDouble() > 0.95 && i != n - 1)
                    {
                        sw.Write($" {rnd.Next(i + 1, n)}");
                    }
                    sw.WriteLine();
                }
            }
        }
    }
}
