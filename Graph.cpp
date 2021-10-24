#include "Graph.h"
#include <string.h>
#include <vector>
#include <unordered_set>
using namespace std;

Graph::Graph(std::unordered_set<int> in_v, std::unordered_set<int> in_e, int in_small_id)
{
    Graph::smallest_edgeid = in_small_id;
    Graph::vertex_ids = in_v;
    Graph::edge_ids = in_e;
}
