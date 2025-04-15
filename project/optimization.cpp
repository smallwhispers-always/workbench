#include "optimization.h"
#include "readRMresultfile.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "OptimizeParameters.h"
using namespace std;

// 复制文件
void copyFile(const std::string& src, const std::string& dst) 
{
    std::ifstream srcFile(src, std::ios::binary);
    std::ofstream dstFile(dst, std::ios::binary);
    dstFile << srcFile.rdbuf();
    srcFile.close();
    dstFile.close();
}

//判断复制出来的文件是否内容相同
bool areFilesEqual(const std::string& file1, const std::string& file2) 
{
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);

    if (!f1.is_open() || !f2.is_open()) 
    {
        std::cerr << "错误: 无法打开文件" << std::endl;
        return false;
    }

    // 检查文件大小是否相同
    f1.seekg(0, std::ios::end);
    f2.seekg(0, std::ios::end);
    if (f1.tellg() != f2.tellg()) 
    {
        return false; // 文件大小不同直接返回不等
    }
    f1.seekg(0, std::ios::beg);
    f2.seekg(0, std::ios::beg);

    // 逐字节比较
    char c1, c2;
    while (f1.get(c1) && f2.get(c2)) 
    {
        if (c1 != c2) 
        {
            return false;
        }
    }
    return true;
}


// 运行FEBio命令
bool reRunFEBio(const std::string& updatedrestartfile, const std::string& dmpfilenameinFeb)
{
    // 构建命令字符串，添加引号以处理路径中可能的空格
    std::string command = "febio3 -r " + updatedrestartfile + " -dump " + dmpfilenameinFeb;
    //std::string command = "febio3 -i " + febinputfile + " -dump";
    // 执行命令
    int result = system(command.c_str());

    // 检查命令是否成功执行
    if (result != 0) 
    {
        std::cerr << "FEBio命令执行失败: " << command << std::endl;
        return false;
    }
    return true;
}

// 优化主算法
void optimizationMain(int inclcstep, 
                      const std::string& dmpfilenameinfeb,
                      const std::string& newdmpfilename, 
                      const std::string& updatedrestartfile)
{ 
        //复制dmp文件
        copyFile(dmpfilenameinfeb, newdmpfilename);

        // 运行febio命令
        reRunFEBio(updatedrestartfile, dmpfilenameinfeb);

        //// 调用readRMresultfile函数
        //std::vector<double> moments = readRMresultfile(resultfilename);
        //// 获取各个力矩值
        //double RCMx1 = moments[0];
        //double RCMy1 = moments[1];
        //double RCMz1 = moments[2];
        //double RCMz2 = moments[3];
        //double RCMy3 = moments[4];
        //double RCMz3 = moments[5];
        //cout << RCMx1 << endl;
        //cout << RCMy1 << endl;
        //cout << RCMz1 << endl;
        //cout << RCMz2 << endl;
        //cout << RCMy3 << endl;
        //cout << RCMz3 << endl;
}

