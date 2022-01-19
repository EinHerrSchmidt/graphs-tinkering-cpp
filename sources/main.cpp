#include "graphs.h"

int main()
{
    std::set<Edge> edges = {Edge(0, 1), Edge(1, 2), Edge(2, 0), Edge(3, 0), Edge(3, 1)};
    int vertices = 4;
    UndirectedGraph graph(vertices, edges);
    std::cout << graph;

    std::cout << "----------------------"
         << "\n";

    GraphFactory gf;
    UndirectedGraph g1 = *gf.createUndirectedGraphFromFile("graph.csv");
    std::cout << g1;
}