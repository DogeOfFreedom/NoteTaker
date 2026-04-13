#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <fileapi.h>
#include <vector>

using namespace std;

void displayCommandList();

const int MAX_LINE_LENGTH = 150;

int main() {
    string dirPath = "./files";

    // Make file directory if it doesn't already exist
    CreateDirectoryA(dirPath.c_str(), nullptr);

    string input;

    cout << "Welcome to the NoteTaker CLI Application" << endl;
    cout << "Please type in \"help\" for the list of available commands" << endl;
    string command;
    do {
        cout << ">>";
        getline(cin, input);
        stringstream ss(input);
        vector<string> words;
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        command = words.at(0);
        // convert to lower case
        ranges::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "help") { // display list of commands

        } else if (command == "open") { // open existing file or create new file if doesn't exist

        } else if (command == "del") { // delete a file

        } else if (command == "ls") { // lists all files

        } else { // Invalid command
            cout << "\"" << command << "\" is an invalid command" << endl;
        }
    } while (command != "exit");
    cout << "Closing program, bye bye!" << endl;
}

void displayCommandList() {

}