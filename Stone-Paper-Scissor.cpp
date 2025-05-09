#include<iostream>
#include<cstdlib>
using namespace std;

enum enChoices{ Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner{ Player = 1, Computer = 2, Draw = 3 };
int RandomNumber(int From, int To)
{
	int Random = rand() % (To - From + 1) + From;
	return Random;
}

struct stRoundInfo
{
	short Round = 0;
	enChoices Player;
	enChoices Computer;
	enWinner WhoWin;
	string Winner;
};
struct stFinalGame
{
	short GameRounds = 0;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner WhoWon;
	string FinalWinner;
};

short HowManyRounds()
{
	short ManyRounds = 1;
	do
	{
		cout << "How many Rounds 1 to 10?\n";
		cin >> ManyRounds;

		if (ManyRounds < 1 || ManyRounds > 10)
		{
			cout << "Sorry, you must ener rounds from 1 to 10.\n";
			cout << "Try again!\n";
		}
	} while (ManyRounds < 1 || ManyRounds > 10);

	return ManyRounds;
}
enChoices ChoicePlayer()
{
	short Choice = 0;
	do
	{
		cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;

		if (Choice < 1 || Choice > 3)
		{
			cout << "Please, enter number from 1 to 3.\n";
		}


	} while (Choice < 1 || Choice > 3);
	
	return (enChoices) Choice;
}
enChoices ChoiceComputer()
{
	return (enChoices)RandomNumber(1, 3);
}

enWinner WhoWinner(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player == RoundInfo.Computer)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player)
	{
	case enChoices::Stone:
		if (RoundInfo.Computer == enChoices::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enChoices::Paper:
		if (RoundInfo.Computer == enChoices::Scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enChoices::Scissors:
		if (RoundInfo.Computer == enChoices::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player;
}

string PrintWhoWinner(enWinner WhoWinner)
{
	string Winner[3] = { "Player", "Computer", "Draw" };
	return Winner[WhoWinner - 1];
}
string PrintChoices(enChoices Choice)
{
	string Winner[3] = { "Stone", "Paper", "Scissors" };
	return Winner[Choice - 1];
}
string PrintFinalWinner(enWinner Final)
{
	string FinalWinner[3] = { "Player", "Computer", "No winner" };
	return FinalWinner[Final - 1];
}

void PrintRound(stRoundInfo RoundInfo)
{
	cout << "\n________________ Round[" << RoundInfo.Round << "]________\n\n";
	cout << "Player Choice   : " << PrintChoices(RoundInfo.Player) << endl;
	cout << "Computer Choice : " << PrintChoices(RoundInfo.Computer) << endl;
	cout << "Round Winner    : " << RoundInfo.Winner << endl;
	cout << "___________________________________________\n\n";
}
void ColorScreen(enWinner WhoWinner)
{
	switch (WhoWinner)
	{
	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		break;

	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

string Tab(short Num)
{
	string Tab = "";

	for (short i = 1; i <= Num; i++)
	{
		Tab = Tab + "\t";
	}
	return Tab;
}

enWinner WhoWon(short PlayerWinTimes, short ComputerWinTimes)
{

	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	
	else if (ComputerWinTimes > PlayerWinTimes)
		return enWinner::Computer;

	else
		return enWinner::Draw;
}
stFinalGame FillRounds(short WhoManyRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stFinalGame FinalGame;

	FinalGame.GameRounds = WhoManyRounds;
	FinalGame.PlayerWonTimes = PlayerWinTimes;
	FinalGame.ComputerWonTimes = ComputerWinTimes;
	FinalGame.DrawTimes = DrawTimes;
	FinalGame.WhoWon = WhoWon(PlayerWinTimes, ComputerWinTimes);
	FinalGame.FinalWinner = PrintFinalWinner(FinalGame.WhoWon);

	return FinalGame;
}
void PrintFinalGame(stFinalGame FinalGame)
{
	cout << Tab(2) << "________________ [Game Result] ________________\n\n";
	cout << Tab(2) << "Game Rounds      : " << FinalGame.GameRounds << endl;
	cout << Tab(2) << "Player won times : " << FinalGame.PlayerWonTimes << endl;
	cout << Tab(2) << "Compter won times: " << FinalGame.ComputerWonTimes << endl;
	cout << Tab(2) << "Draw times       : " << FinalGame.DrawTimes << endl;
	cout << Tab(2) << "Final Winner     : " << FinalGame.FinalWinner << endl;
	cout << Tab(2) << "_______________________________________________\n";
}

stFinalGame PlayGame(short WhoManyRounds)
{

	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	
	for (short Round = 1; Round <= WhoManyRounds; Round++)
	{
		cout << "Round [" << Round << "] begins:\n";
		RoundInfo.Round = Round;
		RoundInfo.Player = ChoicePlayer();
		RoundInfo.Computer = ChoiceComputer();
		RoundInfo.WhoWin = WhoWinner(RoundInfo);
		RoundInfo.Winner = PrintWhoWinner(RoundInfo.WhoWin);


		// Increse in st FinalInfo (struct)
		if (RoundInfo.WhoWin == enWinner::Player)
			PlayerWinTimes++;

		else if (RoundInfo.WhoWin == enWinner::Computer)
			ComputerWinTimes++;

		else
			DrawTimes++;

		ColorScreen(RoundInfo.WhoWin);
		PrintRound(RoundInfo);
	}

	return  FillRounds(WhoManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);

}

void PrintGameOver()
{
	cout << Tab(2) << "__________________________________________\n\n";
	cout << Tab(2) << "         +++ G a m e  O v e r +++\n";
	cout << Tab(2) << "__________________________________________\n\n";
}

void BlackScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char Charcter = 'Y';
	do
	{
		BlackScreen();
		stFinalGame FinalGame = PlayGame(HowManyRounds());
		
		PrintGameOver();
		PrintFinalGame(FinalGame);

		cout << Tab(2) << "Do you want to play again 'Y' Or 'N' ? ";
		cin >> Charcter;

	} while (Charcter == 'Y' || Charcter == 'y');

}



int main()
{
	srand((unsigned)time(NULL));
	

	StartGame();
	

	return 0;
}
