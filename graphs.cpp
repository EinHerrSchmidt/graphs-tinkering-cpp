#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <string>

using namespace std;

class Edge
{
private:
    int v1;
    int v2;

public:
    Edge(int n1, int n2)
    {
        v1 = n1;
        v2 = n2;
    }
    int getV1()
    {
        return v1;
    }
    int getV2()
    {
        return v2;
    }

    bool operator<(const Edge &e) const
    {
        return v1 < e.v1 || (v1 == e.v1 && v2 < e.v2);
    }
};

class UndirectedGraph
{
private:
    friend std::ostream &operator<<(std::ostream &, const UndirectedGraph &);
    int totalVertices;
    vector<set<int>> neighbors;

public:
    UndirectedGraph(int v, set<Edge> edges)
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

    int getTotalVertices()
    {
        return totalVertices;
    }

    static UndirectedGraph *createFromFile(string inputFile)
    {
        int totalVertices = 0;
        set<Edge> edges;
        string line;
        ifstream file(inputFile);
        if (file.is_open())
        {
            getline(file, line);
            totalVertices = stoi(line);
            while (getline(file, line))
            {
                // cout << line << '\n';
                size_t pos = 0;
                string edgeVertices[2];
                char delimiter = '\t';
                int tokenPosition = 0;
                // std::string::npos -> Value returned by various member functions when they fail.
                pos = line.find(delimiter);
                while ((pos = line.find(delimiter)) != std::string::npos)
                {
                    edgeVertices[tokenPosition++] = line.substr(0, pos);
                    // std::cout << token << std::endl;
                    line.erase(0, pos + 1); // + 1 -> delimiter's length
                }
                edgeVertices[tokenPosition] = line.substr(pos + 1, std::string::npos);
                edges.insert(Edge(stoi(edgeVertices[0]), stoi(edgeVertices[1])));
            }
            file.close();
        }
        return new UndirectedGraph(totalVertices, edges);
    }
};

std::ostream &operator<<(std::ostream &strm, const UndirectedGraph &graph)
{
    string graphAsString = "";
    int vertex = 0;
    for (set<int> vertexNeighbors : graph.neighbors)
    {
        graphAsString.append(to_string(vertex++)).append(" -> [");
        for (int neighbor : vertexNeighbors)
        {
            graphAsString.append(to_string(neighbor)).append(", ");
        }
        graphAsString.append("]\n");
    }
    return strm << graphAsString;
}

int main()
{
    set<Edge> edges = {Edge(0, 1), Edge(1, 2), Edge(2, 0), Edge(3, 0), Edge(3, 1)};
    int vertices = 4;
    UndirectedGraph graph(vertices, edges);
    cout << graph;

    cout << "----------------------"
         << "\n";

    UndirectedGraph g1 = *UndirectedGraph::createFromFile("graph.csv");
    cout << g1;
}