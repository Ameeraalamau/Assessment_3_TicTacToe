#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

class Player
{
public:
	string PlayerName;
	int playerMatchCount;
	int winCount;
	int lossCount;
	Player()
	{
		playerMatchCount = 0;
		winCount = 0;
		lossCount = 0;
	}

};

Player objPlayer[100];



int moveCounts = 8;
char board[3][3] = { {'A','B','C'},{'D','E','F'},{'G','H','I'} };
int playerCount = 0;
string PlayerName[100];
int playerMatchCount[100];
int winCount[100];
int lossCount[100];
int computerCount = 0;

int GetWinner();
bool putPossibleMove(char mark);
bool checkEnimeyWin(char mark);
bool checkWin(char move);
void PlayerVSComputer(int Playerid);
void PlayerVSPlayer();
void DisplayBoard();
char getChoice();
bool PutMove(char move, char choice);
void boardRemake();
void ComputerVSComputer();
int main()
{
	objPlayer[0].PlayerName = "Computer";
	int choice, choice1;
	bool flag = true;

	while (flag)
	{
		cout << "Select Game type: \n1)Multi-player \n2)Player vs Computer  \n3)Computer vs Computer\n4)Players History\n5)Exit" << endl;
		cout << "Please Enter your choice : \n";
		choice = _getche();
		system("cls");
		switch (choice) {
		case '1':
		{
			PlayerVSPlayer();
			cout << "Press any key to continue!!";
			_getch();
			system("cls");
			boardRemake();
			break;
		}
		case '2':
		{

			bool temp = true;
			while (temp)
			{
				system("cls");
				cout << "\n1) Select Player \n2) Add New\n3) Exit\n";
				cout << "Please Enter your choice : \n";
				choice = _getche();
				switch (choice)
				{
				case '1':
				{
					try {

						if (playerCount > 0)
						{
							int temp2 = 0;

							for (int i = 1;i <= playerCount;i++)
							{
								cout << i << "Player Name : " << objPlayer[i].PlayerName << endl;
							}
							cout << "\n\nPlease Enter your choice (Please select player with serial no): \n";
							cin >> temp2;
							if (temp2 >= 1 && temp2 <= playerCount)
							{
								PlayerVSComputer(temp2);
								temp = false;
							}
							else if (temp2 > playerCount && temp2 <= 100)
							{
								temp2 = 0;
								cin.clear();
								cin.ignore();
								temp = false;
								cout << "Invalide Choice\n";
							}
							else
							{
								throw ("!!!Invalid Choice\n");
							}
							break;
						}
						else
						{
							cout << "\nNO RECORD FOUND!!" << endl;
						}

					}
					catch (string str)
					{
						cout << str;
					}

				}
				case '2':
				{
					cout << "Enter Your Name : ";
					cin >> objPlayer[playerCount + 1].PlayerName;
					playerCount++;
					PlayerVSComputer(playerCount);
					temp = false;
					break;
				}
				case '3':
				{
					temp = false;
					break;
				}
				default:
				{
					temp = false;
					cout << "Invalid entry!!" << endl;
					break;
				}

				}
			}
			cout << "Press any key to continue!!";
			_getch();
			system("cls");
			boardRemake();
			break;
		}
		case '3':
		{
			ComputerVSComputer();
			cout << "Press any key to continue!!";
			_getch();
			system("cls");
			boardRemake();
			break;
		}
		case '4':
		{
			system("cls");
			for (int i = 0;i <= playerCount;i++)
			{
				cout << "Player Name : " << objPlayer[i].PlayerName << "\t Total Match : " << objPlayer[i].playerMatchCount << "  WIN : " << objPlayer[i].winCount << "  LOSS: " << objPlayer[i].lossCount << endl;
			}
			cout << "Press Any key to go back to Menu";
			_getche();
			break;
		}
		case '5':
		{
			flag = false;
			break;
		}
		default:
		{
			cout << "INVALID CHOICE!!\n";
		}
		}

	}


}
char getChoice(int number)
{
	computerCount++;
	if (number == 1)
		return 'A';
	if (number == 2)
		return 'B';
	if (number == 3)
		return 'C';
	if (number == 4)
		return 'D';
	if (number == 5)
		return 'E';
	if (number == 6)
		return 'F';
	if (number == 7)
		return 'G';
	if (number == 8)
		return 'H';
	else
		return 'I';

}
void PlayerVSComputer(int Playerid)
{
	int computerMove = 0;
	computerCount = 0;
	moveCounts = 8;
	string player1, computer = "computer";
	int player = 1, i;
	char move, choice;
	srand((unsigned)time(0));
	do
	{
		int totalSec = 0;
		DWORD startTime = GetTickCount();
		cout << "YOU CAN ENTER 'Q' or 'q' TO EXIT GAME!!";
		DisplayBoard();

		if (player == 1)
		{
			player = 2;
		}
		else if (player == 2)
		{
			player = 1;
		}
		if (player == 2)
		{
			move = 'O';
			if (computerCount == 0)
			{

				int result = 1 + (rand() % 9);
				choice = getChoice(result);
				cout << endl << choice;
				PutMove(move, choice);
			}
			else
			{
				if (!checkWin(move))
				{
					moveCounts--;
				}
				else if (!checkEnimeyWin(move))
				{
					moveCounts--;
				}
				else if (!putPossibleMove(move))
				{
					moveCounts--;
				}
				else
				{
					moveCounts = 0;
				}
			}
		}
		else
		{
			cout << "\nPlayer " << player << ", enter a move(A-I):  " << endl;
			cin >> choice;
			DWORD endTime = GetTickCount();
			totalSec = (endTime - startTime) / 1000;
			move = 'X';
			if (choice == 'Q' || choice == 'q')
			{
				moveCounts = 0;
			}
			else
			{

				bool moveFlag = PutMove(move, choice);
				if (moveFlag == false)
				{
					cout << "invalid move";

					if (player == 1)
					{
						player = 2;
					}
					else if (player == 2)
					{
						player = 1;
					}
				}
				else
				{
					moveCounts--;
				}
			}
		}

		i = GetWinner();
		if (totalSec > 20)
		{
			if (player == 1)
			{
				player = 2;
			}
			else if (player == 2)
			{
				player = 1;
			}
			cout << "YOU HAVE TAKEN MORE THEN 20 SEC!! \t";
			i = 1;
		}
		if (i == 1)
		{
			objPlayer[Playerid].playerMatchCount += 1;
			objPlayer[0].playerMatchCount += 1;
			if (player == 1)
			{

				objPlayer[0].lossCount += 1;
				objPlayer[Playerid].winCount += 1;
				cout << player1 << " WIN!!" << endl;
			}
			else if (player == 2)
			{
				objPlayer[0].winCount += 1;
				objPlayer[Playerid].lossCount += 1;
				cout << "COMPUTER WIN!!";
			}
			break;

		}
		if (moveCounts == 0)
		{
			objPlayer[0].playerMatchCount += 1;
			objPlayer[Playerid].playerMatchCount += 1;
			cout << "MATCH DRAW !!" << endl;
			i = 1;
			break;
		}
		system("cls");
		cout << endl;
		cout << endl;
	} while (i == -1);
	DisplayBoard();
	_getch();
	system("cls");
	return;
}
void PlayerVSPlayer()
{
	string player1, player2;
	int player = 2, i, count1 = 0, count2 = 0;
	moveCounts = 8;
	char move, choice;
	cout << "\nPlayer 1 Enter your name(X) :  ";
	cin >> player1;
	cout << "\nPlayer 2 Enter your name(O) :  " << endl;
	cin >> player2;

	cout << "Enter 'Q' or 'q' to EXIT!!";

	do
	{
		DWORD startTime = GetTickCount();

		//Do something 

		DisplayBoard();

		if (player == 1)
		{
			player = 2;
		}
		else if (player == 2)
		{
			player = 1;
		}

		cout << "\nPlayer " << player << ", enter a move(A-I):  ";
		cin >> choice;

		if (player == 1)
		{
			move = 'X';
		}
		else if (player == 2)
		{
			move = 'O';
		}
		if (choice == 'Q' || choice == 'q')
		{
			moveCounts = 0;
		}
		else {


			bool moveFlag = PutMove(move, choice);
			if (moveFlag == false)
			{
				cout << "invalid move" << endl;

				if (player == 1)
				{
					player = 2;
				}
				else if (player == 2)
				{
					player = 1;
				}
			}
			else
			{
				moveCounts--;
				i = GetWinner();
				DWORD endTime = GetTickCount();
				int totalSec = (endTime - startTime) / 1000;
				if (totalSec > 20)
				{
					if (player == 1)
					{
						player = 2;
					}
					else if (player == 2)
					{
						player = 1;
					}
					cout << "YOU HAVE TAKEN MORE THEN 20 SEC!! \t";
					i = 1;
				}

				if (i == 1)
				{
					if (player == 1)
					{
						moveCounts++;
						cout << player1 << " WIN!!" << endl;
						break;
					}
					else if (player == 2)
					{
						moveCounts++;
						cout << player2 << " WIN!!" << endl;
						break;
					}
				}
			}
		}
		if (moveCounts == 0)
		{
			cout << "MATCH DRAW !!" << endl;
			i = 1;
			break;
		}
		cout << endl;
		cout << endl;
	} while (i == -1);
	DisplayBoard();
	getchar();

}
void ComputerVSComputer()
{
	string player1, player2;
	int player = 2, i, count1 = 0, count2 = 0;
	moveCounts = 8;
	char move, choice;
	cout << "\nComputer 1 (X) :  " << endl;
	cout << "\nComputer 2 (O) :  " << endl << endl;

	DisplayBoard();
	cout << endl << endl;
	do
	{
		Sleep(2000);
		if (player == 1)
		{
			player = 2;
		}
		else if (player == 2)
		{
			player = 1;
		}

		if (player == 1)
		{
			move = 'X';
		}
		else if (player == 2)
		{
			move = 'O';
		}
		if (count1 == 0 || count2 == 0)
		{
			srand((unsigned)time(0));
			int result = 1 + (rand() % 9);
			choice = getChoice(result);
			bool moveFlag = PutMove(move, choice);
			if (moveFlag == false)
			{

				if (player == 1)
				{
					player = 2;
				}
				else if (player == 2)
				{
					player = 1;
				}
			}
			else
			{
				DisplayBoard();
				cout << endl;
				cout << endl;

				moveCounts--;

				if (player == 1)
					count1++;
				else
					count2++;
			}
		}
		else
		{
			DisplayBoard();
			cout << endl;
			cout << endl;
			if (!checkWin(move))
			{
				moveCounts--;
			}
			else if (!checkEnimeyWin(move))
			{
				moveCounts--;
			}
			else if (putPossibleMove(move))
			{
				moveCounts = 0;
			}
		}

		i = GetWinner();
		if (i == 1)
		{
			if (player == 1)
			{
				moveCounts++;
				cout << player1 << " WIN!!" << endl;
				break;
			}
			else if (player == 2)
			{
				moveCounts++;
				cout << player2 << " WIN!!" << endl;
				break;
			}
		}
		if (moveCounts == 0)
		{
			cout << "MATCH DRAW !!" << endl;
			i = 1;
		}
	} while (i == -1);
	DisplayBoard();
	cout << "Exiting!!";
	getchar();

}

