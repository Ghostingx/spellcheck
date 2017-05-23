#ifndef SPELLCHECK_H
#define SPELLCHECK_H
#include "hashtable.h"

typedef struct node
{
    string correctWord;
    int count;
}correction;

class spellCheck
{
public:
    spellCheck(string file);
    ~spellCheck();
    string check(string file);

private:
    void loadDic(string file);
    void search(string input);
    void find(string s);
    correction c;
    hashTable<string,int> * dic= new hashTable<string,int>(100000);
};

#endif // SPELLCHECK_H
