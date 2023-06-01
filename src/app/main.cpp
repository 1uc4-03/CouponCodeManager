#include <iostream>
#include <limits>
using namespace std;

#include "commands.h"


int main() {

    cout << Commands::displayText << endl;
    char command;

    for (;;) {

        cout << "Input command: ";
        cin.get(command);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (Commands::commands.find(command) != Commands::commands.end()) {
            Commands::commands[command]();
        }
        else {
            cout << "Invalid command. Try again." << endl;
        }
    }

    return 0;
}
