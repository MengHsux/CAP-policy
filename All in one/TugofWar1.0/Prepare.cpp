#include "Prepare.h"

using namespace std;

int ArgMax(double *f,int n)
{
	int *temp;
	double max;
	int c,i;
	c=1;
	temp=(int*)malloc(sizeof(int)*n);
	temp[0]=0;
	max=f[0];
	for(i=1;i<n;i++)
	{
		if (fabs(f[i]-max)==0.0)
		{
			temp[c]=i;
			c++;
		}
		else if (f[i]>max)
		{
			max=f[i];
			temp[0]=i;
			c=1;
		}
	}
	i=temp[rand()%c];
	free(temp);
	return i;
}

int ArgMin(double *f, int n)
{
	int *temp;
	double min;
	int c, i;
	c = 1;
	temp = (int*)malloc(sizeof(int)*n);
	temp[0] = 0;
	min = f[0];
	for (i = 1; i<n; i++)
	{
		if (fabs(f[i] - min) == 0.0)
		{
			temp[c] = i;
			c++;
		}
		else if (f[i]<min)
		{
			min = f[i];
			temp[0] = i;
			c = 1;
		}
	}
	i = temp[rand() % c];
	free(temp);
	return i;
}

double Gaussian(double mean, double dev)
{
	double x1, x2, w, y1;
	static double y2;
	static int use_last = 0;

	if (use_last)		        
	{
		y1 = y2;
		use_last = 0;
	}
	else
	{
		do
		{
			x1 = 2.0 * rand() / RAND_MAX - 1.0;
			x2 = 2.0 * rand() / RAND_MAX - 1.0;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);
		w = sqrt((-2.0 * log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}
	return mean + y1 * dev;
}