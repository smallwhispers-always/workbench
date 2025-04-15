#include "adjustload.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void adjustload(const std::string& filename,
                const std::string& newfilename,
                int loadcurvenumber,
                double adjustloadvalue,
                int firstLCnumber) 
{
    // 打开原始文件进行读取
    std::ifstream inFile(filename);
    if (!inFile.is_open()) 
    {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    // 读取文件内容到向量中
    std::vector<std::string> lines;
    std::string line;
    int numLC5 = 0, numLC6 = 0;

    while (std::getline(inFile, line)) 
    {
        lines.push_back(line);

        // 查找第一个和第二个加载曲线的位置
        std::string findStr1 = "<loadcurve id=\"" + std::to_string(firstLCnumber) + "\">";
        if (line.find(findStr1) != std::string::npos) 
        {
            numLC5 = lines.size() - 1;
        }

        std::string findStr2 = "<loadcurve id=\"" + std::to_string(firstLCnumber + 1) + "\">";
        if (line.find(findStr2) != std::string::npos) 
        {
            numLC6 = lines.size() - 1;
        }
    }
    inFile.close();

    // 计算每个加载曲线中的点数（行数）
    int numLC = numLC6 - numLC5 - 2;  // 减2是因为要排除加载曲线的开始和结束标签

    // 查找指定的加载曲线
    std::string findtxt = "<loadcurve id=\"" + std::to_string(loadcurvenumber) + "\">";
    int i2 = 0;
    while (i2 < lines.size() && lines[i2].find(findtxt) == std::string::npos) 
    {
        i2++;
    }

    // 获取最后一个点的数据
    int i22 = i2 + numLC;
    if (i22 < lines.size()) 
    {
        std::string pointLine = lines[i22];

        // 移除标签和替换逗号
        size_t startPos = pointLine.find("<point>") + 7;
        size_t endPos = pointLine.find("</point>");
        if (startPos != std::string::npos && endPos != std::string::npos) 
        {
            std::string pointData = pointLine.substr(startPos, endPos - startPos);

            // 分割时间和加载值
            size_t commaPos = pointData.find(",");
            if (commaPos != std::string::npos) 
            {
                std::string timeStr = pointData.substr(0, commaPos);
                std::string loadStr = pointData.substr(commaPos + 1);

                // 转换为数值并调整加载值
                try 
                {
                    double time = std::stod(timeStr);
                    double load = std::stod(loadStr);

                    // 调整加载值
                    load += adjustloadvalue;

                    // 更新点数据
                    lines[i22] = pointLine.substr(0, startPos) + timeStr + "," + std::to_string(load) + pointLine.substr(endPos);
                }
                catch (const std::exception& e) 
                {
                    std::cerr << "转换数值时出错: " << e.what() << std::endl;
                }
            }
        }
    }

    // 将修改后的内容写入新文件
    std::ofstream outFile(newfilename);
    if (!outFile.is_open()) 
    {
        std::cerr << "无法创建文件: " << newfilename << std::endl;
        return;
    }

    for (const auto& l : lines) 
    {
        outFile << l << "\r\n";
    }
    outFile.close();
}
