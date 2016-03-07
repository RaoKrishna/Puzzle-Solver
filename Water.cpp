#include<iostream>
#include<conio.h>
#include<cstdlib>
#include "Solver.h"

using namespace std;

vector<vector<int>> TransferWater(vector<int> configJug, int index);

class Water : public Solver<vector<int>>
{
	int finalCapacity;
	vector<int> jugVector;
	vector<int> currentConfig;
	
public :

	Water(int capacity, vector<int> jugCapacity) : finalCapacity(capacity), jugVector(jugCapacity)
	{
	}
	
	vector<vector<int>> FetchNextConfiguration(vector<int> config)
	{
		vector<vector<int>> configVector;
		vector<int> intConfig;
		int amount;
		
		for(int i = 0; i < config.size(); ++i)
		{
			intConfig = config;
				
			if(intConfig[i] != jugVector[i])
			{
				intConfig.at(i) = jugVector.at(i);
				configVector.push_back(intConfig);
				intConfig = config;
			}
			if(intConfig[i] != 0)
			{
				intConfig.at(i) = 0;
				configVector.push_back(intConfig);
				intConfig = config;
			}
			for(int j = 0; j < config.size(); ++j)
			{
				if(i != j)
				{
					 amount = min(config[i], jugVector[j] - config[j]);
					 intConfig = config;
					 intConfig[i] -= amount;
					 intConfig[j] += amount;
					 configVector.push_back(intConfig);
				}
			}
		}

		return configVector;
	}

	bool CheckGoal(vector<int> config)
	{
		bool retValue = false;
		for(vector<int>::iterator iter = config.begin(); iter != config.end(); iter++)
		{

			if(*iter == finalCapacity)
			{
				retValue = true;
				break;
			}
		}
		return retValue;
	}
	   
	vector<vector<int>> FetchInitialConfiguration() 
	{
		vector<vector<int>> configVector;
		for(vector<int>::iterator iter = jugVector.begin(); iter != jugVector.end(); iter++)
		{
			currentConfig.push_back(0);
		}
		configVector.push_back(currentConfig);

		return configVector;
	}

	void Display(list<vector<int>> result)
	{
		cout << "Solution for the puzzle is ==> " << endl;
		vector<int> config;
		for(list<vector<int>>::iterator iter = result.begin(); iter != result.end(); iter++)
		{
			config = *iter;
			for(int j = 0; j < config.size(); j++)
			{
				cout << config.at(j) << " ";
			}
			cout << endl;
		}
	}

};

//int main(int argc, char *argv[])
//{
//	int finalCapacity;
//	vector<int> jugVector;
//	 
//	finalCapacity = atoi(argv[1]);
//
//	for(int i = 2; i < argc; i++)
//	{
//		jugVector.push_back(atoi(argv[i]));
//	}
//
//	Water w(finalCapacity, jugVector);
//	w.solveProblem();
//
//	getch();
//}