#include <bits/stdc++.h>
#include "Kruskal.h"
#include "Prim.h"
#include <fstream>
using namespace std;

int main()
{
    fstream file;
    file.open("mst.in");
    int vertices, edges;
    file >> vertices >> edges;
    GraphPrim g1(vertices);
    GraphKruskal g2(vertices, edges);

    int u, v;
    double w;
    for (int i=0; i<edges; i++)
    {
        file >> u >> v;
        file >> w;
        g1.add_edge(u, v, w);
        g2.add_edge(u, v, w);
    }

    int prim_source = 0;
    g1.MST_prim(prim_source);
    g2.set_total_cost(g2.MST_kruskal());
    if (g1.get_min_cost() == g2.get_min_cost())
    {
        printf("Cost of the minimum spanning tree: %0.1lf\n", g2.get_min_cost());
    } else{
        cout << "Cost didn't match. Something went wrong!" << endl;
        return 0;
    }
        
    cout << "List of edges selected by Prim's: {";
    for (int i=0; i<g1.get_MST_track().size(); i+=2)
    {
        cout << "(" << g1.get_MST_track()[i] << "," << g1.get_MST_track()[i+1] << ")";
        if (i+2<g1.get_MST_track().size()){
            cout << ",";
        } else {
            cout << "}" << endl;
        }
    }

    cout << "List of edges selected by Kruskal's: {";
    for (int i=0; i<g2.get_MST_track().size(); i+=2)
    {
        cout << "(" << g2.get_MST_track()[i] << "," << g2.get_MST_track()[i+1] << ")";
        if (i+2<g2.get_MST_track().size()){
            cout << ",";
        } else {
            cout << "}" << endl;
        }
    }
    return 0;
}