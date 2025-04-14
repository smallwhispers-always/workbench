#pragma once
#include <string>
#include <vector>

//// 复制文件
//void copyFile(const std::string& src, const std::string& dst);
////判断复制出来的文件内容是否相等
//bool areFilesEqual(const std::string& file1, const std::string& file2);
//
//// 运行FEBio命令
//void reRunFEBio(const std::string& command);
//
//// 优化主算法
//void optimizationMain(int incLCstep, const std::string& dmpfilenameinFeb,
//	                  const std::string& newdmpfilename, const std::string& updatedrestartfile);


// 复制文件
void copyFile(const std::string& src, const std::string& dst);

// 运行FEBio命令
void reRunFEBio(const std::string& command);

// 优化主算法
void optimizationMain(int incLCstep, const std::string& dmpfilenameinFeb, const std::string& newdmpfilename, const std::string& updatedrestartfile);


