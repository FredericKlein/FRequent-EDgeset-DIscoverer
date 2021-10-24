#ifndef EDGE_H
#define EDGE_H
#include <Vertex.h>
#include <iostream>
using namespace std;

class Edge
{
    public:
        Vertex *vertex[2];
        int label;
        Edge(Vertex *u, Vertex *v, int label);
        Edge();
        void show()
        {
            cout << "(";
            cout << Edge::vertex[0]->id;
            cout << ", ";
            cout << Edge::vertex[1]->id;
            cout << ")";
        }
};

#endif // EDGE_H
