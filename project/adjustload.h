#pragma once
#include <string>

/**
 * @brief 调整加载曲线的最后一步负载，并创建新文件
 *
 * @param filename 原始文件名
 * @param newfilename 新文件名（可以与原始文件名不同）
 * @param loadcurvenumber 要调整的加载曲线编号
 * @param adjustloadvalue 调整的负载值
 * @param firstLCnumber 第一个加载曲线编号（用于计算每个加载曲线中的点数）
 */
void adjustload(const std::string& filename,
                const std::string& newfilename,
                int loadcurvenumber,
                double adjustloadvalue,
                int firstLCnumber);

