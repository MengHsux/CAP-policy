#include <iostream> 
#include <cstdlib>
#include <queue> 
#include "CAP.h"

using namespace std;


Agent::Agent(int SP)
{
	srand (time(NULL));
	StartPos=SP;
	for (int i=0;i<AgentNumber;i++)
	{
		MaxTD[i] = 0;
		MinTD[i] = 150;
	}
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
						Cooperationprobability[i][j][k][ps][qs]=1.0;
				        Selectedtimes[i][j][k][ps][qs]=0;

					}
					
				}
				
			}
		}
	}
	for(int a=0;a<AgentNumber;a++)
	{
		for(int i=0;i<Resolution;i++)
		{
			for(int j=0;j<NumberofActions;j++)
			{
				Qtable[a][i][j]=10;
				OQtable[a][i][j]=10;
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
		std::queue<CandidateAction> CA,A;
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
						//取绝对值防止数值为负数
						switch(m)
						{
						case 0:
							INDvalue[i][j][k][ps][qs].q[m]=abs(Qtable[m][CurrentPos][i]*Cooperationprobability[i][j][k][ps][qs]);
							break;
						case 1:
							INDvalue[i][j][k][ps][qs].q[m]=abs(Qtable[m][CurrentPos][j]*Cooperationprobability[i][j][k][ps][qs]);
							break;
						case 2:
							INDvalue[i][j][k][ps][qs].q[m]=abs(Qtable[m][CurrentPos][k]*Cooperationprobability[i][j][k][ps][qs]);
							break;
						case 3:
							INDvalue[i][j][k][ps][qs].q[m]=abs(Qtable[m][CurrentPos][ps]*Cooperationprobability[i][j][k][ps][qs]);
							break;
						case 4:
							INDvalue[i][j][k][ps][qs].q[m]=abs(Qtable[m][CurrentPos][qs]*Cooperationprobability[i][j][k][ps][qs]);
							break;

						}
						INDvalue[i][j][k][ps][qs].axioms+=INDvalue[i][j][k][ps][qs].q[m];
						INDvalue[i][j][k][ps][qs].var*=(INDvalue[i][j][k][ps][qs].q[m]-LoseReward);
					}
					if(fabs(INDvalue[i][j][k][ps][qs].axioms-MAXaxioms)<=fabs(MAXaxioms*VARS))
					{
						tmp.a[0]=i;
						tmp.a[1]=j;
						tmp.a[2]=k;
						tmp.a[3]=ps;
						tmp.a[4]=qs;
						CA.push(tmp);
					}else if(INDvalue[i][j][k][ps][qs].axioms>MAXaxioms)
					{
						MAXaxioms=INDvalue[i][j][k][ps][qs].axioms;
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
		for(int i=0; i<CA.size();i++)
		{
			tmp=CA.front();
			if(fabs(INDvalue[tmp.a[0]][tmp.a[1]][tmp.a[2]][tmp.a[3]][tmp.a[4]].var-MAXvar)<=fabs(MAXvar*0.0))
			{
				A.push(tmp);
			}else if(INDvalue[tmp.a[0]][tmp.a[1]][tmp.a[2]][tmp.a[3]][tmp.a[4]].var>MAXvar)
			{
				MAXvar=INDvalue[tmp.a[0]][tmp.a[1]][tmp.a[2]][tmp.a[3]][tmp.a[4]].var;
				while (!A.empty())
				{
					A.pop();
				}
				A.push(tmp);
			}
			CA.pop();
		}
		int mi=rand()%A.size();
		for(int i=0; i<mi;i++)
		{
			A.pop();
		}
		tmp=A.front();
		for(int ag=0; ag<AgentNumber;ag++)
		{
			Action[ag]=tmp.a[ag];
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

double Agent::GetmaxTD(int ID)
{
	return MaxTD[ID];
}

double Agent::GetminTD(int ID)
{
	return MinTD[ID];
}

double Agent::GetTD(int ID)
{

	return QTD[ID];
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

void Agent::UpdateQvalue(int agentID,double reward)
{
	double Qvalue[NumberofActions]={0};
	double NextMaxQ;
	for(int i=0;i<NumberofActions;i++)
	{
		Qvalue[i]=Qtable[agentID][NextPos][i];
	}
	NextMaxQ=Qvalue[ArgMax(Qvalue,NumberofActions)];
	//Get TD error
	double TDerror = reward+Gamma*NextMaxQ-Qtable[agentID][CurrentPos][Action[agentID]];
	QTD[agentID] =  TDerror;  //Get TD error ID-th agent
	if (TDerror>MaxTD[agentID])
	{
		MaxTD[agentID]  = TDerror;
	}
	if (TDerror<MinTD[agentID])
	{
		MinTD[agentID]  = TDerror;
	}

	Qtable[agentID][CurrentPos][Action[agentID]]+=(double)alphas*(reward+Gamma*NextMaxQ-Qtable[agentID][CurrentPos][Action[agentID]]);
}

void Agent::UpdateCooperationprobability(bool Cooperation)
{
	Selectedtimes[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]++;
	if(Cooperation)
	{
		if(Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]<1)
		{
			Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]+=(1-Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]])/Selectedtimes[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]];
		}
	}else{
		if(Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]>0.1)
		{
			Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]+=(0-Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]])/Selectedtimes[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]];
		}
		if(Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]<0.1)
		{
			Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]=0.1;
		}
	}
	if(Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]>1 || Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]<0.1)
	{
		cout<<Cooperationprobability[Action[0]][Action[1]][Action[2]][Action[3]][Action[4]]<<endl;
		cout<<"Cooperationprobability error"<<endl;
		system("pause");
	}
}

void Agent::TakeAction()
{
	CurrentPos=NextPos;
}