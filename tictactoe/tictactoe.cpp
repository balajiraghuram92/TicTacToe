//Tic Tac Toe
//Plays the game of Tic-tac-Toe against a human opponent

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <windows.h>

using namespace std;

//global constants
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';


void gameDetails();
char CheckYesOrNo(string question);
int CheckInput(string question,int high);
char Human();
char opponent(char piece);
void ShowBoard(const vector<char>* board);
char CheckWinner(const vector<char>* board);
bool CheckMoveisValid(const vector<char>* board,int move);
int humanMove(const vector<char>* board,char human);
int computerMove(vector<char> board,char computer);
void announceCheckWinner(char CheckWinner,char computer,char human);

int main()
{
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES,EMPTY);
	gameDetails();
	char human = Human();
	char computer = opponent(human);
	char turn = X;
	ShowBoard(&board);

	while(CheckWinner(&board) == NO_ONE)
	{
		if(turn == human)
		{
			move = humanMove(&board,human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board,computer);
			board[move] = computer;
		}
		ShowBoard(&board);
		turn = opponent(turn);

	}
	announceCheckWinner(CheckWinner(&board),computer,human);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,0);
	return 0;
}


void DisplayString(string _str)
{
	cout << _str << endl;
}


void gameDetails()
{
	DisplayString("Welcome to the TIC-Tac_toe game");
	DisplayString("Enter a number between 0-8");
	DisplayString("To Make Your Move");
	DisplayString("The Number entered corresponds to the desired board position, as illustrated:");
	
	cout<< "0 | 1 | 2 \n \n";
	cout<< "---------- \n";
	cout<< "3 | 4 | 5 \n \n";
	cout<< "---------- \n";
	cout<< "6 | 7 | 8 \n \n";
}

char CheckYesOrNo(string question)
{
	char response;
	do
	{
		cout<<question<<"(y/n) :";
		cin>> response;
	}while(response !='y' && response !='n');

	return response;
}

int CheckInput(string question,int high)
{
	int low = 0;
	int number;
	do
	{
		cout<<question<<"("<<low<<"-"<<high<<"):";
		cin>> number;
	}while(number > high || number < low);

	return number;
}

char Human()
{

	char go_first = CheckYesOrNo("Want to Start First?");
	if(go_first == 'y')
	{
		DisplayString("Make your First Move");
		return X;
	}
	else
	{
		DisplayString("I will go first");
		return O;
	}
}

char opponent(char piece)
{
	if(piece == X)
		return O;
	else 
		return X;
}

void ShowBoard(const vector<char>* board)
{
	cout<<"\n\t"<<(*board)[0]<<"| "<<(*board)[1]<<"| "<<(*board)[2];
	cout<<"\n\t"<<"---------";
	
	cout<<"\n\t"<<(*board)[3]<<"| "<<(*board)[4]<<"| "<<(*board)[5];
	cout<<"\n\t"<<"---------";

	cout<<"\n\t"<<(*board)[6]<<"| "<<(*board)[7]<<"| "<<(*board)[8];
	cout<<"\n\t"<<"---------"<<endl;
}


char CheckWinner(const vector<char>* const board)
{
	//all possible winning rows
	const int WINNING_ROWS[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

	const int TOTAL_ROWS = 8;

	//if any winning row has three values that are the same (and not EMPTY),
	//then we have a CheckWinner
	for(int row =0; row <TOTAL_ROWS; row++)
	{
		if(((*board)[WINNING_ROWS[row][0]] != EMPTY) && ((*board)[WINNING_ROWS[row][0]] == (*board)[WINNING_ROWS[row][1]]) && ((*board)[WINNING_ROWS[row][1]] == (*board)[WINNING_ROWS[row][2]])) 
		{
			return (*board)[WINNING_ROWS[row][0]];
		}
	}

	//since nobody has won, check for a tie(no EMPTY Squares left)
	if(count(board->begin(),board->end(),EMPTY) == 0)
		return TIE;

	//since nobody has won and it is isn't a tie, the game ain't over
	return  NO_ONE;
}

inline bool CheckMoveisValid(int move,const vector<char>* board)
{
	return ((*board)[move] == EMPTY);
}

int humanMove(const vector<char>* const board,char human)
{
	int move = CheckInput("Where will you Move?",(board->size() - 1));

	while(!CheckMoveisValid(move,board))
	{
		DisplayString("That Square is already occupied.Try again !!!");
		move = CheckInput("Where will you Move?",(board->size() - 1));
	}
	cout << "Your Move :" << ' ' << move <<endl;
	return move;
}
bool isFound = false;
int computerMove(vector<char> _board,char computer)
{
	cout <<"My move :" <<' ' ;
	//if computer can win on next move,make that move
	if(!isFound)
	{
		int move = 0;
	for(move = 0; move< _board.size(); ++move)
	{
		if(CheckMoveisValid(move,&_board))
		{
			_board[move] = computer;
			if(CheckWinner(&_board) == computer)
			{
				cout<<move<<endl;
				return move;
				isFound = true;
			}
			//done cheking this move
			_board[move] = EMPTY;
		}
	}
	
	}

	//if human can win on next move,block that move
	if(!isFound)
	{
	int move = 0;
	char human = opponent(computer);
	for(move = 0; move < _board.size(); ++move)
	{
		if(CheckMoveisValid(move,&_board))
		{

			_board[move] = human;
			if(CheckWinner(&_board) == human)
			{
				cout<<move<<endl;
				return move;
				isFound = true;
			}
			//done cheking this move,undo it
			_board[move] = EMPTY;
		}
	}
	}

	if(!isFound)
	{
	//best moves to make,in order to win
	const int BEST_MOVES[] = {4,0,2,6,8,1,3,5,7};
	//since no can win on next move.pick best open square.
	for(int i = 0;i <_board.size();++i)
	{
		int move = BEST_MOVES[i];
		if(CheckMoveisValid(move,&_board))
		{
			cout << move <<endl;
			return move;
			isFound = true;
		}
	}
	}
	return 0;
}


void announceCheckWinner(char CheckWinner,char computer, char human)
{
	if(CheckWinner == human)
	{
		cout<< CheckWinner<<"'s won!\n";
		DisplayString("You Were Smart Enough to Beat Me!!!");
	}
	else if(CheckWinner == computer)
	{
		cout<< CheckWinner<<"'s won!\n";
		DisplayString("You are so Dumb!!!");
	}
	else
	{
		cout<< CheckWinner<<"It's a Tie.\n";
		DisplayString("It was good game");
		DisplayString("Wanna Try Again?");
	}
	system("pause");
}



