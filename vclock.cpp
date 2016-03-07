#include<iostream>
#include<conio.h>
#include<cstdlib>
#include "Solver.h"

using namespace std;

class VClock : public Solver<int>
{
	int initialTime, finalTime, clockFormat, configTime;
	vector<int> setTime;
	
public : 
	
	VClock(int inTime, int fiTime, int clFormat, vector<int> sTime)
	{
		initialTime = inTime;
		finalTime = fiTime;
		clockFormat = clFormat;
		setTime = sTime;
	};
	
	vector<int> FetchNextConfiguration(int config)
	{
		vector<int> configVector;
		int newConfig;

		for(int i = 0; i < setTime.size(); ++i)
		{
			newConfig = config + setTime[i];
			if(newConfig > clockFormat)
			{
				newConfig -= clockFormat;
			}
			else if(newConfig <= 0)
			{
				newConfig += clockFormat;
			}
			configVector.push_back(newConfig);
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

int main(int argc, char *argv[])
{
	int initialTime, finalTime, clockFormat;
	vector<int> setTime;
	 
	clockFormat = atoi(argv[1]);
	initialTime = atoi(argv[2]);
	finalTime = atoi(argv[3]);

	for(int i = 4; i < argc; ++i) 
	{
		setTime.push_back(atoi(argv[i]));
	}

	VClock c(initialTime, finalTime, clockFormat, setTime);
	
	c.solveProblem(); 

	getch();
}