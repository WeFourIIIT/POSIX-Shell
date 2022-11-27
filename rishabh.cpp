#include <unistd.h>
#include "rishabh.h"

struct bg_job
{
    char job_name[300];
    pid_t PID;
};

// bg_job jobs[50];
vector<bg_job> jobs;

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



 
void RUN(vector<string> args, bool should_be_background)//call RUN(args, true);
{
    int status;
    pid_t pid = fork(), wpid;
    // args[] = NULL;
    // args.push_back(nullptr);

    if (pid == 0)
    {
        // cout << RED << "In child" << RESET << endl;

        char *parsed[100];
        int i = 0;
        for (i = 0; i < args.size(); i++)
        {
            parsed[i] = (char *)args[i].c_str();
        }
        parsed[i] = NULL;

        // cout << RED << "execvp for - " << parsed[0] << RESET << endl;

        setpgid(0, 0);
        if (execvp(parsed[0], parsed) < 0)
        {
            perror("Command not found");
            status = false;
            cout << RED << args[0] << RESET << endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    else
    {

        if (should_be_background == 0)
        {
            CURR_JOB = args[0];
            CHILD_ID = pid;

         

            for (   int i = 1;i < args.size();i = i + 1)
            {

                CURR_JOB = CURR_JOB + " ";
                CURR_JOB = CURR_JOB + args[i];

                
            }

            signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(STDIN_FILENO, pid);
            wpid = waitpid(pid, &status, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpgrp());

            signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

           // while (true)
           // {

                if (WIFSTOPPED(status))
                {

                    cout << CURR_JOB << " with PID = " << pid << " suspended." << endl;

                    struct bg_job temp_bg;

                    background_n = background_n + 1;

                 //   while (true)
                  //  {

                        strcpy(temp_bg.job_name, CURR_JOB.c_str());
                        temp_bg.PID = CHILD_ID;
                        jobs.push_back(temp_bg);
                    //    break;
                   // }
                }

            //    break;
           // }

            return;
        }

        else
        {

            //while (true)
            //{

                background_n = background_n + 1;

                struct bg_job temp_bg;

                temp_bg.PID = pid;
                strcpy(temp_bg.job_name, args[0].c_str());

             

                for (   int i = 1;i < args.size(); i = i + 1)
                {

                    strcat(temp_bg.job_name, " ");
                    strcat(temp_bg.job_name, args[i].c_str());

                   
                }

                cout << "[" << background_n << "] " << pid << endl;
                jobs.push_back(temp_bg);

              //  break;
           // }

            return;
        }
    }
}

 

int32_t fg(vector<string> s_args)//call fg(args);
{
    char *args[32];
    int no_args = s_args.size();
    for (int i = 0; i < no_args; i++)
    {
        args[i] = (char *)s_args[i].c_str();
    }

    if (no_args != 2)
    {
        cout << "Syntax = fg <jobNumber>\n"
             << endl;
        return -1;
    }
    int needed_id;
    int job_no = stoi(string(args[1]));
    int status;

    if (job_no <= jobs.size()) // job number are from 0 to n
    {
        // while (true)
        // {

        tcsetpgrp(STDIN_FILENO, getpgrp());
        //  break;
        //   }
    }
    else
    {

        cout << "Not a valid job ID." << endl;
        return -1;
    }

    needed_id = jobs[jobs.size() - 1].PID;
    // strcpy(CURR_JOB, jobs[job_no - 1].job_name);
    CURR_JOB = string(jobs[job_no - 1].job_name);
    CHILD_ID = needed_id;

    //reduce_left_jobs();
	background_n = background_n - 1;
    // TODO: delete last char

    // while (true)
    // {
    signal(SIGTTOU, SIG_IGN);

    //     break;
    // }

    signal(SIGTTIN, SIG_IGN);

    // while ((true))
    // {
    tcsetpgrp(STDIN_FILENO, CHILD_ID);

    // break;
    // }

    int sigcont_var = 18;

    kill(needed_id, 18);

    // while (true)
    // {

    waitpid(needed_id, &status, WUNTRACED);
    //     break;
    // }

    // while (true)
    // {

    tcsetpgrp(STDIN_FILENO, getpgrp());
    //     break;
    // }

    signal(SIGTTOU, SIG_DFL);

    // while (true)
    // {

    signal(SIGTTIN, SIG_DFL);

    //     break;
    // }

    if (!(WIFSTOPPED(status)))
    {

        cout << "Error in WIFSTOPPED\n"
             << endl;
    }
    else
    {

        jobs[background_n].PID = CHILD_ID;

        // while (true)
        // {
        strcpy(jobs[background_n].job_name, CURR_JOB.c_str());
        //     break;
        // }

        // while (true)
        // {
        background_n = background_n + 1;
        // break;
        // }
    }

    return 0;
}

void see_jobs()
{

    char *status = (char *)calloc(52, sizeof(char));

    for (int i = 0; i < jobs.size(); i++)
    {
        FILE *f;

        // while (true)
        // {
        sprintf(status, "/proc/%d/status", jobs.at(i).PID);

        //     break;
        // }

        // while (true)
        // {
        if (!(f = fopen(status, "r")))
        {

            string msg = "Error in see_jobs() while fopen()";
            printBadMessage(msg);
            return;
        }
        //     break;
        // }

        // while (true)
        // {
        fclose(f);
        //     break;
        // }

        string status_info = read_file(3, string(status));

        string temp = status_info;
        char *t1 = (char *)status_info.c_str();
        t1 = strtok(t1, " :\n\t\r");
        // while (true)
        // {
        //     break;
        // }

        // while (true)
        // {
        t1 = strtok(NULL, " :\n\t\r");

        //     break;
        // }

        // while (true)
        // {

        if (status_info[0] != 'T')
        {
            status_info = "Ongoing";
        }
        else
        {
            status_info = "Terminated";
        }

        //     break;
        // }

        cout << "{" << i + 1 - 1 << "} " << jobs[i].job_name << " " << status_info << " {" << jobs[i].PID << "}";
        //  }
    }
}
