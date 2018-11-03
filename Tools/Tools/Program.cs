using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tools
{
    class Program
    {
        public static String bizplane_WindowsShareFolder; // Windows共享目录
        public static String bizplane_LinuxShareFolder;  // Linux 共享目录
        public static String host_IP, host_UserName, model_Dir;
        public static int thread_Num;
        public static string[] variable;
        public static List<Vcxproj_Item> vcxproj_Success_Statistics = new List<Vcxproj_Item>();
        public static List<Vcxproj_Item> vcxproj_Failure_Statistics = new List<Vcxproj_Item>();
        static void Main(string[] args)
        {
            if (null == args[0] || "" == args[0])
            {
                Console.WriteLine("请输入正确的操作标识");
                return;
            }
            //  bizplane_WindowsShareFolder = "D:\\ShareTest";
            //  bizplane_LinuxShareFolder = "/root/ShareTest";
            Console.WriteLine(args[0] + "\n" + args[1] + "\n" + args[2] + "\n" + args[3] + "\n" + args[4] + "\n" + args[5]);
            
            int operate_Flag = System.Convert.ToInt16(args[0]);
            // 0表示撤销操作，1表示转换操作
            #region 撤销操作
            if(0 == operate_Flag)
            {
                bool flag = false;
                int model = 0;
                model = System.Convert.ToInt16(args[1]);
                if(0 == model)
                {
                    if(3 == args.Length)
                    {   // 目录必须以/结尾
                        String ini_Dir = args[2].Substring(0, args[2].Length - 15);
                        // 路径必须以buildsprojs.ini结尾
                        string ini_Path = args[2];
                        Console.WriteLine(ini_Path);
                        Console.WriteLine(ini_Dir + "\n" + ini_Path);
                        String[] lines = File.ReadAllLines(ini_Path).Where(p => (!p.Contains("#"))).ToArray();
                        int count = lines.Length;
                        String[] ini_Line = new String[4];
                        #region foreach
                        foreach(String line in lines)
                        {
                            // 原字符串以多个空格隔开,移除空的子字符串
                            ini_Line = line.Split(new String[] { "" }, StringSplitOptions.RemoveEmptyEntries);
                            if(ini_Line[2].EndsWith(".sln"))
                            {
                                List<Vcxproj_Item> vcxproj_List = new List<Vcxproj_Item>();
                                // 规定在目录的最后一个分隔符都需要包含\
                                vcxproj_List = GetVcxprojListInSln(ini_Dir + "\\" + ini_Line[1] +
                                    "\\", ini_Dir + "\\" + ini_Line[1] + "\\" + ini_Line[2]);
                                foreach(var item in vcxproj_List)
                                {
                                    flag = ProjectDelete.EachProjectDelete(item);
                                    if(flag)
                                    {
                                        vcxproj_Success_Statistics.Add(item);
                                    }
                                    else
                                    {
                                        vcxproj_Failure_Statistics.Add(item);
                                    }
                                }
                            }
                            else if(ini_Line[2].EndsWith(".vcxproj"))
                            {
                                Vcxproj_Item vcxproj = new Vcxproj_Item();
                                vcxproj.vcxproj_Name = ini_Line[0];
                                vcxproj.vcxproj_Dir = ini_Dir + "\\" + ini_Line[1] + "\\";
                                vcxproj.vcxproj_Path = ini_Dir + "\\" + ini_Line[1] + "\\" + ini_Line[2];
                                flag = ProjectDelete.EachProjectDelete(vcxproj);
                                if(flag)
                                {
                                    vcxproj_Success_Statistics.Add(vcxproj);
                                }
                                else
                                {
                                    vcxproj_Failure_Statistics.Add(vcxproj);
                                }
                            }
                        }
                        #endregion foreach
                    }
                    else
                    {
                        Console.WriteLine("参数输入有误");
                    }
                }
            }
            #endregion 撤销操作
            else if(1 == operate_Flag)
            {
                bizplane_WindowsShareFolder = args[1];
                bizplane_LinuxShareFolder = args[2];
                host_IP = args[3];
                host_UserName = args[4];
                thread_Num = System.Convert.ToInt16(args[5] ?? "1");
                variable = args[6].Trim().Split(',');
                model_Dir = args[7].Trim();
                // 解析ini文件，遍历行，如果是sln得到vcxproj的集合，然后遍历并进行工程转换
                // 如果是vcxproj则直接进行工程转换
                int model = 0;
                model = System.Convert.ToInt16(args[8]);
                Console.WriteLine(args[0] + args[1] + args[2] + args[3]);
                bool flag = false; // 转换标识
                #region ini model
                if(0 == model)
                {
                    if(10 == args.Length)
                    {   // 目录必须以/结尾
                        String ini_Dir = args[9].Substring(0, args[9].Length - 15);
                        string ini_Path = args[9]; // 路径必须以buildsprojs.ini结尾
                        String[] lines = File.ReadAllLines(ini_Path).Where(p => (!p.Contains("#"))).ToArray();
                        int count = lines.Length;
                        String[] ini_Line = new String[4];
                        foreach (String line in lines)
                        {
                            // 原字符串以多个空格隔开,移除空的子字符串
                            ini_Line = line.Split(new String[] { "" }, StringSplitOptions.RemoveEmptyEntries);
                            if (ini_Line[2].EndsWith(".sln"))
                            {
                                List<Vcxproj_Item> vcxproj_List = new List<Vcxproj_Item>();
                                // 规定在目录的最后一个分隔符都需要包含\
                                vcxproj_List = GetVcxprojListInSln(ini_Dir + "\\" + ini_Line[1] +
                                    "\\", ini_Dir + "\\" + ini_Line[1] + "\\" + ini_Line[2]);
                                foreach (var item in vcxproj_List)
                                {
                                    flag = FullVcxproj(item);
                                    if (flag)
                                    {
                                        vcxproj_Success_Statistics.Add(item);
                                    }
                                    else
                                    {
                                        vcxproj_Failure_Statistics.Add(item);
                                    }
                                }
                            }
                            else if (ini_Line[2].EndsWith(".vcxproj"))
                            {
                                Vcxproj_Item vcxproj = new Vcxproj_Item();
                                vcxproj.vcxproj_Name = ini_Line[0];
                                vcxproj.vcxproj_Dir = ini_Dir + "\\" + ini_Line[1] + "\\";
                                vcxproj.vcxproj_Path = ini_Dir + "\\" + ini_Line[1] + "\\" + ini_Line[2];
                                flag = FullVcxproj(vcxproj);
                                if (flag)
                                {
                                    vcxproj_Success_Statistics.Add(vcxproj);
                                }
                                else
                                {
                                    vcxproj_Failure_Statistics.Add(vcxproj);
                                }
                            }
                        } // end foreach                   
                    }
                    else
                    {
                        Console.WriteLine("22 参数输入有误");
                    }                                       
                }
                #endregion end ini model 
                #region sln model
                if (1 == model)
                {
                    if(11 == args.Length)
                    {
                        String sln_Dir = args[9];
                        String sln_Path = args[10];
                        List<Vcxproj_Item> vcxproj_List = new List<Vcxproj_Item>();
                        vcxproj_List = GetVcxprojListInSln(sln_Dir, sln_Path);
                        foreach(var item in vcxproj_List)
                        {
                            if(flag)
                            {
                                vcxproj_Success_Statistics.Add(item);
                            }
                            else
                            {
                                vcxproj_Failure_Statistics.Add(item);
                            }
                        }
                    }// end of if(11 == args.Length)
                } // end of if (1 == model)
                #endregion sln model
                #region vcxproj model
                if (2 == model)
                {
                    if(12 == args.Length)
                    {
                        String vcxproj_Name = args[9];
                        String vcxproj_Dir = args[10];
                        String vcxproj_Path = args[11];
                        Vcxproj_Item vcxproj = new Vcxproj_Item()
                        {
                            vcxproj_Name = vcxproj_Name,
                            vcxproj_Dir = vcxproj_Dir,
                            vcxproj_Path = vcxproj_Path,
                        };
                        flag = FullVcxproj(vcxproj);
                        if(flag)
                        {
                            vcxproj_Success_Statistics.Add(vcxproj);
                        }
                        else
                        {
                            vcxproj_Failure_Statistics.Add(vcxproj);
                        }
                    }
                    else
                    {
                        Console.WriteLine("33 参数输入错误");
                    }
                }// end of if (2 == model)
                #endregion vcxproj model
            }
            Console.WriteLine("vcxproj{0} 结果: 成功{1}个,失败{2}个", operate_Flag == 1 ? "转换" : "撤销",
                vcxproj_Success_Statistics.Count, vcxproj_Failure_Statistics.Count);
            if(vcxproj_Success_Statistics.Count > 0)
            {
                Console.WriteLine("成功项如下:");
                foreach(var item in vcxproj_Success_Statistics)
                {
                    Console.WriteLine("vcxproj名称{0},路径:{1}", item.vcxproj_Name, item.vcxproj_Path);
                }
                if(vcxproj_Failure_Statistics.Count > 0)
                {
                    Console.WriteLine("失败项如下：");
                    foreach(var item in vcxproj_Failure_Statistics)
                    {
                        Console.WriteLine("vcxproj名称{0},路径:{1}", item.vcxproj_Name, item.vcxproj_Path);
                    }
                }
            }
        }

        static bool FullVcxproj(Vcxproj_Item vcxproj)
        {
            try
            {
                if(Xdocument.Rename_Vcxproj(vcxproj.vcxproj_Name, vcxproj.vcxproj_Path, vcxproj.vcxproj_Dir))
                {
                    Xdocument.ParseXml_Vcxproj(vcxproj.vcxproj_Name, vcxproj.vcxproj_Path, vcxproj.vcxproj_Dir);
                    Xdocument.Add_Xml_Release_gdbsettings(vcxproj.vcxproj_Name, vcxproj.vcxproj_Path, vcxproj.vcxproj_Dir);
                    Xdocument.Add_Xml_Release_mak(vcxproj.vcxproj_Name, vcxproj.vcxproj_Path, vcxproj.vcxproj_Dir);
                    Xdocument.Add_Xml_Makefile(vcxproj.vcxproj_Name, vcxproj.vcxproj_Path, vcxproj.vcxproj_Dir);
                }
                return true;
            }catch(Exception ex)
            {
                return false;
                throw ex;
            }
        }

        static List<Vcxproj_Item> GetVcxprojListInSln(string sln_Dir, string sln_Path) // Dir为绝对目录
        {
            List<Vcxproj_Item> vcxproj_List = new List<Vcxproj_Item>();
            if("" != sln_Path)
            {
                String[] lines = File.ReadAllLines(sln_Path);
                foreach(String line in lines)
                {
                    if(line.Contains("Global"))
                    {
                        break;
                    }
                    if(line.StartsWith(@"Project("))
                    {
                        if(SlnLineParse(line, sln_Dir) != null)
                        {
                            vcxproj_List.Add(SlnLineParse(line, sln_Dir));
                        }
                    }
                }
                if(vcxproj_List.Count > 0)
                {
                    return vcxproj_List;
                }
                return null;
            }
            return null;
        }

        static Vcxproj_Item SlnLineParse(String sln_line, String sln_Dir)
        {
            if(sln_line != "" && null != sln_line)
            {
                Vcxproj_Item vcxproj = new Vcxproj_Item();
                String[] array0 = sln_line.Split(',');
                vcxproj.vcxproj_Name = array0[0].Split('=')[1].Replace(@"""", "").Trim();
                vcxproj.vcxproj_Path = sln_Dir + array0[1].Replace(@"""", "").Replace("/", "\\").Trim();
                vcxproj.vcxproj_Dir = vcxproj.vcxproj_Path.Replace(vcxproj.vcxproj_Name + ".vcxproj", "").Trim();
                return vcxproj;
            }
            return null;
        }

        static String GetPathOfSuffix(String path, String suffix)//返回文件路径并且包含文件名
        {
            DirectoryInfo direc = new DirectoryInfo(path);
            FileInfo file_Name = direc.GetFiles("*." + suffix).FirstOrDefault();
            if(null != file_Name)
            {
                return file_Name.FullName;
            }
            return "";
        }
    }
}
