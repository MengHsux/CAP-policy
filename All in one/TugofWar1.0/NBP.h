#include "Prepare.h"

class Agent
{	
	private:
		int	StartPos;
		int			Action[AgentNumber];
		int			OAction[AgentNumber];
		double		Resultant[2];
		double		Qtable[AgentNumber][Resolution][NumberofActions][NumberofActions][NumberofActions][NumberofActions][NumberofActions];
	public:
		int FixedRope[Resolution];
		bool Succeed, Fail;
		int	CurrentPos;
		int	NextPos;
		Agent(int SP);
		void ResetAll();
		void ResetAgents();
		void ChooseAction();
		void OChooseAction();
		void GetResultant();
		void UpdateQvalue(int agentID,double reward);
		void OUpdateQvalue(int agentID,double reward);
		void TakeAction();
		void OTakeAction();
		bool Simulator();
};