#include<iostream>
#include"header.h"
#include<iomanip>
#include<windows.h>
#include<fstream>
#include<ctime>

using namespace std;
void initi(int init_state[5][5]);//initializing initial state
void goal(int goalState[5][5]);//initializing goal state
bool isSolvable(int goalState[5][5], int init_state[5][5]);//checking that is the initial state is reachable to goal state
bool isGoal(int init_state[5][5], int goalState[5][5]);//checking is goal state is reached or not
bool legalmoves(int init_state[5][5], char move);//checking the legal moves for space tile
void make_move(int init_state[5][5], char move);//making move by swapping tiles
void change(int goalState[5][5], int init_state[5][5]);//as the initial state is declared in seperate function so to making change in it we use this function
void file(int init_state[5][5], int goalState[5][5], int const_array[5][5], char attempt[5]);
void printpath();
int init_state[5][5];
int goalState[5][5];

int f = 0;

int main()
{
	srand(time(0));
	char move; char choice = '1';
	char random;
	

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int goalState[5][5];
	int init_state[5][5];
	goal(goalState);        //randomly initializing
	SetConsoleTextAttribute(h, 7);
	do
	{
		cout << "Do you want to initialize the initial state randonmly or want to have it by a file?" <<endl ;
		cout << "Press I for initializing randomly."<<endl;
		cout << "Press f for taking it from file"<<endl ;
		cin >> random;
		if (random == 'i' || random == 'I')
		{
			do
			{
				initi(init_state);              //randomly initializing

			} while (!isSolvable(goalState, init_state));        //checking solvability

			break;
		}
		else if (random == 'f' || random == 'F')
		{
			fstream  afile;
			afile.open("init.txt", ios::in);
			if (!(afile.is_open()))              //opening file
			{
				cout << "Error opening File.." << endl;
				system("pause");

			}
			else                                //reading array from text file
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						afile >> init_state[i][j];
					}
				}
				SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << setw(25) << "***INITIAL STATE***" << endl << endl << setw(3);
				for (int i = 0; i < 5; i++)        //printing array read from file in console
				{
					for (int j = 0; j < 5; j++)
					{
						const_array[i][j] = init_state[i][j];
						if (const_array[i][j] == 25)
						{
							cout << "|" << setw(3) << " " << "|" << setw(3);


						}
						else
							cout << "|" << setw(3) << const_array[i][j] << "|" << setw(3);
					}
					cout << endl;
				}
				cout << endl;

				system("pause");
			}
			break;
		}
		else
			cout << "You entered wrong input.Try again."<<endl;
	} while ( random != 'i'|| random != 'I' || random != 'f' || random != 'F');
	
	

	bool isgoal = isGoal(init_state, goalState);            //declaring a variable for checking that ,Is initial is reached to goal or not.
	do
	{
		system("cls");
		change(goalState, init_state);           //printing the goal and initial state (changed).
		cout << endl;
		SetConsoleTextAttribute(h, 7);           //printing in color
		cout << "**Enter U for moving the space up.**" << char(24) << endl;
		cout << "**Enter D for moving the space down.**" << char(25) << endl;
		cout << "**Enter R for moving the space right.**" << char(26) << endl;
		cout << "**Enter L for moving the space left.**" << char(27) << endl;
		cin >> move;
		if (legalmoves(init_state, move))	//checking the legal moves
		{
			attempt[f] = move;
			f++;
		}

		bool check2 = legalmoves(init_state, move);
		if (check2 == true)
		{
			counter++;	//taken to count the number of moves
			make_move(init_state, move);
		}
		else
		{
			cout << "Invalid move..." << endl;
			system("pause");
		}

		isgoal = isGoal(init_state, goalState);		//to check wether the initial state has reached to goal or not
		SetConsoleTextAttribute(h, 13);
		cout << "Want to play more? Press 1" << endl;
		cin >> choice;


	} while (isgoal == false && choice == '1');
	if (isgoal == true)		//in case of completing the puzzle
	{
		SetConsoleTextAttribute(h, 2);
		cout << "You have reached your Goal state" << endl;			
		cout << "Game Over" << endl;

		change(goalState, init_state);
		printpath();
		file(init_state, goalState, const_array, attempt);
	}
	if (choice != '1')
	{					//incase when user exit the game itself

		cout << "Game over" << endl;
		cout << "You have exited without reaching the goal state.\n";
		
		change(goalState, init_state);
		printpath();
		file(init_state, goalState, const_array, attempt);
	}
	system("pause>0");
	return 0;
}



