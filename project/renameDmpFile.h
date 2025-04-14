#pragma once
#include <string>

// 重命名DMP文件
// 参数：
//   oldFileName - 原始文件名
//   newFileName - 新文件名
// 返回值：
//   bool - 操作是否成功
bool renameDmpFile(const std::string& oldFileName,const std::string& newFileName);

