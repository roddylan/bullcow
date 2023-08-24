#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all values initialized to zero (0)
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame
{
public:
	FBullCowGame(); //constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; // TODO make more rich return value
	bool CheckLetterCountValidity(int32) const;

	//counts bulls and cows, increases try # assuming valid guess
	void Reset(); //TODO Make more rich return value
	FBullCowCount SubmitValidGuess(FString);
	bool SetHiddenWord(int32);


private:
	//see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	bool bGameStart = false; 

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};