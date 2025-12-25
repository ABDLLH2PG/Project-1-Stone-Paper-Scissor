//Project #1, Stone, Paper, Scissor;
//Due: 2025/11/20, Time: 11:54
//My Self Solution, First Project; 

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice = enGameChoice::Stone;
	enGameChoice ComputerChoice = enGameChoice::Stone;
	enWinner RoundWinner = enWinner::Draw;
	string WinnerName = "";
};

struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner FinalWinner = enWinner::Draw;
	string FinalWinnerName = "";
};

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

short HowManyRound()
{
	short Rounds = 1;

	do
	{
		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> Rounds;

	} while (Rounds < 1 || Rounds > 10);

	return Rounds;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;

	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return enGameChoice(Choice);
}

enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));
}

string ChoiceName(enGameChoice Choice)
{
	string arrChoiceName[3] = { "Stone", "Paper", "Scissors" };

	return arrChoiceName[Choice - 1];
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", "Draw" };

	return arrWinnerName[Winner - 1];
}

enWinner WhoWinTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
			return enWinner::Player1;
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Player1;
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Player1;
		break;
	}

	return enWinner::Computer;
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("Color 2F"); //Green
		break;
	case enWinner::Computer:
		system("Color 4F"); //Red
		break;
	case enWinner::Draw:
		system("Color 6F"); //Yellow
		break;
	}
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n____________Round[" << RoundInfo.RoundNumber << "]____________\n";
	cout << "\nPlayer1  Choice: " << ChoiceName(RoundInfo.Player1Choice);
	cout << "\nComputer Choice: " << ChoiceName(RoundInfo.ComputerChoice);
	cout << "\nRound Winner   : " << "[" << WinnerName(RoundInfo.RoundWinner) << "]";
	cout << "\n________________________________\n\n";

	SetWinnerScreenColor(RoundInfo.RoundWinner);
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.FinalWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.FinalWinnerName = WinnerName(GameResults.FinalWinner);

	return GameResults;
}

stGameResults PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;

	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}

	return FillGameResults(HowManyRound, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = "";

	for (int i = 0; i < NumberOfTabs; i++)
	{
		t += "\t";
	}

	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "                 +++ G a m e O v e r +++                  \n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "_____________________[Game Results]_______________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.FinalWinnerName << endl;
	cout << Tabs(2) << "__________________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.FinalWinner);
}

void ResetScreen()
{
	system("Color 0F");
	system("cls");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResult = PlayGame(HowManyRound());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResult);

		cout << Tabs(2) << "Do you want to play again? Y/N ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}


int main()
{
	srand((unsigned)time(NULL));

	StartGame();


	return 0;
}