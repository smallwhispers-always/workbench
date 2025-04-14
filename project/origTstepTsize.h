#pragma once
#include <string>

// 从FEB文件中获取时间步长和步长大小
// 参数：
//   febfilename - FEB文件名
//   originaltimestep - 输出参数，原始时间步长
//   originalstepsize - 输出参数，原始步长大小
void origTstepTsize(const std::string& febfilename, int& originaltimestep, double& originalstepsize);

