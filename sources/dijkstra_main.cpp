#include "graphs.h"

int main()
{
    Vertex<std::string> a(0, "A", "a");
    Vertex<std::string> b(1, "B", "b");
    Vertex<std::string> c(2, "C", "c");
    Vertex<std::string> d(3, "D", "d");
    Vertex<std::string> e(4, "E", "e");
    Vertex<std::string> f(5, "F", "f");
    Vertex<std::string> g(6, "G", "g");
    std::set<Vertex<std::string>> vertices = {a, b, c, d, e, f, g};
    Edge<std::string> ab(a, b, 1);
    Edge<std::string> bc(b, c, 3);
    Edge<std::string> cd(c, d, 4);
    Edge<std::string> db(d, b, 5);
    Edge<std::string> da(d, a, 6);
    Edge<std::string> cg(c, g, 7);
    Edge<std::string> dg(d, g, 2);
    Edge<std::string> de(d, e, 2);
    Edge<std::string> gf(g, f, 3);
    Edge<std::string> fe(f, e, 4);
    Edge<std::string> ea(e, a, 5);
    std::set<Edge<std::string>> edges = {ab,
                                         bc,
                                         cd,
                                         db,
                                         da,
                                         cg,
                                         dg,
                                         de,
                                         gf,
                                         fe,
                                         ea};

    DirectedGraph dgManual(vertices, edges);

    std::cout << "(Manual) Directed Graph:"
              << "\n\n"
              << dgManual << "\n";

    dgManual.printMinPath(a);
}