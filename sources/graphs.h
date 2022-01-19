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

public:
    int size();
    std::vector<std::set<int>> getAdjacencyLists();
};

class UndirectedGraph : public Graph
{
public:
    UndirectedGraph(int v, std::set<Edge> edges);
};

class DirectedGraph : public Graph
{
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
};

#endif