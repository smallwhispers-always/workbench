#include "renameDmpFile.h"
#include <iostream>
#include <fstream>
using namespace std;

bool renameDmpFile(const std::string& oldFileName, const std::string& newFileName)
{
	////检查文件是否存在
	//std::ifstream file(oldfilename);
	//if (!file.good())
	//{
	//    std::cerr << "错误: 源文件不存在."<< std::endl;
	//    return false;
	//}
	//else
	//{
		//std::cerr << "正确: 源文件存在." << std::endl;
		std::cout << oldFileName.c_str() << std::endl;
		std::cout << newFileName.c_str() << std::endl;
		int result = 0;
		//string str1;
	    //string str2;
	    //str1 = "C:\\Users\\Mayn\\Desktop\\ori\\walk-Denver-female-ori.dmp";
	    //cout << (str1 == oldFileName) << endl;
	    //str1 = oldFileName;
	    //str2 = "C:\\Users\\Mayn\\Desktop\\ori\\restart-hip1D-msl.dmp";
	    //cout << (str2 == newFileName) << endl;
	    //str2 = newFileName;
	    ////result = rename(str1.c_str(), str2.c_str());
		result = rename(oldFileName.c_str(), newFileName.c_str());
		//result = rename(newFileName.c_str(), oldFileName.c_str());
		//C:\Users\Mayn\Desktop\ori\walk-Denver-female-ori.dmp
		//	C:\Users\Mayn\Desktop\ori\restart-hip1D-msl.dmp
			//int result = rename(oldFileName.c_str(), newFileName.c_str());
			//std::cout << oldFileName.c_str() << std::endl;
			//std::cout << newFileName.c_str() << std::endl;
		if (result == -1)
		{
			std::cerr << "重命名文件失败，返回值: " << result << std::endl;
			return false;
		}
		else
		{
			std::cout << "文件重命名成功: " << oldFileName << " -> " << newFileName << std::endl;
			return true;
		}
	
}
