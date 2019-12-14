#pragma once

#include "FBullCowGame.h"
#include <map>

// To make syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

EGuessStatus FBullCowGame::CheckGuessValidity (FString Guess) const {
	if (!IsIsogram(Guess))
		return EGuessStatus::Not_Isogram;
	else if (!IsLowercase(Guess))
		return EGuessStatus::Not_Lowercase;
	else if (Guess.length() != GetHiddenWordLength())
		return EGuessStatus::Wrong_Length;

	return EGuessStatus::OK;
}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLenthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLenthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset() {
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	MyCurrentTry++;

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
		bGameIsWon = true;

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1)
		return true;

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter] == true)
			return false;
		else
			LetterSeen[Letter] = true;
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word)
		if (isupper(Letter))
			return false;
	
	return true;
}

