#include "graphs.h"

int main()
{
    GraphFactory gf;
    UndirectedGraph g1 = *gf.createUndirectedGraphFromFile("..\\data\\in\\ugraph.csv");
    std::cout << "Undirected Graph:"
              << "\n\n"
              << g1 << "\n";

    DirectedGraph g2 = *gf.createDirectedGraphFromFile("..\\data\\in\\dgraph.csv");
    std::cout << "Directed Graph:"
              << "\n\n"
              << g2;

    gf.generateDOTFile(g1, "..\\data\\out\\", "undirected");
    gf.generateDOTFile(g2, "..\\data\\out\\", "directed");
}