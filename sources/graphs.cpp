#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <set>
#include <string>
#include "graphs.h"

using namespace std;

template <typename T>
Vertex<T>::Vertex() {}

template <typename T>
Vertex<T>::Vertex(int i, string l, T v)
{
    id = i;
    label = l;
    value = v;
}

template <typename T>
int Vertex<T>::getId()
{
    return id;
}

template <typename T>
string Vertex<T>::getLabel()
{
    return label;
}

template <typename T>
T Vertex<T>::getValue()
{
    return value;
}
std::string getLabel();

template <typename T>
bool Vertex<T>::operator<(const Vertex<T> &v) const
{
    return id < v.id;
}

template <typename T>
bool Vertex<T>::operator==(const Vertex<T> &v) const
{
    return id == v.id;
}

template <typename T>
void Vertex<T>::addNeighbor(Vertex<T> n)
{
    adjacentNodes.insert(n);
}

template <typename T>
std::set<Vertex<T>> Vertex<T>::getAdjacentNodes()
{
    return adjacentNodes;
}

template <typename T>
Edge<T>::Edge() {}

template <typename T>
Edge<T>::Edge(Vertex<T> n1, Vertex<T> n2)
{
    v1 = n1;
    v2 = n2;
}

template <typename T>
Edge<T>::Edge(Vertex<T> n1, Vertex<T> n2, int wt)
{
    v1 = n1;
    v2 = n2;
    weight = wt;
}

template <typename T>
Vertex<T> Edge<T>::getV1()
{
    return v1;
}

template <typename T>
Vertex<T> Edge<T>::getV2()
{
    return v2;
}

template <typename T>
int Edge<T>::getWeight()
{
    return weight;
}

template <typename T>
bool Edge<T>::operator<(const Edge<T> &e) const
{
    return v1 < e.v1 || (v1 == e.v1 && v2 < e.v2);
}

template <typename T>
int Graph<T>::size() const
{
    return vertices.size();
}

template <typename T>
std::set<Vertex<T>> Graph<T>::getVertices()
{
    return vertices;
}

template <typename T>
std::set<Edge<T>> Graph<T>::getEdges()
{
    return edges;
}

template <typename T>
string Graph<T>::adjacencyListsAsString(const string edgeType, const string separator, const string bracketType) const
{
    string openBracket;
    string closeBracket;
    if (bracketType == "curly")
    {
        openBracket = "{";
        closeBracket = "}";
    }
    else if (bracketType == "square")
    {
        openBracket = "[";
        closeBracket = "]";
    }
    else
    {
        openBracket = "(";
        closeBracket = ")";
    }
    string graphAsString = "";
    for (Vertex<T> v : this->vertices)
    {
        graphAsString.append(v.getLabel() + " " + edgeType + " " + openBracket);
        int i = 0;
        for (Vertex<T> neighbor : v.getAdjacentNodes())
        {
            graphAsString.append((neighbor).getLabel());
            if (i++ < v.getAdjacentNodes().size() - 1)
            {
                graphAsString.append(separator + " ");
            }
        }
        graphAsString.append(closeBracket + "\n");
    }
    return graphAsString;
}

template <typename T>
void Graph<T>::updateVertices(Vertex<T> v1, Vertex<T> v2)
{
    this->vertices.erase(v1);
    this->vertices.erase(v2);
    this->vertices.insert(v1);
    this->vertices.insert(v2);
}

template <typename T>
void Graph<T>::checkEdgeConsistency(Edge<T> e)
{
    if (this->vertices.find(e.getV1()) == this->vertices.end())
    {
        throw invalid_argument("Vertex " + to_string(e.getV1().getId()) + " belongs to an edge, but it is not in the vertexes set.");
    }
    if (this->vertices.find(e.getV2()) == this->vertices.end())
    {
        throw invalid_argument("Vertex " + to_string(e.getV2().getId()) + " belongs to an edge, but it is not in the vertexes set.");
    }
}

template <typename T>
UndirectedGraph<T>::UndirectedGraph(set<Vertex<T>> vertices, set<Edge<T>> edges)
{
    this->vertices = vertices;
    this->edges = edges;

    for (Edge<T> e : this->edges)
    {
        this->checkEdgeConsistency(e);

        Vertex<T> v1 = *this->vertices.find(e.getV1());
        Vertex<T> v2 = *this->vertices.find(e.getV2());
        v1.addNeighbor(v2);
        v2.addNeighbor(v1);
        this->updateVertices(v1, v2);
    }
}

template <typename T>
string UndirectedGraph<T>::toDOT(string title) const
{
    string graphAsString = "strict graph " + title + " {\n";
    graphAsString.append(this->adjacencyListsAsString("--", ";", "curly"));
    graphAsString.append("}");
    return graphAsString;
}

template <typename T>
DirectedGraph<T>::DirectedGraph(set<Vertex<T>> vertices, set<Edge<T>> edges)
{
    this->vertices = vertices;
    this->edges = edges;

    for (Edge<T> e : this->edges)
    {
        this->checkEdgeConsistency(e);

        Vertex<T> v1 = *this->vertices.find(e.getV1());
        Vertex<T> v2 = *this->vertices.find(e.getV2());
        v1.addNeighbor(v2);
        this->updateVertices(v1, v2);

        this->edges.insert(e);
    }
}

template <typename T>
string DirectedGraph<T>::toDOT(string title) const
{
    string graphAsString = "digraph " + title + " {\n";
    graphAsString.append(this->adjacencyListsAsString("->", ";", "curly"));
    graphAsString.append("}");
    return graphAsString;
}

template <typename T>
pair<int, set<Edge<T>>> *GraphFactory<T>::verticesNumberAndEdgeSetFromFile(string inputFilePath)
{
    int totalVertices = 0;
    set<Edge<T>> edges;
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
            // edges.insert(Edge(Vertex(stoi(edgeVertices[0]), "a", 0), Vertex(stoi(edgeVertices[1]), "b", 0)));
        }
    }
    return new pair<int, set<Edge<T>>>(totalVertices, edges);
}

template <typename T>
UndirectedGraph<T> *createUndirectedGraph(std::string inputFile)
{
}
template <typename T>
DirectedGraph<T> *createDirectedGraph(std::string inputFile)
{
}

template <typename T>
UndirectedGraph<T> *GraphFactory<T>::createUndirectedGraphFromFile(string inputFile)
{
    pair<int, set<Edge<T>>> verticesAndEdges = *this->verticesNumberAndEdgeSetFromFile(inputFile);
    return NULL;
}

template <typename T>
DirectedGraph<T> *GraphFactory<T>::createDirectedGraphFromFile(string inputFile)
{
    pair<int, set<Edge<T>>> verticesAndEdges = *this->verticesNumberAndEdgeSetFromFile(inputFile);
    return NULL;
}

template <typename T>
void GraphFactory<T>::generateDOTFile(const Graph<T> &graph, const string filePath, const string title)
{
    string fileContent = graph.toDOT(title);
    ofstream outputFile(filePath + title + ".dat", std::ios_base::out);
    outputFile << fileContent;
    outputFile.close();
}

template class Vertex<int>;
template class Edge<int>;
template class Graph<int>;
template class UndirectedGraph<int>;
template class DirectedGraph<int>;
template class GraphFactory<int>;

template class Vertex<string>;
template class Edge<string>;
template class Graph<string>;
template class UndirectedGraph<string>;
template class DirectedGraph<string>;
template class GraphFactory<string>;