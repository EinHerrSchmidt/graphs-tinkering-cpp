#include "graphs.h"

int main()
{
    /*
    GraphFactory<int> gf;
    UndirectedGraph g1 = *gf.createUndirectedGraphFromFile("..\\data\\in\\ugraph.csv");
    std::cout << "Undirected Graph:"
              << "\n\n"
              << g1 << "\n";

    DirectedGraph g2 = *gf.createDirectedGraphFromFile("..\\data\\in\\dgraph.csv");
    std::cout << "Directed Graph:"
              << "\n\n"
              << g2;

              */

    Vertex<std::string> a1(0, "A", "a");
    Vertex<std::string> b1(1, "B", "b");
    Vertex<std::string> c1(2, "C", "c");
    Vertex<std::string> d1(3, "D", "d");
    Vertex<std::string> e1(4, "E", "e");
    std::set<Vertex<std::string>> vertices = {a1, b1, c1, d1, e1};
    Edge<std::string> e11(a1, b1);
    Edge<std::string> e21(b1, c1);
    Edge<std::string> e31(d1, a1);
    Edge<std::string> e41(d1, c1);
    std::set<Edge<std::string>> edges = {e11, e21, e31, e41};

    DirectedGraph dgManual(vertices, edges);

    std::cout << "(Manual) Directed Graph:"
              << "\n\n"
              << dgManual << "\n";

    UndirectedGraph udgManual(vertices, edges);

    std::cout << "(Manual) Undirected Graph:"
              << "\n\n"
              << udgManual;

    GraphFactory<std::string> gf;

    gf.generateDOTFile(dgManual, "..\\data\\out\\", "directed");
    gf.generateDOTFile(udgManual, "..\\data\\out\\", "undirected");
}