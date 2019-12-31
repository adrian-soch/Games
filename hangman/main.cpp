//============================================================================
// Name        : hangman.cpp
// Author      : Adrian Sochaniwsky
// Version     :
// Copyright   : 
// Description : Hangman in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

void welcome(){
	puts("Welcome to Hangman");
	cout <<"Press enter to continue" << endl;
	cin.ignore();
}

void gameOver(){
	puts("Game Over");
	cout <<"Press any key to exit" << endl;
	cin.ignore();
}

string getPhrase(){

	string phrase;
	cout << "Enter the secret phrase: ";
	getline(cin, phrase);

	while(phrase == ""){
		cout << "\nPhrase invalid, Enter the secret phrase: ";
		getline(cin, phrase);
	}
	return phrase;
}
string hidePhrase(string secret){

	string hidden = "";
	for(string::size_type i = 0; i < secret.length(); i++){
		if(secret[i] != ' ')
			hidden.append("*");
		else if(secret[i] == ' ')
			hidden.append("_");
	}
	return hidden;
}
void drawBoard(string guess);
bool updateBoard(string guess, string secret, string hidden);
string getGuess();

int main() {

	welcome();
	string secret = getPhrase();
	string hidden = hidePhrase(secret);
	string guess;
	int attemps = 6;
	bool done = false;
	bool correctGuess;
	drawBoard(hidden);
	do{
		guess = getGuess();
		correctGuess = updateBoard(guess, secret, hidden);
		done  = true;
	}while(!done);



	return 0;
}
