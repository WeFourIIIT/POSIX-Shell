#include <vector>
#include <string>
#include <map>
#include <dirent.h>
#include <limits.h>
using namespace std;
void insertWordInTrie(string);
void populateTrie(void);
static inline void trim(string &);
// class TrieNode{
//     public:
//         bool isLeaf;
//         string word;
//         TrieNode() {
//             isLeaf = false;
//             word = "";
//         }
// };
// class Trie{
//     public:
//         TrieNode *root;
//         Trie();
//         void insert(string);
//         bool search(string);
//         bool startsWith(string);
//         bool isLastNode(TrieNode *);
//         void autocompleteRecUtil(TrieNode *, string &, vector<string> &);
//         void autocomplete(string &, vector<string> &);
//         void autocorrectRecUtil(TrieNode *, char, string &, vector<int>, vector<pair<string, int> > &, int &);
//         void autocorrect(string, int, vector<pair<string, int> > &);
//         void insertWordInTrie(string);
//         void populateTrie();
// };
// class his_trie{
//     public:
//         his_trie *ref[26];
//         bool flag;
//         int count;

//         void insert(his_trie*, string, int);
//         bool char_exist(char);
//         bool check(his_trie, string);
//         bool is_valid_check(his_trie, string, vector<pair<int, string>>);
//         void collect_strings(vector<pair<int, string>>, his_trie*, string);
// };

class TrieNode
{
public:
    bool isLeaf;
    string word;
    // TrieNode *arr[26];
    map<char, TrieNode *> children;

    TrieNode()
    {
        this->isLeaf = false;
        this->word = "";
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
        if (curr->isLeaf) {
            res.push_back(currPrefix);
        }

        if (isLastNode(curr)) {
            return;
        }

        for (auto itr = curr->children.begin(); itr != curr->children.end(); itr++) {
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
        vector<pair<string, int> > &res,
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
            res.push_back({ curr->word, currentRow[lastIndex] });
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

    void autocorrect(string word, int maxCostAllowed, vector<pair<string, int> > &res)
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

    void insertWordInTrie(string word) // priyank  done   moved
    {
        insert(word);
    }

    void populateTrie(vector<string> &path_variable) /// priyank  done    moved
    {
        vector<string> basicCommands; 
        DIR *dr; 
        struct dirent *en;
 
        for(unsigned int i=0;i<path_variable.size();i++) 
        { 
            dr = opendir(path_variable[i].c_str()); //open all directory 
            if (dr)  
            { 
                while ((en = readdir(dr)) != NULL)  
                { 
                    string type="other"; 
                    if(en->d_type==DT_REG) 
                    { 
                        basicCommands.push_back(string(en->d_name)); 
                    }
                } 
                closedir(dr); //close all directory 
            } 
 
        } 

        for (int i = 0; i < basicCommands.size(); i++)
        {
            // trie->insert(basicCommands[i]);
            insertWordInTrie(basicCommands[i]);
        }
    }
    // END autocorrect
};
class his_trie
{
    public:
        his_trie *ref[256]={NULL};
        bool flag=false;
        int count=0;

    void insert(his_trie *curr, string word, int &gb_count)
    {
        char ch;
        his_trie *curr1 = curr;
        for(int i=0;i<word.size();i++)
        {
            ch=word[i];
            int ascii=0;
            ascii=int(ch);
            if(curr1->ref[ascii]==NULL)
            {
                his_trie *temp=new his_trie();
                curr1->ref[ascii]=temp;
            }
            curr1=curr1->ref[ascii];
        }
        curr1->flag=true;
        curr1->count=gb_count;
    }

    bool char_exist(char ch)
    {
        return ref[int(ch)]!=NULL;
    }

    bool check(his_trie * curr,string word)
    {
        bool is_there=true;
        char ch;
        for(int i=0;i<word.size();i++)
        {
            ch=word[i];
            if(curr->char_exist(ch))
                is_there=true;
            else
                return false;

            curr=curr->ref[int(ch)];

        }
        if(curr->flag==true)
            return true;
        return false;
    }

    bool is_valid_prefix(his_trie *curr,string word,vector<pair<int,string> >&prefix)
    {
        char ch;
        for(int i=0;i<word.size();i++)
        {
            ch=word[i];

            if(!curr->char_exist(ch))
            {
                return false;
            }
            curr=curr->ref[int(ch)];
        }
        collect_strings(prefix,curr,word);
        return true;
    }
    // void collect_strings(vector<string>&prefix,his_trie * curr,char *c_arr,string word,int pos=0)
    void collect_strings(vector< pair<int,string> >&prefix,his_trie * curr,string word)
    {
        if(curr->flag==true)
        {
            prefix.push_back({curr->count,word});
        }
        for(int i=0;i<256;i++)
        {
            if(curr->ref[i]!=NULL)
            {
                char x=i;
                word+=x;
                collect_strings(prefix,curr->ref[i],word);
                word.pop_back();
            }
        }
    }
};

void load_history(his_trie*, string, int &);
void save_history(his_trie, string);
void print_history(his_trie, int, string &);
