/*
    Solution of Offline 2 on Single Source Shortest Path Algorithm: Bellman Ford 
    Author: Md. Asif Haider, 1805112
    Date: 14 December 2021
*/

#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

struct Edge
{
    int source, destination, weight;
};

class Graph
{
    int total_vertices, total_edges;
    // edge list
    vector<Edge> edges;

public:
    Graph(int V, int E);
    void add_edges(int u, int v, int w);
    void bellman_ford_shortest_path(int source, int destination);
};

Graph::Graph(int V, int E)
{
    this->total_vertices = V;
    this->total_edges = E;
}
void Graph::add_edges(int u, int v, int w)
{
    Edge edge;
    edge.source = u;
    edge.destination = v;
    edge.weight = w;
    edges.push_back(edge);
}

void Graph::bellman_ford_shortest_path(int source, int destination)
{
    vector<int> distances(total_vertices, INF);
    vector<int> parents (total_vertices);

    distances[source] = 0;
    parents[source] = -1;
    
    for (int i = 0; i < total_vertices - 1; i++)
    {
        for (int j = 0; j < total_edges; j++)
        {
            int u = edges[j].source;
            int v = edges[j].destination;
            int w = edges[j].weight;

            // edge relaxation
            if (distances[u] != INF && distances[v] > distances[u] + w)
            {
                distances[v] = distances[u] + w;
                parents[v] = u;
            }
        }
    }

    // negative cycle checking, if edges can be relaxed more efficiently, then negative cycle exists
    for (int i = 0; i < total_edges; i++)
    {
        int u = edges[i].source;
        int v = edges[i].destination;
        int w = edges[i].weight;
        if (distances[u] != INF && distances[v] > distances[u] + w)
        {
            cout << "The graph contains a negative cycle" << endl;
            return;
        }
    }

    cout << "The graph does not contain a negative cycle" << endl;

    vector <int> result;
    int j = destination;
    result.push_back(j);
    int total_cost = distances[j];
    while(parents[j]!=-1)
    {
        result.push_back(parents[j]);
        j = parents[j];
    }

    cout << "Shortest path cost: " << total_cost << endl;

    for (int i = result.size() - 1; i >= 0; i--)
    {
        cout << result[i];
        if (i != 0)
            cout << " -> ";
    }
    cout << endl;
}

int main()
{
    fstream file;
    file.open("input2.txt");
    int vertices, edges;
    file >> vertices >> edges;
    Graph g (vertices, edges);

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

    g.bellman_ford_shortest_path(start, end);
    return 0;
}