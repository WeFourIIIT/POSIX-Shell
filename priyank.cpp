#include "priyank.h"


// ////////////////////////////
// /** TRIE BEGINS **/

class TrieNode
{
public:
    bool isLeaf;
    string word;
    // TrieNode *arr[26];
    map<char, TrieNode *> children;

    TrieNode()
    {
        // cout << "created new node" << endl;
        this->isLeaf = false;
        this->word = "";
        // this->arr = new TrieNode();
        // for (int i = 0; i < 26; i++)
        // {
        //     this->arr[i] = nullptr;
        // }
    }
};

class Trie
{

public:
    TrieNode *root;

    Trie()
    {
        root = new TrieNode();
    }

    void insert(string word) // priyank done
    {

        TrieNode *curr = this->root;

        for (int i = 0; i < word.size(); i++)
        {

            int index = word[i] - 'a';

            if (curr->children.find(word[i]) == curr->children.end()) // if anything with char word[i] not found in map 
            {
                curr->children[word[i]] = new TrieNode();
            }

            // curr = curr->arr[index];
            curr = curr->children[word[i]];
        }
        curr->isLeaf = true;
        curr->word = word;

        // cout << "insertion done " << curr->word << endl;
    }

    bool search(string word)  // not found any use done priyank 
    {
        TrieNode *curr = this->root;
        if (curr == nullptr)
        {
            return false;
        }

        for (int i = 0; i < word.size(); i++)
        {

            int index = word[i] - 'a';

            // curr = curr->arr[index];
            curr = curr->children[word[i]];
            if (curr == nullptr)
            {
                return false;
            }
        }

        return curr->isLeaf;
    }

    bool startsWith(string prefix)  // not found any use done priyank 
    {

        TrieNode *curr = this->root;
        if (curr == nullptr)
        {
            return false;
        }

        for (int i = 0; i < prefix.size(); i++)
        {

            int index = prefix[i] - 'a';

            // curr = curr->arr[index];
            curr = curr->children[prefix[i]];

            if (curr == nullptr)
            {
                return false;
            }
        }

        return true;
    }

    // begin autocomplete

