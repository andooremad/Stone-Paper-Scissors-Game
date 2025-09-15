#include <iostream>
#include <cstdlib>
using namespace std;

// Enum for player choices
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

// Enum for round winner
enum enWinner { Player1 = 1, Computer = 2, NoWinner = 3 };

// Function to read number of rounds from user (between 1 and 10)
int ReadHowManyRounds()
{
	int number;

	do
	{
		cout << "Please, Enter a Round Number From 1 To 10 : ";
		cin >> number;

	} while (number < 1 || number > 10);

	return number;
}

// Function to generate a random number in range [From, To]
int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;

	return RandomNumber;
}

// Struct to store one round information
struct stRoundInfo
{
	short RoundNumber = 0;        // round number
	enGameChoice Player1Choice;   // player choice
	enGameChoice ComputerChoice;  // computer choice
	enWinner Winner;              // round winner
	string WinnerName;            // winner name
};

// Struct to store overall game results
struct stGameResults
{
	short GameRounds = 0;        // total rounds
	short Player1WonTimes = 0;   // player win count
	short ComputerWonTimes = 0;  // computer win count
	short DrawTimes = 0;         // draw count
	enWinner GameWinner;         // final winner
	string WinnerName = "";      // final winner name
};

// Function to read player1 choice
enGameChoice ReadPlayer1Choice()
{
	int number;
	do
	{
		cout << "Enter Your Choice : [1] Stone, [2] Paper, [3] Scissors ? ";
		cin >> number;
	} while (number < 1 || number > 3);

	return enGameChoice(number);
}

// Function to get computer choice randomly
enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));
}

// Function to decide who won the round
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return enWinner::NoWinner;

	switch (RoundInfo.ComputerChoice)
	{
	case enGameChoice::Paper:
		if (RoundInfo.Player1Choice == enGameChoice::Stone)
			return enWinner::Computer;
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.Player1Choice == enGameChoice::Paper)
			return enWinner::Computer;
		break;

	case enGameChoice::Stone:
		if (RoundInfo.Player1Choice == enGameChoice::Scissors)
			return enWinner::Computer;
		break;
	}

	return enWinner::Player1;
}

// Function to convert winner enum to string
string WinnerName(enWinner Winner)
{
	string Array[3] = { "Player1", "Computer", "No Winner" };
	return Array[Winner - 1];
}

// Function to convert choice enum to string
string ToText(enGameChoice Choice)
{
	string Array[3] = { "Stone", "Paper", "Scissors" };
	return Array[Choice - 1];
}

// Function to set console color depending on the winner
void SetWinnerScreenColor(enWinner Winner)
{
	if (Winner == enWinner::Player1)
	{
		system("color 2F"); // Green for player
	}
	else if (Winner == enWinner::Computer)
	{
		system("color 4F"); // Red for computer
		cout << "\a";       // Beep sound
	}
	else
		system("color 6F"); // Yellow for draw
}

// Function to print round info
void PrintRoundInfo(stRoundInfo RoundInfo)
{
	cout << "\n\n---------------- Round " << RoundInfo.RoundNumber << " Results --------------------\n\n";
	cout << "Player 1 Choice Is  : " << ToText(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice Is  : " << ToText(RoundInfo.ComputerChoice) << endl;
	cout << "The Round Winner Is : " << RoundInfo.WinnerName << "\n\n";
	cout << "-------------------------------------------------------\n\n";

	SetWinnerScreenColor(RoundInfo.Winner);
}

// Function to decide who won the whole game
enWinner WhoWonTheGame(stGameResults GameResult)
{
	if (GameResult.Player1WonTimes == GameResult.ComputerWonTimes)
		return enWinner::NoWinner;
	else if (GameResult.Player1WonTimes > GameResult.ComputerWonTimes)
		return enWinner::Player1;
	else
		return enWinner::Computer;
}

// Function to fill final game results into struct
stGameResults FillGameResults(int GameRounds, short Player1WonTimes, short ComputerWonTimes, short DrawTimes)
{
	stGameResults GameResult;

	GameResult.Player1WonTimes = Player1WonTimes;
	GameResult.ComputerWonTimes = ComputerWonTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameRounds = GameRounds;
	GameResult.GameWinner = WhoWonTheGame(GameResult);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}

// Function to play the game for N rounds
stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;

	short Player1WonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\n Round [ " << GameRound << " ] Begins : \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WonTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWonTimes++;
		else
			DrawTimes++;

		PrintRoundInfo(RoundInfo);
	}

	return FillGameResults(HowManyRounds, Player1WonTimes, ComputerWonTimes, DrawTimes);
}

// Function to reset screen (clear + default color)
void ResetScreen()
{
	system("cls");
	system("color 0F");
}

// Function to generate tabs
string Tabs(int number)
{
	string tabs = "";
	for (int i = 0; i < number; i++)
	{
		tabs = tabs + "\t";
	}
	return tabs;
}

// Function to show game over screen
void ShowGameOverScreen()
{
	cout << Tabs(2) << "-------------------------------------------------\n\n";
	cout << Tabs(2) << "           +++ G A M E   O V E R +++             \n\n";
	cout << Tabs(2) << "-------------------------------------------------\n\n";
}

// Function to show final game results
void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "-------------------- Game Results ------------------------\n";
	cout << Tabs(2) << "The Game Rounds Is    : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player 1 Won Times Is : " << GameResults.Player1WonTimes << endl;
	cout << Tabs(2) << "Computer Won Times Is : " << GameResults.ComputerWonTimes << endl;
	cout << Tabs(2) << "The Draws Times Is    : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "The Final Winner Is   : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "\n----------------------------------------------------------\n";
}

// Function to start the game loop
void StartGame()
{
	char playagain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << "Do You Want To Play Again ? ( Y , N ) ";
		cin >> playagain;

	} while (playagain == 'Y' || playagain == 'y');
}

// Main function
int main()
{
	srand(time(0)); // Seed random generator
	StartGame();    // Start game
}
