#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<fstream>
#include<string>
#include "Solver.h"

using namespace std;

class Lloyd : public Solver<vector<char>>
{

public :
	
	int width, height;
	vector<char> initConfigVector;
	vector<char> finalConfigVector;
	bool fromFile;
	ostream *osp;
	Lloyd(int w, int h, vector<char> initConf, vector<char> finalConf, ostream *ospInput)
	{
		width = w;
		height = h;
		initConfigVector = initConf;
		finalConfigVector = finalConf;
		osp = ospInput;
	}

	vector<vector<char>> FetchNextConfiguration(vector<char> inputConfig)
	{
		vector<vector<char>> configVector;
		char temp;
		int rowIndex, columnIndex;
		vector<char> tempChar;
		tempChar = inputConfig;

		for(int index = 0; index < initConfigVector.size(); ++index)
		{
			if(canSlideLeft(index, tempChar))
			{
				temp = tempChar[index - 1];
				tempChar[index - 1] = tempChar[index];
				tempChar[index] = temp;

				configVector.push_back(tempChar);

				tempChar = inputConfig;
			}
			if(canSlideRight(index, tempChar))
			{
				temp = tempChar[index + 1];
				tempChar[index + 1] = tempChar[index];
				tempChar[index] = temp;

				configVector.push_back(tempChar);

				tempChar = inputConfig;
			}
			if(canSlideUp(index, tempChar))
			{
				temp = tempChar[index - width];
				tempChar[index - width] = tempChar[index];
				tempChar[index] = temp;

				configVector.push_back(tempChar);

				tempChar = inputConfig;
			}
			if(canSlideDown(index, tempChar))
			{
				temp = tempChar[index + width];
				tempChar[index + width] = tempChar[index];
				tempChar[index] = temp;

				configVector.push_back(tempChar);

				tempChar = inputConfig;
			}
		}

		return configVector;
	}

	bool CheckGoal(vector<char> config)
	{
		bool retValue = true;

		for(int i = 0; i < config.size(); ++i)
		{
			if(config.at(i) != finalConfigVector.at(i))
			{
				retValue = false;
				break;
			}
		}

		return retValue;
	}
	   
	vector<vector<char>> FetchInitialConfiguration() 
	{
		vector<vector<char>> initConfig;
		
		initConfig.push_back(initConfigVector);
		return initConfig;
	}

	bool canSlideLeft(int index, vector<char> config)
	{
		return ((index % width != 0) && config[index - 1] == '.');
	}

	bool canSlideRight(int index, vector<char> config)
	{
		return (((index + 1) % width != 0) && config[index + 1] == '.');
	}

	bool canSlideUp(int index, vector<char> config)
	{
		return ((index - width > 0) && config[index - width] == '.');
	}

	bool canSlideDown(int index, vector<char> config)
	{
		return ((index + width < initConfigVector.size()) && config[index + width] == '.');
	}

	void Display(list<vector<char>> result)
	{
		vector<char> config;
		int index;
		ostream &os = *osp;
		os << "Solution for the puzzle is ==> " << endl;
		os << endl;

		for(list<vector<char>>::iterator iter = result.begin(); iter != result.end(); iter++)
		{
			config = *iter;
			index = 0;
			for(int  i = 0; i < height; i++)
			{
				for(int  j = 0; j < width; j++)
				{
					os << config.at(index++) << " ";
				}
				os << endl;
			}
			os << endl;
		}
	}
};

/*int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cerr << "2 args only." << endl;
	}
	else
	{
		istream *isp;
		ifstream ifs;
		ostream *osp;
		ofstream ofs;

		if(argv[1][0] == '-' && argv[1][1] == '\0')
		{
			isp = &cin;
		}
		else
		{
			ifs.open(argv[1]);
			isp = &ifs;
		}
		istream &is = *isp;

		if(argv[2][0] == '-' && argv[2][1] == '\0')
		{
			osp = &cout;
		}
		else
		{
			ofs.open(argv[2]);
			osp = &ofs;
		}
		ostream &os = *osp;
		
		int height, width;
		
		string line;
		if(argv[1][0] == '-')
		{
			cout << "Enter width and height : " << endl;
		}
			is >> width;
			is >> height;
		if(argv[1][0] == '-')
		{
			cout<<"enter initial config:"<<endl;
		}
		vector<char> initConf;
		vector<char> finalConf;

		for(int i = 0; i < height; i++)
		{
			is >> line;
			for(int  j = 0 ; j < line.size(); ++j)
			{
				initConf.push_back(line[j]);
			}
		}

		if(initConf.size() > (height * width))
		{
			cout << "Invalid input" << endl;
		}
		else
		{
			if(argv[1][0] == '-')
			{
				cout<<"enter final config:"<<endl;
			}
			for(int i = 0; i < height; i++)
			{
				is >> line;
				for(int  j = 0 ; j < line.size(); ++j)
				{
					finalConf.push_back(line[j]);
				}
			} 

			if(finalConf.size() > (height * width))
			{
				cout << "Invalid input" << endl;
			}
			else
			{
				Lloyd l(width, height, initConf, finalConf, osp);
				l.solveProblem();

				cout << "Puzzle processed successfully ! " << endl;
			}
		}
	}
	getch();
}*/