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
    std::set<Vertex<std::string> *> dgVertices = {&a1, &b1, &c1, &d1, &e1};
    Edge<std::string> e11(&a1, &b1);
    Edge<std::string> e21(&b1, &c1);
    Edge<std::string> e31(&d1, &a1);
    Edge<std::string> e41(&d1, &c1);
    std::set<Edge<std::string>> dgEdges = {e11, e21, e31, e41};

    DirectedGraph dgManual(dgVertices, dgEdges);

    std::cout << "(Manual) Directed Graph:"
              << "\n\n"
              << dgManual << "\n";

    Vertex<std::string> a2(0, "A", "a");
    Vertex<std::string> b2(1, "B", "b");
    Vertex<std::string> c2(2, "C", "c");
    Vertex<std::string> d2(3, "D", "d");
    Vertex<std::string> e2(4, "E", "e");
    std::set<Vertex<std::string> *> udgVertices = {&a2, &b2, &c2, &d2, &e2};
    Edge<std::string> e12(&a2, &b2);
    Edge<std::string> e22(&b2, &c2);
    Edge<std::string> e32(&d2, &a2);
    Edge<std::string> e42(&d2, &c2);
    std::set<Edge<std::string>> udgEdges = {e12, e22, e32, e42};

    UndirectedGraph udgManual(udgVertices, udgEdges);

    std::cout << "(Manual) Undirected Graph:"
              << "\n\n"
              << udgManual;

    GraphFactory<std::string> gf;

    gf.generateDOTFile(dgManual, "..\\data\\out\\", "directed");
    gf.generateDOTFile(udgManual, "..\\data\\out\\", "undirected");
}