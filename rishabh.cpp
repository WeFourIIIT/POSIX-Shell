#include <unistd.h>
#include "rishabh.h"
 
void alarmMessage(vector<string> mymsg, int sec) // if (args[0] == "alarm") alarmMessage(args, stoi(args[1]));
{
    int mysize;
    mysize = mymsg.size();
    if (mysize < 3)
    {
        cout<<endl<<"Invalid alarm";
        cout<<endl;
        return;
    }
    else
    {

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
        if (pid == 0) {
            sleep(sec);
            cout<<sms;
            cout<<endl;
            
            ch=10; 
 
        if(ch==10) 
        { 
 exit(EXIT_SUCCESS);
           // break; 
 
        } 
        }else{
            return;
        }
    }
}

void fileOpen(const char *filename) {
    pid_t pid = fork();
    if (pid == 0) {
        close(2);
        execlp("open", "open", filename, NULL);
        exit(0);
    }
}



