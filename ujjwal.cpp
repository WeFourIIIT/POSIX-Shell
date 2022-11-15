#include <bits/stdc++.h>
#include <termios.h>
#include <unordered_map>

#include "ujjwal.h"

using namespace std;

unordered_map<string, string> envVars;
struct termios oldTermios, newTermios;

void clearScreen(void) {
    printf("\033[2J\033[1;1H");
}
// Place cursor based on x and y coordinates
void placeCursor(int x, int y) {
    cout << "\033[" << x << ";" << y << "H";
    fflush(stdout);
}


// Reading all env variables stored in .bashrc on startup
void readEnvVariables(void) {
    fstream file;
    file.open(".bashrc", ios::in);
    if(file.is_open()) {
        string line, delimiter = "=", key, value;
        int idx;
        while(getline(file, line)) {
            idx = line.find(delimiter);
            key = line.substr(0, idx);
            value = line.substr(idx + 1);
            envVars[key] = value;
        }
        file.close();
    }
}

string getEnvVariable(string key) {
    if(envVars.find(key) != envVars.end()) {
        return envVars[key];
    }
    return "Environment variable not found!";
}

void switchToCanonicalMode() {
    tcgetattr(0, &oldTermios);
    newTermios = oldTermios;
    // The actual magic happens here
    newTermios.c_lflag &= ~(ICANON | ECHO);
    newTermios.c_cc[VMIN] = 1;
    newTermios.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &newTermios);
    return;
}

void exitShell(int sigNum) {
    exit(0);
}
void takeInput() {
    string s;
    char ch;
    while(true) {
        cout<<getEnvVariable("PS1");
        // ASCII codes
        // (q, 113) (esc, 27) (:, 58) (enter, 10) (backspace, 127)
        // Run loop till esc or enter key is not pressed
        s = "";
        while((ch = cin.get()) != 27 && ch != 10) {
            cout<<ch;

            // If backspace key is pressed
            if(ch == 127) {
                if(s.size()){
                    s.pop_back();
                    printf("\b \b");
                }else{
                    // placeCursor(rows, 0);
                }
            }else{
                s += ch;
            }
        }

        if(ch == 27) {
            // ESC key is pressed, switch to normal mode
            // closeCanonicalMode();
            break;
        }else{
            // Enter key was pressed
            // parseInputString(s);
            exit(0);
        }
    }
}

// Initialise the POSIX shell
// All startup functions are called here
void initialise() {
    clearScreen();
    readEnvVariables();
    switchToCanonicalMode();
    takeInput();
    string s;
}