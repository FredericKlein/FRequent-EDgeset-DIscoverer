#ifndef EDGESET_H
#define EDGESET_H
#include <unordered_set>
#include<iostream>
using namespace std;
class EdgeSet
{
    public:
        std::unordered_set<int> edge_ids;
        EdgeSet(std::unordered_set<int> in_e);
        EdgeSet();
        void show()
        {
            for (auto & e: EdgeSet::edge_ids)
            {
                cout << e;
                cout << ", ";
            }
        }

        bool contains(std::unordered_set<int> new_edges)
        {
            if (new_edges.size() > EdgeSet::edge_ids.size())
            {
                // new_edges contain more edges that this EdgeSet
                return false;
            }
            for (auto & e: new_edges)
            {
                if (EdgeSet::edge_ids.find(e) == EdgeSet::edge_ids.end())
                {
                    return false;
                }
            }
            // all edges in new_edges were found.
            return true;
        }
        bool contains(int new_edge)
        {
            if (EdgeSet::edge_ids.find(new_edge) == EdgeSet::edge_ids.end())
            {
                return false;
            }
            // edge was found.
            return true;
        }
};

#endif // EDGESET_H
