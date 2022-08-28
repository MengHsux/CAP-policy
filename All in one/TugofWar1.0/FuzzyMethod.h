#ifndef _FUZZYMETHOD_H
#define _FUZZYMETHOD_H

#include <ctime>
#include <cmath>
#include <iostream>
#include <ctime> 
#include <cstdlib> 

#include "FuzzyPar.h"  //包含参数头文件

using namespace std;

class FuzzyMethod
{
public:
	FuzzyMethod();
	~FuzzyMethod();

	//输入的隶属度函数
	double u_d_1(double r);
	double u_d_2(double d_dot);
	double u_d_3(double d_dot);
	double u_d_4(double d_dot);
	double u_d_5(double d_dot);

	//输出的隶属度函数
	double  u_alpha_1(double alpha);
	double u_alpha_2(double alpha);
	double u_alpha_3(double alpha);
	double u_alpha_4(double alpha);
	double u_alpha_5(double alpha);

	//求最小值
	double min(double x, double y);

	//求最大值,输入是五个数,从大到小排序
	double sort(double a1, double a2, double a3, double a4, double a5);

	//输入数组，输出最大值
	double sort1(double arrays[],int ns);

	//求和函数
	double sum(double arrays[],int nss);

	//求积
	double qiuji(double array1[], double array2[],int ks);

	//主方法,实现最大最小模糊控制，输入为特征变化误差，输出为学习率
	double FuzzyMeth(double reward);

public:
	double membership_degree;  //隶属度
	double gamma_d[5][n];
	double eta_alpha[5][ms];
	double R[n][ms];
	double temp_1[n][ms];
	double temp_2[n][ms];
	double temp_3[n][ms];
	double temp_4[n][ms];
	double temp_5[n][ms];
	double alpha_0[6001];
	double d_dot_0[6001];
	double rho[n];
	double u_temp[n];
	double beta[ms];
	double temp_min[ms][n];
	double alpha;

	//隶属度参数
	double  u_1;
	double u_2 ;
	double u_3 ;
	double u_4 ;
	double u_5 ;
	double u_sum ;
	double beta_sum ;

};


#endif