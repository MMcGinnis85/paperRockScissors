// HurlingManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int choice1;
int choice2;
string CompName;
char response;
int compScore, playScore;
bool quitFlag = false;
int numUsers = 1;
int numChoices = 3;
int choiceRock, choicePaper, choiceScissor; //Numbers for the choices to be stored
int currentRock = 0;
int currentPaper = 0;
int currentScissor = 0;
int main()
{
	srand(time(NULL));

	//Functions
	int CompMove();
	void Winner();
	string CompMoveName();
	int PlayerChoice();
	void WelcomeScreen();
	string getFileContents(ifstream& File);
	int MenuOption();
	void DoQuit();
	void LoadItemsFromDatabase();
	void LoadChoicessFromData();
	void SaveItemsToDatabase();
	void SaveChoice();
	void ResetScores();
	void DisplayScore();
	void CheatMode();
	void MyChoices();

	system("Color 03");
	srand(time(NULL)); //initialize the random seed
	WelcomeScreen();
	LoadItemsFromDatabase();
	LoadChoicessFromData();
	int option = 0;
	do
	{
		option = MenuOption();
		switch (option)
		{
		case 1:
			PlayerChoice();
			CompMove();
			CompMoveName();
			cout << CompName;
			Winner();
			break;
		case 2:
			DisplayScore();
			break;
		case 3:
			ResetScores();
			SaveItemsToDatabase();
			break;
		case 4:
			MyChoices();
			break;
		case 99:
			CheatMode();
			CompMove();
			CompMoveName();
			cout << "I am gonna choose " << CompName << endl;
			PlayerChoice();
			cout << CompName;
			Winner();
			cout << endl;
			cout << "Did that make you proud?" << endl;
			break;
		case 0:
			DoQuit();
			break;
		default:
			cout << "invalid option\n";
		}
	} while (!quitFlag);

	SaveItemsToDatabase();
	SaveChoice();
	return 0;
}

void DoQuit(void)
{
	quitFlag = true;
}

int MenuOption()
{
	int option = 0;
	cout << endl;
	cout << "\t\t\t\t\t\t\t Menu " << endl;
	cout << "\t\t\t\t\t(1). Start Game" << endl;
	cout << "\t\t\t\t\t(2). Check Current Scores" << endl;
	cout << "\t\t\t\t\t(3). Reset Scores" << endl;
	cout << "\t\t\t\t\t(0). Quit " << endl;
	cout << "\t\t\t\t\t ";
	cin >> option;
	cout << endl << endl;
	return option;
}
string getFileContents(ifstream& File)
{
	std::string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}
void WelcomeScreen()
{
	std::ifstream Reader("Welcome.txt");             //Open file

	std::string Art = getFileContents(Reader);       //Get file

	std::cout << Art << std::endl;               //Print it to the screen

	Reader.close();                           //Close file
}

void LoadItemsFromDatabase()
{
	//Load list from .dat file
	ifstream infile("scores.dat");
	if (!infile)
	{
		cout << "database file scores.dat does not exist.";
	}
	else
	{
		infile >> numUsers;

		for (int i = 0; i < numUsers; i++)
		{
			infile >> playScore >> compScore;
		}
	}
}

void LoadChoicessFromData()
{
	//Load list from .dat file
	ifstream infile("choices.dat");
	if (!infile)
	{
		cout << "database file choices.dat does not exist.";
	}
	else
	{
		infile >> numChoices;

		for (int i = 0; i < numChoices; i++)
		{
			infile >> choiceRock >> choicePaper >> choiceScissor;
		}
	}
}

int PlayerChoice()
{
	cout << "Enter your move (P)aper (R)ock (S)cissors : " << endl;
	cin >> response;

	if (response == 'R' || response == 'r')
	{
		choice1 = 1;
		choiceRock++;
		currentRock++;
		cout << "You choose Rock. I choose ";
		return choice1;
	}
	else if (response == 'S' || response == 's')
	{
		choice1 = 2;
		choiceScissor++;
		currentScissor++;
		cout << "You chose Scissors. I choose ";
		return choice1;
	}
	else if (response == 'p' || response == 'P')
	{
		choice1 = 3;
		choicePaper++;
		currentPaper++;
		cout << "You chose Paper. I choose ";
		return choice1;
	}
	else
	{
		choice1 = -1;
		return PlayerChoice();
	}
	return 0;
}

int CompMove()
{
	int RandIndex = rand() % 3; //generates a random number between 0 and 3
	choice2 = RandIndex + 1;

	return choice2;
}

string CompMoveName()
{
	if (choice2 == 1)
	{
		CompName = "Rock";
	}
	else if (choice2 == 2)
		CompName = "Scissors";
	else
	{
		CompName = "Paper";
	}

	return CompName;
}
void Winner()
{
	if ((choice1 == 3 && choice2 == 1) || (choice1 == 2 && choice2 == 3) || (choice1 == 1 && choice2 == 2))
	{
		cout << endl;
		cout << "You win!";
		playScore++;
	}
	else if ((choice2 == 3 && choice1 == 1) || (choice2 == 2 && choice1 == 3) || (choice2 == 1 && choice1 == 2))
	{
		cout << endl;
		cout << "You lose!";
		compScore++;
	}
	else
	{
		cout << endl;
		cout << "Its a draw!";
	}
}
void ResetScores()
{
	playScore = 0;
	compScore = 0;
	choicePaper = 0;
	choiceRock = 0;
	choiceScissor = 0;
}
void SaveItemsToDatabase()
{
	if (numUsers == 0)
		return;
	ofstream outfile("scores.dat");
	outfile << numUsers << endl;

	for (int i = 0; i < numUsers; i++)
	{
		outfile << playScore << "  "
			<< compScore << "  "
			<< endl;
	}

	outfile.close();
}
void SaveChoice()
{
	if (numUsers == 0)
		return;
	ofstream outfile("choices.dat");
	outfile << numUsers << endl;

	for (int i = 0; i < numUsers; i++)
	{
		outfile << choiceRock << "  "
			<< choicePaper << "  "
			<< choiceScissor << "  "
			<< endl;
	}

	outfile.close();
}
void MyChoices()
{
	cout << "You have choosen Rock " << choiceRock << " times" << endl;
	cout << "You have choosen Paper " << choicePaper << " times" << endl;
	cout << "You have choosen Scissors " << choiceScissor << " times" << endl;
}
void DisplayScore()
{
	cout << "Player current score is " << playScore << endl;
	cout << "Computer current score is " << compScore << endl << endl;
	MyChoices();
}
void CheatMode()
{
	cout << "You Cheating Bastard!!!" << endl;
}