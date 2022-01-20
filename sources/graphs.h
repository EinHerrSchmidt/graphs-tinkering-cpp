#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <string>

class Edge
{
private:
    int v1;
    int v2;

public:
    Edge(int n1, int n2);
    int getV1();
    int getV2();
    bool operator<(const Edge &e) const;
};

class Graph
{
protected:
    int totalVertices;
    std::vector<std::set<int>> neighbors;
    friend std::ostream &operator<<(std::ostream &, const Graph &);
    std::string adjacencyListsAsString(const std::string edgeType, const std::string separator, const std::string bracketType) const;

public:
    int size() const;
    std::vector<std::set<int>> getAdjacencyLists() const;
    virtual std::string toDOT(std::string title) const = 0; // this is an abstract method (pure virtual function)
};

class UndirectedGraph : public Graph
{
protected:
    std::string toDOT(std::string title) const;

public:
    UndirectedGraph(int v, std::set<Edge> edges);
};

class DirectedGraph : public Graph
{
protected:
    std::string toDOT(std::string title) const;

public:
    DirectedGraph(int v, std::set<Edge> edges);
};

class GraphFactory
{
private:
    std::pair<int, std::set<Edge>> *verticesAndEdgeSetFromFile(std::string inputFile);

public:
    UndirectedGraph *createUndirectedGraphFromFile(std::string inputFile);
    DirectedGraph *createDirectedGraphFromFile(std::string inputFile);
    void generateDOTFile(const Graph &graph, const std::string filePath, const std::string title);
};

#endif