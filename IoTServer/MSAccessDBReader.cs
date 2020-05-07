using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.Odbc;
using Microsoft.SqlServer;


namespace IoTServer
{
    public class MSAccessDBReader : IDBReader
    {
        Access.Application OAcesss = null;
        
        public string ReadRecord(string sqlRequest)
        {


            return "";
        }

        public bool OpenDB(string filepath)
        {
            
        }
    }
}
