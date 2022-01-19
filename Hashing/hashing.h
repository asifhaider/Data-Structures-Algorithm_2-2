/*
    Solution of Offline 5 on Hashing and Collision Resolve Techniques
    Author: Md. Asif Haider, 1805112
    Date: 19 January 2021
*/

#include <bits/stdc++.h>
#include <cmath>
using namespace std;

#define M 30013 // 10009, 20021, 30013
#define C1 112
#define C2 41

static const char alphabets[] = "abcdefghijklmnopqrstuvwxyz";

class Hash_Table
{
private:
    int string_length;
    int collision;
    int probe;
    int not_found;
    int found;
    list<pair<string, int>> *table;

public:
    Hash_Table(int n);         // constructor with input hash table length
    string String_Generator(); // random alphabetic string input generator
    void print_table();        // hash table size and all entries

    int Hash_Function_1(string s); // length 4 folding hash algorithm
    int Hash_Function_2(string s); // polynomial rolling hash algorithm
    int aux_hash(string s);

    // methods used for separate chaining
    void insert_chain(string s, int i);
    int search_chain(string s);
    void remove_chain(string s);

    // methods used for double hashing
    void insert_double(string s, int i);
    int search_double(string s);
    void remove_double(string s);

    // methods used for custom probing
    void insert_custom(string s, int i);
    int search_custom(string s);
    void remove_custom(string s);
};

Hash_Table::Hash_Table(int n)
{
    this->string_length = n;
    this->collision = 0;
    this->probe = 0;
    this->found = 0;
    this->not_found = 0;
    this->table = new list<pair<string, int>>[M];
}

string Hash_Table::String_Generator()
{
    int total_size = sizeof(alphabets) - 1;
    string key = "";
    for (int i = 0; i < string_length; i++)
    {
        key = key + alphabets[rand() % total_size];
    }
    cout << key << endl;
    return key;
}

void Hash_Table::print_table()
{
    int count = 0;
    for (int i = 0; i < M; i++)
    {
        if (table[i].size() > 0)
        {
            for (auto x = table[i].begin(); x != table[i].end(); x++)
            {
                cout << (*x).first << " " << (*x).second << endl;
                count++;
            }
        }
    }
    cout << "Total entries: " << count << endl;
}

int Hash_Table::Hash_Function_1(string s)
{
    long long sum = 0, mul = 1;
    for (int i = 0; i < s.length(); i++)
    {
        mul = (i % 4 == 0) ? 1 : mul * 256;
        sum += s[i] * mul;
    }
    return (int)(abs(sum) % M);
}

int Hash_Table::Hash_Function_2(string s)
{
    const int p = 31;
    long long sum = 0;
    long long pow = 1;
    for (char c : s)
    {
        sum = (sum + (c - 'a' + 1) * pow) % M;
        pow = (pow * p) % M;
    }
    return (int)sum;
}

int Hash_Table::aux_hash(string s)
{
    long long int sum = 0;
    for (char c : s)
    {
        sum = sum + ((c - 'a') * (c - 'a'));
    }
    return (int)(abs(sum) % M);
}

void Hash_Table::insert_chain(string s, int i)
{
    int index = Hash_Function_2(s);
    if (table[index].size() > 0)
    {
        collision++;
    }
    table[index].push_back(make_pair(s, i));
    cout << "Inserted (Chain)" << endl;
    cout << "Total Collisions: " << collision << endl;
}

void Hash_Table::insert_double(string s, int i)
{
    int index1 = Hash_Function_2(s);
    int index = index1;
    int index2 = aux_hash(s);

    int x = 0;
    while (table[index].size() > 0)
    {
        x++;
        index = (index1 + x * index2) % M;
        collision++;
    }
    table[index].push_back(make_pair(s, i));
    cout << "Inserted (Double)" << endl;
    cout << "Total Collisions: " << collision << endl;
}

