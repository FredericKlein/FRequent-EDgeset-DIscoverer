#include <string.h>
#include <Vertex.h>
#include <Edge.h>
#include <Graph.h>
#include <EdgeSet.h>
#include <EdgeSetDatabase.h>
#include<iostream>
#include <map>
#include<Found.h>
using namespace std;
bool is_canidate(EdgeSetDatabase *D, int e, Graph *c, Found *found)
{
    // KantenID bereits im zuvor aufgebauten Graphen
    if (c->has_edgeid(e))
    {
        return false;

    }
    // neuer Graph ist bereits gefunden
    std::unordered_set<int> new_edgeset = c->edge_ids;
    new_edgeset.insert(e);
    for (auto & g : found->edge_sets)
    {
        if (new_edgeset == g.edge_ids)
        {
            return false;
        }
    }
    // bisher kein Graph aufgebaut beginne mit neuer KantenID
    if (c->edge_ids.size() == 0)
    {
        return true;
    }
    Edge edge_e = D->edge_map[e];
    // Einer der Knoten der Kante ist bereits im aufgebauten Graphen -> Kante ist zusammenhängend mit aufgebautem Graphen
    if (c->vertex_ids.find(edge_e.vertex[0]->id) != c->vertex_ids.end())
    {
        return true;
    }
    // Einer der Knoten der Kante ist bereits im aufgebauten Graphen -> Kante ist zusammenhängend mit aufgebautem Graphen
    if (c->vertex_ids.find(edge_e.vertex[1]->id) != c->vertex_ids.end())
    {
        return true;
    }

    // Kante bindet nicht an
    return false;
}
void internal_advancedFCESM(EdgeSetDatabase *D, int t, Graph *c, Found *found, FILE *f)
{
    for (int i=0; i < D->all_edge_ids.size(); i++)
    {
        int current_edge_id = D->all_edge_ids[i];
        if (is_canidate(D, current_edge_id, c, found))
        {
            // erstelle neuen Graphen
            std::unordered_set<int> new_vertices = c->vertex_ids;
            std::unordered_set<int> new_edges = c->edge_ids;
            int smallest_edgeid = c->smallest_edgeid;
            if (current_edge_id < smallest_edgeid || smallest_edgeid == -1)
            {
                smallest_edgeid = current_edge_id;
            }
            new_edges.insert(current_edge_id);
            int identifier = D->edge_map[current_edge_id].vertex[0]->id;
            if (new_vertices.find(identifier) == new_vertices.end())
                new_vertices.insert(identifier);
            identifier = D->edge_map[current_edge_id].vertex[1]->id;
            if (new_vertices.find(identifier) == new_vertices.end())
                new_vertices.insert(identifier);
            Graph new_c = Graph(new_vertices, new_edges, smallest_edgeid);

            // Zähle: ist neuer Graph häufig?
            int nog = 0;
            for (auto & local_e_set: D->all_edgesets)
            {
                if (local_e_set.contains(new_edges))
                {
                    // g contains all edges of C
                    nog++;
                }
            }

            if (nog >= t)
            {
                // neuer Graph ist häufig, gebe diesen aus, und erstelle neue verworfene Kantenmenge
                new_c.output(D, f);
                found->edge_sets.push_back(new_c);
                // rekursiver Aufruf
                internal_advancedFCESM(D, t, &new_c, found, f);
            }
        }
    }
}
void ADVANCED_Frequent_Connected_Edge_Set_Miner(EdgeSetDatabase *D, int t, std::string out_path)
{
    if (D->all_edge_ids.size() == 0)
    {
        perror("No Edges in the Dataset!");
        return;
    }

    // count the frequency of all edgeids
    // edgeid_count_map[edge_id] = frequency
    std::unordered_map<int, int> edgeid_count_map;
    for (int i = 0; i < D->all_edgesets.size(); i++)
    {
        for (auto id : D->all_edgesets[i].edge_ids)
        {
            // edge_id was found add +1 to frequency
            if (edgeid_count_map.find(id) == edgeid_count_map.end())
            {
                // edge_id is new, initialize frequency as 1
                edgeid_count_map[id] = 1;
            }
            else
            {
                edgeid_count_map[id]++;

            }
        }
    }
    // delete all_edge_ids
    D->all_edge_ids.clear();

    // add frequent edge_ids
    std::unordered_map<int, int>::iterator iterator1 = edgeid_count_map.begin();
    // Iterate over the map using Iterator till end.
    while (iterator1 != edgeid_count_map.end())
    {
        // Accessing KEY from element pointed by it.
        int id = iterator1->first;
        // Accessing VALUE from element pointed by it.
        int frequency = iterator1->second;

        if (frequency >= t)
        {
            D->all_edge_ids.push_back(id);
        }
        // Increment the Iterator to point to next entry
        iterator1++;
    }

    // start algorithm
    std::unordered_set<int> empty_v = {};
    std::unordered_set<int> empty_e_ids = {};
    Graph empty_graph = Graph(empty_v, empty_e_ids, -1);
    Found found = Found();
    FILE* f = fopen(out_path.c_str(), "w");

    internal_advancedFCESM(D, t, &empty_graph, &found, f);
    fclose(f);
}



int main()
{
    int threshhold = 80;
    string path_a = "D:/MyData/MyData_A.txt";
    string path_graph = "D:/MyData/MyData_graph_indicator.txt";
    string path_node = "D:/MyData/MyData_node_labels.txt";
    string path_edge_labels = "D:/MyData/MyData_edge_labels.txt";

    string out_path = "D:/MyData/MyData_freddi.txt";

    EdgeSetDatabase myData = EdgeSetDatabase(path_graph, path_a, path_node, path_edge_labels);
    cout << "Die Daten wurden erfolgreich eingelesen. Die Datenbank besteht aus ";
    cout << myData.all_edgesets.size();
    cout << " Graphen/Kantenmengen.";
    cout << endl;

    ADVANCED_Frequent_Connected_Edge_Set_Miner(&myData, threshhold, out_path);
    return 0;
}

