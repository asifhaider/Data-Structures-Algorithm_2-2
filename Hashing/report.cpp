#include "hashing.h"

int main()
{
    vector<string> v;
    Hash_Table h1(7);
    Hash_Table h2(7);
    Hash_Table h3(7);
    string s;

    // ==================== chain ======================

    // for (int i = 0; i < 10000; i++)
    // {
    //     s = h1.String_Generator();
    //     int j;
    //     for (j = 0; j < v.size(); j++)
    //     {
    //         if (v[j] == s)
    //             break;
    //     }
    //     if (j == v.size())
    //     {
    //         h1.insert_chain(s, i + 1);
    //         v.push_back(s);
    //     }
    //     else
    //         i--;
    // }

    // h1.print_table();
    // cout << v.size() << endl;

    // for (int i = 0; i < 1000; i++)
    // {
    //     int index = rand() % 10000;
    //     string s = v[index];
    //     cout << "Searching string with value: " << s << endl;
    //     h1.search_chain(s);
    // }

    // ==================== double ======================

    // for (int i = 0; i < 10000; i++)
    // {
    //     s = h2.String_Generator();
    //     int j;
    //     for (j = 0; j < v.size(); j++)
    //     {
    //         if (v[j] == s)
    //             break;
    //     }
    //     if (j == v.size())
    //     {
    //         h2.insert_double(s, i + 1);
    //         v.push_back(s);
    //     } else
    //         i--;
    // }

    // h2.print_table();
    // cout << v.size() << endl;

    // for (int i = 0; i < 1000; i++)
    // {
    //     int index = rand()%10000;
    //     string s = v[index];
    //     cout << "Searching string with value: " << s << endl;
    //     h2.search_double(s);
    // }

    // ==================== custom ========================

    for (int i = 0; i < 10000; i++)
    {
        s = h3.String_Generator();
        int j;
        for (j = 0; j < v.size(); j++)
        {
            if (v[j] == s)
                break;
        }
        if (j == v.size())
        {
            h3.insert_custom(s, i + 1);
            v.push_back(s);
        }
        else
            i--;
    }

    // h3.print_table();
    // cout << v.size() << endl;

    // for (int i = 0; i < 1000; i++)
    // {
    //     int index = rand() % 10000;
    //     string s = v[index];
    //     cout << "Searching string with value: " << s << endl;
    //     h3.search_custom(s);
    // }

    return 0;
}
