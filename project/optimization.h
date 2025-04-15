#pragma once
#include <string>
#include <vector>

// 复制文件
void copyFile(const std::string& src, const std::string& dst);

//判断复制出来的文件内容是否相等
bool areFilesEqual(const std::string& file1, const std::string& file2);

/**
 * 运行FEBio命令
 *
 * @param updatedrestartfile 重启文件路径
 * @param dmpfilenameinFeb dump文件路径
 * @return 命令执行是否成功
 */
bool reRunFEBio(const std::string& foldername, const std::string& updatedrestartfile, const std::string& dmpfilenameinfeb);

// 优化主算法
void optimizationMain(int incLCstep, const std::string& dmpfilenameinFeb,
	                  const std::string& newdmpfilename, const std::string& updatedrestartfile);


