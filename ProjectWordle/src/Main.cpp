#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <windows.h> 

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::getline;

using std::ifstream;
using std::srand;
using std::time;



const int WORD_LENGTH = 5; //dont touch cuz wordmaster_guesses has 5 letter words

//changable variables
const int NUMBER_OF_GUESSES = 6;
const bool ENABLE_HINTS = true;

const char MATCHED = 'W';
const char PARTIAL = 'o';
const char NOT_MATCHED = 'x';

const string VALID_WORDS_FILE = "valid-wordle-words.txt";
const string POTENTIAL_WORDS_FILE = "wordmaster_guesses.txt";


//colors
#define GREEN 2
#define YELLOW 6
#define GRAY 7

//cheating

bool usedHints = false;

int main();

void toLowerCase(string &input)
{
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c)
        {return std::tolower(c); });
}



string getWord()
{
    string word;
    ifstream file(POTENTIAL_WORDS_FILE);
    int countLine = 0;
    while (getline(file, word))
    {
        countLine++;
    }
    file.clear();
    file.seekg(0);
    /*
    srand(time(NULL));

    int rand1 = rand() % countLine + 1;
    int rand2 = rand() % countLine + 1;
    */
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, countLine);
    cout << dist6(rng) << endl;
    
    int line = dist6(rng);
    
    
    int currentLine = 0;

    while (getline(file, word))
    {
        currentLine++;
        if (currentLine == line)
        {
            break;
        }
    }

    for (int i = 0; i < word.length(); i++)
    {
        word[i] = tolower(word[i]);
    }

    return word;
}

bool validation(string input)
{
	if (input.length() == WORD_LENGTH)
	{
		if (input.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == string::npos)
		{
            ifstream file(VALID_WORDS_FILE);
            string wordFromFile;
            while(getline(file, wordFromFile))
            {
	            if (wordFromFile == input)
	            {
                    return true;
	            } 
            }
            //cout << "Not a valid word from list!" << endl;
            ifstream file2(POTENTIAL_WORDS_FILE);
            while(getline(file2, wordFromFile))
            {
	            if (wordFromFile == input)
	            {
	            	return true;
	            } 
            }
            return false;
		} else
		{
            //cout << "Not a valid character" << endl;
            return false;
		}
		
	} else
	{
		//cout << "Please enter a five letter word." << endl;
		return false;
	}
}

void winScreen(int guesses)
{
    cout << "\033c";
    cout << "$$\       $$\   $$$$$$\   $$\       $$\\" << endl;
	cout << "$$ |  $\  $$ | $$  __$$\  $$ |  $\  $$ |" << endl;
	cout << "$$ | $$$\ $$ | $$ /   $$ |$$ | $$$\ $$ |" << endl;
	cout << "$$  $$ $$\$$ | $$ |   $$ |$$  $$ $$\$$ |" << endl;
	cout << "$$$$   _$$$$ | $$ |   $$ |$$$$   _$$$$ |" << endl;    
	cout << "$$$   / \$$$ | $$ |   $$ |$$$   / \$$$ |" << endl;
	cout << "$$   /   \$$ |  $$$$$$   |$$   /   \$$ |" << endl;
	cout << "\__ /     \__|  \______ / \__ /     \__|" << endl;


    cout << "\n\nYou Won!\nTotal Guesses: " << guesses << endl;
    if (usedHints)
    {
	    cout << "\nDon't be too happy, you used hints!\n" << endl;
    }
    cout << "Would you like to restart ? (Y / N) : "; char input; cin >> input;
    if (input == 'Y' || input == 'y')
    {
    	cout << "\033c";
		main();
	} else
	{
		cout << "\033c";
		cout << "Thanks for playing!" << endl;
	}
}

