#include "Prepare.h"

class Agent
{	
	private:
		int	StartPos;
		int			Action[AgentNumber];
		int			OAction[AgentNumber];
		double		Resultant[2];
		double      MaxTD[AgentNumber]; //最大的TD error for each agent
		double      MinTD[AgentNumber]; //最小的TD error for each agent
		double      QTD[AgentNumber]; //TD error for each agent
		double		Qtable[AgentNumber][Resolution][NumberofActions];
		double		OQtable[AgentNumber][Resolution][NumberofActions];
		double		Cooperationprobability[NumberofActions][NumberofActions][NumberofActions][NumberofActions][NumberofActions]; //五个智能体
		int			Selectedtimes[NumberofActions][NumberofActions][NumberofActions][NumberofActions][NumberofActions];
	public:
		int FixedRope[Resolution];
		bool Succeed, Fail;
		int	CurrentPos;
		int	NextPos;
		Agent(int SP);
		//获取最大与最小的TD error for each agent
		double GetmaxTD(int ID);
		double GetminTD(int ID);
		double GetTD(int ID);
		void ResetAll();
		void ResetAgents();
		void ChooseAction();
		void OChooseAction();
		void GetResultant();
		void UpdateQvalue(int agentID,double reward);
		void OUpdateQvalue(int agentID,double reward);
		void UpdateCooperationprobability(bool Cooperation);
		void TakeAction();
		void OTakeAction();
		/*void GetTile(int agentID,int* x,int* y,int* z,bool ThisState);*/
		bool Simulator();
};