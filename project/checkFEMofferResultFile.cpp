#include "checkFEMofferResultFile.h"
#include <iostream>
#include <fstream>
#include <string>

std::string checkFEMofferResultFile(const std::string& logfilename, const std::string& febinputfile) 
{
    std::ifstream logFile(logfilename);
    if (!logFile.is_open()) 
    {
        std::cerr << "无法打开日志文件: " << logfilename << std::endl;
        return "";
    }

    // 检查日志文件是否包含正常终止信息
    std::string line;
    bool normalTermination = false;
    while (std::getline(logFile, line)) 
    {
        if (line.find("N O R M A L   T E R M I N A T I O N") != std::string::npos) 
        {
            normalTermination = true;
            std::cout << "FE仿真成功" << std::endl;
            break;
        }
        else if (line.find("E R R O R   T E R M I N A T I O N") != std::string::npos) 
        {
            std::cerr << "FE仿真以错误终止" << std::endl;
            logFile.close();
            return "";
        }
    }
    logFile.close();

    if (!normalTermination) 
    {
        std::cerr << "未找到正常终止信息" << std::endl;
        return "";
    }

    // 打开FEB输入文件，查找结果文件名
    std::ifstream febFile(febinputfile);
    if (!febFile.is_open()) 
    {
        std::cerr << "无法打开FEB文件: " << febinputfile << std::endl;
        return "";
    }

    std::string resultFilename;
	while (std::getline(febFile, line)) 
    {
		size_t pos = line.find("<rigid_connector_data file=\"");
		if (pos != std::string::npos) 
        {
			resultFilename = line.substr(pos + 28); // 28是"<rigid_connector_data file=\""的长度
			size_t endPos = resultFilename.find("\"");
			if (endPos != std::string::npos) 
            {
				resultFilename = resultFilename.substr(0, endPos);
				break;
			}
		}
	}
    if (resultFilename.empty()) 
    {
        std::cerr << "未找到结果文件名" << std::endl;
    }
    /*else
    {
        std::cout << resultFilename << std::endl;
    }*/
    return resultFilename;
}

