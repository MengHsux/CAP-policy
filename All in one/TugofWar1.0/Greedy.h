#include "Prepare.h"

//��NB���ƶ������Ա
class Agent
{	
	private:
		int	StartPos;
		int			Action[AgentNumber];
		int			OAction[AgentNumber];
		double		Resultant[2];
		//Q�����Ҫ������������������仯
		double		Qtable[AgentNumber][Resolution][NumberofActions][NumberofActions][NumberofActions][NumberofActions];
	public:
		int FixedRope[Resolution];
		bool Succeed, Fail;
		int	CurrentPos;
		int	NextPos;

		Agent(int SP);

		void ResetAll();
		void ResetAgents();
		void ChooseAction(int agentID);
		void OChooseAction();
		void GetResultant();

		void UpdateQvalue(int agentID,double reward);
		void TakeAction();
		bool Simulator();
};