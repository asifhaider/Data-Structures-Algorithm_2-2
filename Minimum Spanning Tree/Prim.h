#include <bits/stdc++.h>
using namespace std;

#define INF DBL_MAX
#define NIL -1

class GraphPrim
{
    int vertices;   // O(1)
    vector <pair <int, double>> *adj_list; // vertex first, weight later    // O(M)
    double min_cost = 0.0;
    // storage for MST path
    vector <int> MST_track;

    

public:
    GraphPrim (int V);
    void add_edge (int u, int v, double w);
    void MST_prim(int source);
    double get_min_cost()
    {
        return this->min_cost;
    }
    vector<int> get_MST_track()
    {
        return this->MST_track;
    }
};

// O(1)
GraphPrim::GraphPrim(int V)
{
    this->vertices = V;
    adj_list = new vector<pair<int, double>> [vertices];   // storing adjacency and weights
}

// O(1)
void GraphPrim::add_edge(int u, int v, double w)
{
    adj_list[u].push_back(make_pair(v, w)); // undirected graph
    adj_list[v].push_back(make_pair(u, w));
}


void GraphPrim::MST_prim(int source)
{
    // min heap, using customized stl priority queue, O(M)
    priority_queue < pair <double, int>, vector <pair <double, int>>, greater<pair<double, int>> > pq; // weight first, vertex later
    // storing keys, O(N)
    vector <double> keys(vertices, INF);
    // storing parents, O(N)
    vector <int> ancestors(vertices, NIL);
    // checking if in MST or not, O(N) 
    vector <bool> insideMST (vertices, false);
    
    // double min_cost = 0.0;
    // O(log M)
    pq.push(make_pair(0, source));
    keys[source] = 0;


    while(!pq.empty())
    {
        // O(log N)
        int u = pq.top().second;
        pq.pop();
        
        if (insideMST[u]==true){
            continue;
        }
        insideMST[u] = true;
            
        if (ancestors[u] != -1){
            min_cost += keys[u];
            MST_track.push_back(ancestors[u]);
            MST_track.push_back(u);    
        }
        vector <pair <int, double> >:: iterator it;
        for (it = adj_list[u].begin(); it!= adj_list[u].end(); it++)
        {
            int v = (*it).first;
            int w = (*it).second;
            if (insideMST[v] == false && keys[v] >= w)
            {
                keys[v] = w;
                pq.push(make_pair(keys[v], v));
                ancestors[v] = u;
            }
        }
    }

}
