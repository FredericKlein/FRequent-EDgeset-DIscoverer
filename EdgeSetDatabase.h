#ifndef EDGESETDATABASE_H
#define EDGESETDATABASE_H
#include <EdgeSet.h>
#include <vector>
#include <unordered_map>
#include <Edge.h>
using namespace std;

class EdgeSetDatabase
{
    public:
        std::vector<EdgeSet> all_edgesets = {};
        std::vector<int> all_edge_ids = {};
        std::unordered_map<int, Edge> edge_map;
        EdgeSetDatabase(string graph_id_path, string edge_path, string node_identity_path, string edge_label_path);
        EdgeSetDatabase();
};

#endif // EDGESETDATABASE_H
