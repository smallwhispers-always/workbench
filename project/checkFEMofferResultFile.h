#pragma once
#include <string>

// 检查FEBio仿真是否成功，并返回结果文件名
// 参数：
//   logfilename - 日志文件名
//   febinputfile - FEB输入文件名
// 返回值：
//   std::string - 结果文件名
std::string checkFEMofferResultFile(const std::string& logfilename, const std::string& febinputfile);

