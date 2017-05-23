#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
//#include "hash.h"  // mapping functions from K to nonnegative integer
#include "myexception.h"

using namespace std;



template <class K> class hash1;

template<>
class hash1<string>
{
public:
    size_t operator()(const string theKey) const
    {// Convert theKey to a nonnegative integer.
        unsigned long hashValue = 0;
        int length = (unsigned int) theKey.length();
        for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + theKey.at(i);

        return size_t(hashValue);
    }
};




template<class K, class E>
class hashTable
{
public:
    hashTable(int theDivisor = 11);
    ~hashTable(){delete [] table;}

    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    pair<const K, E>* find(const K&) const;
    void insert(const pair<const K, E>&);
    void output(ostream& out) const;

protected:
    int search(const K&) const;
    pair<const K, E>** table;  // hash table
    hash1<K> hash;              // maps type K to nonnegative integer
    int dSize;                 // number of pairs in dictionary
    int divisor;               // hash function divisor
};

template<class K, class E>
hashTable<K,E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;

    // allocate and initialize hash table array
    table = new pair<const K, E>* [divisor];
    for (int i = 0; i < divisor; i++)
        table[i] = NULL;
}

template<class K, class E>
int hashTable<K,E>::search(const K& theKey) const
{

    int i = (unsigned int) hash(theKey) % divisor;
    int j = i;
    do
    {
        if (table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    } while (j != i);

    return j;  // table full
}

template<class K, class E>
pair<const K,E>* hashTable<K,E>::find(const K& theKey) const
{
    int b = search(theKey);

    // see if a match was found at table[b]
    if (table[b] == NULL || table[b]->first != theKey)
        return NULL;           // no match

    return table[b];  // matching pair
}

template<class K, class E>
void hashTable<K,E>::insert(const pair<const K, E>& thePair)
{
    int b = search(thePair.first);

    // check if matching pair found
    if (table[b] == NULL)
    {
        // no matching pair and table not full
        table[b] = new pair<const K,E> (thePair);
        dSize++;
    }
    else
    {// check if duplicate or table full
        if (table[b]->first == thePair.first)
        {// duplicate, change table[b]->second
            table[b]->second = thePair.second;
        }
        else // table is full
            throw hashTableFull();
    }
}

template<class K, class E>
void hashTable<K,E>::output(ostream& out) const
{// Insert the hash table into the stream out.
    for (int i = 0; i < divisor; i++)
        if (table[i] == NULL)
            out << "NULL" << endl;
        else
            out << table[i]->first << " "
            << table[i]->second << endl;
}

// overload <<
template <class K, class E>
ostream& operator<<(ostream& out, const hashTable<K,E>& x)
{x.output(out); return out;}

#endif // HASHTABLE_H
