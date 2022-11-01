#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Word {
private:
	string word;
	string type;
	string defenition;

public:
	Word(string word, string type, string defenition)
	{
		Word::word = word;
		Word::type = type;
		Word::defenition = defenition;

	}

	string getType()
	{
		return type;

	}

	string getWord()
	{

		return word;

	}

	string getDefenition()
	{
		return defenition;
	}

	void printDefenition()
	{
		//Set proper noun words to have capital letters at the begining
		if (type == "ProperNouns")
		{
			std::transform(word.begin(), word.end(), word.begin(), ::toupper);
			cout << "\nWord: " << word << endl;
		}
		else
		{
			cout << "\nWord: " << word << endl;
		}

		cout << "Type: " << type << endl;

		// Print each defenition containing the delimiters in a new line 
		if (defenition.find(";") != string::npos)
		{
			replace(defenition.begin(), defenition.end(), ';', '\n');
			cout << "Defenition: " << defenition << "\n" << endl;
		}
		else
		{
			cout << "Defenition: " << defenition << "\n" << endl;
		}

	}
};