bool PutMove(char move, char choice)
{
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (board[i][j] == choice & choice != 'X' && choice != 'O')
			{
				board[i][j] = move;
				return true;
			}
		}
	}
	return false;
}
bool checkWin(char mark)
{
	if (((board[0][1] == board[0][2] && board[0][1] == mark) || (board[1][0] == board[2][0] && board[1][0] == mark) || (board[1][1] == board[2][2] && board[1][1] == mark)) && (board[0][0] == 'A'))    //Check win for 'A' place
	{
		board[0][0] = mark;
		return false;
	}
	else if (((board[0][0] == board[0][2] && board[0][0] == mark) || (board[1][1] == board[2][1] && board[1][1] == mark)) && (board[0][1] == 'B'))    //Check win for 'B' place
	{
		board[0][1] = mark;
		return false;
	}
	else if (((board[0][0] == board[0][1] && board[0][1] == mark) || (board[1][2] == board[2][2] && board[1][2] == mark) || (board[1][1] == board[2][0] && board[1][1] == mark)) && (board[0][2] == 'C'))    //Check win for 'C' place
	{
		board[0][2] = mark;
		return false;
	}
	else if (((board[0][0] == board[2][0] && board[0][0] == mark) || (board[1][1] == board[1][2] && board[1][1] == mark)) && (board[1][0] == 'D'))    //Check win for 'D' place
	{
		board[1][0] = mark;
		return false;
	}
	else if (((board[1][0] == board[1][2] && board[1][2] == mark) || (board[0][1] == board[2][1] && board[2][1] == mark) || (board[0][0] == board[2][2] && board[0][0] == mark) || (board[2][0] == board[0][2] && board[2][0] == mark)) && (board[1][1] == 'E'))    //Check win for 'E' place
	{
		board[1][1] = mark;
		return false;
	}
	else if (((board[0][2] == board[2][2] && board[0][2] == mark) || (board[1][0] == board[1][1] && board[1][1] == mark)) && (board[1][2] == 'F'))    //Check win for 'F' place
	{
		board[1][2] = mark;
		return false;
	}
	else if (((board[0][0] == board[1][0] && board[0][0] == mark) || (board[1][1] == board[0][2] && board[1][1] == mark) || (board[2][1] == board[2][2] && board[2][1] == mark)) && (board[2][0] == 'G'))    //Check win for 'G' place
	{
		board[2][0] = mark;
		return false;
	}
	else if (((board[2][0] == board[2][2] && board[2][2] == mark) || (board[0][1] == board[1][1] && board[1][1] == mark)) && (board[2][1] == 'H'))    //Check win for 'H' place
	{
		board[2][1] = mark;
		return false;
	}
	else if (((board[2][0] == board[2][1] && board[2][1] == mark) || (board[1][1] == board[0][0] && board[1][1] == mark) || (board[0][2] == board[1][2] && board[1][2] == mark)) && (board[2][2] == 'I'))    //Check win for 'I' place
	{
		board[2][2] = mark;
		return false;
	}
	else
		return true;
}
bool checkEnimeyWin(char mark)
{
	if (((board[0][1] == board[0][2] && board[0][1] != mark) || (board[1][0] == board[2][0] && board[1][0] != mark) || (board[1][1] == board[2][2] && board[1][1] != mark)) && (board[0][0] == 'A'))    //Check win for 'A' place
	{
		board[0][0] = mark;
		return false;
	}
	else if (((board[0][0] == board[0][2] && board[0][0] != mark) || (board[1][1] == board[2][1] && board[1][1] != mark)) && (board[0][1] == 'B'))    //Check win for 'B' place
	{
		board[0][1] = mark;
		return false;
	}
	else if (((board[0][0] == board[0][1] && board[0][1] != mark) || (board[1][2] == board[2][2] && board[1][2] != mark) || (board[1][1] == board[2][0] && board[1][1] != mark)) && (board[0][2] == 'C'))    //Check win for 'C' place
	{
		board[0][2] = mark;
		return false;
	}
	else if (((board[0][0] == board[2][0] && board[0][0] != mark) || (board[1][1] == board[1][2] && board[1][1] != mark)) && (board[1][0] == 'D'))    //Check win for 'D' place
	{
		board[1][0] = mark;
		return false;
	}
	else if (((board[1][0] == board[1][2] && board[1][2] != mark) || (board[0][1] == board[2][1] && board[2][1] != mark) || (board[0][0] == board[2][2] && board[1][1] != mark) || (board[2][0] == board[0][2] && board[2][0] != mark)) && (board[1][1] == 'E'))    //Check win for 'E' place
	{
		board[1][1] = mark;
		return false;
	}
	else if (((board[0][2] == board[2][2] && board[0][2] != mark) || (board[1][0] == board[1][1] && board[1][1] != mark)) && (board[1][2] == 'F'))    //Check win for 'F' place
	{
		board[1][2] = mark;
		return false;
	}
	else if (((board[0][0] == board[1][0] && board[0][0] != mark) || (board[1][1] == board[0][2] && board[1][1] != mark) || (board[2][1] == board[2][2] && board[2][1] != mark)) && (board[2][0] == 'G'))    //Check win for 'G' place
	{
		board[2][0] = mark;
		return false;
	}
	else if (((board[2][0] == board[2][2] && board[2][2] != mark) || (board[0][1] == board[1][1] && board[1][1] != mark)) && (board[2][1] == 'H'))    //Check win for 'H' place
	{
		board[2][1] = mark;
		return false;
	}
	else if (((board[2][0] == board[2][1] && board[2][1] != mark) || (board[1][1] == board[0][0] && board[1][1] != mark) || (board[0][2] == board[1][2] && board[1][2] != mark)) && (board[2][2] == 'I'))    //Check win for 'I' place
	{
		board[2][2] = mark;
		return false;
	}
	else
		return true;
}
bool putPossibleMove(char mark)
{
	if (((board[0][2] == 'C' && board[0][1] == mark) || (board[0][2] == mark && board[0][1] == 'B') || (board[2][0] == 'G' && board[1][0] == mark) || (board[2][0] == mark && board[1][0] == 'D') || (board[2][2] == 'I' && board[1][1] == mark) || (board[2][2] == mark && board[1][1] == 'E')) && (board[0][0] == 'A'))    //Check win for 'A' place
	{
		board[0][0] = mark;
		return false;
	}
	else if (((board[0][2] == 'C' && board[0][0] == mark) || (board[0][2] == mark && board[0][0] == 'A') || (board[2][1] == 'H' && board[1][1] == mark) || (board[2][1] == mark && board[1][1] == 'E')) && (board[0][1] == 'B'))    //Check win for 'B' place
	{
		board[0][1] = mark;
		return false;
	}
	else if (((board[0][0] == mark && board[0][1] == 'B') || (board[0][0] == 'A' && board[0][1] == mark) || (board[2][2] == 'I' && board[1][2] == mark) || (board[2][2] == mark && board[1][2] == 'F') || (board[1][1] == mark && board[2][0] == 'G') || (board[1][1] == 'E' && board[2][0] == mark)) && (board[0][2] == 'C'))    //Check win for 'C' place
	{
		board[0][2] = mark;
		return false;
	}
	else if (((board[2][0] == 'G' && board[0][0] == mark) || (board[2][0] == mark && board[0][0] == 'A') || (board[1][2] == 'F' && board[1][1] == mark) || (board[1][2] == mark && board[1][1] == 'E')) && (board[1][0] == 'D'))    //Check win for 'D' place
	{
		board[1][0] = mark;
		return false;
	}
	else if (((board[1][0] == 'D' && board[1][2] == mark) || (board[1][0] == mark && board[1][2] == 'F') || (board[0][1] == 'B' && board[2][1] == mark) || (board[0][1] == mark && board[2][1] == 'H') || (board[0][0] == 'A' && board[2][2] == mark) || (board[0][0] == mark && board[2][2] == 'I') || (board[0][2] == 'C' && board[2][0] == mark) || (board[0][2] == mark && board[2][0] == 'G')) && (board[1][1] == 'E'))    //Check win for 'E' place
	{
		board[1][1] = mark;
		return false;
	}
	else if (((board[2][2] == 'I' && board[0][2] == mark) || (board[2][2] == mark && board[0][2] == 'C') || (board[1][0] == mark && board[1][1] == 'E') || (board[1][0] == 'D' && board[1][1] == mark)) && (board[1][2] == 'F'))    //Check win for 'F' place
	{
		board[1][2] = mark;
		return false;
	}
	else if (((board[1][0] == 'D' && board[0][0] == mark) || (board[1][0] == mark && board[0][0] == 'A') || (board[0][2] == mark && board[1][1] == 'E') || (board[0][2] == 'C' && board[1][1] == mark) || (board[2][2] == 'I' && board[2][1] == mark) || (board[2][2] == mark && board[2][1] == 'H')) && (board[2][0] == 'G'))    //Check win for 'G' place
	{
		board[2][0] = mark;
		return false;
	}
	else if (((board[2][0] == mark && board[2][2] == 'I') || (board[2][0] == 'G' && board[2][2] == mark) || (board[0][1] == 'B' && board[1][1] == mark) || (board[0][1] == mark && board[1][1] == 'E')) && (board[2][1] == 'H'))    //Check win for 'H' place
	{
		board[2][1] = mark;
		return false;
	}
	else if (((board[2][0] == 'G' && board[2][1] == mark) || (board[2][0] == mark && board[2][1] == 'H') || (board[0][0] == 'A' && board[1][1] == mark) || (board[0][0] == mark && board[1][1] == 'E') || (board[0][2] == mark && board[1][2] == 'F')) && (board[2][2] == 'I'))    //Check win for 'I' place
	{
		board[2][2] = mark;
		return false;
	}
	else
		return true;
}
int GetWinner()
{
	if (board[0][0] == board[0][1] && board[0][1] == board[0][2])

		return 1;
	else if (board[1][0] == board[1][1] && board[1][1] == board[1][2])

		return 1;
	else if (board[2][0] == board[2][1] && board[2][1] == board[2][2])

		return 1;
	else if (board[0][0] == board[1][0] && board[1][0] == board[2][0])

		return 1;
	else if (board[0][1] == board[1][1] && board[1][1] == board[2][1])

		return 1;
	else if (board[0][2] == board[1][2] && board[1][2] == board[2][2])

		return 1;
	else if (board[0][0] == board[1][1] && board[1][1] == board[2][2])

		return 1;
	else if (board[0][2] == board[1][1] && board[1][1] == board[2][0])

		return 1;
	else
		return -1;
}
void DisplayBoard()
{
	cout << "\n  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << endl << "_____ _____ _____" << endl << endl << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << endl << "_____ _____ _____" << endl << endl << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << endl;
}
void boardRemake()
{
	board[0][0] = 'A';
	board[0][1] = 'B';
	board[0][2] = 'C';
	board[1][0] = 'D';
	board[1][1] = 'E';
	board[1][2] = 'F';
	board[2][0] = 'G';
	board[2][1] = 'H';
	board[2][2] = 'I';
}

