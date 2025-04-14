#include "OptimizeParameters.h"

// 构造函数，初始化所有参数
OptimizeParameters::OptimizeParameters()
{
	// 力矩容差参数
	mtol_x1 = 300.0;
	mtol_y1 = 300.0;
	mtol_z1 = 300.0;
	mtol_z2 = 300.0;
	mtol_y3 = 300.0;
	mtol_z3 = 300.0;

	// 肌肉数量
	n_msl = 55;

	// 每个负载曲线中增加的步数
	incLCstep = 14;

	// 文件夹路径和文件名
	//C:\\Users\\Mayn\\Desktop\\ori\\walk-Denver-female-ori.feb
	foldername = "C:\\Users\\Mayn\\Desktop\\ori\\";
	febinputfile = "walk-Denver-female-ori.feb";
	originalrestartfile = "restart-1Dmsl_knee_H2_pelSYS_ABrev2.feb";
	updatedrestartfile = "restart-1Dmsl_knee_H2_pelSYS_ABrev201.feb";
	alteredrestartfile = "restart-1Dmsl_knee_H2_pelSYS_ABrev202.feb";

	//定义一个临时重启文件
	temprestartfile = "restart-MSK-temp.feb";


	// 转储文件名
	newdmpfilename = "restart-hip1D-msl1.dmp";
	dmpfilenameinFeb = "restart-hip1D-msl.dmp";

	//初始febio文件全名称
	fullpath = this->foldername + this->febinputfile;

	// 提取原始DMP文件名（去掉.feb后缀，添加.dmp后缀）
	oldDmpFile = foldername + febinputfile.substr(0, febinputfile.length() - 4) + ".dmp";
	newDmpFile = foldername + dmpfilenameinFeb;
	logFile = foldername + febinputfile.substr(0, febinputfile.length() - 4) + ".log";
	// 肌肉力负载曲线参数
	firstLCmsl = 8;
	lastLCmsl = 62;

	// 优化增量参数
	adjustloadvalue = 10.0;
	increasedtimestep = 1;
};