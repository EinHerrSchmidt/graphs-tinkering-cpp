#include "graphs.h"

int main()
{
    GraphFactory gf;
    UndirectedGraph g1 = *gf.createUndirectedGraphFromFile("..\\data\\ugraph.csv");
    std::cout << "Undirected Graph:" << "\n\n" << g1 << "\n";

    DirectedGraph g2 = *gf.createDirectedGraphFromFile("..\\data\\dgraph.csv");
    std::cout << "Directed Graph:" << "\n\n" << g2;
}