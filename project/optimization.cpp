#include "optimization.h"
#include "readRMresultfile.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "OptimizeParameters.h"
using namespace std;

//// 复制文件
//void copyFile(const std::string& src, const std::string& dst) 
//{
//    std::ifstream srcFile(src, std::ios::binary);
//    std::ofstream dstFile(dst, std::ios::binary);
//    dstFile << srcFile.rdbuf();
//    srcFile.close();
//    dstFile.close();
//}
//
////判断复制出来的文件是否内容相同
//bool areFilesEqual(const std::string& file1, const std::string& file2) 
//{
//    std::ifstream f1(file1, std::ios::binary);
//    std::ifstream f2(file2, std::ios::binary);
//
//    if (!f1.is_open() || !f2.is_open()) 
//    {
//        std::cerr << "错误: 无法打开文件" << std::endl;
//        return false;
//    }
//
//    // 检查文件大小是否相同
//    f1.seekg(0, std::ios::end);
//    f2.seekg(0, std::ios::end);
//    if (f1.tellg() != f2.tellg()) 
//    {
//        return false; // 文件大小不同直接返回不等
//    }
//    f1.seekg(0, std::ios::beg);
//    f2.seekg(0, std::ios::beg);
//
//    // 逐字节比较
//    char c1, c2;
//    while (f1.get(c1) && f2.get(c2)) 
//    {
//        if (c1 != c2) 
//        {
//            return false;
//        }
//    }
//    return true;
//}
//
//
//// 运行FEBio命令
//void reRunFEBio(const std::string& command) 
//{
//    int result = std::system(command.c_str());
//    if (result != 0) 
//    {
//        std::cerr << "FEBio命令执行失败: " << command << std::endl;
//    }
//}
//
//// 优化主算法
//void optimizationMain(int inclcstep, const std::string& dmpfilenameinfeb,
//                      const std::string& newdmpfilename, const std::string& updatedrestartfile)
//{
//    //for (int increasedsteps = 1; increasedsteps <= inclcstep; ++increasedsteps) 
//    //{
//        //复制dmp文件
//        copyFile(dmpfilenameinfeb, newdmpfilename);
//
//        // 运行febio命令
//        std::string febiocommand = "febio3 -r " + updatedrestartfile + " -dump " + dmpfilenameinfeb;
//        reRunFEBio(febiocommand);
//
//        //// 调用readRMresultfile函数
//        //std::vector<double> moments = readRMresultfile(resultfilename);
//        //// 获取各个力矩值
//        //double RCMx1 = moments[0];
//        //double RCMy1 = moments[1];
//        //double RCMz1 = moments[2];
//        //double RCMz2 = moments[3];
//        //double RCMy3 = moments[4];
//        //double RCMz3 = moments[5];
//        //cout << RCMx1 << endl;
//        //cout << RCMy1 << endl;
//        //cout << RCMz1 << endl;
//        //cout << RCMz2 << endl;
//        //cout << RCMy3 << endl;
//        //cout << RCMz3 << endl;
//    //}
//}

// 复制文件
void copyFile(const std::string& src, const std::string& dst) 
{
    std::ifstream srcFile(src, std::ios::binary);
    std::ofstream dstFile(dst, std::ios::binary);
    dstFile << srcFile.rdbuf();
    srcFile.close();
    dstFile.close();
}

// 运行FEBio命令
void reRunFEBio(const std::string& command) 
{
    int result = std::system(command.c_str());
    if (result != 0) 
    {
        std::cerr << "FEBio命令执行失败: " << command << std::endl;
    }
}

//// 优化主算法
//void optimizationMain(int incLCstep, const std::string& dmpfilenameinFeb, const std::string& newdmpfilename, const std::string& updatedrestartfile) 
//{
//    for (int increasedsteps = 1; increasedsteps <= incLCstep; ++increasedsteps) 
//    {
//        // 复制DMP文件
//        copyFile(dmpfilenameinFeb, newdmpfilename);
//
//        // 运行FEBio命令
//        std::string febioCommand = "febio3 -r " + updatedrestartfile + " -dump " + dmpfilenameinFeb;
//        reRunFEBio(febioCommand);
//    }
//}

// 优化主算法
void optimizationMain(int incLCstep, const std::string& dmpfilenameinFeb, const std::string& newdmpfilename, const std::string& updatedrestartfile)
{
	//for (int increasedsteps = 1; increasedsteps <= incLCstep; ++increasedsteps)
	//{
		// 复制DMP文件
	copyFile(dmpfilenameinFeb, newdmpfilename);
	// 进入工作文件
	//std::string fileCommand = "cd C:\\Users\\Mayn\\Desktop\\ori";
	//int result = std::system(fileCommand.c_str());
	Sleep(10000);
	// 运行FEBio命令
	//std::string febioCommand = "febio3 -r " + updatedrestartfile + " -dump " + dmpfilenameinFeb;
	std::string febioCommand = "febio3 -r C:\\Users\\Mayn\\Desktop\\ori\\restart-1Dmsl_knee_H2_pelSYS_ABrev201.feb -dump C:\\Users\\Mayn\\Desktop\\ori\\restart-hip1D-msl.dmp";
	reRunFEBio(febioCommand);
	//}
}