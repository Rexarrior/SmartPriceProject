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
            connetionString = @"Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=" + dbFilepath;
            OdbcConnection odbcConnection = new OdbcConnection(connetionString);

            OdbcCommand odbcCommand = new OdbcCommand("select * from Products", odbcConnection);

            try
            {
                odbcConnection.Open();

                OdbcDataReader odbcDataReader = odbcCommand.ExecuteReader();

                int foundPrice = -1;

                if (!odbcDataReader.HasRows)
                {
                    return -1;
                }

                int deviceIDColumn = 0;
                int priceColumn = 0;

                for (int i = 0; i < odbcDataReader.FieldCount; i++)
                {
                    if (odbcDataReader.GetName(i) == "device_id")
                    {
                        deviceIDColumn = i;
                    }

                    if (odbcDataReader.GetName(i) == "price")
                    {
                        priceColumn = i;
                    }
                }

                while(odbcDataReader.Read())
                {
                    if (!odbcDataReader.IsDBNull(deviceIDColumn))
                    {
                        if (odbcDataReader.GetInt32(deviceIDColumn) == deviceID)
                        {
                            if (foundPrice == -1)
                            {
                                foundPrice = odbcDataReader.GetInt32(priceColumn);
                            }
                            else
                            {
                                foundPrice = -1;
                                break;
                            }
                        }
                    }
                }

                odbcDataReader.Close();
                odbcConnection.Close();

                return foundPrice;
            }
            catch (Exception exc)
            {
                Console.WriteLine("GetPrice (DBReader) exception:\r\n" +  exc.Message);
                return -1;
            }
        }
    }
}
