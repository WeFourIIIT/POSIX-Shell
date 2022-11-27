#include "ujjwal.h"
#include "priyank.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <limits.h>
#include <vector>

using namespace std;

string removeCharacters(string &S, char c) {
    S.erase(remove(S.begin(), S.end(), c), S.end());
    return S;
}

static inline void ltrim(string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch){ 
            return !isspace(ch); 
        })
    );
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch){ 
            return !isspace(ch);
        }).base(), s.end()
    );
}

static inline void trim(string &s) {
    ltrim(s);
    rtrim(s);
}

void load_history(his_trie root, his_trie *curr, string hist_filename)   //priyank 
{
    vector<string> hist;
    int gb_count = 0;
    FILE *file = fopen(hist_filename.c_str(), "r");
    if (file != NULL) {
        char line[128];
        int no = 0;
        string comm; // priyank_added
        while (fgets(line, sizeof(line), file) != NULL) {
            hist.push_back(string(line));
            curr=&root;  // priyank_added
            gb_count+=1;
            comm=string(line);
            comm = removeCharacters(comm, '\n');
            comm = removeCharacters(comm, '\t');
            root.insert(curr,comm,gb_count);
            no++;
        }
        fclose(file);
    }
    else {
        cout<<"Loading "<<hist_filename<<" failed"<<endl;
        exit(EXIT_FAILURE);
    }
    return;
}

void save_history(his_trie root, his_trie *curr, string hist_filename)  // priyank 
{
    FILE *file = fopen(hist_filename.c_str(), "a");
    vector< pair<int,string> > save_vec;
    save_vec.clear();
    curr=&root;
    root.is_valid_prefix(curr,"",save_vec); // priyank_added
    sort(save_vec.begin(),save_vec.end());

    for (int i = 0; i < save_vec.size(); i++)
    {
        trim(save_vec[i].second);
        if (!save_vec[i].second.empty())
        {
            fprintf(file, "\n%s", save_vec[i].second.c_str());
             cout<<"hello save "<<save_vec[i].second<<endl;
        }
    }   
    fclose(file);
}

// void print_history()  // priyank
// {
//     for (int i = 0; i < hist.size(); i++)
//     {
//         trim(hist[i]);
//         hist[i] = removeCharacters(hist[i], '\n');
//         hist[i] = removeCharacters(hist[i], '\t');
//         if (!hist[i].empty())
//         {
//             cout << " - " << hist[i] << endl;
//         }
//     }
// }

// void print_history2()  // priyank_added
// {
//     vector< pair<int,string> > print_vec;
//     print_vec.clear();
//     curr=&root;
//     root.is_valid_prefix(curr,"",print_vec); // priyank_added
//     sort(print_vec.begin(),print_vec.end());
//     reverse(print_vec.begin(),print_vec.end());
//     for(int i=0;i<print_vec.size();i++)
//     {
//         cout<<print_vec[i].second<<endl;
//     }    
// }
