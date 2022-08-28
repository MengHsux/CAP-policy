#include "FuzzyMethod.h"

//实现最大最小合成法，依据具体的调节内容而论，可以被用来直接调节beta
FuzzyMethod::FuzzyMethod()
{

}

FuzzyMethod::~FuzzyMethod()
{

}

double FuzzyMethod::u_d_1(double r)
{
	if (r<-40)
	{
		membership_degree = 1.0;
	}
	else if (r >= -40 && r< -10)
	{
		membership_degree = (-10 - r) / (-10 + 40);
	}
	else if (r >= -10)
	{
		membership_degree = 0;
	}
	return membership_degree;
}

double FuzzyMethod::u_d_2(double d_dot)
{
	if (d_dot < -70)
		membership_degree = 0.0;
	if (d_dot >= -70 && d_dot < -40)
		membership_degree = (d_dot + 70) / (-40 + 70);
	if (d_dot >= -40 && d_dot < -10)
		membership_degree = 1;
	if (d_dot >= -10 && d_dot < 0)
		membership_degree = (0 - d_dot) / (0 + 10);
	if (d_dot >= 0)
		membership_degree = 0;
	return membership_degree;
}

double FuzzyMethod::u_d_3(double d_dot)
{
	if (d_dot < -10)
		membership_degree = 0.0;
	if (d_dot >= -10 && d_dot < 0)
		membership_degree = (d_dot + 10) / (0 + 10);
	if (d_dot >= 0 && d_dot < 10)
		membership_degree = (10 - d_dot) / (10 - 0);
	if (d_dot >= 10)
		membership_degree = 0.0;
	return membership_degree;
}

double FuzzyMethod::u_d_4(double d_dot)
{
	if (d_dot < 0)
		membership_degree = 0.0;
	if (d_dot >= 0 && d_dot < 10)
		membership_degree = (d_dot - 0) / (10 - 0);
	if (d_dot >= 10 && d_dot < 40)
		membership_degree = 1;
	if (d_dot >= 40 && d_dot < 70)
		membership_degree = (70 - d_dot) / (70 - 40);
	if (d_dot >= 70)
	{
		membership_degree = 0;
	}
	return membership_degree;
}

double FuzzyMethod::u_d_5(double d_dot)
{
	if (d_dot < 10)
		membership_degree = 0.0;
	if (d_dot >= 10 && d_dot < 40)
		membership_degree = (d_dot - 10) / (40 - 10);
	if (d_dot >= 40)
		membership_degree = 1;
	return membership_degree;
}

double FuzzyMethod::u_alpha_1(double alpha)
{
	if (alpha < 0.48)
		membership_degree = 0.0;
	if (alpha >= 0.48 && alpha < 0.64)
		membership_degree = (alpha - 0.48) / (0.64 - 0.48);
	if (alpha >= 0.64)
		membership_degree = 1;
	return membership_degree;
}

double FuzzyMethod::u_alpha_2(double alpha)
{
	if (alpha < 0.32)
		membership_degree = 0.0;
	if (alpha >= 0.32 && alpha < 0.48)
		membership_degree = (alpha - 0.32) / (0.48 - 0.32);
	if (alpha >= 0.48 && alpha < 0.64)
		membership_degree = 1;
	if (alpha >= 0.64 && alpha < 0.80)
		membership_degree = (0.80 - alpha) / (0.80 - 0.64);
	if (alpha >= 0.80)
		membership_degree = 0;
	return membership_degree;
}

double FuzzyMethod::u_alpha_3(double alpha)
{
	if (alpha < 0.16)
		membership_degree = 0.0;
	if (alpha >= 0.16 && alpha < 0.32)
		membership_degree = (alpha - 0.16) / (0.32 - 0.16);
	if (alpha >= 0.32 && alpha < 0.48)
		membership_degree = 1;
	if (alpha >= 0.48 && alpha < 0.64)
		membership_degree = (0.64 - alpha) / (0.64 - 0.48);
	if (alpha >= 0.64)
		membership_degree = 0;
	return membership_degree;
}

double FuzzyMethod::u_alpha_4(double alpha)
{
	if (alpha < 0)
		membership_degree = 0.0;
	if (alpha >= 0 && alpha < 0.16)
		membership_degree = (alpha - 0) / (0.16 - 0);
	if (alpha >= 0.16 && alpha < 0.32)
		membership_degree = 1;
	if (alpha >= 0.32 && alpha < 0.48)
		membership_degree = (0.48 - alpha) / (0.48 - 0.32);
	if (alpha >= 0.48)
		membership_degree = 0;
	return membership_degree;
}

double FuzzyMethod::u_alpha_5(double alpha)
{
	if (alpha < 0)
		membership_degree = 0.0;
	if (alpha >= 0 && alpha < 0.16)
		membership_degree = 1;
	if (alpha >= 0.16 && alpha < 0.32)
		membership_degree = (0.32 - alpha) / (0.32 - 0.16);
	if (alpha >= 0.32)
		membership_degree = 0;
	return membership_degree;
}

