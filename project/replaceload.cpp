#include "replaceload.h"
#include "timeloadlaststep.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

void replaceload(const std::string& filename,
                 const std::string& newfilename,
                 int loadcurvenumber,
                 double replaceloadvalue,
                 int firstLCnumber)
{
    // 读取原始文件内容
    std::ifstream inFile(filename);
    std::vector<std::string> lines;
    std::string line;
    int numLC5 = 0, numLC6 = 0;

    while (std::getline(inFile, line)) 
    {
        lines.push_back(line);

        // 查找第一个和第二个负载曲线位置
        std::string target1 = "<loadcurve id=\"" + std::to_string(firstLCnumber) + "\">";
        if (line.find(target1) != std::string::npos) 
        {
            numLC5 = lines.size(); // 记录行号(从1开始)
        }

        std::string target2 = "<loadcurve id=\"" + std::to_string(firstLCnumber + 1) + "\">";
        if (line.find(target2) != std::string::npos) 
        {
            numLC6 = lines.size(); // 记录行号
        }
    }
    inFile.close();

    // 获取最后一步时间和原负载值
    auto result = timeloadlaststep(filename, loadcurvenumber, firstLCnumber);
    double timelaststep = result[0];

    // 定位目标负载曲线
    std::string targetLC = "<loadcurve id=\"" + std::to_string(loadcurvenumber) + "\">";
    for (size_t n = 0; n < lines.size(); ++n) 
    {
        if (lines[n].find(targetLC) != std::string::npos) 
        {
            // 计算最后一个点的行号
            int pointCount = numLC6 - numLC5 - 2; // 根据相邻LC计算点数
            int lastPointLine = n + pointCount;    // 最后一点的行号

            if (lastPointLine < lines.size()) 
            {
                // 构造新的点数据行
                std::string newPoint = "\t\t\t<point>"
                    + std::to_string(timelaststep) + ","
                    + std::to_string(replaceloadvalue) + "</point>";

                lines[lastPointLine] = newPoint;
            }
            break;
        }
    }

    // 写入新文件
    std::ofstream outFile(newfilename);
    for (const auto& l : lines) 
    {
        outFile << l << "\r\n";
    }
    outFile.close();
}
