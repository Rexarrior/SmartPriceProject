using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IoTServer
{
    public class Test
    {
        public void Huy()
        {
            Console.WriteLine("Huy");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Test tt = new Test();
            tt.Huy();
        }
    }
}
