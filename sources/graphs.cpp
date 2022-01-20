#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <string>
#include "graphs.h"

using namespace std;

Edge::Edge(int n1, int n2)
{
    v1 = n1;
    v2 = n2;
}

int Edge::getV1()
{
    return v1;
}

int Edge::getV2()
{
    return v2;
}

bool Edge::operator<(const Edge &e) const
{
    return v1 < e.v1 || (v1 == e.v1 && v2 < e.v2);
}

int Graph::size()
{
    return totalVertices;
}

vector<set<int>> Graph::getAdjacencyLists()
{
    return neighbors;
}

std::ostream &operator<<(std::ostream &strm, const Graph &graph)
{
    string graphAsString = "";
    int vertex = 0;
    for (set<int> vertexNeighbors : graph.neighbors)
    {
        graphAsString.append(to_string(vertex++)).append(" -> [");
        int i = 0;
        for (int neighbor : vertexNeighbors)
        {
            graphAsString.append(to_string(neighbor));
            if (i++ < vertexNeighbors.size() - 1)
            {
                graphAsString.append(", ");
            }
        }
        graphAsString.append("]\n");
    }
    return strm << graphAsString;
}

UndirectedGraph::UndirectedGraph(int v, set<Edge> edges)
{
    totalVertices = v;
    for (int i = 0; i < totalVertices; i++)
    {
        set<int> s;
        neighbors.push_back(s);
    }

    for (Edge e : edges)
    {
        neighbors[e.getV1()].insert(e.getV2());
        neighbors[e.getV2()].insert(e.getV1());
    }
}

DirectedGraph::DirectedGraph(int v, set<Edge> edges)
{
    totalVertices = v;
    for (int i = 0; i < totalVertices; i++)
    {
        set<int> s;
        neighbors.push_back(s);
    }

    for (Edge e : edges)
    {
        neighbors[e.getV1()].insert(e.getV2());
    }
}

pair<int, set<Edge>> *GraphFactory::verticesAndEdgeSetFromFile(string inputFilePath)
{
    int totalVertices = 0;
    set<Edge> edges;
    string line;
    ifstream file(inputFilePath);
    if (file.is_open())
    {
        // first line contains number of vertices in the graph
        getline(file, line);
        totalVertices = stoi(line);
        while (getline(file, line))
        {
            size_t pos = 0;
            string edgeVertices[2];
            char delimiter = '\t';
            int tokenPosition = 0;
            // std::string::npos -> Value returned by various member functions when they fail.
            pos = line.find(delimiter);
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                edgeVertices[tokenPosition++] = line.substr(0, pos);
                line.erase(0, pos + 1); // + 1 -> delimiter's length
            }
            edgeVertices[tokenPosition] = line.substr(pos + 1, std::string::npos);
            edges.insert(Edge(stoi(edgeVertices[0]), stoi(edgeVertices[1])));
        }
    }
    return new pair<int, set<Edge>>(totalVertices, edges);
}

UndirectedGraph *GraphFactory::createUndirectedGraphFromFile(string inputFile)
{
    pair<int, set<Edge>> verticesAndEdges = *this->verticesAndEdgeSetFromFile(inputFile);
    return new UndirectedGraph(verticesAndEdges.first, verticesAndEdges.second);
}

DirectedGraph *GraphFactory::createDirectedGraphFromFile(string inputFile)
{
    pair<int, set<Edge>> verticesAndEdges = *this->verticesAndEdgeSetFromFile(inputFile);
    return new DirectedGraph(verticesAndEdges.first, verticesAndEdges.second);
}