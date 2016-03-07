#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<list>

using namespace std;

template<class classType>class Solver
{
public :
	queue<classType> configurations;
	vector<classType> configVector;
	map<classType, classType> configMap;
	list<classType> resultConfig;
	typename map<classType, classType> :: iterator iter;

	void solveProblem()
	{
		bool goalAchieved = false;
		classType goal, initialConfig;
		configVector = FetchInitialConfiguration();

		initialConfig = configVector.front();
		configurations.push(initialConfig);

		configMap[initialConfig] = initialConfig;
		
		while(!configurations.empty())
		{
			classType config = configurations.front();
			
			configurations.pop();
			
			if(!CheckGoal(config))
			{
				configVector = FetchNextConfiguration(config);
				while(!configVector.empty())
				{
					classType element = configVector.back();
					if(configMap.count(element) == 0)
					{
						configurations.push(element);
						configMap[element] = config;
					}
					configVector.pop_back();
				}
			}
			else
			{
				goal = config;
				goalAchieved = true;
				break;
			}
		}

		if(goalAchieved)
		{
			resultConfig.push_front(goal);

			iter = configMap.find(goal);

			classType val = iter->second;

			while(val != initialConfig)
			{
				resultConfig.push_front(val);
				iter = configMap.find(val);
				val = iter->second;
			}

			if(goal != initialConfig)
			{
				resultConfig.push_front(val);
			}

			Display(resultConfig);
		}
		else
		{
			cout << "There is no solution for this puzzle! " << endl;
		}
	}

	virtual vector<classType> FetchInitialConfiguration() = 0;
	
	virtual vector<classType> FetchNextConfiguration(classType config) = 0;

	virtual bool CheckGoal(classType config) = 0;

	virtual void Display(list<classType> result) = 0;
};