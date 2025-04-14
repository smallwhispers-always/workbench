#include "timeloadlaststep.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<double> timeloadlaststep(const std::string& febfilename, int loadcurvenumber, int firstLCnumber) 
{
    std::vector<double> result(2, 0.0); // 初始化时间和负载值为0.0

    // 打开文件
    std::ifstream file(febfilename);
    if (!file.is_open()) 
    {
        std::cerr << "无法打开文件: " << febfilename << std::endl;
        return result;
    }

    // 读取文件内容
    std::string line;
    int numLC5 = 0, numLC6 = 0;
    std::vector<std::string> lines;

    while (std::getline(file, line)) 
    {
        lines.push_back(line);
        // 查找第一个负载曲线的行号
        if (line.find("<loadcurve id=\"" + std::to_string(firstLCnumber) + "\">") != std::string::npos) 
        {
            numLC5 = lines.size();
        }
        // 查找下一个负载曲线的行号
        if (line.find("<loadcurve id=\"" + std::to_string(firstLCnumber + 1) + "\">") != std::string::npos) 
        {
            numLC6 = lines.size();
        }
    }
    file.close();

    // 计算每个负载曲线的行数
    int numLC = numLC6 - numLC5 - 2;

    // 查找指定负载曲线的最后一步
    std::string findtxt = "<loadcurve id=\"" + std::to_string(loadcurvenumber) + "\">";
    size_t i2 = 0;
    while (i2 < lines.size() && lines[i2].find(findtxt) == std::string::npos) 
    {
        i2++;
    }

    if (i2 < lines.size()) 
    {
        size_t i22 = i2 + numLC;
        if (i22 < lines.size()) 
        {
            std::string newtline6 = lines[i22];
            size_t pos1 = newtline6.find("<point>");
            size_t pos2 = newtline6.find("</point>");
            if (pos1 != std::string::npos && pos2 != std::string::npos) 
            {
                std::string pointData = newtline6.substr(pos1 + 7, pos2 - (pos1 + 7));
                std::replace(pointData.begin(), pointData.end(), ',', ' ');
                std::istringstream iss(pointData);
                iss >> result[0] >> result[1];
            }
        }
    }

    return result;
}
