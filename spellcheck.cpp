#include "spellcheck.h"
#include <iostream>
//#include <map>
#include <stdio.h>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>    // transform
using namespace std;

#define DEBUG
spellCheck::spellCheck(string file){

#ifdef DEBUG
    clock_t start,end;
    start = clock();
#endif
    loadDic(file);
#ifdef DEBUG
    end = clock();
    cout<<"加载用时:"<<(end-start)/1000.0<<"ms"<<endl;
#endif

}
spellCheck::~spellCheck(){
    delete dic;
    dic = NULL;
}

string spellCheck::check(string f)
{

    ifstream word(f,std::ios::in);
    if(!word)
        cout<<"打开文件失败!!!\n";
    string s,wordList[1000],rightList[1000],wrongList[1000];
    int n=0;
#ifdef DEBUG
    clock_t start,end;
    start = clock();
#endif
    while(word>>s)
    {
        wordList[n++]=s;
    }
    word.close();
    int i=0,k=0;
    string input,input2;
    while(i<n)
    {

        c.count=1;
        c.correctWord="";
        input=wordList[i];
        input2=input;
        transform(input2.begin(),input2.end(),input2.begin(),::tolower);
        if(dic->find(input)!=NULL||dic->find(input2)!=NULL)
            ;//rightList[i]=input;
        else
        {
         //   cout<<"haha";
            search(input);
        //    cout<<"co "<<c.correctWord<<"  co";
            if(c.correctWord==""||c.correctWord==input){
                cout<<"co "<<c.correctWord<<"  co";
                i++;
                continue;
            }

            if(dic->find(c.correctWord)->second!=0)
            {
                wrongList[k] = input;
                rightList[k]=c.correctWord;
                k++;
            }
            //else
                //rightList[i]=input;
        }
        i++;
    }
#ifdef DEBUG
    end = clock();
    cout<<(end-start)/1000.0<<"ms"<<endl;
#endif
    int j=0;
    string text ="";
    while(j<k){
        cout<<wrongList[j]<<"->";
        cout<<rightList[j]<<"   ";
        text += wrongList[j];
        text += "->";
        text += rightList[j];
        text += " ";
        j++;
    }
    cout<<endl;

/*    pair<string, int> p;
    pair<string, int> * q=new pair<string, int>();
    p.first="ss";
    p.second=6;
    hashTable<string, int>  *d=new hashTable<string, int>();
    d->insert(p);
    d->find("ss")->second=d->find("ss")->second+1;
    q=d->find("ss");*/
    return text;
}

void spellCheck::loadDic(string file)
{   ifstream fin(file,std::ios::in);
    if(!fin)
        cout<<"打开文件失败!!!\n";
    string s;
    while(fin>>s)
    {
        if(dic->find(s)==NULL)
        {
           // dic[s]=1;

            dic->insert(pair<string, int>(s,1));
        }
        else
        {
           // int count=dic.at(s);
            int count= dic->find(s)->second;
            dic->find(s)->second=count+1;
            //dic[s]=(count+1);
        }
    }
    fin.close();
 //   dic->output(cout);

}

void spellCheck::search(string input)
{
    char set[27]="abcdefghijklmnopqrstuvwxyz";
    int length=input.length();
    // delete
    for(int i=0;i<length;i++)
    {
        string temp=input.substr(0,i)+input.substr(i+1);
        find(temp);
    }

    // transportation
    for(int i=0;i<length-1;i++)
    {
        string temp=input;
        char s;
        s=temp[i];
        temp[i]=temp[i+1];
        temp[i+1]=s;
        find(temp);
    }

    // alterneration
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<26;j++)
        {
            string temp=input;
            temp[i]=set[j];
            find(temp);
        }
    }

    // insertion
    for(int i=0;i<=length;i++)
        for(int j=0;j<26;j++)
        {
            string temp=input.substr(0,i)+set[j]+input.substr(i);
            find(temp);
        }
}
void spellCheck::find(string s)
{
    int number=0;
    if(dic->find(s)==NULL)
    {
        number=1;
    }
    else
        number=dic->find(s)->second;
        //number=dic.at(s);

    if(number>c.count)
    {
        c.count=number;
        c.correctWord=s;
    }
}
