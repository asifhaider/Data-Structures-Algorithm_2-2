/*
    Solution of Offline 4 on Maximum Network Flow: Edmonds-Karp Algorithm
    Author: Md. Asif Haider, 1805112
    Date: 11 January 2022
*/

#include "ford-fulkerson.h"
class Baseball_Elimination
{

    // storing input information
    int total_teams;
    vector<int> won;
    vector<int> lost;
    vector<int> remaining;
    vector<vector<int>> matches;
    map<string, int> teams;

public:
    Baseball_Elimination(int n)
    {
        total_teams = n;
    }

    void add_team(int s, string t, int a, int b, int c, vector<int> d)
    {

        won.push_back(a);
        lost.push_back(b);
        remaining.push_back(c);
        matches.push_back(d);
        teams[t] = s;
    }

    string get_teams(int i)
    {
        for (auto x : teams)
        {
            if (x.second == i)
            {
                // cout << x.first;
                return x.first;
            }
        }
        return "";
    }

    bool is_eliminated(string name)
    {
        int x = teams[name];
        // cout << x << endl;
        for (int i = 0; i < total_teams; i++)
        {
            if (won[x] + remaining[x] < won[i])
            {
                // cout << i;
                return true;
            }
        }
        // cout << "bruh";
        int total_matches = (total_teams) * (total_teams - 1) / 2;

        Flow_Network graph(total_matches + total_teams + 2);

        int s = total_matches + total_teams;
        int t = s + 1;
        // cout << s << " " << t << endl;
        int node = 0;

        // cout << "bruh ";

        for (int i = 0; i < total_teams; i++)
        {
            for (int j = i + 1; j < total_teams; j++)
            {
                if (i == j)
                {
                    continue;
                }
                // cout << "bruh";
                // cout << matches[i][j] << " ";
                Edge e1(s, node, matches[i][j], 0); // src to match
                // cout << e1.get_capacity() << e1.get_destination();
                graph.add_edge(e1);
                Edge e2(node, total_matches + i, INF, 0);
                graph.add_edge(e2);
                Edge e3(node, total_matches + j, INF, 0);
                graph.add_edge(e3);
                node++;
                // cout << "bruh";
                // vector <Edge> a = graph.get_adj(0);
                // for (auto i:a)
                // {
                //     cout << i.get_capacity() << endl;
                // }
            }
            Edge e4(total_matches + i, t, max(0, won[x] + remaining[x] - won[i]), 0);
            graph.add_edge(e4);
        }

        // cout << graph.total_edges() << endl;
        

        // cout << s << " " << t;
        graph.ford_fulkerson(s, t);
        // cout << "bruh";

        for (Edge e : graph.get_adj(s))
        {
            // cout << e.get_flow() << " " << e.get_capacity() << endl;
            if (e.get_flow() != e.get_capacity())
                return true;
        }
        // cout << "spuer bruh";
        return false;
    }
};

int main()
{

    fstream file;
    file.open("input.txt");

    // vector <int> wins, left;
    int total_teams;
    file >> total_teams;
    Baseball_Elimination instance(total_teams);

    string team;
    int w, l, r, x;

    for (int i = 0; i < total_teams; i++)
    {
        vector<int> g;

        file >> team;

        file >> w >> l >> r;
        for (int j = 0; j < total_teams; j++)
        {
            file >> x;
            g.push_back(x);
        }

        instance.add_team(i, team, w, l, r, g);
        // cout << "bruh";
    }

    for (int i = 0; i < total_teams; i++)
    {
        if (instance.is_eliminated(instance.get_teams(i)))
        {
            cout << instance.get_teams(i) << " is eliminated." << endl;
        }
    }

    // if (instance.is_eliminated(instance.get_teams(2)))
    //     cout << instance.get_teams(2) << " is eliminated." << endl;
    // else
    //     cout << "Still in game!";
    return 0;
}