#pragma once
#include <string>

// 修改重启文件中的DMP文件名
// 参数：
//   restartFilename - 重启文件名
//   newDMPfilename - 新的DMP文件名
void changeDMPnameInRestart(const std::string& restartFilename, const std::string& newDMPfilename);
