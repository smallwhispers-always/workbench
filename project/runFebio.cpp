#include "runFebio.h"
#include <iostream>
#include <string>

int runFebio(const std::string& febinputfile) 
{
    // 构建命令字符串
    std::string command = "febio3 -i " + febinputfile + " -dump";

    //std::cout << "执行命令: " << command << std::endl;

    // 执行系统命令
    int result = system(command.c_str());

    if (result != 0) 
    {
        std::cerr << "运行FEBio命令失败，返回值: " << result << std::endl;
    }

    return result;
}
