#include "Prepare.h"

class Agent
{	
	private:
		int	StartPos;
		int			Action[AgentNumber];
		int			OAction[AgentNumber];
		double		Resultant[2];
		double		Qtable[AgentNumber][Resolution][NumberofActions];
		double		Probability[AgentNumber][Resolution][NumberofActions];
		double		AProbability[AgentNumber][Resolution][NumberofActions];
		int			VisitedTimes[AgentNumber][Resolution];
		
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
		void OUpdateQvalue(int agentID,double reward);
		void UpdateProbability(int agentID);
		void TakeAction();
		void OTakeAction();
		bool Simulator();
};