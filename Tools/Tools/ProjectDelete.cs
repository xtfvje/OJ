using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tools
{
    public class ProjectDelete
    {
        public static bool EachProjectDelete(Vcxproj_Item vcxproj)
        {
            try
            {
                FileDelete(vcxproj.vcxproj_Path);
                string _01vcxproj = vcxproj.vcxproj_Dir + vcxproj.vcxproj_Name + "_01.vcxproj";
                if(File.Exists(_01vcxproj))
                {
                    FileInfo finfo = new FileInfo(_01vcxproj);
                    finfo.MoveTo(vcxproj.vcxproj_Path);
                }
                string vgdbsettings = vcxproj.vcxproj_Dir + vcxproj.vcxproj_Name + "-Release.vgdbsettings";
                FileDelete(vgdbsettings);
                string mak = vcxproj.vcxproj_Dir + "release.mak";
                FileDelete(mak);
                string Makefile = vcxproj.vcxproj_Dir + "Makefile";
                FileDelete(Makefile);
                string Makefileold = vcxproj.vcxproj_Dir + "Makefile.old";
                FileDelete(Makefileold);
                string Release = vcxproj.vcxproj_Dir + "Release";
                if(Directory.Exists(Release))
                {
                    Directory.Delete(Release, true);
                }
                string VisualGDBCache = vcxproj.vcxproj_Dir + "VisualGDBCache";
                if(Directory.Exists(VisualGDBCache))
                {  // 如果子文件属性为只读，报错
                    Directory.Delete(VisualGDBCache, true);
                }
                return true;
            }catch(Exception ex)
            {
                Console.WriteLine(ex);
                return false;
                throw ex;
            }
        }

        public static bool FileDelete(string path)
        {
            if(File.Exists(path))
            {
                File.Delete(path);
                return true;
            }
            return false;
        }
    }
}
