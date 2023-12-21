// InputHandler.cpp

#include "InputHandler.h"
#include <iostream>
#include <limits>

using namespace std;

string InputHandler::getInformationFromUser(const string& prompt) {
    string input;
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, input);
    return input;
}




