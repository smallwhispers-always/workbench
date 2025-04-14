#pragma once
#include <string>

// 调整指定负载曲线的最后一步负载值
void adjustload(const std::string& filename, const std::string& newfilename, int loadcurvenumber, double adjustloadvalue, int firstLCnumber);

