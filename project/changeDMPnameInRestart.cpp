#include "changeDMPnameInRestart.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void changeDMPnameInRestart(const std::string& restartFilename, const std::string& newDMPfilename) 
{
    // 打开重启文件
    std::ifstream file(restartFilename);
    if (!file.is_open()) 
    {
        std::cerr << "无法打开文件: " << restartFilename << std::endl;
        return;
    }

    // 读取文件内容
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) 
    {
        lines.push_back(line);
    }
    file.close();

    // 查找并修改<Archive>标签
    for (auto& l : lines) 
    {
        size_t pos = l.find("<Archive>");
        if (pos != std::string::npos) 
        {
            // 替换为新的DMP文件名
            l = "        <Archive>" + newDMPfilename + "</Archive>";
        }
    }

    // 将修改后的内容写回文件
    std::ofstream outFile(restartFilename);
    for (const auto& l : lines) 
    {
        outFile << l << std::endl;
    }
    outFile.close();
}
