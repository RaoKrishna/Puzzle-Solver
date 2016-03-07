#include<iostream>
#include<conio.h>
#include<cstdlib>
#include "Solver.h"

using namespace std;

class Clock : public Solver<int>
{
	int initialTime, finalTime, clockFormat, configTime;
	
public :
	
	Clock(int inTime, int fiTime, int clFormat)
	{
		initialTime = inTime;
		finalTime = fiTime;
		clockFormat = clFormat;
	};
	
	vector<int> FetchNextConfiguration(int config)
	{
		vector<int> configVector;
		if(config == 1) 
		{
			configVector.push_back(config + 1);
			configVector.push_back(clockFormat);
		}
		else if(config == clockFormat)
		{
			configVector.push_back(1);
			configVector.push_back(config - 1);
		}
		else
		{
			configVector.push_back(config + 1);
			configVector.push_back(config - 1);
		}

		return configVector;
	}

	bool CheckGoal(int config)
	{
		return config == finalTime;
	}
	   
	vector<int> FetchInitialConfiguration() 
	{
		vector<int> configVector;
		configVector.push_back(initialTime);

		return configVector;
	}

	void Display(list<int> result)
	{
		cout << "Solution for the puzzle is ==> " << endl;
		for(list<int>::iterator iter = result.begin(); iter != result.end(); iter++)
		{
			cout << *iter << " ";
		}
	}
};

//int main(int argc, char *argv[])
//{
//	int initialTime, finalTime, clockFormat;
//	 
//	clockFormat = atoi(argv[1]);
//	initialTime = atoi(argv[2]);
//	finalTime = atoi(argv[3]);
//
//	Clock c(initialTime, finalTime, clockFormat);
//	
//	c.solveProblem(); 
//
//	getch();
//}