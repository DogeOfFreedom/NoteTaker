#include <algorithm>
#include <iostream>
#include <filesystem>
#include <string>
#include <fileapi.h>
#include <vector>
#include <fstream>

using namespace std;

void displayCommandList();
void makeNewNote();
void openFile(string filename);
void deleteFile(string filename);
void listAllFiles();

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
        vector<string> arguments;
        string tmp;
        bool commandFlag = true;
        bool quoteFlag = false;
        for (char c : input) {
            if (c != ' ' || quoteFlag) {
                if (c == '"') {
                    quoteFlag = !quoteFlag;
                }
                tmp += c;
            } else {
                if (commandFlag) {
                    command = tmp;
                    commandFlag = false;
                } else {
                    arguments.push_back(tmp);
                }
                tmp.clear();
            }
        }
        if (arguments.empty() && commandFlag) {
            command = tmp;
        } else if (!tmp.empty()) {
            arguments.push_back(tmp);
        }

        if (!tmp.empty()) {
            tmp.clear();
        }

        if (quoteFlag) {
            cout << "Invalid arguments, you must close the quotes" << endl;
            continue;
        }

        // convert command to lower case
        ranges::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "help") { // display list of commands
            if (!arguments.empty()) {
                cout << "\"help\" takes zero arguments" << endl;
            } else {
                displayCommandList();
            }
        } else if (command == "new") {
            if (!arguments.empty()) {
                cout << "\"new\" doesn't require arguments" << endl;
            } else {
                makeNewNote();
            }
        } else if (command == "open") { // open existing file or create new file if doesn't exist
            if (arguments.size() != 1) {
                cout << "\"open\" only accepts one argument" << endl;
            } else {
                openFile(arguments.at(0));
            }
        } else if (command == "del") { // delete a file
            if (arguments.size() != 1) {
                cout << "\"del\" only accepts one argument" << endl;
            } else {
                deleteFile(arguments.at(0));
            }
        } else if (command == "ls") { // lists all files
            if (!arguments.empty()) {
                cout << "\"ls\" doesn't require arguments" << endl;
            } else {
                listAllFiles();
            }
        } else { // Invalid command
            cout << "\"" << command << "\" is an invalid command" << endl;
        }
    } while (command != "exit");
    cout << "Closing program, bye bye!" << endl;
}

void displayCommandList() {
    cout << "NoteTaker has the following commands:" << endl;
    cout << "\"new\" - Creates a new file" << endl;
    cout << "\"open\" [file argument] - Opens the specified file" << endl;
    cout << "\"del\" [file argument] - Deletes the specified file" << endl;
    cout << "\"ls\" - Lists all files" << endl;
}

void makeNewNote() {
    string filename;
    cout << "New Note Name:";
    getline(cin, filename);
    ofstream file("files/" + filename + ".txt");
    cout << "Enter the contents of the new note below. Press \"enter\" to finished" << endl;
    string tmp;
    while (getline(cin, tmp) && !tmp.empty()) {
        file << (tmp + "\n");
    }
    cout << "\"" << filename << "\" has been created" << endl;
}

void openFile(string filename) {
    fstream file("files/" + filename, ios::in | ios::out);
    if (file.fail()) {
        cout << "\"" << filename << "\" doesn't exist" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void deleteFile(string filename) {
    if (remove(("files/" + filename).c_str()) == 0) {
        cout << "\"" << filename << "\" deleted" << endl;
    } else {
        cout << "\"" << filename << "\" doesn't exist" << endl;
    }
}

void listAllFiles() {
    string dirPath = "./files";
    for (auto file : filesystem::directory_iterator(dirPath)) {
        cout << file.path().filename() << endl;
    }
}