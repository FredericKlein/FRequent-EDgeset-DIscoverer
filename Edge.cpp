#include "Edge.h"
#include <Vertex.h>

Edge::Edge(Vertex *u, Vertex *v, int l)
{
    Edge::vertex[0] = u;
    Edge::vertex[1] = v;
    Edge::label = l;
}
Edge::Edge()
{

}
