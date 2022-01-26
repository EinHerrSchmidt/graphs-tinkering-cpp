#include "graphs.h"

int main()
{
    GraphFactory<int> gf;
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

    Vertex<std::string> a(1,"A","a");
    Vertex<std::string> b(2,"B","b");
    Vertex<std::string> c(3,"C","c");
    Vertex<std::string> d(4,"D","d");
    Edge<std::string> e1(a, b);
    Edge<std::string> e2(b, c);
    Edge<std::string> e3(d, a);
    Edge<std::string> e4(d, c);
    std::set<Edge<std::string>> edges = {e1, e2, e3, e4};
    
    DirectedGraph dgManual(4, edges);
    std::cout << "Directed Graph:"
              << "\n\n"
              << dgManual;
}