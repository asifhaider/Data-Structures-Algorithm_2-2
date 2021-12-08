#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
    int *parent, *rank;
    int n;
public: 
    DisjointSet(int n);
    int find_set(int v);
    void union_sets(int a, int b);
};

DisjointSet::DisjointSet(int n)
{
    this->n = n;
    parent = new int[n+1];
    rank = new int[n+1];
    for (int i =0; i<n; i++)
    {
        rank[i] = 0;
        parent[i] = i;    
    }

}

int DisjointSet::find_set(int v)
{
    if(parent[v] == v){
        return v;
    }
    return parent[v] = find_set(parent[v]);
}

void DisjointSet::union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a!=b)
    {
        if(rank[a]<rank[b]){
            swap(a,b);
        }
        parent[b] = a;
        if(rank[a] == rank[b])
        {
            rank[a]++;
        }
    }
}

class GraphKruskal
{
    int vertices, edges; 
    vector <pair<double, pair<int, int>>> weighted_edges;
    vector <int> MST_track;
    double total_cost;
    
public:
    GraphKruskal (int V, int E);
    void add_edge (int u, int v, double w);
    double MST_kruskal();
    vector <int> get_MST_track();
    double get_min_cost();
    void set_total_cost(double cost);
    
};


GraphKruskal::GraphKruskal(int V, int E)
{
    this->vertices = V;
    this->edges = E;
}

void GraphKruskal::add_edge(int u, int v, double w)
{
    weighted_edges.push_back({w, {u,v}});
}


double GraphKruskal::MST_kruskal()
{
    double total_weight = 0;
    sort(weighted_edges.begin(), weighted_edges.end());
    
    DisjointSet ds(vertices);
    vector <pair<double, pair<int, int>>>:: iterator it;
    
    for (it=weighted_edges.begin(); it!= weighted_edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
        if(ds.find_set(u)!=ds.find_set(v))
        {
            MST_track.push_back(u);
            MST_track.push_back(v);
            total_weight += it->first;
            ds.union_sets(u, v);
        }
    }
    return total_weight;
}

vector <int> GraphKruskal::get_MST_track()
{
    return this->MST_track;
}

double GraphKruskal::get_min_cost()
{
    return this->total_cost;
}

void GraphKruskal::set_total_cost(double cost)
{
    this->total_cost = cost;
}
