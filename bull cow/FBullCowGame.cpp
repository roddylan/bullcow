#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

void FBullCowGame::Reset()
{
	//constexpr int32 MAX_TRIES = 3;
	//MyHiddenWord = "planet";
	MyCurrentTry = 1;
	bGameWon = false;
	bGameStart = false;
	return;
}

int FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,6}, {5,8}, {6,10}, {7,13} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	//int32 HiddenWordLength = MyHiddenWord.length();
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (! IsIsogram(Guess)) //if guess isnt isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (! IsLowercase(Guess)) //if guess isnt lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if guess length wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else //otherwise, return OK
	{
		return EGuessStatus::OK;
	};
	
}

bool FBullCowGame::CheckLetterCountValidity(int32 LetterCount) const
{
	if (LetterCount < 3 || 7 < LetterCount)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// recieves valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	
	FBullCowCount FBullCowCount;

	int32 WordLength = MyHiddenWord.length(); //guess length = hidden word length
	//loop through all letters in Hidden Word
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++) // HWChar = Hidden word character # | GChar = Guess Character #
	{
		//compare letters against guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//if match
			if (Guess[GChar] == MyHiddenWord[HWChar])
			{
				//if in same place
				if (HWChar == GChar)
				{
					//increment bulls
					FBullCowCount.Bulls++;
				}
				//if not
				else
				{
					//increment cows
					FBullCowCount.Cows++;
				};

			};
		};
	};
	if (FBullCowCount.Bulls == WordLength)
	{
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	return FBullCowCount;
}

bool FBullCowGame::SetHiddenWord(int32 LetterCount)
{
	TMap<int32, FString> LetterCountToHiddenWord{ {3,"ban"},{4,"sand"},{5,"throw"},{6,"planet"},{7,"planets"} };
	MyHiddenWord = LetterCountToHiddenWord[LetterCount];
	bGameStart = true;
	return bGameStart; //TODO change return
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; //setup map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		};

	}

	//run through letters
		//if the letter is in the map
			//NO ISOGRAM
		//otherwise
			//add letter to map as seen


	return true; // for ex in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (! islower(Letter)) 
		{
			return false;
		};
	}
	return true;
}
