/*
    Solution of Offline 3 on All Pair Shortest Path Algorithm: Floyd Warshall
    Author: Md. Asif Haider, 1805112
    Date: 21 December 2021
*/

#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

void floyd_warshall(vector <vector<int>> graph, int vertices)
{
    vector <vector <int> > distance;
    distance = graph;

    for(int k=0; k<vertices; k++)
    {
        for (int i=0; i<vertices; i++)
        {
            for(int j=0; j<vertices; j++)
            {
                if(distance[i][k] < INF && distance[k][j] < INF)
                {
                    distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
                }
            }
        }
    }

    cout << "Shortest distance matrix" << endl << endl;
    for(int i=0; i<vertices; i++)
    {
        for(int j=0; j<vertices; j++)
        {
            if(distance[i][j] == INF)
            {
                cout << "INF";
            } else{
                cout << " " << distance[i][j] << " ";
            }
            cout << "   ";
        }
        cout << endl;
    }
}

int main()
{
    fstream file;
    file.open("input.txt");

    int vertices, edges;
    file >> vertices >> edges;

    vector<vector<int>>graph(vertices, vector<int>(vertices, INF));

    for(int i=0; i<vertices; i++)
    {
        for(int j=0; j<vertices; j++)
        {
            if (i==j){
                graph[i][j] = 0;
            }
        }
    }

    int u, v;
    double w;
    for (int i=0; i<edges; i++)
    {
        file >> u >> v;
        file >> w;
        graph[u-1][v-1] = w;
    }

    floyd_warshall(graph, vertices);
    return 0;
}
