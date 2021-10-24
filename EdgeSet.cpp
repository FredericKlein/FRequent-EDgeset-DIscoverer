#include "EdgeSet.h"
#include <unordered_set>

EdgeSet::EdgeSet(std::unordered_set<int> in_e)
{
    EdgeSet::edge_ids = in_e;
}

EdgeSet::EdgeSet()
{
    //dtor
}
