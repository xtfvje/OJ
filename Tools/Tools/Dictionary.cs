using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tools
{
    public class Dictionary
    {
        public static String[] PredefineDiscard = {"WIN32", "_WIN32", "_WINDOWS",
            "WINDWOS", "_USRDLL", "XALAN_USE_NATIVE_WCHAR_T"};
        public static Dictionary<string, string> preprocessorDefinitions_Dic = new Dictionary<string, string>
        {
            {"EMF_WIN32", "EMF_LINUX" },
            {"EMF_WIN2000", "EMF_LINUX" },
            {"__alpha_win", "__alpha" },
            {"IMAP_DBTYPE_ORACLE_win", "IMAP_DBTYPE_SYBASE" },
            {"IMAP_DBTYPE_SYBASE_win", "IMAP_DBTYPE_SYBASE" }
        };

        public static Dictionary<string, string> additionalDependencies_Dic = new Dictionary<string, string>
        {
            {"libipsi_crypto", "crypto" },
            {"boost_python-vc100-mt-1_47", "boost_python-gcc41-mt-1_47" },
            {"boost_regex-vc100-mt-1_47", "boost_regex-gcc41-mt-1_47" },
            {"zdll", "zlib" }, {"python27", "python2.7" },{"tcl85t","tcl8.5" },
            {"tcl84","tcl8.4" }, {"msvcrt","msvcprt" }, {"ws2_32","" },
            {"$(NOINHERIT)","" }, {"XalanMessages_1_10","" }, {"snaccCpp","asn1c++" },
            {"snacccpp","asn1c++" }, {"ace","ACE" },{"msq63-m", "dbt63-m" },
            {"xerces-c_2","xerces-c" }, {"Xalan-C_1","xalan-c" },
            {"xalan-c_1","xalan-c" }, {"cppunit_dll","" }, {"libeay_oss32","crypto" },
            {"odbc32","" }, {"ssleay_oss32","ssl" }, {"odbccp32","" },
            {"FrameUtil","" }, {"libIPSI_ACE_SSL","IPSI_ACE_SSL" },
            {"libcurl_imp", "curl" }
        };

        public string PredefineAdd = "EMF_LINUX;ACE_HAS_EXCEPTIONS";
        public string LibAdd = "c;dl";
    }
}
