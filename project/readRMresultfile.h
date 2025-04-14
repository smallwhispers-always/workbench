#pragma once
#include <string>
#include <vector>

// 读取结果文件中的反应力矩
// 参数：
//   resultfilename - 结果文件名
// 返回值：
//   std::vector<double> - 包含6个反应力矩的向量，顺序为 RCMx1, RCMy1, RCMz1, RCMz2, RCMy3, RCMz3
std::vector<double> readRMresultfile(const std::string& resultfilename);

