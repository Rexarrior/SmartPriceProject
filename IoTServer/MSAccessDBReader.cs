using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.Odbc;
using Microsoft.SqlServer;
using System.IO;

namespace IoTServer
{
    public class MSAccessDBReader
    {
        public int GetPrice(string dbFilepath, int deviceID)
        {
            if (!File.Exists(dbFilepath))
            {
                throw new Exception(dbFilepath + " not found");
            }

            string connetionString = null;
            connetionString = @"Driver={Microsoft Access Driver 
                                (*.mdb, *.accdb)};DBQ=" + dbFilepath;
            OdbcConnection odbcConnection = new OdbcConnection(connetionString);

            try
            {
                odbcConnection.Open();

                string[] restrictions = new string[4];
                restrictions[2] = "Products";

                DataTable schema = odbcConnection.GetSchema("Tables");

                int foundPrice = -1;

                foreach (DataRow row in schema.Rows)
                {
                    if (Convert.ToInt32(row["device_id"].ToString(), 10) == deviceID)
                    {
                        if (foundPrice == -1)
                        {
                            foundPrice = Convert.ToInt32(row["device_id"].ToString(), 10);
                        }
                        else
                        {
                            foundPrice = -1;
                            break;
                        }
                    }
                }
                    
                odbcConnection.Close();

                return foundPrice;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return -1;
            }
        }
    }
}
