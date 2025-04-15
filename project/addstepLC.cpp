#include "addstepLC.h"
#include "timeloadlaststep.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

void addstepLC(const std::string& oldfilename, const std::string& newfilename,
    const std::string& tempfilename, int firstLCnumber, int lastLCnumber,
    int originaltimestep, double originalstepsize, int timestepincrease)
{
    // 复制并创建临时文件
    std::string copyCmd = "copy " + oldfilename + " " + tempfilename;
    system(copyCmd.c_str());

    // 读取原始文件
    std::ifstream inFile(oldfilename);
    if (!inFile.is_open())
    {
        std::cerr << "无法打开文件: " << oldfilename << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    int numLC5 = 0, numLC6 = 0;

    // 读取文件内容并修改时间步
    while (std::getline(inFile, line))
    {
        // 修改时间步
        if (line.find("<time_steps>") != std::string::npos)
        {
            std::stringstream ss;
            ss << "\t<time_steps>" << (originaltimestep + timestepincrease) << "</time_steps>";
            line = ss.str();
        }

        // 查找负载曲线的行号
        if (line.find("<loadcurve id=\"" + std::to_string(firstLCnumber) + "\">") != std::string::npos)
        {
            numLC5 = lines.size();
        }
        if (line.find("<loadcurve id=\"" + std::to_string(firstLCnumber + 1) + "\">") != std::string::npos)
        {
            numLC6 = lines.size();
        }

        lines.push_back(line);
    }
    inFile.close();

    // 计算每个负载曲线的行数
    int numLC = numLC6 - numLC5 - 2;

    // 写入新文件
    std::ofstream outFile(newfilename);
    if (!outFile.is_open())
    {
        std::cerr << "无法创建文件: " << newfilename << std::endl;
        return;
    }

    // 写入文件头部直到第一个负载曲线
    int i = 0;
    while (i < lines.size() && lines[i].find("<loadcurve id=\"2\">") == std::string::npos)
    {
        i++;
    }

    for (int o = 0; o < i - 1; o++)
    {
        outFile << lines[o] << std::endl;
    }

    // 为每个负载曲线添加时间步
    for (int LCid = firstLCnumber; LCid <= lastLCnumber; LCid++)
    {
        std::string findtxt = "<loadcurve id=\"" + std::to_string(LCid) + "\">";
        int i2 = 0;
        while (i2 < lines.size() && lines[i2].find(findtxt) == std::string::npos)
        {
            i2++;
        }

        int i22 = i2 + numLC;

        // 写入当前负载曲线的内容
        for (int j = i - 1; j <= i22; j++)
        {
            outFile << lines[j] << std::endl;
        }
        i = i22 + 2;

        // 调用timeloadlaststep获取最后一步的时间和负载值
        std::vector<double> result = timeloadlaststep(tempfilename, LCid, firstLCnumber);
        double timelaststep = result[0];
        double loadlaststep = result[1];

        // 添加新的时间步
        outFile << "\t\t\t<point>" << (timelaststep + originalstepsize * timestepincrease)
            << "," << loadlaststep << "</point>" << std::endl;

        // 如果是最后一个负载曲线，写入剩余内容
        if (LCid == lastLCnumber)
        {
            for (int noo = i22 + 1; noo < lines.size(); noo++)
            {
                outFile << lines[noo] << std::endl;
            }
        }
    }

    outFile.close();
}
