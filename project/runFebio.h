#pragma once
#include <string>

// 运行FEBio软件并生成dump文件
// 参数：
//   febinputfile - FEB输入文件名
// 返回值：
//   int - 系统命令的返回值，0表示成功
int runFebio(const std::string& febinputfile);

