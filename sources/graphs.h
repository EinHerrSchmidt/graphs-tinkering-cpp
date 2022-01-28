#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <string>

template <typename T>
class Vertex
{
private:
    int id;
    std::string label;
    T value;
    std::set<Vertex<T> *> adjacentNodes;

public:
    Vertex();
    Vertex(int i, std::string l, T v);
    int getId();
    std::string getLabel();
    T getValue();
    std::set<Vertex<T> *> getAdjacentNodes();
    void addNeighbor(Vertex<T> *n);
    bool operator<(const Vertex<T> &v) const;
    bool operator==(const Vertex<T> &v) const;
};

template <typename T>
class Edge
{
private:
    Vertex<T> *v1;
    Vertex<T> *v2;
    int weight;

public:
    Edge();
    Edge(Vertex<T> *n1, Vertex<T> *n2);
    Edge(Vertex<T> *n1, Vertex<T> *n2, int wt);
    Vertex<T> *getV1();
    Vertex<T> *getV2();
    int getWeight();
    bool operator<(const Edge<T> &e) const;
};

template <typename T>
class Graph
{
protected:
    int totalVertices;
    std::set<Vertex<T> *> vertices;
    std::set<Edge<T> *> edges;
    template <typename E>
    friend std::ostream &operator<<(std::ostream &, const Graph<E> &);
    std::string adjacencyListsAsString(const std::string edgeType, const std::string separator, const std::string bracketType) const;

public:
    int size() const;
    std::set<Vertex<T> *> getVertices();
    virtual std::string toDOT(std::string title) const = 0; // this is an abstract method (pure virtual function)
};

template <typename T>
std::ostream &operator<<(std::ostream &strm, const Graph<T> &graph)
{
    std::string graphAsString = graph.adjacencyListsAsString("->", ",", "square");
    return strm << graphAsString;
}

template <typename T>
class UndirectedGraph : public Graph<T>
{
protected:
    std::string toDOT(std::string title) const;

public:
    UndirectedGraph(std::set<Edge<T>> edges);
};

template <typename T>
class DirectedGraph : public Graph<T>
{
protected:
    std::string toDOT(std::string title) const;

public:
    DirectedGraph(std::set<Edge<T>> edges);
};

template <typename T>
class GraphFactory
{
private:
    std::pair<int, std::set<Edge<T>>> *verticesNumberAndEdgeSetFromFile(std::string inputFile);

public:
    UndirectedGraph<T> *createUndirectedGraphFromFile(std::string inputFile);
    DirectedGraph<T> *createDirectedGraphFromFile(std::string inputFile);
    void generateDOTFile(const Graph<T> &graph, const std::string filePath, const std::string title);
};

#endif