char getHint(const std::string& guessedLetters, const std::string& word) {
    std::vector<char> potentialHints;

    for (char ch : word) {
        if (guessedLetters.find(ch) == std::string::npos) {
            potentialHints.push_back(ch);
        }
    }

    if (!potentialHints.empty()) {
        srand(static_cast<unsigned>(time(NULL)));
        return potentialHints[rand() % potentialHints.size()];
    }

    return '\0';
}

int main()
{

    string word = getWord();
    cout << word << endl;

    string input;
    int guesseCount = 0;

    cout << "$$\\      $$\\                           $$\\  $$\\           " << endl;
    cout << "$$ | $\\  $$ |                          $$ | $$ |          " << endl;
    cout << "$$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ | $$ | $$$$$$\\  " << endl;
    cout << "$$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$  __$$ | $$ |$$  __$$\\ " << endl;
    cout << "$$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ /  $$ | $$ |$$$$$$$$ |" << endl;
    cout << "$$$  / \\$$$ |$$ |  $$ |$$ |      $$ |  $$ | $$ |$$   ____|" << endl;
    cout << "$$  /   \\$$ |\\$$$$$$  |$$ |      \\$$$$$$$ | $$ |\\$$$$$$$\\ " << endl;
    cout << "\\__/     \\__| \\______/ \\__|       \\_______| \\__| \\_______|" << endl;

			
        
    cout << "\nPress enter to continue..." << endl;
    cin.get();
    cout << "\033c";
    
    vector<char> result(WORD_LENGTH);
    string guessedLetters;
    

    while (guesseCount < NUMBER_OF_GUESSES)
    {
	    do
	    {
		    cout << guesseCount + 1 << "\\" << NUMBER_OF_GUESSES << " Enter a five letter word: ";
            getline(cin, input);
			toLowerCase(input);
            if (validation(input))
            {
                if (input != word)
                {
                    guesseCount++;
                    for (int i = 0; i < input.length(); i++)
                    {
	                    if (input[i] == word[i])
	                    {
		                    result[i] = MATCHED;
                            if (guessedLetters.find(input[i]) == string::npos)
                            {
                            	guessedLetters += input[i];
                            }
	                    } else if (word.find(input[i]) != string::npos)
	                    {
	                    	result[i] = PARTIAL;

                            if (guessedLetters.find(input[i]) == string::npos)
                            {
                                guessedLetters += input[i];
                            }
	                    } else
	                    {
	                    	result[i] = NOT_MATCHED;
                            if (guessedLetters.find(input[i]) == string::npos)
                            {
                                guessedLetters += input[i];
                            }
	                    }
                    }
                    int temp = 0;
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    for (char c : result)
                    {
                        
                        if (c == MATCHED)
                        {
                            SetConsoleTextAttribute(hConsole, GREEN);
                            cout << input[temp] << " ";
                        } else if (c == PARTIAL)
                        {
                            SetConsoleTextAttribute(hConsole, YELLOW);
                            cout << input[temp] << " ";
						} else
						{
                            SetConsoleTextAttribute(hConsole, GRAY);
                            cout << input[temp] << " ";
						}
                        SetConsoleTextAttribute(hConsole, GRAY);
                        temp++;
                    }
                    cout << "\n" << endl;
                    
                    
                } else
                {
                    winScreen(guesseCount + 1);
                    return 0;
                }
			} else if(input == "h")
			{
				if (ENABLE_HINTS)
				{
                    char hint = getHint(guessedLetters, word);
                    if (hint != '\0') {
                        std::cout << "Hint : " << hint << std::endl;
                    }
                    else {
                        std::cout << "No hint available." << std::endl;
                    }
                    cout << "\n" << endl;
                    guesseCount++;
                    usedHints = true;
				} else
				{
					cout << "Hints are disabled!\n" << endl;
				}
			}else if (input == "q")
            {
                cout << "\033c" << "Quit Game!~" << endl;
                return -1;
            }
			else
			{
				cout << "Invalid input!\n" << endl;
			}


        } while (true);

    }

    cout << "\033cYou lost!\nCorrect word was : " << word << endl;
    return 0;
}