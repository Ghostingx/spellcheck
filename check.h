#ifndef CHECK_H
#define CHECK_H

#include <iostream>
#include <map>
#include <stdio.h>
#include <fstream>
#include <string>
#include <time.h>
#include "hashtable.h"
//#include"vector"
using namespace std;

typedef struct node
{
    string correctWord;
    int count;
}correction;
void loadDic();
void search(string input);
void find(string s);
correction c;
//map<string,int> dic;
hashTable<string,int> dic(100000);
string check(string f)
{
    clock_t start,end;
    start = clock();
    loadDic();
    end = clock();
    cout<<(end-start)/1000.0<<"ms"<<endl;
    ifstream word(f,std::ios::in);
    if(!word)
        cout<<"打开文件失败!!!\n";
    string s,wordList[100],rightList[100],wrongList[100];
    int n=0;

    start = clock();

    while(word>>s)
    {
        wordList[n++]=s;
    }
    word.close();
    int i=0,k=0;
    string input;
    while(i<n)
    {

        c.count=-1;
        input=wordList[i];
        if(dic.find(input)>0)
            rightList[i]=input;
        else
        {
            search(input);
            if(dic.find(c.correctWord)!=0)
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

    end = clock();
    cout<<(end-start)/1000.0<<"ms"<<endl;

    int j=0;
    string text ="";
    while(j<n){
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

void loadDic()
{   ifstream fin("/Users/ghost/Documents/xcode/spellCheck/spellCheck/model.txt",std::ios::in);
    if(!fin)
        cout<<"打开文件失败!!!\n";
    string s;
    while(fin>>s)
    {
        if(dic.find(s)==NULL)
        {
           // dic[s]=1;

            dic.insert(pair<string, int>(s,1));
        }
        else
        {
           // int count=dic.at(s);
            int count= dic.find(s)->second;
            dic.find(s)->second=count+1;
            //dic[s]=(count+1);
        }
    }
    fin.close();
}

void search(string input)
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
void find(string s)
{
    int number=0;
    if(dic.find(s)==NULL)
    {
        number=1;
    }
    else
        number=dic.find(s)->second;
        //number=dic.at(s);

    if(number>c.count)
    {
        c.count=number;
        c.correctWord=s;
    }
}

#endif // CHECK_H
