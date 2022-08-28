#include <iostream> 
#include <cstdlib>
#include "Prepare.h"
#include "CAP.h"
#include "FuzzyMethod.h"
using namespace std; 

int Startpos=10,Goalpos=20;
Agent *agents;
//In this cpp, we can add different header files to implement different methods.
int main()
{
	//定义agent
	agents=new Agent(Startpos);
	bool EpFail;
	int step,RecordCooperation,tempstep;
	FuzzyMethod fuzzy;   //Fuzzy logic agent
	//start training
	for(int av=0 ;av<AverageTime;av++)
	{
		agents->ResetAll();
		step=0;
		tempstep=0;
		for(int ep=0 ;ep <TotalEpisode; ep++)
		{
			EpFail=false;
			RecordCooperation=0;
			cout.setf(ios::fixed);
			cout<<"\r"<<"progress rate:"<<((double)ep/(double)TotalEpisode)*100<<"% | "<< av+1 <<"";
			for(double i=0 ;i<1 ; i=i+0.05)
			{
				if(i<((double)ep/(double)TotalEpisode))
				{
					cout<<"";
				}else{
					cout<<"  ";
				}
			}
			cout<<"";
			agents->ResetAgents();
			while((!agents->Succeed)&&(!agents->Fail)&&(!EpFail))
			{
				agents->ChooseAction();
				agents->OChooseAction();
				agents->GetResultant();
				bool Cooperation=agents->Simulator();
				double reward;
				if(!Cooperation)
				{
					RecordCooperation++;
					reward=CantCooperation;
					if(agents->NextPos==0)
					{
						agents->Fail=true;
						reward=LoseReward;
					}else if(agents->NextPos==Goalpos)
					{
						agents->Succeed=true;
						reward=WinReward;
					}else
					{
						reward=DrawReward;
					}
				}else
				{
					if(agents->NextPos==Goalpos)
					{
						reward=WinReward;
						agents->Succeed=true;
					}else if(agents->NextPos==0)
					{
						reward=LoseReward;
						agents->Fail=true;
					}else
					{
						reward=DrawReward;
					}

				}
				for(int ag=0; ag<AgentNumber;ag++)
				{
					
					agents->UpdateQvalue(ag,reward);
					
				}
				agents->UpdateCooperationprobability(Cooperation);
				agents->TakeAction();
				if(step>=MaxStepNum)
				{
					EpFail=true;
				}
			}
			if(agents->Succeed)
			{
				step++;
			}else if(agents->NextPos>Startpos)
			{
				step++;
			}
			if((ep+1)%10==0)
			{
				cout << (double)(step - tempstep) / (double)10 << " ";
				tempstep=step;
			}

			//调整 var
			double TDS[5]={0};
			for (int i=0;i<5;i++)
			{
				TDS[i] = agents->GetTD(i);
				TDS[i] = TDS[i];

			}

			//We can use different schemes to adjust the size of the candidate action space
			// agents->VASS = fuzzy.FuzzyMeth(TDS[0]);  //The fuzzy method adjusts the size of the candidate action space
		}
		cout << endl;
		cout << (double)step / (double)TotalEpisode << endl;
	}
	//释放agent
	free(agents);
	return 0;
}