using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace Tools
{
    class ProjectChange
    {
    }

    public class Xdocument
    {
        static String Path = Program.model_Dir, ImportLibrary = "", ProgramDatabaseFile = "";
        // vcxproj文件重命名，相当于备份
        public static bool Rename_Vcxproj(String project_Name, String project_Path, String project_Direc)
        {
            try
            {
                FileInfo finfo = new FileInfo(project_Path);
                if(! FileCheck.FileExisted(project_Direc + project_Name + "_01.vcxproj"))
                {
                    finfo.MoveTo(project_Direc + project_Name + "_01.vcxproj");
                }
                return true;
            }catch(Exception ex)
            {
                return false;
                throw ex;
            }
        }

        public static void ParseXml_Vcxproj(String project_Name, String project_Path, String project_Direc)
        {
            // <ProjectGuid> <ItemGroup>下的<CICompile>
            if(FileCheck.FileExisted(project_Path))
            {
                FileStream myFs = new FileStream(project_Path, FileMode.Create);
                myFs.Close();
                // 将model中的内容复制到新文件中
                String model_Path = Path + "model.vcxproj";
                XmlDocument new_Xml = new XmlDocument();
                new_Xml.Load(model_Path);
                XmlDocument project_Xml = new XmlDocument();
                project_Xml.Load(project_Direc + project_Name + "_01.vcxproj");//导入原来的项目的xml文件
                XmlElement project_Xelement_ProjectGuid = (XmlElement)project_Xml.GetElementsByTagName("ProjectGuid").Item(0);
                new_Xml.GetElementsByTagName("ProjectGuid").Item(0).InnerText = project_Xelement_ProjectGuid.InnerText;
                // Debug <NMakeOutput>
                XmlNodeList node = new_Xml.GetElementsByTagName("PropertyGroup");
                XmlNode node1 = node.Item(4);
                foreach (XmlNode item in node1)
                {
                    if(item.Name == "NMakeOutput")
                    {
                        item.InnerText = "$(ProjectDir)" + project_Name + "-Debug.vgdbsettings";
                    }
                }
                // Release <NMakeOutput>
                XmlNode node2 = node.Item(5);
                foreach (XmlNode item in node2)
                {
                    if (item.Name == "NMakeOutput")
                    {
                        item.InnerText = "$(ProjectDir)" + project_Name + "-Release.vgdbsettings";
                    }
                }
                // <ItemGroup>
                XmlNode ss = null;
                XmlNodeList project_ItemGroup_node = project_Xml.GetElementsByTagName("Project").Item(0).ChildNodes;
                foreach (XmlNode list in project_ItemGroup_node)
                {
                    if(list.Name == "ItemGroup")
                    {
                        if(list.ChildNodes.Count > 0)
                        {
                            if(list.ChildNodes.Item(0).Name == "CICompile")
                            {
                                ss = list;
                            }                          
                        }
                    }
                }
                XmlNodeList ItemGroup_node = new_Xml.GetElementsByTagName("ItemGroup");
                foreach(XmlNode list in ItemGroup_node)
                {
                    if(0 == list.ChildNodes.Count)
                    {
                        list.InnerXml = ss.InnerXml;
                    }
                }
                XmlTextWriter writer = new XmlTextWriter(project_Path, Encoding.Default);
                writer.Formatting = Formatting.Indented;
                new_Xml.Save(writer);
            }
        }

        public static void Add_Xml_Release_gdbsettings(String project_Name, String project_Path, String project_Direc)
        {
            String new_Path = project_Direc + project_Name + "-Release.vgdbsettings";
            if(FileCheck.FileChecks(new_Path))
            {
                FileStream myFs = new FileStream(new_Path, FileMode.Create);
                myFs.Close();
                String model_Path = Path + "model-Release.vgdbsettings";
                XmlDocument new_Xml = new XmlDocument();
                new_Xml.Load(model_Path);
                // 修改HostName  UserName
                XmlNodeList hostname_Node = new_Xml.GetElementsByTagName("HostName");
                foreach(XmlNode node in hostname_Node)
                {
                    node.InnerText = Program.host_IP;                     
                }
                XmlNodeList username_Node = new_Xml.GetElementsByTagName("UserName");
                foreach(XmlNode node in username_Node)
                {
                    node.InnerText = Program.host_UserName;
                }
                //修改默认工具链
                XmlNodeList toolchain_Node = new_Xml.GetElementsByTagName("Toolchain").Item(0).ChildNodes;
                foreach(XmlNode item in toolchain_Node)
                {
                    if("Name" == item.Name)
                    {
                        item.InnerText = "Default GCC toolchain on" + Program.host_IP;
                    }
                }
                //完善MountInfo中的RemoteDirectory
                XmlNodeList mountinfor_Node = new_Xml.GetElementsByTagName("MountInfo").Item(0).ChildNodes;
                foreach(XmlNode item in mountinfor_Node)
                {
                    if("RemoteDirectory" == item.Name)
                    {
                        item.InnerText = project_Direc.Replace("\\", "/").Replace(Program.bizplane_WindowsShareFolder.Replace("\\", "/"), Program.bizplane_LinuxShareFolder);
                    }
                }
                XmlNode makearg_Node = new_Xml.GetElementsByTagName("AdditionalMakeArguments").Item(0);
                makearg_Node.InnerText = "-j" + Program.thread_Num;
                // 添加环境变量
                XmlNode uservariable_Node = new_Xml.GetElementsByTagName("UserDefinedVariables").Item(0);
                for(int i = 0; i < Program.variable.Length; ++i)
                {
                    string key = Program.variable[i].Split(':')[0];
                    string value = Program.variable[i].Split(':')[1];
                    XmlElement element = new_Xml.CreateElement("BuildVariable");
                    XmlElement element1 = new_Xml.CreateElement("Lable");
                    XmlElement element2 = new_Xml.CreateElement("Description");
                    XmlElement element3 = new_Xml.CreateElement("Value");
                    XmlElement element4 = new_Xml.CreateElement("Name");
                    element4.InnerText = key;
                    XmlElement element5 = new_Xml.CreateElement("PromoteToEnvironment");
                    element5.InnerText = "true";

                    element.AppendChild(element1);
                    element.AppendChild(element2);
                    element.AppendChild(element3);
                    element.AppendChild(element4);
                    element.AppendChild(element5);
                    uservariable_Node.AppendChild(element);
                }
                XmlTextWriter writer = new XmlTextWriter(new_Path, Encoding.Default);
                writer.Formatting = Formatting.Indented;
                new_Xml.Save(writer);
            }
        }

        public static void Add_Xml_Release_mak(String project_Name, String project_Path, String project_Direc)
        {
            try
            {
                String new_Path = project_Direc + "release.mak";
                if(FileCheck.FileChecks(new_Path))
                {
                    FileStream myFs = new FileStream(new_Path, FileMode.Create);
                    myFs.Close();
                    String source_Path = Path + "model_release.mak";
                    String dest_Path = new_Path;
                    File.Copy(source_Path, dest_Path, true); // 覆盖已存在的文件
                    XmlDocument project_Xml = new XmlDocument();
                    // 导入原来项目的xml文件
                    project_Xml.Load(project_Direc + project_Name + "_01.vcxproj");
                    XmlNode root = project_Xml.DocumentElement;
                    XmlNode node_PreprocessorDefinitions = null;
                    XmlNode node_AdditionalIncludeDirectories = null;
                    XmlNode node_AdditionalLibraryDirectories = null;
                    XmlNode node_AdditionalDependencies = null;
                    foreach(XmlNode node in root.ChildNodes)
                    {
                        XmlElement elem = (XmlElement)node;
                        if(node.Name == "ItemDefinitionGroup" && 
                            elem.GetAttribute("Condition") == "'$(Configuration)|$(Platform)'=='Release|Win32'")
                        {
                           // node_PreprocessorDefinitions = node;
                           foreach(XmlNode compile_Node in node.ChildNodes)
                            {
                                if(compile_Node.Name == "CICompile")
                                {
                                    foreach(XmlNode build_Node in compile_Node.ChildNodes)
                                    {
                                        if(build_Node.Name == "PreprocessorDefinitions")
                                        {
                                            node_PreprocessorDefinitions = build_Node;
                                        }
                                        else if(build_Node.Name == "AdditionalIncludeDirectories")
                                        {
                                            node_AdditionalIncludeDirectories = build_Node;
                                        }
                                    }
                                }
                                else if(compile_Node.Name == "Link")
                                {
                                    foreach(XmlNode link_Node in compile_Node.ChildNodes)
                                    {
                                        if(link_Node.Name == "AdditionalLibraryDirectories")
                                        {
                                            node_AdditionalLibraryDirectories = link_Node;
                                        }
                                        else if(link_Node.Name == "AdditionalDependencies")
                                        {
                                            node_AdditionalDependencies = link_Node;
                                        }
                                        else if(link_Node.Name == "ProgramDatabaseFile")
                                        {
                                            if(link_Node.InnerText.EndsWith(@"$(TargetName).pdb"))
                                            {
                                                ProgramDatabaseFile = link_Node.InnerText.Replace(@"/$(TargetName).pdb", "").Trim();
                                            }
                                            else if(link_Node.InnerText.EndsWith(project_Name + ".pdb"))
                                            {
                                                ImportLibrary = link_Node.InnerText.Replace("/" + project_Name + ".pdb", "").Trim();
                                            }
                                        }
                                        else if(link_Node.Name == "ImportLibrary")
                                        {
                                            if(link_Node.InnerText.EndsWith(@"$(TargetName).lib"))
                                            {
                                                ImportLibrary = link_Node.InnerText.Replace(@"/$(TargetName).lib", "").Trim();
                                            }
                                            else if(link_Node.InnerText.EndsWith(project_Name + ".lib"))
                                            {
                                                ImportLibrary = link_Node.InnerText.Replace("/" + project_Name + ".lib", "").Trim();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        String new_PreprocessorDefinitions = "";
                        string key = "", value = "";
                        if(node_PreprocessorDefinitions != null)
                        {
                            string[] old_PreprocessorDefinitions = node_PreprocessorDefinitions.InnerText.Replace("%(PreprocessorDefinitions)", "").Trim().Split(';');// 预定义宏
                            for(int i = 0; i < old_PreprocessorDefinitions.Length - 1; ++i)
                            {
                                key = old_PreprocessorDefinitions[i];
                                if(Dictionary.PredefineDiscard.Contains(key))
                                {
                                    continue; // 如果存在，就消除掉
                                }
                                else
                                {
                                    if(Dictionary.preprocessorDefinitions_Dic.ContainsKey(key))
                                    {
                                        value = Dictionary.preprocessorDefinitions_Dic[key];
                                    }
                                    else
                                    {
                                        value = key;
                                    }
                                }
                                new_PreprocessorDefinitions += value + " ";
                            }
                        }

                        String AdditionalIncludeDirectories = "";
                        if(node_AdditionalIncludeDirectories != null)
                        {
                            AdditionalIncludeDirectories = node_AdditionalIncludeDirectories.InnerText.Replace("%(AdditionalIncludeDirectories)", "").Replace(";", " ");
                        }

                        String AdditionalLibraryDirectories = "";
                        if(node_AdditionalLibraryDirectories != null)
                        {
                            AdditionalLibraryDirectories = node_AdditionalLibraryDirectories.InnerText.Replace("%(AdditionalLibraryDirectories)", "").Replace(";", " ");
                        }

                        String new_AdditionalDependencies = "";
                        if(node_AdditionalDependencies != null)
                        {
                            String[] old_AdditionalDependencies = node_AdditionalDependencies.InnerText.Replace("%(AdditionalDependencies)", "").Trim().Split(';');
                            for(int i = 0; i < old_AdditionalDependencies.Length - 1; ++i)
                            {
                                key = old_AdditionalDependencies[i].Substring(0, old_AdditionalDependencies[i].Length - 4);
                                if(Dictionary.additionalDependencies_Dic.ContainsKey(key))
                                {
                                    value = Dictionary.additionalDependencies_Dic[key];
                                }
                                else
                                {
                                    value = key;
                                }
                                new_AdditionalDependencies += value + " ";
                            }
                        }

                        String[] lines = File.ReadAllLines(dest_Path);
                        lines[14] = "PREPROCESSOR_MACROS := " + new_PreprocessorDefinitions + "EMF_LINUX_EMF_LINUXACE_HAS_EXCEPTIONS";
                        lines[15] = "INCLUDE_DIRS :=" + AdditionalIncludeDirectories;
                        lines[16] = "LIBRARY_DIRS :=" + AdditionalLibraryDirectories;
                        lines[17] = "LIBRARY_NAMES := " + new_AdditionalDependencies + "cdl";
                        String str = String.Join("\r\n", lines);
                        File.WriteAllText(new_Path, str);
                    }
                }              
            }catch(Exception ex)
            {
                throw ex;
            }
        }

        public static void Add_Xml_Makefile(String project_Name, String project_Path, String project_Direc)
        {
            String new_Path = project_Direc + "Makefile";
            if(FileCheck.FileChecks(new_Path))
            {
                FileStream myFs = new FileStream(new_Path, FileMode.Create);
                myFs.Close();
                String source_Path = Path + "Makefile";
                String dest_Path = new_Path;
                File.Copy(source_Path, dest_Path, true);

                String[] lines = File.ReadAllLines(new_Path);
                lines[7] = "TARGETNAME := lib" + project_Name + ".so";
                lines[10] = "ImportLibrary := " + ImportLibrary;
                lines[11] = "ProgramDatabaseFile := " + ProgramDatabaseFile;
                String str = String.Join("\r\n", lines);
                File.WriteAllText(new_Path, str);
            }
        }

    }
}
