using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tools
{
    public class Sln_Item
    {
        string sln_name { get; set; }
        string sln_Dir { get; set; }
        string sln_Path { get; set; }
        List<Vcxproj_Item> vcxproj_List { get; set; }
    }
}
