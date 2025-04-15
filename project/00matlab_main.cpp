#include <iostream>
#include <fstream>
#include "OptimizeParameters.h"
#include "origTstepTsize.h"
#include "runFebio.h"
#include "renameDmpFile.h"
#include "checkFEMofferResultFile.h"
#include "timeloadlaststep.h"
#include "changeDMPnameInRestart.h"
#include "readRMresultfile.h"
#include "optimization.h"
#include <windows.h>
#include "addstepLC.h"
#include <direct.h> // Windows下用于chdir
#include "adjustload.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

int main()
{
	OptimizeParameters data;
	// 在main函数开头添加存储容器
	std::vector<double> RCMx_history, RCMy_history, RCMz_history, RCMz2_history, RCMy3_history, RCMz3_history;
//	//cout << "肌肉数量为：" << data.n_msl << endl;
//
//
//1.origTstepTsize函数的测试
	 //构建完整的文件路径
	string fullPath = data.foldername + data.febinputfile;
	int originaltimestep = 0;
	double originalstepsize = 0.0;
	cout << "尝试打开文件: " << fullPath << endl;
	// 测试origTstepTsize函数
	try
	{
		origTstepTsize(fullPath, originaltimestep, originalstepsize);
		data.originaltimestep = originaltimestep;
		data.originalstepsize = originalstepsize;
		cout << "从文件中读取参数：" << endl;
		cout << "时间步长(time_steps): " << data.originaltimestep << endl;
		cout << "步长大小(step_size): " << data.originalstepsize << endl;
	}
	catch (const std::exception& e)
	{
		cerr << "发生错误: " << e.what() << endl;
	}

	//2.runFebio函数测试

	//cout << "运行febio软件..." << endl;
	//int febioresult = runFebio(data.fullpath);
	//if (febioresult == 0)
	//{
	//    cout << "febio运行成功" << endl;
	//}

	//3.renameDmpFile函数测试

	 //重命名文件
	 //renameDmpFile(data.oldDmpFile, data.newDmpFile);

//	//4.checkFEMofferResultFile函数测试
//
	//判断优化是否成功
	//如果成功进入下一阶段
	data.originalresultfilename = checkFEMofferResultFile(data.logFile, data.fullpath);
	data.resultfilenameandlocation = data.foldername + data.originalresultfilename;
	cout << "resultfilenameandlocation的路径：" << data.resultfilenameandlocation << endl;

	////5.timeloadlaststep函数测试
	//
 //   // 调用timeloadlaststep函数
	//std::vector<double> result = timeloadlaststep(data.foldername + data.updatedrestartfile, 8 ,8);
	//// 输出结果
	//std::cout << "时间: " << result[0] << std::endl;
	//std::cout << "负载值: " << result[1] << std::endl;
	//std::string command = "febio3 -r " + data.foldername + data.updatedrestartfile + " -dump " + data.foldername + data.dmpfilenameinFeb;
	//cout << command << endl;
	/*int result = system(command.c_str());
	if (result == 0)
	{
		cout << "成功" << endl;
	}*/

	//5.addstepLC函数测试

	 //调用addstepLC函数
	addstepLC(data.foldername + data.originalrestartfile, 
		      data.foldername + data.updatedrestartfile,
		      data.foldername + data.temprestartfile,
		      data.firstLCmsl, 
		      data.lastLCmsl, 
		      data.originaltimestep,
		      data.originalstepsize, 
		      data.increasedtimestep);

	//6.changeDMPnameInRestart函数测试


	changeDMPnameInRestart(data.foldername + data.updatedrestartfile, data.newdmpfilename);


	//7.开始主优化循环配置函数测试

	//copyFile(data.foldername + data.dmpfilenameinFeb, data.foldername + data.newdmpfilename);
	////判断文件内容是否相同
	//if (areFilesEqual(data.foldername + data.dmpfilenameinFeb, data.foldername + data.newdmpfilename))
	//{
	//    std::cout << "文件内容相同" << std::endl;
	//}
	//else 
	//{
	//    std::cout << "文件内容不同" << std::endl;
	//}
	// 执行命令
	// 定义目标目录
	const char* targetDirectory = "C:\\Users\\Mayn\\Desktop\\ori";

	// 使用chdir函数切换到目标目录
	int r = _chdir(targetDirectory);

	// 检查是否成功切换目录
	if (r != 0)
	{
		std::cerr << "切换目录失败！" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "成功切换到目录: " << targetDirectory << std::endl;
	}
	//for (int increasedsteps = 1; increasedsteps <= data.incLCstep; ++increasedsteps)
	//{
		optimizationMain(data.incLCstep,
			             data.foldername + data.dmpfilenameinFeb,
			             data.foldername + data.newdmpfilename,
			             data.foldername + data.updatedrestartfile);

		//8.readRMresultFile函数测试
		// 调用readRMresultfile函数
		// 在读取力矩值后存储初始值
		std::vector<double> moments = readRMresultfile(data.resultfilenameandlocation);
		RCMx_history.push_back(moments[0]);
		RCMy_history.push_back(moments[1]);
		RCMz_history.push_back(moments[2]);
		RCMz2_history.push_back(moments[3]);
		RCMy3_history.push_back(moments[4]);
		RCMz3_history.push_back(moments[5]);
		// 获取各个力矩值
		//double RCMx1 = moments[0];
		//double RCMy1 = moments[1];
		//double RCMz1 = moments[2];
		//double RCMz2 = moments[3];
		//double RCMy3 = moments[4];
		//double RCMz3 = moments[5];
		//cout << RCMx1 << endl;
		//cout << RCMy1 << endl;
		//cout << RCMz1 << endl;
		//cout << RCMz2 << endl;
		//cout << RCMy3 << endl;
		//cout << RCMz3 << endl << endl;


		//9.replaceload函数测试
		//.......

		// 优化循环
		//while (std::abs(RCMx1) > data.mtol_x1 ||
		//	   std::abs(RCMy1) > data.mtol_y1 ||
		//	   std::abs(RCMz1) > data.mtol_z1 ||
		//	   std::abs(RCMz2) > data.mtol_z2 ||
		//	   std::abs(RCMz3) > data.mtol_z3)
		//{
			int k = 2; // C++索引从0开始，所以这里k=2对应MATLAB中的k=2

			// 调整每个加载曲线的最后一步负载
			for (int LCid = data.firstLCmsl; LCid <= data.lastLCmsl; LCid++)
			{
				//int kk = LCid - data.firstLCmsl + 1;

				// 获取最后一步的时间和负载
				//std::pair<double, double> result = timeloadlaststep(data.foldername + data.updatedrestartfile, LCid, data.firstLCmsl);
				std::vector<double> result = timeloadlaststep(data.foldername + data.updatedrestartfile, LCid, data.firstLCmsl);
				double timelaststep = result[0];
				double loadlaststep = result[1];
				cout << LCid << endl << timelaststep << endl;
				cout << loadlaststep << endl;

				 //调整负载
				adjustload(data.foldername + data.updatedrestartfile,
					       data.foldername + data.alteredrestartfile,
					       LCid,
					       data.adjustloadvalue,
					       data.firstLCmsl);

				std::vector<double> result_ = timeloadlaststep(data.foldername + data.alteredrestartfile, LCid, data.firstLCmsl);
				double timelaststep_ = result_[0];
				double loadlaststep_ = result_[1];
				cout << LCid << endl << timelaststep_ << endl;
				cout << loadlaststep_ << endl;

				// 运行重启文件
				std::string command = "febio3 -r " + data.foldername + data.alteredrestartfile + " -dump " + data.foldername + data.dmpfilenameinFeb;
				system(command.c_str());

				// 存储反应力矩
				// 在肌肉循环内部存储每次调整后的力矩值
				std::vector<double> newMoments = readRMresultfile(data.resultfilenameandlocation);
				RCMx_history.push_back(newMoments[0]);
				RCMy_history.push_back(newMoments[1]);
				RCMz_history.push_back(newMoments[2]);
				RCMz2_history.push_back(newMoments[3]);
				RCMy3_history.push_back(newMoments[4]);
				RCMz3_history.push_back(newMoments[5]);
				//RCMx1 = newMoments[0];
				//RCMy1 = newMoments[1];
				//RCMz1 = newMoments[2];
				//RCMz2 = newMoments[3];
				//RCMy3 = newMoments[4];
				//RCMz3 = newMoments[5];
				//cout << RCMx1 << endl;
				//cout << RCMy1 << endl;
				//cout << RCMz1 << endl;
				//cout << RCMz2 << endl;
				//cout << RCMy3 << endl;
				//cout << RCMz3 << endl<< endl;
				//k++;
			}
			// delta计算部分
			int muscleCount = data.lastLCmsl - data.firstLCmsl + 1;
			std::vector<double> deltRCMx1(muscleCount), deltRCMy1(muscleCount), deltRCMz1(muscleCount),
				deltRCMz2(muscleCount), deltRCMy3(muscleCount), deltRCMz3(muscleCount);

			for (int nn = 1; nn <= muscleCount; ++nn) 
			{ // 对应MATLAB的nn=2:lastLCmsl-firstLCmsl+2
				int k = nn - 1; // C++索引从0开始
				deltRCMx1[k] = RCMx_history[nn] - RCMx_history[0];
				deltRCMy1[k] = RCMy_history[nn] - RCMy_history[0];
				deltRCMz1[k] = RCMz_history[nn] - RCMz_history[0];
				deltRCMz2[k] = RCMz2_history[nn] - RCMz2_history[0];
				deltRCMy3[k] = RCMy3_history[nn] - RCMy3_history[0];
				deltRCMz3[k] = RCMz3_history[nn] - RCMz3_history[0];
				cout << deltRCMx1[k] << endl;
			}

			
		/*}*/
	/*}*/

	system("pause");
	return 0;
}



//int main() 
//{
//    OptimizeParameters data;
//    // 定义目标目录
//    const char* targetDirectory = "C:\\Users\\Mayn\\Desktop\\ori";
//
//    // 使用chdir函数切换到目标目录
//    int r = _chdir(targetDirectory);
//
//    // 检查是否成功切换目录
//    if (r != 0) 
//    {
//        std::cerr << "切换目录失败！" << std::endl;
//        return 1;
//    }
//    else 
//    {
//        std::cout << "成功切换到目录: " << targetDirectory << std::endl;
//    }
//
//    std::string command = "febio3 -r " + data.updatedrestartfile + " -dump " + data.dmpfilenameinFeb;
//    cout << command << endl;
//    //std::string command = "febio3 -i " + febinputfile + " -dump";
//    // 执行命令
//    int ret = system(command.c_str());
//    if (ret != 0)
//    {
//        std::cerr << "失败！" << std::endl;
//        return 1;
//    }
//    else
//    {
//        std::cout << "成功!" << targetDirectory << std::endl;
//    }
//    
//
//    return 0;
//}