#ifndef _FUZZYMETHOD_H
#define _FUZZYMETHOD_H

#include <ctime>
#include <cmath>
#include <iostream>
#include <ctime> 
#include <cstdlib> 

#include "FuzzyPar.h"  //��������ͷ�ļ�

using namespace std;

class FuzzyMethod
{
public:
	FuzzyMethod();
	~FuzzyMethod();

	//����������Ⱥ���
	double u_d_1(double r);
	double u_d_2(double d_dot);
	double u_d_3(double d_dot);
	double u_d_4(double d_dot);
	double u_d_5(double d_dot);

	//����������Ⱥ���
	double  u_alpha_1(double alpha);
	double u_alpha_2(double alpha);
	double u_alpha_3(double alpha);
	double u_alpha_4(double alpha);
	double u_alpha_5(double alpha);

	//����Сֵ
	double min(double x, double y);

	//�����ֵ,�����������,�Ӵ�С����
	double sort(double a1, double a2, double a3, double a4, double a5);

	//�������飬������ֵ
	double sort1(double arrays[],int ns);

	//��ͺ���
	double sum(double arrays[],int nss);

	//���
	double qiuji(double array1[], double array2[],int ks);

	//������,ʵ�������Сģ�����ƣ�����Ϊ�����仯�����Ϊѧϰ��
	double FuzzyMeth(double reward);

public:
	double membership_degree;  //������
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

	//�����Ȳ���
	double  u_1;
	double u_2 ;
	double u_3 ;
	double u_4 ;
	double u_5 ;
	double u_sum ;
	double beta_sum ;

};


#endif