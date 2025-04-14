#include "readRMresultfile.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<double> readRMresultfile(const std::string& resultfilename) 
{
    std::vector<double> result(6, 0.0); // 初始化6个力矩值为0.0
    std::ifstream file(resultfilename);
    if (!file.is_open()) 
    {
        std::cerr << "无法打开文件: " << resultfilename << std::endl;
        return result;
    }

    std::string line;
    int lineCount = 0;
    while (std::getline(file, line)) 
    {
        lineCount++;
        if (lineCount >= 3) { // 跳过前两行
            std::istringstream iss(line);
            double value;
            int index = 0;
            while (iss >> value) 
            {
                if (index == 4) 
                { // 第5列是x方向力矩
                    result[0] = value;
                }
                else if (index == 5) 
                { // 第6列是y方向力矩
                    result[1] = value;
                }
                else if (index == 6) 
                { // 第7列是z方向力矩
                    result[2] = value;
                }
                index++;
            }
        }
    }
    file.close();

    return result;
}
