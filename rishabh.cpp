#include "rishabh.h"


void alarmMessage(vector<string> mymsg, int sec)// if (args[0] == "alarm") alarmMessage(args, stoi(args[1]));
{
    int mysize;
    mysize = mymsg.size();
    if (mysize < 3)
    {
        cout << "Invalid alarm";
        cout << endl;
        return;
    }
   else{
   
    string sms;
    sms = "";

    int i;
    i = 2;

    while (i < mysize)
    {
        sms = sms + mymsg[i];
        sms = sms + " ";
        i = i + 1;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(sec);
        cout << sms;
        cout << endl;
        cout << prompt();
        exit(EXIT_SUCCESS);
    }
    
    }
}

void fileOpen(const char *filename)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        close(2);
        execlp("xdg-open", "xdg-open", filename, NULL);
        exit(0);
    }
}



 /* export x = 3, export -p, export -n name */
    if (args[0] == "export")
    {
        int mysize;
        mysize = args.size();

        if (mysize == 0)
        {
            status = false;
            return;
        }
        if (mysize > 1 && args[1].empty())
        {
            status = false;
            return;
        }
        else
        {
            if (mysize > 1 && !(args[1] != "-p" || args[1] != "-n"))
            {
                status = false;
                return;
            }
        }

        if (mysize > 1 && args[1] == "-p")
        {
            int expsize = exportMap.size();
            if (0 < expsize)
            {
                cout << "Export Variables are";
                cout << endl;
                for (auto itr : exportMap)
                {
                    cout << itr.first;
                    cout << " = ";
                    cout << itr.second;
                    cout << endl;
                }
            }
        }
        else if (mysize > 1 && args[1] == "-n")
        {
            string myremove;
            myremove = args[2];
            exportMap.erase(myremove);
        }
        else if (mysize == 4)
        {

            exportMap[args[1]] = args[3];

            setenv(args[1].c_str(), args[3].c_str(), 1);

            cout << GREEN;
            cout << "Exported successfully";
            cout << RESET;
            cout << endl;
        }
        else
        {
            status = false;
            cout << "Invalid command";
            cout << endl;
        }
    }




































