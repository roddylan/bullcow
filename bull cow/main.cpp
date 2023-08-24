#include <iostream>
#include <string>
#include <map>
#include "FBullCowGame.h"
#define TMap std::map;


using FText = std::string;
using int32 = int;

void ChooseWordLength();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool bAskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game


// entry point of app
int main()
{
	do 
	{
		ChooseWordLength();

		PrintIntro();

		PlayGame();

	} while (bAskToPlayAgain());

	return 0; // exit app

}

void PrintIntro()
{
	// intro game
	//int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cow Game \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of? \n";
	return;
}

FText GetValidGuess() //loop continually until user gives valid guess
{


	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		//get guess
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter a Guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please Enter a Word With No Repeating Letters \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please Enter Your Guess in All Lowercase \n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until valid input
	return Guess;
}

void PlayGame()
{

	BCGame.Reset();
	// loop for num of turns asking for guesses
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while game is NOT WON
	//and while tries still remain
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess();
		//std::cout << std::endl;


		//submit valid guess
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << ". ";
		std::cout << "Cows = " << BullCowCount.Cows << std::endl << std::endl;

		//TODO Summarize game
	}
	PrintGameSummary();
}

bool bAskToPlayAgain()
{
	std::cout << "Play again? (y/n) \n";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) //the game is won
	{
		std::cout << "You Win! Good Job! \n";
	}
	else
	{
		std::cout << "Better luck next time :( \n";
	};
}

void ChooseWordLength()
{
	int32 LetterCount;
	FText temporary = "";
	std::cout << "Please Enter a Preferred Word Length (3-6): ";
	do
	{
		std::cin >> LetterCount;
		std::getline(std::cin, temporary); //temp variable to get rid of weird input skip
		if (BCGame.CheckLetterCountValidity(LetterCount))
		{
			
			BCGame.SetHiddenWord(LetterCount);
		}
		else
		{
			std::cout << "Please enter a valid response. \n";
		}
	} while (!BCGame.CheckLetterCountValidity(LetterCount));
}