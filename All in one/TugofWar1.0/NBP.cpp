#include <iostream> 
#include <cstdlib>
#include <queue> 
#include "NBP.h"

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
			for(int j=0;j<NumberofActions;j++)
			{
				for(int k=0;k<NumberofActions;k++)
				{
					for(int l=0;l<NumberofActions;l++)
					{
						for(int ps=0;ps<NumberofActions;ps++)
						{
							for(int qs=0;qs<NumberofActions;qs++)
							{
						        Qtable[a][i][j][k][l][ps][qs]=10;
						       
							}
						}
					}
				}
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

void Agent::ChooseAction()
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
		std::queue<CandidateAction> CA;
		CandidateAction tmp;
		double MAXaxioms=-99999,MAXvar=-99999;
		payoff INDvalue[NumberofActions][NumberofActions][NumberofActions][NumberofActions][NumberofActions];
		for(int i=0;i<NumberofActions;i++)
		{
			for(int j=0;j<NumberofActions;j++)
			{
				for(int k=0;k<NumberofActions;k++)
				{
				  for(int ps=0;ps<NumberofActions;ps++)
				  {
					for(int qs=0;qs<NumberofActions;qs++)
					{
					INDvalue[i][j][k][ps][qs].axioms=0;
					INDvalue[i][j][k][ps][qs].var=1;
					for(int m=0;m<AgentNumber;m++)
					{
						switch(m)
						{
						case 0:
							  INDvalue[i][j][k][ps][qs].q[m]=Qtable[m][CurrentPos][i][j][k][ps][qs];
							  break;
						    case 1:
							  INDvalue[i][j][k][ps][qs].q[m]=Qtable[m][CurrentPos][j][j][k][ps][qs];
							  break;
						    case 2:
							  INDvalue[i][j][k][ps][qs].q[m]=Qtable[m][CurrentPos][k][j][k][ps][qs];
							  break;
							case 3:
							  INDvalue[i][j][k][ps][qs].q[m]=Qtable[m][CurrentPos][ps][qs][i][j][k];
							  break;
							case 4:
							  INDvalue[i][j][k][ps][qs].q[m]=Qtable[m][CurrentPos][ps][qs][j][j][k];
							  break;
						}
						INDvalue[i][j][k][ps][qs].axioms+=INDvalue[i][j][k][ps][qs].q[m]; 
						INDvalue[i][j][k][ps][qs].var*=(INDvalue[i][j][k][ps][qs].q[m]-LoseReward); //这个var就相当于以前的axioms

					}
					if(fabs(INDvalue[i][j][k][ps][qs].var-MAXvar)<=fabs(MAXvar*0.0))
					{
						tmp.a[0]=i;
						tmp.a[1]=j;
						tmp.a[2]=k;
						tmp.a[3]=ps;
						tmp.a[4]=qs;
						CA.push(tmp);
					}else if(INDvalue[i][j][k][ps][qs].var>MAXvar)
					{
						MAXvar=INDvalue[i][j][k][ps][qs].var;
						while (!CA.empty())
						{
							CA.pop();
						}
						tmp.a[0]=i;
						tmp.a[1]=j;
						tmp.a[2]=k;
						tmp.a[3]=ps;
						tmp.a[4]=qs;
						CA.push(tmp);
					}
				}
			}
		}
	}
}
		int mi=rand()%CA.size();
		for(int i=0; i<mi;i++)
		{
			CA.pop();
		}
		tmp=CA.front();
		for(int ag=0; ag<AgentNumber;ag++)
		{
			Action[ag]=tmp.a[ag];
		}
	}
}

//随机选择动作
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

//判断智能体之间是否协同，在相同的时刻产生动作
bool Agent::Simulator()
{
	for(int ag=0; ag<AgentNumber;ag++)
	{
		if(Action[ag]!=Action[(ag+1)%AgentNumber])
		{
			return false;
		}
	}
	return true;
	
}

void Agent::UpdateQvalue(int agentID,double reward)
{
	double Qvalue[NumberofActions*NumberofActions*NumberofActions*NumberofActions*NumberofActions]={0};
	double NextMaxQ;
	int t=0;
	for(int i=0;i<NumberofActions;i++)
	{
		for(int j=0;j<NumberofActions;j++)
		{
			for(int k=0;k<NumberofActions;k++)
			{
				for(int ps=0;ps<NumberofActions;ps++)
				{
					for(int qs=0;qs<NumberofActions;qs++)
					{
						
				      Qvalue[t]=Qtable[agentID][NextPos][i][j][k][ps][qs];
				      t++;
					}
				}
			}
		}
	}
	NextMaxQ=Qvalue[ArgMax(Qvalue,NumberofActions*NumberofActions*NumberofActions*NumberofActions*NumberofActions)];
	Qtable[agentID][CurrentPos][Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]+=(double)alphas*(reward+Gamma*NextMaxQ-Qtable[agentID][CurrentPos][Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]);
}

void Agent::TakeAction()
{
	CurrentPos=NextPos;
}