#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice {Stone = 1,Paper = 2,Scissors = 3};
enum enWinner {Player1 = 1,Computer = 2,Draw = 3};

struct stRoundInfo
{
    short RandNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner Winner;
    string WinnerName;
};

int RandNumber(int From,int To)
{
    return rand() % (To + 1 - From) + From;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandNumber(1,3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if(RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    };

    switch (RoundInfo.Player1Choice)
    {
        case enGameChoice::Stone:
           if(RoundInfo.ComputerChoice == enGameChoice::Paper)
            {
              return enWinner::Computer;
            }
            break;

        case enGameChoice::Paper:
            if(RoundInfo.ComputerChoice == enGameChoice::Scissors)
            {
               return enWinner::Computer;
            }
            break;

        case enGameChoice::Scissors:
           if(RoundInfo.ComputerChoice == enGameChoice::Stone)
            {
               return enWinner::Computer;
            }
            break;
    }
    return enWinner::Player1;
}

enGameChoice ReadPlayer1Choice()
{
    int Choice;
    do
    {
        cout << "\nYou Choice : [1]:Stone, [2]:Paper, [3]:Sicesses ? ";
        cin >> Choice;
    }while(Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

string WinnerName(enWinner Winner)
{
  string arrWinnerName[3] = {"Player1", "Computer", "Draw"};
  return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
    string arrChoice[3] = {"Stone", "Paper", "Sciesses"};
    return arrChoice[Choice -1];
}

void PrintRoundresult(stRoundInfo RoundInfo)
{
    cout << "_________ Round [" << RoundInfo.RandNumber << "]_________\n\n";
    cout << "Player Choice   :" << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice :" << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner    [" << RoundInfo.WinnerName << "]\n";
    cout << "______________________________________________________\n";
}

enWinner WhoWonTheGame(short Player1WinTimes,short ComputerWinTimes,short DrawTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
    {
       return enWinner::Player1;
    }
    else if (ComputerWinTimes > Player1WinTimes)
    {
       return enWinner::Computer;
    }
    else 
    return enWinner::Draw;

}

void SetWinnerScreenColor(enWinner Winner)
{
    switch(Winner)
    {
        case enWinner::Player1:
           system("color 2F");
           break;

        case enWinner::Computer:
           system("color 4F");
           cout << "\a";
           break;
        default:
          system("color 6F");
          break;

    }
}

string Tabs (short HowTabs)
{
    string t = "";

    for(int i = 1;i <= HowTabs;i++)
    {
        t += "\t";
    }
    return t;
}

stGameResults FinalGameResult(short GameRounds,short Player1WinTimes,short ComputerWinTimes,short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.Winner = WhoWonTheGame(Player1WinTimes,ComputerWinTimes,DrawTimes);
    GameResults.WinnerName = WinnerName(GameResults.Winner);

    return GameResults;
}

void ShowFinalGameResult(stGameResults GameResults)
{
    cout << Tabs(2) << "_________________ [ Game Reslut ]_________________\n";
    cout << Tabs(2) << "Game Rounds       : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "player1 won time  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won time : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw won time     : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Round Winner      : " << GameResults.WinnerName << endl;

    SetWinnerScreenColor(GameResults.Winner);
}

int ReadHowManyRounds()
{
    short Rounds;
    do
    {
        cout << "How Wat Play 1 to 10 ?\n";
        cin >> Rounds;
    }while(Rounds < 1 || Rounds > 10);

    return Rounds;
}

void ShowGameOverSceen()
{
    cout << Tabs(2) << "\n\n____________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G A M E O V E R +++ \n\n";
    cout << Tabs(2) << "\n\n____________________________________________________\n\n";

}
 
stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;

    short Player1WinTimes = 0,ComputerWinTimes = 0,DrawTimes = 0;

    for (int GameRound = 1;GameRound <= HowManyRounds;GameRound++)
    {
        cout << "Round [" << GameRound << "] begins:\n";
        RoundInfo.RandNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        
        if(RoundInfo.Winner == enWinner::Player1)
           Player1WinTimes++;
    
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else 
            DrawTimes++;

        PrintRoundresult(RoundInfo);
    }

    return FinalGameResult(HowManyRounds,Player1WinTimes,ComputerWinTimes,DrawTimes);
}

void ResetScrenn()
{
    system("cls");
    system("color 0F");

}

void StartGame()
{
    char GameAgain = 'Y';
    do
    {

      ResetScrenn();
      stGameResults GameResults = PlayGame(ReadHowManyRounds());
      ShowGameOverSceen();
      ShowFinalGameResult(GameResults);

      cout << Tabs(3) << "\nDo you Game Again? you Ask (Y/N)?\n";
      cin >> GameAgain;

    }while(GameAgain == 'Y' || GameAgain == 'y');

}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}