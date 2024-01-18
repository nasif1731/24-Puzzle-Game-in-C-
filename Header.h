#pragma once

#include<iostream>
#include<iomanip>
#include<windows.h>
#include<fstream>
#include<ctime>
using namespace std;
int const_array[5][5];
char attempt[1000];
int counter = 0;
void initi(int init_state[5][5])			//for initializing the initial state
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 5; i++)				//initializing the initial state array to 0 for avoiding garbage values
	{
		for (int j = 0; j < 5; j++)
		{
			init_state[i][j] = 0;
		}
	}
	for (int i = 0; i < 5; i++)			
	{
		for (int j = 0; j < 5; )
		{
			int k, l, count = 0;
			init_state[i][j] = rand() % 25 + 1;			//random values
			for (k = 0; k < 5; k++)
			{
				for (l = 0; l < 5; l++)
				{
					if (init_state[i][j] == init_state[k][l])
					{
						count++;
					}
				}
			}
			if (count == 1)			//for generating unique values on each index of array
			{
				j++;
			}
		}
	}
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			const_array[i][j] = init_state[i][j];			//here const_array will remain same throughout the program

															//will only change initial array for updating moves
		}
		cout << endl;
	}
	
}
void change(int goalState[5][5], int init_state[5][5])			//for printing all states when  function is called
{																		//initial state(const_array)
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);							//goal state
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);	//updated state(status)
	cout << setw(25) << "***INITIAL STATE***" << endl << endl << setw(3);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (const_array[i][j] == 25)		//const_array printing
			{
				cout << "|" <<setw(3)<< " " << "|"<<setw(3);


			}
			else
			cout << "|" << setw(3)<< const_array[i][j] << "|" << setw(3);

		}
		cout << endl;
	}
	cout << endl;
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);				//giving colours
	cout << setw(25) << "****GOAL STATE****" << endl << setw(3);
	cout << endl;
	for (int i = 0; i < 5; i++)		//goalstate printing
	{
		for (int j = 0; j < 5; j++)
		{
			if (goalState[i][j] == 25)
			{
				cout << "|" << setw(3)<< " " << "|" << setw(3);


			}
			else
				cout << "|" << setw(3) << goalState[i][j] << "|" << setw(3);
		}
		cout << endl;
	}
	cout << endl;
	cout << setw(25) << "****STATUS****" << endl<<setw(3);
	cout << endl;
	for (int i = 0; i < 5; i++)				//updated array printing
	{
		for (int j = 0; j < 5; j++)
		{
			if (init_state[i][j] == 25)
			{
				cout << "|" <<setw(3) << " " << "|" << setw(3);


			}
			else
				cout << "|" << setw(3) << init_state[i][j] << "|" << setw(3);
		}
		cout << endl;
	}
}
void goal(int goalState[5][5])
{

	for (int i = 0; i < 5; i++)					//randomly initializing goal state with unique value in each index
	{
		for (int j = 0; j < 5; )
		{
			int k, l, count = 0;
			goalState[i][j] = rand() % 25 + 1;
			for (k = 0; k < 5; k++)
			{
				for (l = 0; l < 5; l++)
				{
					if (goalState[i][j] == goalState[k][l])
					{
						count++;
					}
				}
			}
			if (count == 1)
			{
				j++;
			}
		}
	}
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << setw(25) << "****GOAL STATE****" << endl << setw(3);
	cout << endl;
	for (int i = 0; i < 5; i++)						//printing goal state
	{
		for (int j = 0; j < 5; j++)
		{
			if (goalState[i][j] == 25)
				cout << "|" << setw(3) << " " << "|" << setw(3);
			else
				cout << "|" << setw(3) << goalState[i][j] << "|" << setw(3);
		}
		cout << endl;
	}

}

