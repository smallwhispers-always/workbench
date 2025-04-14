#pragma once
#include <iostream>

class OptimizeParameters
{
public:
    // 力矩容差参数（用于while循环）
    double mtol_x1;
    double mtol_y1;
    double mtol_z1;
    double mtol_z2;
    double mtol_y3;
    double mtol_z3;

    // 肌肉数量
    int n_msl;

    // 每个负载曲线中增加的步数
    int incLCstep;

    // 文件夹路径和文件名
    std::string foldername;
    std::string febinputfile;
    std::string originalrestartfile;
    std::string updatedrestartfile;
    std::string alteredrestartfile;
    std::string fullpath;
    std::string oldDmpFile;
    std::string newDmpFile;
    std::string logFile;

    //定义一个临时重启文件
    std::string temprestartfile;


    //中间文件路径,不进行初始化，在中间过程函数中调用
    std::string originalresultfilename;
    std::string resultfilenameandlocation;

    //定义两个参数originaltimestep和originalstepsize去接受1.函数提去出的数据
    //不去初始化这个两个参数
    int originaltimestep;
    double originalstepsize;

    // 肌肉力负载曲线参数
    int firstLCmsl;
    int lastLCmsl;

    // 优化增量参数
    double adjustloadvalue;
    int increasedtimestep;

    // 转储文件名
    std::string newdmpfilename;
    std::string dmpfilenameinFeb;

    OptimizeParameters();//在类中进行构造函数的声明
};