void Hash_Table::insert_custom(string s, int i)
{
    int index1 = Hash_Function_2(s);
    int index = index1;
    int index2 = aux_hash(s);

    int x = 0;
    while (table[index].size() > 0)
    {
        x++;
        index = (index1 + C1 * x * index2 + C2 * x * x) % M;
        collision++;
    }
    table[index].push_back(make_pair(s, i));
    cout << "Inserted (Custom)" << endl;
    cout << "Total Collisions: " << collision << endl;
}

int Hash_Table::search_chain(string s)
{
    int index = Hash_Function_2(s);
    list<pair<string, int>>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++)
    {
        if ((*i).first == s)
        {
            found++;
            cout << "Found (Chain) " << found << endl;
            cout << "Total Probes: " << probe << endl;
            return (*i).second;
        }
        probe++;
    }
    not_found++;
    cout << "Not Found (Chain) " << not_found << endl;
    return -1; // as input is always natural number
}

int Hash_Table::search_double(string s)
{
    int index1 = Hash_Function_2(s);
    int index = index1;
    int index2 = aux_hash(s);

    auto i = table[index].begin();

    int x = 0;
    while ((*i).first != s)
    {
        x++;
        index = (index1 + x * index2) % M;
        probe++;
        i = table[index].begin();
    }

    if ((*i).first == s)
    {
        found++;
        cout << "Found (Double) " << found << endl;
        cout << "Total Probes: " << probe << endl;
        return (*i).second;
    }
    else
    {
        not_found++;
        cout << "Not Found (Double) " << not_found << endl;
        return -1; // as input is always natural number
    }
}

int Hash_Table::search_custom(string s)
{
    int index1 = Hash_Function_2(s);
    int index = index1;
    int index2 = aux_hash(s);

    auto i = table[index].begin();

    int x = 0;
    while ((*i).first != s)
    {
        x++;
        index = (index1 + C1 * x * index2 + C2 * x * x) % M;
        probe++;
        i = table[index].begin();
    }

    if ((*i).first == s)
    {
        found++;
        cout << "Found (Custom) " << found << endl;
        cout << "Total Probes: " << probe << endl;
        return (*i).second;
    }
    else
    {
        not_found++;
        cout << "Not Found (Custom) " << not_found << endl;
        return -1; // as input is always natural number
    }
}

void Hash_Table::remove_chain(string s)
{
    int index = Hash_Function_2(s);
    list<pair<string, int>>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++)
    {
        if ((*i).first == s)
        {
            cout << "Found, Now Delete (Chain)!" << endl;
            break;
        }
    }
    if (i != table[index].end())
    {
        table[index].erase(i);
        cout << "Deleted (Chain)" << endl;
    }
    else
    {
        cout << "Not Found, Could not Delete (Chain)" << endl;
    }
}

void Hash_Table::remove_double(string s)
{
    int index1 = Hash_Function_2(s);
    int index = index1;
    int index2 = aux_hash(s);

    int x = 0;
    while (table[index].size() > 1)
    {
        index = (index1 + x * index2) % M;
    }
    auto i = table[index].begin();
    if ((*i).first == s)
    {
        cout << "Found, Now Delete (Double)!" << endl;
        table[index].erase(i);
        cout << "Deleted (Double)" << endl;
    }
    else
        cout << "Not Found, Could not Delete (Double)" << endl;
}

void Hash_Table::remove_custom(string s)
{
    int index1 = Hash_Function_2(s);
    int index = index1;
    int index2 = aux_hash(s);

    int x = 0;
    while (table[index].size() > 1)
    {
        index = (index1 + C1 * x * index2 + C2 * x * x) % M;
    }
    auto i = table[index].begin();
    if ((*i).first == s)
    {
        cout << "Found, Now Delete (Custom)!" << endl;
        table[index].erase(i);
        cout << "Deleted (Custom)" << endl;
    }
    else
        cout << "Not Found, Could not Delete (Custom)" << endl;
}