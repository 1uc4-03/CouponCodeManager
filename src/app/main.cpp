#include <iostream>
#include "commands.h"

using namespace std;


int main() {

    cout << Commands::displayText << endl;
    char command;

    for (;;) {

        cout << "Input command: ";
        cin >> command;

        if (Commands::commands.find(command) != Commands::commands.end()) {
            Commands::commands[command];
        }
        else {
            cout << "Invalid command. Try again." << endl;
        }
    }

    return 0;
}
