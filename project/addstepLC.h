#pragma once
#include <string>

// 增加时间步长并为重启文件中的每个负载曲线添加一个时间步
// 参数：
//   oldfilename - 原始重启文件名
//   newfilename - 新重启文件名
//   tempfilename - 临时文件名
//   firstLCnumber - 第一个负载曲线编号
//   lastLCnumber - 最后一个负载曲线编号
//   originaltimestep - 原始时间步数
//   originalstepsize - 原始步长大小
//   timestepincrease - 时间步增量
void addstepLC(const std::string& oldfilename, const std::string& newfilename,
               const std::string& tempfilename, int firstLCnumber, int lastLCnumber,
               int originaltimestep, double originalstepsize, int timestepincrease);

