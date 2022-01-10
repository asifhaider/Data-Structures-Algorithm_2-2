/*
    Solution of Offline 2 on Single Source Shortest Path Algorithm: Dijkstra 
    Author: Md. Asif Haider, 1805112
    Date: 14 December 2021
*/

#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

class Graph
{
    int total_vertices;
    // adjacency list
    vector <pair<int, int>> *adj_list;
public:
    Graph(int n);
    void add_edges(int u, int v, int w);
    void dijkstra_shortest_path(int source, int destination);

};

Graph::Graph(int n)
{
    this->total_vertices = n;
    adj_list = new vector<pair<int, int>>[total_vertices];
}
void Graph::add_edges(int u, int v, int w)
{
    adj_list[u].push_back(make_pair(v, w)); // directed graph
}

void Graph::dijkstra_shortest_path(int source, int destination)
{
    vector<int> distances (total_vertices, INF);
    priority_queue <pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;
    vector<int> parents (total_vertices);

    distances[source] = 0;
    pq.push(make_pair(0, source));
    parents[source] = -1;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        vector<pair<int, int>>::iterator i;
        for (i=adj_list[u].begin(); i!=adj_list[u].end(); i++)
        {
            int v = (*i).first;
            int w = (*i).second;

            // edge relaxation
            if(distances[v] > distances[u] + w)
            {
                distances[v] = distances[u] + w;
                pq.push(make_pair(distances[v], v));
                parents[v] = u;
            }
        }
    }

    int j = destination;
    vector<int> result;
    result.push_back(j);
    int total_cost = distances[j];
    while(parents[j]!=-1)
    {
        result.push_back(parents[j]);
        j = parents[j];
    }

    
    cout << "Shortest path cost: " << total_cost << endl;
    
    for (int i = result.size()-1; i>=0; i--)
    {
        cout << result[i];
        if (i!=0)
            cout << " -> ";
    }
    cout << endl;
}

int main()
{
    fstream file;
    file.open("input1.txt");
    int vertices, edges;
    file >> vertices >> edges;
    Graph g (vertices);

    int u, v;
    double w;
    for (int i=0; i<edges; i++)
    {
        file >> u >> v;
        file >> w;
        g.add_edges(u, v, w);
    }

    int start, end;
    file >> start >> end;

    g.dijkstra_shortest_path(start, end);
    return 0;
}