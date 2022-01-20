#include "graphs.h"

int main()
{
    GraphFactory gf;
    UndirectedGraph g1 = *gf.createUndirectedGraphFromFile("ugraph.csv");
    std::cout << "Undirected Graph:" << "\n\n" << g1 << "\n";

    DirectedGraph g2 = *gf.createDirectedGraphFromFile("dgraph.csv");
    std::cout << "Directed Graph:" << "\n\n" << g2;
}