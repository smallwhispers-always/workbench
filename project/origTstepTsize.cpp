#include "origTstepTsize.h"
#include <fstream>
#include <iostream>
#include <string>

void origTstepTsize(const std::string& febfilename, int& originaltimestep, double& originalstepsize)
{
    // 打开FEB文件
    std::ifstream file(febfilename);
    if (!file.is_open()) 
    {
        std::cerr << "无法打开文件: " << febfilename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        // 查找<time_steps>标签
        size_t pos = line.find("<time_steps>");
        if (pos != std::string::npos) 
        {
            // 提取时间步长值
            std::string value = line.substr(pos + 12); // 12是"<time_steps>"的长度
            // 移除结束标签和空白
            size_t endPos = value.find("<");
            if (endPos != std::string::npos) 
            {
                value = value.substr(0, endPos);
            }
            // 转换为整数
            originaltimestep = std::stoi(value);
        }

        // 查找<step_size>标签
        pos = line.find("<step_size>");
        if (pos != std::string::npos) 
        {
            // 提取步长大小值
            std::string value = line.substr(pos + 11); // 11是"<step_size>"的长度
            // 移除结束标签和空白
            size_t endPos = value.find("<");
            if (endPos != std::string::npos) 
            {
                value = value.substr(0, endPos);
            }
            // 转换为浮点数
            originalstepsize = std::stod(value);
        }
    }

    file.close();
}
