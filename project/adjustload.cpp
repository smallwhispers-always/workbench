#include "adjustload.h"
#include "timeloadlaststep.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>


void adjustload(const std::string& filename, const std::string& newfilename, int loadcurvenumber, double adjustloadvalue, int firstLCnumber) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

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

    // 获取最后一步的时间和负载值
    std::vector<double> timeload = timeloadlaststep(filename, loadcurvenumber, firstLCnumber);
    double timelaststep = timeload[0];
    double loadlaststep = timeload[1];

    // 查找指定负载曲线的最后一步并更新负载值
    std::string findtxt = "<loadcurve id=\"" + std::to_string(loadcurvenumber) + "\">";
    for (size_t n = 0; n < lines.size(); n++) 
    {
        if (lines[n].find(findtxt) != std::string::npos) 
        {
            size_t iii = n + numLC;
            if (iii < lines.size()) 
            {
                std::stringstream ss;
                ss << "\t\t\t<point>" << timelaststep << "," << (loadlaststep + adjustloadvalue) << "</point>";
                lines[iii] = ss.str();
            }
        }
    }

    // 将更新后的内容写入新文件
    std::ofstream outfile(newfilename);
    for (const auto& line : lines) 
    {
        outfile << line << std::endl;
    }
    outfile.close();
}
