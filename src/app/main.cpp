#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::fstream;

#include "commands.h"


void createFile() {
    fstream file(Commands::fileName, fstream::in | fstream::out | fstream::trunc);
    file.close();
}

int main() {

    createFile();

    cout << Commands::displayText << endl;
    char command;

    for (;;) {

        cout << "Input command: ";
        cin >> command;

        if (Commands::commands.find(command) != Commands::commands.end()) {
            Commands::commands[command]();
        }
        else {
            cout << "Invalid command. Try again." << endl;
        }
    }

    return 0;
}
