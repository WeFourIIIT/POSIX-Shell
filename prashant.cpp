#include "prashant.h"
#include <bits/stdc++.h>
using namespace std;

vector<string> history;
string PowerShell1 = "";
string HOMEPATH, USERNAME, HOSTSYSTEM;
bool exitStatusOfPreviousCommand = true;
int firsRow = 0;
int firstColumn = 0;
string myHistoryFile = "history.txt";
unordered_map<string, string> mapForAlias;

vector<string> mergeAlltokensInSingleCommand(string cmd)
{
    vector<string> myResult;
    int size = cmd.size() + 10;
    char cmdCopied[size];
    strcpy(cmdCopied, cmd.c_str());
    char delimeter[32] = " \n\t\r";
    char *temp = (char *)calloc(2048, sizeof(char));
    temp = strtok(cmdCopied, delimeter);
    if (temp == NULL)
    {
        return myResult;
    }
    else
    {
        while (temp != NULL)
        {
            string str = string(temp);
            divideCommand(str);
            myResult.push_back(str);
            temp = strtok(NULL, delimeter);
        }
    }
    return myResult;
}

void pipeHandler(string cmd)
{
}

void redirectionHandler(string cmd)
{
}

void performcdCommand(string pathCmd)
{
}

void RUNAlias(vector<string> args, bool status)
{
}

void settleMapAlias()
{
    // ifstream inputFile(".myrc");
    // string line;
    // while (getline(inputFile, line))
    // {
    //     vector<string> rcVector=
    // }
}

void historySave()
{
    FILE *txtFile = fopen(myHistoryFile.c_str(), "a");
    int i = 0;
    while (i < history.size())
    {
        divideCommand(history[i]);
        history[i].erase(remove(
                             history[i].begin(), history[i].end(), '\n'),
                         history[i].end());

        history[i].erase(remove(
                             history[i].begin(), history[i].end(), '\t'),
                         history[i].end());

        if (!history[i].empty())
        {
            fprintf(txtFile, "\n%s", history[i].c_str());
        }
        i++;
    }
    fclose(txtFile);
}

void cursorPointer(int r, int c)
{
    string row, col;
    string setCursor = "\033[";
    row = to_string(r);
    setCursor.append(row);
    setCursor.append(";");
    col = to_string(c);
    setCursor.append(col);
    setCursor.append("H");
    std::cout << setCursor;
    fflush(stdout);
}