double FuzzyMethod::min(double x, double y)
{
	if (x<y)
		return x;
	else
		return y;
}
//这个函数没用
double FuzzyMethod::sort(double a1, double a2, double a3, double a4, double a5)
{
	double arrays[5] = { 0 };
	arrays[0] = a1; arrays[1] = a2; arrays[2] = a3;
	arrays[3] = a4; arrays[4] = a5;
	int i, j;
	double t;
	int nt = sizeof(arrays) / sizeof(arrays[0]);    //这种确定数组长度的方式是错误的
	for (i = 0; i<nt; i++)
	{
		for (j = 0; j<nt - 1; j++)
		{
			if (arrays[j]<arrays[j + 1])
			{
				t = arrays[j];
				arrays[j] = arrays[j + 1];
				arrays[j + 1] = t;
			}
		}
	}
	return arrays[0];
}

double FuzzyMethod::sort1(double arrays[],int ns)
{
	int  i, j;
	double t;
	for (i = 0; i<ns; i++)
	{
		for (j = 0; j<ns - 1; j++)
		{
			if (arrays[j]<arrays[j + 1])
			{
				t = arrays[j];
				arrays[j] = arrays[j + 1];
				arrays[j + 1] = t;
			}
		}
	}
	return arrays[0];
}

double FuzzyMethod::sum(double arrays[],int nss)
{
	double sums = 0;
	for (int i = 0; i<nss; i++)
	{
		sums += arrays[i];
	}
	return sums;
}

double FuzzyMethod::qiuji(double array1[], double array2[],int ks)
{
	double product = 0;
	for (int i = 0; i<ks; i++)
	{
		product += array1[i] * array2[i];
	}
	return product;
}

double FuzzyMethod::FuzzyMeth(double reward)
{
	for (int j = 0; j<n; j++)
	{
		gamma_d[0][j] = u_d_1(p_d[j]);
		gamma_d[1][j] = u_d_2(p_d[j]);
		gamma_d[2][j] = u_d_3(p_d[j]);
		gamma_d[3][j] = u_d_4(p_d[j]);
		gamma_d[4][j] = u_d_5(p_d[j]);

	}
	for (int j = 0; j<ms; j++)
	{
		eta_alpha[0][j] = u_alpha_1(p_alpha[j]);
		eta_alpha[1][j] = u_alpha_2(p_alpha[j]);
		eta_alpha[2][j] = u_alpha_3(p_alpha[j]);
		eta_alpha[3][j] = u_alpha_4(p_alpha[j]);
		eta_alpha[4][j] = u_alpha_5(p_alpha[j]);
	}

	for (int i = 0; i<n; i++)
		for (int j = 0; j<ms; j++)
		{
			temp_1[i][j] = min(gamma_d[0][i], eta_alpha[0][j]);
			temp_2[i][j] = min(gamma_d[1][i], eta_alpha[1][j]);
			temp_3[i][j] = min(gamma_d[2][i], eta_alpha[2][j]);
			temp_4[i][j] = min(gamma_d[3][i], eta_alpha[3][j]);
			temp_5[i][j] = min(gamma_d[4][i], eta_alpha[4][j]);
			R[i][j] = sort(temp_1[i][j], temp_2[i][j], temp_3[i][j], temp_4[i][j], temp_5[i][j]);
			
		}

	//求奖励的隶属度
	u_1 = u_d_1(reward);
	u_2 = u_d_2(reward);
	u_3 = u_d_3(reward);
	u_4 = u_d_4(reward);
	u_5 = u_d_5(reward);
	u_sum = u_1 + u_2 + u_3 + u_4 + u_5;
	

	//初始化rho数组
	for (int k = 0; k<n; k++)
	{
		rho[k] = 0;
	}
	for (int k = 0; k<ms; k++)
	{
		beta[k] = 0;
	}
	for (int j = 0; j<n; j++)
	{
		u_temp[j] = u_1 * gamma_d[0][j] + u_2 * gamma_d[1][j] + u_3 * gamma_d[2][j] + u_4 * gamma_d[3][j] + u_5 * gamma_d[4][j];
		
		rho[j] = (double)(u_temp[j] / u_sum);
		
		//cout << rho[j] << endl;
	}
	for (int j = 0; j<ms; j++)
	{
		for (int k = 0; k<n; k++)
		{
			temp_min[j][k] = min(rho[k], R[k][j]);
		}
		beta[j] = sort1(temp_min[j],n);   //依次求每行的最大值
	}
	beta_sum = sum(beta,ms);
	if (beta_sum == 0)
	{
		beta_sum = 0.5;
	}
	
	alpha = (double)qiuji(beta, p_alpha,ms) / beta_sum;   //求出学习率
	// cout << "learning rate:" << alpha << endl;

	return alpha;
}