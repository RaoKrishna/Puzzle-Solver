Puzzle Solver - Version 1.3
==============================

No changes were made to the Solver class.
Following new class was added to implement the variant clock puzzle : 

1. VClock
-------------

This accepts arbitrary number of arguments. First argument is No of hours on the clock, second is initial time, third is final time and rest of the arguments are the time by which the clock can be moved forward or back. If no arguments are given, clock hands cannot be moved. Next configuration is computed by moving the clock hands forward or backward by the specified time. This algorithm generates the minimum steps to be taken to generate the result.

Execution result : 
-----------------------

12 10 8 3 -3 4

Solution for the puzzle ==>

10 2 11 8

------------------------------------------------------------ END ------------------------------------------------------------------------


Puzzle Solver - Version 1.2
==============================

No changes were made to the Solver class.
Following new class was added to implement the Lloyd puzzle : 

1. Lloyd
------------
The user gives two commandline inputs to the program, 1st is the input method and the 2nd wil be the output method.
These methods indicate the way in which the user gives the input and gets the output. These methods are:
1) standard input/output:
	The standard input/output is indicated using the "-"
	Input:
	When the command line 1st input is "-" this means that the input is to be taken from the user at the time the program is being run.
	In this case the user is prompted to give the input.
	Output:
	When the command line 2nd input is "-" this means that the output is to be shown as standard output after the program is executed.
	

2) file
	The file input/output is indicated by giving the file name to be used for input or output
	Input:
	When the command line 1st input is a filename this means that the input is to be taken from the file indicated by the filename at the time the program is being run.
	Output:
	When the command line 2nd input is a filename this means that the output is to be written in the file indicate by  the filename after the program is executed.
	
Execution result : 
-----------------------

- -

Enter width and height : 
4 1
Enter initial config : 
..xy
Enter final config : 
xy..

Solution for the puzzle is ==> 

. . x y 

. x . y 

. x y . 

x . y . 

x y . . 

Puzzle processed successfully !

------------------------------------------------------------ END ------------------------------------------------------------------------

Puzzle Solver - Version 1.1
==============================

Following changes were made in the application in this version : 

The Solver class has been templated to accept puzzles invloving any datatype. The new Solver class declaration looks like : 

template<class classType>class Solver

The corresponding changes in the methods have been made. The method declaration looks like : 

FetchNextConfiguration(classType config)
CheckGoal(classType config)

The implementation of these methods remain the same in Clock class.

Another change that has been made is that the Display() method has been made pure virtual and its implementation depends on the individual puzzle classes. The method declaration looks like : 

virtual void Display(list<classType> result) = 0;

This method accepts list of the configurations to be displayed.

The Solver class also handles the puzzles for which no solution is possible. If such a puzzle is encountered, the puzzle will give out the message that no solution exists for the given puzzle.

===================================
Individual puzzle class used : 
====================================

1. Clock
---------------

It now implements the display method which accepts list of integers to be displayed.

2. Water
---------------

This class contains the main method for running the water puzzle. It can accept "n" no of arguments. The first argument is the quantity of water to be obtained and the following arguments represent the available jugs. Depending on the quantity of the water present in the jug, water can be transferred into another jug, another jug can be emptied, this jug can be emptied or water can be added to this jug. These represent the different configurations possible for a given configuration. 

Execution result : 
-----------------------

4 3 5

Solution of the puzzle is ==>

0 0
0 5
3 2
0 2
2 0
2 5
3 4

------------------------------------------------------------ END ------------------------------------------------------------------------

Puzzle Solver - Version 1.0
==============================

This application can be used to solve any puzzle involving integer values. The application takes a puzzle as an input and gives the series of configurations needed to reach the final output.

Parent class implementing the solution : Solver.cpp

Design :

The Solver class is responsible for generating the output and solving the puzzle. It is an abstract class and contains the following 3 virtual methods : 

1. FetchInitialConfiguration()
=================================

This function is implemented by every individual puzzles and the objective of this function is to fetch the initial state of the puzzle. 

2. FetchNextConfiguration(int config)
=========================================

For a given configuration, this function returns all the possible configurations that can be achieved in the next step. It returns a vector holding all the possible configurations.

3. CheckGoal(int config)
===========================

This method serves as the endpoint of the problem solving mechanism. As the name suggests, this function checks if the given configuration is the goal of the puzzle. 

This class also implements 2 methods. They are : 

1. solveProblem()
====================

This is the primary method. It constitutes the puzzle solving logic required by the Solver. It contains a  queue(configurations) for holding all the possible configurations, a vector(configVector) for containing the next possible configurations that is returned by an individual puzzle, a map(configMap) that holds all the configurations along with its parent config, a list(resultConfig) containing the output config and an iterator(iter) for iterating through the map.

This function calls the function FetchInitialConfiguration() to fetch the initial state of the puzzle. This method will always return a single value and it will be inserted into the queue. This is also inserted into the map. The key of the map contains the value that is inserted into the queue and its value contains the parent element that generated this configuration. 

The program tries to reach the goal till the queue is not empty. The head of the queue is popped and this popped element is checked for goal. If that is the final configuration, the program stops searching. If the element is not a goal, it calls FetchNextConfiguration(int config) function. This method returns the vector of integers representing the next possible configurations. These are then inserted into the queue and the map. The configuration returned from the function becomes the key while config becomes the value n the map. The iteration continues with the newly added values in the queue.

Once the goal is achieved the next step is to find the print the series of configurations taken to reach the goal. This is achieved by tracking the parent element which generated the goal configuration. It is stored in the value of the goal element in the map. This parent element is then looked up in the map and its parent is tracked. This process continues till it reaches the initial configuration. As the program iterates through the elements in the map, it adds the subsequent elements in the list. This list will then be used to display the series of configurations.

2. Display()
================

This method displays the series of configurations needed to reach the goal from the initial configuration.
The function iterates through the list and prints each value contained in the list.

===================================
Individual puzzle class used : 
====================================

1. Clock
---------------

The primary actions of this class are providing initial configuration, next configurations and checking if the give configuration is the goal.
It extends the Solver class and also contains the main() method. It accepts 3 arguments viz. the number of hours on the dial, initial time and the final time to be displayed.

Initial time is the intial configuration for this puzzle. For a given configuration, it fetches the 2 possible and logical configurations by simply adding and subtracting 1 from the given config.

Execution result : 
-----------------------

12 9 4

Solution for the puzzle is ==> 
9 8 7 6 5 4


 
