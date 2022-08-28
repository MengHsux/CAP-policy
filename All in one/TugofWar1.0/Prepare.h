#ifndef _DEF_H
#define _DEF_H


#include <math.h>
#include <time.h> 
#include <iostream>
#include <cstdlib>

#define	Turns			20
#define NumberofActions	5 //5
#define	AgentNumber		5 // ���������������̫�࣬����Ҫ����
#define Side			2

#define	LoseReward		-50
#define	WinReward		50
#define	DrawReward		0.0
#define CantCooperation	0.0

#define VARS 0.05 //CAP�еĳ�����, from 0.05

#define alphas			0.9 //0.8
#define Gamma			0.95 //0.9
#define Epsilon			0.05 //̰���㷨ѡ����

#define Resolution		21

#define TotalEpisode	1500
#define AverageTime		50
#define MaxStepNum		1000

#define RateWIN			0.025
#define RateFast		0.05

struct payoff{
	double q[AgentNumber];
	double axioms;
	double var;
};

struct CandidateAction{
	int a[AgentNumber];
};


int ArgMax(double *f, int n);
int ArgMin(double *f, int n);
double Gaussian(double mean, double dev);

#endif