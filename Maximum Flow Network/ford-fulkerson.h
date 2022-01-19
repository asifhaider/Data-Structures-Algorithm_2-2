#include <bits/stdc++.h>
#define INF INT_MAX

using namespace std;

class Edge
{
    int source, destination, capacity, flow;
public:

    Edge()
    {

    }
    Edge(int u, int v, int c, int f)
    {
        source = u;
        destination = v;
        capacity = c;
        flow = f;
    }

    int residual_capacity (int n)
    {
        if (n == source) return flow;
        else if (n == destination) return (capacity - flow);
        else return -1;
    }

    int get_source ()
    {
        return source;
    }

    int get_destination ()
    {
        return destination;
    }

    int get_flow ()
    {
        return flow;
    }

    int get_capacity()
    {
        return capacity;
    }

    void set_flow (int f)
    {
        flow = f;
    }

    int other_node(int v)
    {
        if (v == source) return destination;
        else if (v == destination) return source;
        else return -1;
    }
};

class Flow_Network
{
    int vertices, edges=0;
    vector < vector <Edge> > adj;

    int max_flow = 0;
    vector <bool> visited;  // marked
    vector < Edge > residual_edges;   // edgeTo
public:
    Flow_Network(int v)
    {
        vertices = v;
        edges = 0;
        Edge e(-1,-1,-1,-1);
        adj = vector <vector <Edge>>(vertices);

        visited = vector<bool>(vertices, false);
        residual_edges = vector<Edge>(vertices);
        // for (int v = 0; v<vertices; v++)
            // adj[v] = vector <Edge>(vertices);
        // adj.resize(vertices, vector<Edge>(vertices, e));
    }

    int get_max_flow()
    {
        return max_flow;
    }

    vector <Edge> get_adj(int v)
    {
        return adj[v];
    }

    int total_edges()
    {
        return edges;
    }

    void add_edge(Edge e)
    {
        // cout << "bruh";
        int u = e.get_source();
        int v = e.get_destination();
        // cout << "bruh";

        // ============ break point ==============
        adj[u].push_back(e);
        // cout << adj[u][v].get_capacity() << " ";
        // cout << "bruh";
        adj[v].push_back(e);
        edges++ ;
        // cout << edges;
        // int i = adj.size();
        // cout << i;
        // while(i>0)
        // {
        //     cout << adj[u][v].get_capacity() << endl;
        //     i--;
        // }

    }

    bool found_augmented_path(int s, int t)
    {
       
        // bfs
        queue <int> q;
        q.push(s);
        visited[s] = true;

        // cout << "bruh";
        // cout << get_adj(10)[100].get_destination();

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            // cout << get_adj(0).size() << endl;
        
            for (Edge e: get_adj(u))
            {
                // cout << "bruh";
                int v = e.other_node(u);
                // infinite loop 
                // cout << u << " " << v << endl;
                

                // residual capacity check
                if (e.residual_capacity(v) > 0)
                {
                    // cout << "bruh";
                    if (!visited[v])
                    {
                        // cout << "bruh";
                        residual_edges[v] = e;
                        visited[v] = true;
                        if (v==t){
                            return true;
                        }
                        q.push(v);
                    }
                }
            }
        }

        return false;
    }

    void ford_fulkerson(int s, int t)
    {
        int max_flow = 0;
        // cout << adj[t].size();
        for (Edge e: adj[t])
        {
            if (t == e.get_destination())
                max_flow -= e.get_flow();
            else
                max_flow += e.get_flow();
            // cout << e.get_destination() << endl;
        }
        // cout << "bruh";
        // cout << max_flow;

        while (found_augmented_path(s, t))
        {
            // cout << "bruh";
            int bottleneck = INF;
            int v = t;
            while (v!=s)
            {
                bottleneck = min(bottleneck, residual_edges[v].residual_capacity(v));
                v=residual_edges[v].other_node(v);
                // cout << bottleneck << " ";
            }

            // cout << "bruh";
            // break;
            v = t;
            while (v!=s)
            {
                if (residual_edges[v].get_source() == v)
                {
                    residual_edges[v].set_flow(residual_edges[v].get_flow() - bottleneck);
                } else if (residual_edges[v].get_destination() == v)
                {
                    residual_edges[v].set_flow(residual_edges[v].get_flow() + bottleneck);
                }
                v=residual_edges[v].other_node(v);
                
                // cout << "bruh ";
            }

            max_flow += bottleneck;
            // cout << max_flow << endl;
        }
    }
};