    bool isLastNode(TrieNode *root)  // done priyank
    {
        if (root->children.size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void autocompleteRecUtil(TrieNode *curr, string &currPrefix, vector<string> &res) // dfs here done priyank
    {
        if (curr->isLeaf)
        {
            res.push_back(currPrefix);
            // cout<<currPrefix<<endl;
        }

        if (isLastNode(curr))
        {
            return;
        }

        for (auto itr = curr->children.begin(); itr != curr->children.end(); itr++)
        {
            char currentChar = itr->first;
            TrieNode *nextChild = itr->second;

            currPrefix.push_back(currentChar);

            autocompleteRecUtil(nextChild, currPrefix, res);

            currPrefix.pop_back();
        }
    }

    void autocomplete(string &prefix, vector<string> &res)  // done priyank 
    {
        TrieNode *curr = this->root;

        if (curr == nullptr)
        {
            return;
        }

        // check if prefix itself is present or not
        for (int i = 0; i < prefix.size(); i++)
        {
            if (curr->children[prefix[i]] == nullptr)
            {
                return;
            }
            else
            {
                curr = curr->children[prefix[i]];
            }
        }

        // if prefix is a word add it to result
        if (curr->isLeaf && isLastNode(curr))
        {
            res.push_back(prefix);
            // MAY need to delete this statement because first line in recursive function is doing this
            // OR may node to exactly follow gf reference.
        }

        // if prefix is last node in branch
        if (isLastNode(curr))
        {
            return;
        }

        // if prefix branch has more nodes below
        string tempPrefix = prefix;
        autocompleteRecUtil(curr, tempPrefix, res);

        return;
    }

    // END autocomplete

    // BEGIN autocorrect

    void autocorrectRecUtil(
        TrieNode *curr,
        char ch,
        string &word,
        vector<int> pRow,
        vector<pair<string, int>> &res,
        int &maxCostAllowed)
    {
        int cols = word.size() + 1;
        vector<int> currentRow(1, pRow[0] + 1);

        for (int i = 1; i < cols; i++)
        {
            int insertCost = currentRow[i - 1] + 1;
            int deleteCost = pRow[i] + 1;

            int replaceCost = -1;
            if (word[i - 1] != ch)
            {
                replaceCost = pRow[i - 1] + 1;
            }
            else
            {
                replaceCost = pRow[i - 1];
            }

            int minCost = min(insertCost, min(deleteCost, replaceCost));
            currentRow.push_back(minCost);
        }

        // if the last entry in the row indicates the optimal cost is less than the
        // maximum cost, and there is a word in this trie node, then add it
        int lastIndex = currentRow.size() - 1;
        if (currentRow[lastIndex] <= maxCostAllowed && !(curr->word.empty()))
        { // may need to consider second condition
            res.push_back({curr->word, currentRow[lastIndex]});
        }

        // if any entries in the row are less than the maximum cost, then
        // recursively search each branch of the trie
        int minCurrRow = INT_MAX;
        for (int i = 0; i < currentRow.size(); i++)
        {
            minCurrRow = min(minCurrRow, currentRow[i]);
        }

        if (minCurrRow <= maxCostAllowed)
        {
            for (auto itr = curr->children.begin(); itr != curr->children.end(); itr++)
            {
                char ch = itr->first;
                TrieNode *nextNode = itr->second;

                autocorrectRecUtil(curr->children[ch], ch, word, currentRow, res, maxCostAllowed);
            }
        }
    }

    void autocorrect(string word, int maxCostAllowed, vector<pair<string, int>> &res)
    {
        // creating first row for given word, Trie is not considered at this point
        int wl = word.size();
        vector<int> currentRow(wl + 1);
        for (int i = 0; i < wl + 1; i++)
        {
            currentRow[i] = i;
            // cout << currentRow[i] << endl;
        }

        TrieNode *curr = this->root;

        for (auto itr = curr->children.begin(); itr != curr->children.end(); itr++)
        {
            char ch = itr->first;
            TrieNode *nextNode = itr->second;

            autocorrectRecUtil(curr->children[ch], ch, word, currentRow, res, maxCostAllowed);
        }

        // return res; no need here becuase pass by reference
    }

    // END autocorrect
};

Trie *trie = new Trie();

// Trie *h_trie = new Trie();

void insertWordInTrie(string word) // priyank  done   moved
{
    trie->insert(word);
}

void populateTrie() /// priyank  done    moved
{
    vector<string> basicCommands = {"ls", "echo", "touch", "mkdir", "grep", "pwd", "cd", "cat", "head", "tail", "exit", "history", "clear", "cp"};

    for (int i = 0; i < basicCommands.size(); i++)
    {
        // trie->insert(basicCommands[i]);
        insertWordInTrie(basicCommands[i]);
    }
}

// /** TRIE ENDS **/

// ///////////////////////////////////




 /////////////////// his_trie BEGINS


class his_trie
{
    public:
        his_trie *ref[26]={NULL};
        bool flag=false;
        int count=0;

    void insert(his_trie * curr,string word,int &gb_count)
    {    
        char ch;
        for(int i=0;i<word.size();i++)
        {
            ch=word[i];
            if(!curr->char_exist(ch))
            {
                his_trie *temp=new his_trie();
                curr->ref[ch-'a']=temp;
            }
            curr=curr->ref[ch-'a'];
            //cout<<ch<<" ";

        }
        curr->flag=true;
        curr->count=gb_count;
        //cout<<endl;
    }

    bool char_exist(char ch)
    {
        return ( ref[ch-'a']!=NULL );
    }


    bool check(his_trie * curr,string word)
    {
        // if(word=="")
        //     return false;
        bool is_there=true;
        char ch;
        for(int i=0;i<word.size();i++)
        {
            ch=word[i];
            if(curr->char_exist(ch))
                is_there=true;
            else
                return false;

            curr=curr->ref[ch-'a'];

        }
        //cout<<" Subset checked "<<endl;
        if(curr->flag==true)
            return true;
        return false;    

    }


    bool is_valid_prefix(his_trie *curr,string word,vector< pair<int,string> >&prefix)
    {
        // if(word=="")
        //     return false;
        char ch;
        // string element="";
        for(int i=0;i<word.size();i++)
        {
            ch=word[i];

            if(!curr->char_exist(ch))
            {
                return false;
            }
            curr=curr->ref[ch-'a'];

        }
        // prefix is found to be valid

        // char c_arr[2000];
        // collect_strings(prefix,curr,c_arr,word);
        collect_strings(prefix,curr,word);


        return true;
    }

    // void collect_strings(vector<string>&prefix,his_trie * curr,char *c_arr,string word,int pos=0)
    void collect_strings(vector< pair<int,string> >&prefix,his_trie * curr,string word)
    {
        // if(curr==NULL)
        //     return;
        if(curr->flag==true)
        {
            prefix.push_back({curr->count,word});
        }
            
        
        for(int i=0;i<26;i++)
        {
            if(curr->ref[i]!=NULL)
            {
                //c_arr[pos]='a'+i;
                word+='a'+i;

                // collect_strings(prefix,curr->ref[i],c_arr,word,pos+1);
                collect_strings(prefix,curr->ref[i],word);
                word.pop_back();
            }
        }

    }

};

his_trie root;
his_trie *curr=new his_trie();

 /////////////////// his_trie ENDS



void load_history()   //priyank
{
      cout<<"hello load"<<endl;
    // strcpy(hist_filename, HOME);
    hist_filename = string(getenv("PWD"));
    // strcat(hist_filename, "/history.txt");
    hist_filename += "/history.txt";
    // debug(hist_filename)
    FILE *file = fopen(hist_filename.c_str(), "r");
    if (file != NULL)
    {
        // debug("loading history")
        char line[128];
        int no = 0;
        string comm; // priyank_added
        while (fgets(line, sizeof(line), file) != NULL)
        {
            // debug(string(line))
            hist.push_back(string(line));

                curr=&root;  // priyank_added
                gb_count+=1;
                comm=string(line);
                // trim(string(line));
                comm = removeCharacters(comm, '\n');
                comm = removeCharacters(comm, '\t');
                root.insert(curr,comm,gb_count);
                cout<<"hello load "<<comm<<endl;

            no++;
        }

        fclose(file);
    }
    else
    {
        custom_exit("History.txt failed");
    }
    return;
}

void save_history()  // priyank
{
    //  cout<<"hello save"<<endl;
    FILE *file = fopen(hist_filename.c_str(), "w");


    vector< pair<int,string> > save_vec;
    save_vec.clear();
    curr=&root;
    root.is_valid_prefix(curr,"",save_vec); // priyank_added
    sort(save_vec.begin(),save_vec.end());

    for (int i = 0; i < save_vec.size(); i++)
    {
        trim(save_vec[i].second);
        // hist[i] = removeCharacters(hist[i], '\n');
        // hist[i] = removeCharacters(hist[i], '\t');
        if (!save_vec[i].second.empty())
        {
            fprintf(file, "\n%s", save_vec[i].second.c_str());
             cout<<"hello save "<<save_vec[i].second<<endl;
        }
    }   

    

    // for (int i = 0; i < hist.size(); i++)
    // {
    //     trim(hist[i]);
    //     hist[i] = removeCharacters(hist[i], '\n');
    //     hist[i] = removeCharacters(hist[i], '\t');
    //     if (!hist[i].empty())
    //     {
    //         fprintf(file, "\n%s", hist[i].c_str());
    //          cout<<"hello save"<<endl;
    //     }
    // }

    fclose(file);
}

// void history(char *command)
// {
//     char *token = command;
//     token = strtok(NULL, " \"\n\t\r");

//     int n = 10;
//     if (token != NULL)
//         n = atoi(token);

//     int count = n;

//     for (int i = hist_i - count; count > 0; i++, count--)
//     {
//         printf("%s", hist[i % 20].c_str());
//         //count++;
//     }
// }

void print_history()  // priyank
{
    for (int i = 0; i < hist.size(); i++)
    {
        trim(hist[i]);
        hist[i] = removeCharacters(hist[i], '\n');
        hist[i] = removeCharacters(hist[i], '\t');
        if (!hist[i].empty())
        {
            cout << " - " << hist[i] << endl;
        }
    }
}

void print_history2()  // priyank_added
{   
    // TrieNode *hp = h_trie->root;
    // vector<string> op;
    // string tem="";
    // h_trie->autocompleteRecUtil(hp,tem, op);
    // // cout<<op.size();
    // for(int i=0;i<op.size();i++)
    // {
    //     cout<<op[i]<<endl;
    // }


    vector< pair<int,string> > print_vec;
    print_vec.clear();
    curr=&root;
    root.is_valid_prefix(curr,"",print_vec); // priyank_added
    sort(print_vec.begin(),print_vec.end());
    reverse(print_vec.begin(),print_vec.end());
    for(int i=0;i<print_vec.size();i++)
    {
        cout<<print_vec[i].second<<endl;
    }


    
}

