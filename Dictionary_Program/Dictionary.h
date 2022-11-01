#include <iostream>
#include "Word.h"
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

class Dictionary_Part01 {
protected:
	vector<Word> words;

public:

	//Function to get word type. The function recives a string and searches it to find the words within the square brackets. 
	string getWordType(string record)
	{
		string type;

		if (record.find("[misc]") != string::npos)
		{
			type = "Misc";
		}
		else if (record.find("[v]") != string::npos)
		{
			type = "Verb";
		}

		else if (record.find("[adv]") != string::npos)
		{
			type = "Adverb";
		}
		else if (record.find("[adj]") != string::npos)
		{
			type = "Adjactive";
		}
		else if (record.find("[prep]") != string::npos)
		{
			type = "Preposition";
		}
		else if (record.find("[pn]") != string::npos)
		{
			type = "ProperNouns";
		}
		else if (record.find("[n_and_v]") != string::npos)
		{
			type = "NounAndVerb";
		}
		else if (record.find("[n]") != string::npos)
		{
			type = "Noun";
		}

		return type;

	}

	//Funtion to read file into vector
	void createDictionary(string filename = "dictionary2021.txt")
	{
		ifstream myfile(filename);
		if (myfile.is_open())
		{
			cout << "Attempting to read text file...\n";
			string currentLine;
			string currentWord = "none";
			string type = "none";
			string currentDescription = "none";

			while (!myfile.eof())
			{

				getline(myfile, currentLine);
				//currentWord will only hold the first part of the string utill the first space
				currentWord = currentLine.substr(0, currentLine.find(" ", 0));


				type = getWordType(currentLine);

				getline(myfile, currentLine);
				currentDescription = currentLine;


				getline(myfile, currentLine);

				//Put words into the Words vector
				Word newWord(currentWord, type, currentDescription);
				words.push_back(newWord);

			}
			myfile.close();
			cout << "Reading from file complete!\n";
		}

		else cout << "unable to open file";
	}


	//Function for Searching the dictionary 
	void searchWord()
	{
		string wordInput;
		cout << "Enter a word to see the defenition: ";
		cin >> wordInput;

		//Convert all user input to lowercase
		transform(wordInput.begin(), wordInput.end(), wordInput.begin(), ::tolower);

		for (Word w : words)
		{
			if (w.getWord() == wordInput)
			{
				w.printDefenition();
				return;
			}
		}
		cout << "word not found" << endl;
	}


	//Function to print all words with more than 3 'Z's
	void zCount()
	{
		for (Word w : words)
		{
			string word = w.getWord();

			//Count number of z in word
			size_t n = count(word.begin(), word.end(), 'z');

			if (n > 3)
			{
				cout << "Word: " << word << "\n" << endl;
			}
		}

	}


	//Funtion to find words with Qs without a following U
	void qWords()
	{

		for (Word w : words)
		{
			//Find words that have a 'q' and then print only words without a following 'u'
			string word = w.getWord();
			if (word.find("q") != string::npos)
			{
				if (word.find("qu") == string::npos)
				{
					cout << word << endl;

				}
			}
		}
		cout << "\n";
	}

};


class Dictionary_part02 : public Dictionary_Part01 {

public:

	//Funtion to list all words that are noun and verb
	void outputNounVerb() {
		for (Word w : words)
		{
			string word = w.getWord();

			if (w.getType() == "NounAndVerb")
			{
				cout << word << endl;
			}
		}
	}


	//Funtion to list all words that are palindromes
	void outputPalindrome() {
		for (Word w : words)
		{
			string word = w.getWord();

			//Check if word reversed is still the same word
			if (word == string(word.rbegin(), word.rend()))
			{
				cout << word << endl;
			}
		}
	}

	//Funtion to list all words that are anagrams
	void outputAnagram()
	{
		bool isAnagram = false;
		string inputWord;
		cout << "Please enter word: ";
		cin >> inputWord;

		for (Word w : words)
		{
			isAnagram = false;
			string word = w.getWord();

			//Make sure word lengths are the same
			if (inputWord.length() == word.length())
			{
				//Sort both word in alphabetical order
				sort(inputWord.begin(), inputWord.end());
				sort(word.begin(), word.end());

				//Check if sorted words are a match
				if (inputWord == word)
				{
					cout << w.getWord() << endl;
				}
			}
		}
	}


	//Funtion to play the word guessing game
	void guessingGame()
	{
		srand(time(0));
		string guessAttempt;
		string guessWord;
		int counter = 0;

		int random = (rand() % words.size());

		//Get the random word only if its a Noun
		do {
			//Create random number
			random = (rand() % words.size());

		} while (words[random].getType() != "Noun");

		//Set the random word
		guessWord = words[random].getWord();

		cout << "Word defenition: " << words[random].getDefenition() << endl;
		cout << "Word length: " << guessWord.length() << "\n";


		//Loop for guessing word
		do {
			cout << "Guess the word: ";
			cin >> guessAttempt;

			//Convert all user input to lowercase
			transform(guessAttempt.begin(), guessAttempt.end(), guessAttempt.begin(), ::tolower);

			if (guessAttempt == guessWord)
			{
				cout << "\nCorrect!" << endl;
				break;
			}
			else
			{
				cout << "\nWrong!" << endl;
				if (counter != 2)
				{
					cout << "Hint: Letter " << counter + 1 << " is " << guessWord[counter] << endl;
				}
				counter = counter + 1;
			};
		} while (counter != 3);

		cout << "Word is: " << guessWord << endl;
	}

	// Function to run the main menu of the application
	void run()
	{
		Dictionary_Part01::createDictionary();
		cout << "---- W E L C O M E  T O   T H E  D I C T I O N A R Y  A P P L I C A T I O N ----\n";
		bool exit = 0;
		char selection;
		while (!exit)
		{
			cout << "\n(1) Search for a word.\n";
			cout << "(2) Find words with more than 3 'Z's.\n";
			cout << "(3) List words with 'Q' and no following 'U'.\n";
			cout << "(4) List words that are both Noun and Verb.\n";
			cout << "(5) List all words that are palindromes.\n";
			cout << "(6) List anagrams.\n";
			cout << "(7) Guessing Game.\n";
			cout << "(8) Exit\n\n";

			cout << "Enter your choice and press enter: ";
			cin >> selection;

			switch (selection)
			{
			case '1':
				Dictionary_Part01::searchWord();
				break;

			case '2':
				Dictionary_Part01::zCount();
				break;

			case '3':
				Dictionary_Part01::qWords();
				break;

			case '4':
				outputNounVerb();
				break;

			case '5':
				outputPalindrome();
				break;

			case '6':
				outputAnagram();
				break;

			case '7':
				guessingGame();
				break;

			case '8':
				exit = 1;
				break;
			default:
				cout << "Invalid option, try again\n";
			}
		}
	}


};
