// Rock-Paper-Scissors-Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include <string>
#include<cstdlib>
#include<ctime>
using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };
struct strRoundInfo {
	short  Round = 0;
	enGameChoice Player1;
	enGameChoice Computer;
	enWinner Winner;
	string Winner_Name = "";
};
struct strGameResult {
	short Round = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string Winner_Name = "";
};
int RandomNumber(int From, int to) {
	int randl = rand() % (to - From + 1) + From;
	return randl;
}
short ReadHowManyRound() {
	int RoundNumber = 0;
	do
	{
		cout << "How Many Round 1 To 10 ? " << endl;
		cin >> RoundNumber;
	} while (RoundNumber < 1 || RoundNumber > 10);
	return RoundNumber;
}
enGameChoice ReadPlayer1Choice() {
	short Choice = 1;
	do
	{
		cout << "Your Choice [1]:Stone,[2]:Paper,[3]:Scissors \n";
		cin >> Choice;
	} while (Choice < 1 || Choice >3);
	return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice() {
	return (enGameChoice)RandomNumber(1, 3);
}
enWinner WhoWonTheRound(strRoundInfo Roundinfo) {

	if (Roundinfo.Player1 == Roundinfo.Computer)
	{
		return enWinner::Draw;
	}
	switch (Roundinfo.Player1)
	{
	case enGameChoice::Stone:
		if (Roundinfo.Computer == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (Roundinfo.Computer == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (Roundinfo.Computer == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
	}
	return enWinner::Player1;
}
enWinner WhoWonTheGame(short Player1wintimes, short ComputerWinTimes) {
	if (Player1wintimes > ComputerWinTimes)
	{
		return enWinner::Player1;
	}
	else 	if (ComputerWinTimes > Player1wintimes)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::Draw;
	}
}
void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner)
	{
	case enWinner::Player1:
		system("Color 2f ");
		break;
	case enWinner::Computer:
		system("Color 4f ");
		break;
	default:
		system("Color 6f ");
		break;
	}
}
string WinnerGame(enWinner Winner) {
	string arrwinner[3] = { "Player1","Computer","Draw" };
	return arrwinner[Winner - 1];
}
string ChoiceName(enGameChoice Choice) {
	string arrChoice[3] = { "Stone","Paper","Scissors" };
	return arrChoice[Choice - 1];
}
void PrintRoundResult(strRoundInfo RoundInfo) {
	cout << "\n____________ Round [" << RoundInfo.Round << "] ____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.Computer) << endl;
	cout << "Round Winner   : [" << RoundInfo.Winner_Name << "]\n";
	cout << "_________________________________________\n" << endl;
	SetWinnerScreenColor(RoundInfo.Winner);
}
string Tabs(short NumberOfTabs) {
	string t = "";
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		t += "\t";
	}
	return t;
}
void ShowFinalGameResult(strGameResult GameResult) {
	cout << Tabs(2) << "----------------------[Game Result]-------------------" << endl;
	cout << Tabs(2) << "Game Round   : " << GameResult.Round << endl;
	cout << Tabs(2) << "Player1 Win Times   : " << GameResult.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Win Times   : " << GameResult.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw   Times   : " << GameResult.DrawTimes << endl;
	cout << Tabs(2) << "Final Winners   : " << GameResult.Winner_Name << endl;
	SetWinnerScreenColor(GameResult.Winner);
}
strGameResult FillGameResult(short GameRound, short Player1wintimes, short Computerwintimes, short Drawstimes) {
	strGameResult GameResult;
	GameResult.Round = GameRound;
	GameResult.Player1WinTimes = Player1wintimes;
	GameResult.ComputerWinTimes = Computerwintimes;
	GameResult.DrawTimes = Drawstimes;
	GameResult.Winner = WhoWonTheGame(Player1wintimes, Computerwintimes);
	GameResult.Winner_Name = WinnerGame(GameResult.Winner);
	return GameResult;
}
void ShowGameOVerScreen() {
	cout << Tabs(2) << "-------------------------------------------------------------------------\n";
	cout << Tabs(2) << "\n                                          +++ Game Over +++               \n";
	cout << Tabs(2) << "-------------------------------------------------------------------------\n";
}
strGameResult PlayGame(short HowManyRound) {
	strRoundInfo Roundinfo;
	short Player1 = 0, Computer = 0, Draw = 0;
	for (short Gameround = 1; Gameround <= HowManyRound; Gameround++)
	{
		cout << "\nRound [" << Gameround << "] begins: \n";
		Roundinfo.Round = Gameround;
		Roundinfo.Player1 = ReadPlayer1Choice();
		Roundinfo.Computer = GetComputerChoice();
		Roundinfo.Winner = WhoWonTheRound(Roundinfo);
		Roundinfo.Winner_Name = WinnerGame(Roundinfo.Winner);
		if (Roundinfo.Winner == enWinner::Player1)
		{
			Player1++;
		}
		else if (Roundinfo.Winner == enWinner::Computer)
		{
			Computer++;
		}
		else
		{
			Draw++;
		}
		PrintRoundResult(Roundinfo);
	}
	return FillGameResult(HowManyRound, Player1, Computer, Draw);
}
void resetScreen() {
	system("cls");
	system("color 0f");
}
void StartGame() {
	char PlayAgain = 'Y';
	do
	{
		resetScreen();
		strGameResult GameRresult = PlayGame(ReadHowManyRound());
		ShowGameOVerScreen();
		ShowFinalGameResult(GameRresult);
		cout << endl << Tabs(3) << "Do You Want To Play Again Y/N ? " << endl;
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main() {
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}