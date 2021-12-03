#include <bits/stdc++.h>
#include <fstream>

using namespace std;

class Graph
{
    int vertices;   // no. of vertices
    list<int> *adj; // adjacency list pointer

public:

    Graph(int V); // constructor
    void addEdge (int u, int v); // edge between to vertices;
    // void DFS(int source);   // DFS traversal
    bool isCyclic();
    bool isCycleUtil(int v, bool visited[], bool *recordStack);

};

Graph::Graph (int V)
{
    this->vertices = V;
    adj = new list<int>[V]; // initializing new adjacency list
}

void Graph::addEdge (int u, int v)
{
    adj[u].push_back(v);    // assigning adjacency
}

bool Graph::isCyclic(){
    bool *visited = new bool[vertices];
    bool *recordStack = new bool[vertices];
    for (int i=0; i<vertices; i++)
    {
        visited[i] = false;
        recordStack[i] = false;
    }

    for (int i=0; i<vertices; i++)
    {
        if(isCycleUtil(i, visited, recordStack))
            return true;
    }
    return false;
}

bool Graph::isCycleUtil(int v, bool visited[], bool *recordStack)
{
    if (!visited[v])
    {
        visited[v] = true;
        recordStack[v] = true;

        list<int>::iterator i;
        for (i=adj[v].begin(); i!=adj[v].end(); i++)
        {
            if (!visited[*i] && isCycleUtil(*i, visited, recordStack))
            {
                return true;
            } else if (recordStack[*i])
                return true;
        }
    }
    recordStack[v] = false;
    return false;
}

// driver code to run bfs
int main()
{
    fstream file;
    file.open("test.txt");
    int total_vertex, total_edge;
    file >> total_vertex >> total_edge;
    // cout << total_vertex << " " << total_edge;

    // edge input start
    Graph g(total_vertex);
    int u, v;
    for (int i=0; i<total_edge; i++)
    {
        file >> u >> v;
        // cout << u << " " << v;
        g.addEdge(u, v);    // 1 indexed
    }

    // cout << "============= Finding Cycle ==============" << endl;
    // g.DFS(3);   // 1 indexed
    if (g.isCyclic())
        cout << "No" << endl;
    else
        cout << "Yes" << endl;

    return 0;
}
