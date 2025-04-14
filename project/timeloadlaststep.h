#pragma once
#include <string>
#include <vector>

// 获取指定负载曲线的最后一步时间和负载值
// 参数：
//   febfilename - FEB文件名
//   loadcurvenumber - 负载曲线编号
//   firstLCnumber - 第一个负载曲线编号
// 返回值：
//   std::vector<double> - 包含两个元素的向量，第一个是时间，第二个是负载值
std::vector<double> timeloadlaststep(const std::string& febfilename, int loadcurvenumber, int firstLCnumber);

