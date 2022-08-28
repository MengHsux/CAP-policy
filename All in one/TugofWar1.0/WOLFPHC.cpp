#include <iostream> 
#include <cstdlib>
#include <queue> 
#include "WOLFPHC.h"

using namespace std;


Agent::Agent(int SP)
{
	srand (time(NULL));
	StartPos=SP;
	ResetAll();
}

void Agent::ResetAll()
{
	FixedRope[0]=0;
	FixedRope[1]=0;
	FixedRope[2]=3;
	FixedRope[3]=3;
	FixedRope[4]=4;
	FixedRope[5]=2;
	FixedRope[6]=1;
	FixedRope[7]=1;
	FixedRope[8]=2;
	FixedRope[9]=0;
	FixedRope[10]=0;
	FixedRope[11]=0;
	FixedRope[12]=0;
	FixedRope[13]=3;
	FixedRope[14]=3;
	FixedRope[15]=4;
	FixedRope[16]=2;
	FixedRope[17]=1;
	FixedRope[18]=1;
	FixedRope[19]=2;
	FixedRope[20]=0;
	
	for(int a=0;a<AgentNumber;a++)
	{
		for(int i=0;i<Resolution;i++)
		{
			VisitedTimes[a][i]=0;
			for(int j=0;j<NumberofActions;j++)
			{
				Qtable[a][i][j]=10;
				Probability[a][i][j]=(double)1/(double)NumberofActions;
				AProbability[a][i][j]=0;
				
			}	
		}
	}
	ResetAgents();
}

void Agent::ResetAgents()
{
	CurrentPos=StartPos;
	NextPos=StartPos;
	Succeed=false;
	Fail=false;
}

void Agent::ChooseAction(int agentID)
{
	double chance=(double)rand()/RAND_MAX;
	if(chance<(double)Epsilon)
	{
		for(int ag=0; ag<AgentNumber;ag++)
		{
			Action[ag]=rand()%NumberofActions;
		}
	}else
	{
		double ra=(double)rand()/RAND_MAX;
		if(ra<=Probability[agentID][CurrentPos][0])
		{
			Action[agentID]=0;
		}else if(ra<=Probability[agentID][CurrentPos][0]+Probability[agentID][CurrentPos][1])
		{
			Action[agentID]=1;
		}else if(ra<=Probability[agentID][CurrentPos][0]+Probability[agentID][CurrentPos][1]+Probability[agentID][CurrentPos][2])
		{
			Action[agentID]=2;
		}else if(ra<=Probability[agentID][CurrentPos][0]+Probability[agentID][CurrentPos][1]+Probability[agentID][CurrentPos][2]+Probability[agentID][CurrentPos][3])
		{
			Action[agentID]=3;
		}else if(ra<=Probability[agentID][CurrentPos][0]+Probability[agentID][CurrentPos][1]+Probability[agentID][CurrentPos][2]+Probability[agentID][CurrentPos][3]+Probability[agentID][CurrentPos][4])
		{
			Action[agentID]=4;
		}
	}
}

void Agent::OChooseAction()
{
	int a1=rand()%NumberofActions;
	int a2=rand()%NumberofActions;
	int a3=rand()%NumberofActions;
	int a4=rand()%NumberofActions;

	OAction[0]=a1;
	OAction[1]=a2;
	OAction[2]=a3;
	OAction[3]=a3;
	OAction[4]=a4;
}

void Agent::GetResultant()
{
	double R=0,OR=0;
	double count[NumberofActions]={0};
	double Ocount[NumberofActions]={0};
	for(int ag=0; ag<AgentNumber;ag++)
	{
		count[Action[ag]]++;
		Ocount[OAction[ag]]++;
	}
	for(int ag=0; ag<AgentNumber;ag++)
	{
		if(Action[ag]!=FixedRope[CurrentPos])
		{
			R+= pow (count[Action[ag]],2.0);
		}
		if(OAction[ag]!=FixedRope[CurrentPos])
		{
			OR+=pow (Ocount[OAction[ag]],2.0);
		}
	}
	Resultant[0]=R;
	Resultant[1]=OR;
	if(R>OR)
	{
		NextPos=CurrentPos+1;
	}else if(R<OR)
	{
		NextPos=CurrentPos-1;
	}else
	{
		int w=rand()%Side;
		if(w==0)
		{
			NextPos=CurrentPos+1;
		}else{
			NextPos=CurrentPos-1;
		}
	}
}

bool Agent::Simulator()
{
	
	return true;
	if(NextPos>CurrentPos)
	{
		return true;
	}else if(NextPos<=CurrentPos)
	{
		return false;
	}
}

void Agent::UpdateQvalue(int agentID,double reward)
{
	double Qvalue[NumberofActions]={0};
	double NextMaxQ;
	int t=0;
	for(int i=0;i<NumberofActions;i++)
	{	
		Qvalue[i]=Qtable[agentID][NextPos][i];
	}
	NextMaxQ=Qvalue[ArgMax(Qvalue,NumberofActions)];
	Qtable[agentID][CurrentPos][Action[agentID]]+=(double)alphas*(reward+Gamma*NextMaxQ-Qtable[agentID][CurrentPos][Action[agentID]]);
}

void Agent::UpdateProbability(int agentID)
{
	VisitedTimes[agentID][CurrentPos]++;
	for(int i=0;i<NumberofActions;i++)
	{
		AProbability[agentID][CurrentPos][i]+=(Probability[agentID][CurrentPos][i]-AProbability[agentID][CurrentPos][i])/VisitedTimes[agentID][CurrentPos];
	}
	double Expectations=0,AExpectations=0;
	for(int i=0;i<NumberofActions;i++)
	{
		Expectations+=Probability[agentID][CurrentPos][i]*Qtable[agentID][CurrentPos][i];
		AExpectations+=AProbability[agentID][CurrentPos][i]*Qtable[agentID][CurrentPos][i];
	}
	double LearningRate;
	if(Expectations>AExpectations)
	{
		LearningRate=RateWIN;
	}else{
		LearningRate=RateFast;
	}
	double min,total=0,MaxQa;
	double tmp[NumberofActions]={0};
	for(int i=0;i<NumberofActions;i++)
	{
		tmp[i]=Qtable[agentID][CurrentPos][i];
	}
	MaxQa=ArgMax(tmp,NumberofActions);
	for(int i=0;i<NumberofActions;i++)
	{
		if(i==MaxQa)
		{
			Probability[agentID][CurrentPos][i]+=LearningRate;
		}else{
			Probability[agentID][CurrentPos][i]-=LearningRate/(double)(NumberofActions-1);
		}
		tmp[i]=Probability[agentID][CurrentPos][i];
	}
	min=tmp[ArgMin(tmp,NumberofActions)];
	if(min<0){
		for(int i=0;i<NumberofActions;i++)
		{
			Probability[agentID][CurrentPos][i]-=min;
			Probability[agentID][CurrentPos][i]/=(1+fabs(NumberofActions*min));
			total+=Probability[agentID][CurrentPos][i];
			if(Probability[agentID][CurrentPos][i]>1 || Probability[agentID][CurrentPos][i]<0 )
			{
				cout<<"P error1 !"<<endl;
			}
		}
		if(total>1.1 || total<0.9)
		{
			cout<<"P error2 !"<<endl;
		}
	}
}

void Agent::TakeAction()
{
	CurrentPos=NextPos;
}