static inline void divideCommand(std::string &s)
{
    // leftTrim
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
    // righttrim
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

void commandTOBeExecuted(string commandName)
{
    vector<string> arguments;
    arguments = mergeAlltokensInSingleCommand(commandName);
    history.push_back(commandName);
    divideCommand(commandName);

    //  if PS1 detected;
    if (commandName.rfind("PS1", 0) == 0)
    {
        cout << "PS1 Detected" << endl;
        commandName.erase(remove(commandName.begin(), commandName.end(), '"'), commandName.end());
        size_t pos = commandName.find("DEFAULT");
        if (pos != std::string::npos)
        {
            commandName.erase(pos, string("DEFAULT").length());
        }
        PowerShell1 = commandName.substr(commandName.find_first_of("=") + 1);
        return;
    }

    // Handle pipes
    size_t pipeFound = commandName.find("|");
    if (!(pipeFound == std::string::npos))
    {
        pipeHandler(commandName);
        return;
    }

    // Shell Input/Output Redirections
    size_t redirection1 = commandName.find(">>");
    size_t redirection2 = commandName.find(">");
    size_t redirection3 = commandName.find("<");

    if (!(redirection1 == std::string::npos && redirection2 == std::string::npos && redirection3 == std::string::npos))
    {
        redirectionHandler(commandName);
    }

    // Environment variables
    // If user enter echo $HOME command print HOME directory path
    if (commandName == "echo $HOME")
    {
        cout << HOMEPATH << endl;
    }

    // used to show the user names of users currently logged in to the current host
    else if (commandName == "echo $USER")
    {
        cout << USERNAME << endl;
    }
    // displays the name of the current host system
    else if (commandName == "echo $HOSTNAME")
    {
        cout << HOSTSYSTEM << endl;
    }

    // the pid (process id) of the shell interpreter running your script
    else if (commandName == "echo $$")
    {
        cout << getpid() << endl; // process ID of the calling process
    }

    // represents the exit status of the previous command.
    else if (commandName == "echo $?")
    {
        if (exitStatusOfPreviousCommand)
        {
            cout << "0" << endl;
        }
        else
        {
            cout << "1" << endl;
        }
    }

    // Full path name of your current directory (from the root directory).
    else if (arguments[0] == "pwd")
    {
        char path[1024];
        getcwd(path, sizeof(path));
        cout << string(path) << endl;
    }

    // change the directory
    else if (arguments[0] == "cd")
    {
        performcdCommand(commandName);
    }

    // print all the command that was previously executed
    else if (arguments[0] == "history")
    {
        int i = 0;
        while (i < history.size())
        {
            divideCommand(history[i]);
            history[i].erase(remove(
                                 history[i].begin(), history[i].end(), '\n'),
                             history[i].end());

            history[i].erase(remove(
                                 history[i].begin(), history[i].end(), '\t'),
                             history[i].end());

            if (!history[i].empty())
            {
                cout << i << " " << history[i] << endl;
            }
            i++;
        }
    }

    // clear the screen
    else if (arguments[0] == "clear")
    {
        // clear line micro
        cout << "\033[2K";
        // clear screen micro
        cout << "\033[H\033[J";
        // set the pointer
        cursorPointer(firsRow, firstColumn);
    }

    // quit the posix shell
    else if (arguments[0] == "quit")
    {
        historySave();
        cout << "Good Bye" << endl;
    }

    else if (arguments[0] == "export")
    {
        // from 1994 line to 2060 rishabh will do
    }
    else if (arguments[0] == "alarm")
    {
        // rishabh will do
    }

    else if (arguments[0] == "open")
    {
        const char *nameOfFile = arguments[1].c_str();
        pid_t processID = fork();
        if (processID == 0)
        {
            close(2);
            execlp("xdg-open", "xdp-open", nameOfFile, NULL);
        }
    }
    // check is there any alias or not in map;
    else if (mapForAlias.find(arguments[0]) != mapForAlias.end())
    {
        string valueOfAlias = mapForAlias[arguments[0]];
        vector<string> tokenAlias;
        stringstream check1(valueOfAlias);
        string str;
        while (getline(check1, str, ' '))
        {
            tokenAlias.push_back(str);
        }
        int i = 1;
        while (i < arguments.size())
        {
            tokenAlias.push_back(arguments[i]);
            i++;
        }
        RUNAlias(tokenAlias, false);
    }
    // if no alias present in map and new alias comes
    else if (arguments[0] == "alias")
    {
        if (arguments.size() <= 3)
        {
            cout << "Invalid Alias!!!" << endl;
            exitStatusOfPreviousCommand = false;
            return;
        }
        else
        {
            string keyAlias = arguments[1];
            string valueAlias = "";
            int i = 0;
            while (i < arguments.size())
            {
                valueAlias += arguments[i] + " ";
                i++;
            }
            divideCommand(valueAlias);
            mapForAlias[keyAlias] = valueAlias;
            ofstream outputFile;
            outputFile.open(".myrc", std::ios_base::app);
            outputFile << '\n'
                       << commandName;

            outputFile.close();
            settleMapAlias();
        }
    }
    else if (arguments[0] == "fg")
    {
        // Ujjwal will do this foreground precess part;
    }
    else if (arguments[0] == "setenv")
    {
        // ujjwal will do
    }
    else if (arguments[0] == "unsetenv")
    {
        // ujjwal will do
    }
    else if (arguments.back() == "&")
    {
        arguments.pop_back();
        RUNAlias(arguments, true);
    }
    else if (arguments.back().back() == '&')
    {
        arguments[arguments.size() - 1][arguments.back().size() - 1] = '\0';
        RUNAlias(arguments, true);
    }

    // jobs left

    else
    {
        RUNAlias(arguments, false);
    }
}