bool isSolvable(int goalState[5][5], int init_state[5][5])		//checking solvability
{
	bool  check1 = false;							//checking the solvabity by taking inversion count of both initial and goal state
	bool check2 = false;
	bool solve = false;
	int count1 = 0, count2 = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int x = i; x < 5; x++)
			{
				for (int y = j; y < 5; y++)
				{
					if (init_state[i][j] != 25 && init_state[x][y] != 25)
					{
						if (init_state[i][j] < init_state[x][y])
						{
							count1++;
						}
					}
				}
			}
		}
	}
	if (count1 % 2 == 0)
	{
		check1 = true;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int x = i; x < 5; x++)
			{
				for (int y = j; y < 5; y++)
				{
					if (goalState[i][j] != 25 && goalState[x][y] != 25)
					{
						if (goalState[i][j] < goalState[x][y])
						{
							count2++;
						}
					}
				}
			}
		}
	}
	if (count2 % 2 == 0)
	{
		check2 = true;
	}
	if (check1 == true && check2 == true)		//if both counts are even then the puzzle is solvable
	{
		solve = true;
	}
	else if (check1 == false && check2 == false)	//if both counts are odd then the puzzle is solvable
	{
		solve = true;
	}
	return solve;									//in any other case the puzzle is not solvable

}
bool isGoal(int init_state[5][5], int goalState[5][5])		//check is the puzzle is solved or not
{
	bool check;
	int k = 0, l = 0;
	for (int i = 0; i < 5; i++)						//comparing both states
	{
		for (int j = 0; j < 5; j++)
		{
			if (init_state[i][j] == goalState[k][l])
			{
				check = true;
			}
			else
			{
				check = false;
				break;
			}
			l++;
		}
		if (check == true)
			k++;
		else
			break;
	}
	return check;
}
bool legalmoves(int init_state[5][5], char move)
{
	int i, j;
	bool check = false;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (init_state[i][j] == 25)			//taking index of the space(25) and validating the move as per legal moves that can be taken on
			{									//that specific index
				if (i == 0 && j == 0)
				{

					switch (move)
					{
					case 'R':
					case 'r':
					case 'd':
					case 'D':
						check = true;
						break;
					default:
						check = false;
					}
				}
				else if ((i == 0 && j == 1) || (i == 0 && j == 2) || (i == 0 && j == 3))
				{

					switch (move)
					{
					case 'R':
					case 'r':
					case 'l':
					case 'L':
					case 'd':
					case 'D':
						check = true;
						break;
					default:
						check = false;
					}
				}

				else if (i == 0 && j == 4)
				{
					switch (move)
					{
					case 'L':
					case 'l':
					case 'd':
					case 'D':
						check = true;
						break;
					default:
						check = false;
					}
				}

				else if ((i == 1 && j == 0) || (i == 2 && j == 0) || (i == 3 && j == 0))
				{

					switch (move)
					{
					case 'R':
					case 'r':
					case 'u':
					case 'U':
					case 'd':
					case 'D':
						check = true;
						break;
					default:
						check = false;
					}
				}

				else if (i == 4 && j == 0)
				{

					switch (move)
					{
					case 'R':
					case 'r':
					case 'u':
					case 'U':
						check = true;
						break;
					default:
						check = false;
					}
				}

				else if ((i == 4 && j == 1) || (i == 4 && j == 2) || (i == 4 && j == 3))
				{

					switch (move)
					{
					case 'R':
					case 'r':
					case 'u':
					case 'U':
					case 'l':
					case 'L':
						check = true;
						break;
					default:
						check = false;
					}
				}
				else if (i == 4 && j == 4)
				{

					switch (move)
					{
					case 'L':
					case 'l':
					case 'u':
					case 'U':
						check = true;
						break;
					default:
						check = false;
					}
				}

				else if ((i == 3 && j == 4) || (i == 2 && j == 4) || (i == 1 && j == 4))
				{

					switch (move)
					{
					case 'L':
					case 'l':
					case 'u':
					case 'U':
					case 'd':
					case 'D':
						check = true;
						break;
					default:
						check = false;
					}
				}

				else
				{
					check = true;
				}
			}
		}
	}
	return check;
}
void make_move(int init_state[5][5], char move)
{
	int temp, row, column;
	bool check = legalmoves(init_state, move);			//first check if the move given by user is legal or ot then make move by
														//shuffling the value of space with its nearby tile that user want to shuffle

	if (check == true)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (init_state[i][j] == 25)
				{
					row = i;
					column = j;
				}
			}
		}
		switch (move)				//taking switch case in moves, for shufling with respect to row and column index
		{
		case 'u':
		case 'U':

			temp = init_state[row][column];
			init_state[row][column] = init_state[row - 1][column];
			init_state[row - 1][column] = temp;

			break;
		case 'd':
		case 'D':
			temp = init_state[row][column];
			init_state[row][column] = init_state[row + 1][column];
			init_state[row + 1][column] = temp;

			break;
		case 'l':
		case 'L':
			temp = init_state[row][column];
			init_state[row][column] = init_state[row][column - 1];
			init_state[row][column - 1] = temp;
			break;
		case 'R':
		case 'r':
			temp = init_state[row][column];
			init_state[row][column] = init_state[row][column + 1];
			init_state[row][column + 1] = temp;
			break;

		default:
			cout << "Invalid move." << endl;
		}
	}
}

void file(int init_state[5][5], int goalState[5][5], int const_array[5][5], char attempt[5])
{												//this is for storing the data in file if the game is over 
	ofstream outfile("gameOver.txt");
	if (outfile.is_open())
	{
		outfile << "\n\n Your goal state was: \n";		//storing goal state in .txt file
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				outfile << goalState[i][j] << setw(5);
			}
			outfile << "\n";
		}
		outfile << "\n\n Your initial state was: \n";	//storing initial state in .txt file
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				outfile << const_array[i][j] << setw(5);
			}
			outfile << "\n";
		}
		outfile << "\n\n Your ending up state was: \n";		//storing ending up state in .txt file
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				outfile << init_state[i][j] <<setw(5);
			}
			outfile << "\n";
		}
		outfile << "\n\n Your moves are: \n";			//sequence of moves user has taken

		for (int i = 0; attempt[i] != '\0'; i++)
		{
			outfile << attempt[i] << "  ";
		}
		outfile << "\nYour have done " << counter << " moves\n";		//number of moves user has taken
		if (isGoal(init_state, goalState))
		{
			outfile << "You have reached the goal state.\n";
		}
		else
		{
			outfile << "You have exited without reaching the goal state.\n";
		}
		outfile.close();
	}
	else
	{
		cout << "Error" << endl;;
	}
}
void printpath()			//printing the path in console
{													
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 6);
	cout << "\n\n Your moves are: \n";

	for (int i = 0; attempt[i] != '\0'; i++)
	{
		cout << attempt[i] << "  ";
	}
	cout << "\nYour have done " << counter << " moves\n";
}
