#include <iostream> 
#include <cstdlib>
#include <queue> 
#include "Greedy.h"

using namespace std;


//构造函数
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
			for(int j=0;j<NumberofActions;j++)
			{
				for(int k=0;k<NumberofActions;k++)
				{
					for(int l=0;l<NumberofActions;l++)
					{
						for(int p=0;p<NumberofActions;p++)
						{
								 Qtable[a][i][j][k][l][p]=10;
							
						}
						
					}
				}
			}	
		}
	}
	ResetAgents();
}


//重置agents
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
		Action[agentID]=rand()%NumberofActions;
	}else
	{
		int x,y,z,m=0;
		double qtmp[NumberofActions*NumberofActions*NumberofActions*NumberofActions]={0};
		for(int i=0;i<NumberofActions;i++)
		{
			for(int j=0;j<NumberofActions;j++)
			{
				for(int k=0;k<NumberofActions;k++)
				{
					for(int p=0;p<NumberofActions;p++)
					{
							qtmp[m]=Qtable[agentID][CurrentPos][i][j][k][p];
						    m++;
							
					}
					
				}
			}
		}
		int maxnum=ArgMax(qtmp,NumberofActions*NumberofActions*NumberofActions*NumberofActions);
		Action[agentID]=maxnum/(NumberofActions*NumberofActions*NumberofActions);
	}

}

//对手选择动作，不能每个动作都随机，不然很容易被打败
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

}

//产生动作之后获得新的state
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

//更新Q值
void Agent::UpdateQvalue(int agentID,double reward)
{
	double Qvalue[NumberofActions*NumberofActions*NumberofActions*NumberofActions]={0};
	double NextMaxQ;
	int t=0;
	for(int i=0;i<NumberofActions;i++)
	{
		for(int j=0;j<NumberofActions;j++)
		{
			for(int k=0;k<NumberofActions;k++)
			{
				for(int p=0;p<NumberofActions;p++)
				{
					
						Qvalue[t]=Qtable[agentID][NextPos][i][j][k][p];
				        t++;
								
				}
			}
		}
	}
	NextMaxQ=Qvalue[ArgMax(Qvalue,NumberofActions*NumberofActions*NumberofActions*NumberofActions)];
	Qtable[agentID][CurrentPos][Action[0]][Action[1]][Action[2]][Action[3]]+=(double)alphas*(reward+Gamma*NextMaxQ-Qtable[agentID][CurrentPos][Action[0]][Action[1]][Action[2]][Action[3]]);
}


void Agent::TakeAction()
{
	CurrentPos=NextPos;
}


bool Agent::Simulator()
{
	if(NextPos>CurrentPos)
	{
		return true;
	}else if(NextPos<=CurrentPos)
	{
		return false;
	}
}