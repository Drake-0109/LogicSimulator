#include <cstdio>
#include <cstdlib>

#include "../include/textUI.h"

int main() {
    int command;
    TextUI* UI = new TextUI();

    while(true) {
        UI->displayMenu();

        if(scanf("%d", &command) == 1) {
            UI->processCommand(command);
        } else {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');   // Clear the input buffer
        }
    }
    delete UI;
    return 0;
}