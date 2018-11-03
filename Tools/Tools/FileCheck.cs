using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tools
{
    public class FileCheck
    {
        public static bool FileExisted(String file_Path)
        {
            if(File.Exists(file_Path))
            {
                return true;
            }
            return false;
        }

        public static bool FileChecks(String file_Path)
        {
            try
            {
                if(File.Exists(file_Path))
                {
                    File.Delete(file_Path);
                }
                return true;
            }catch(Exception ex)
            {
                return false;
                throw ex;
            }
        }
    }
}
