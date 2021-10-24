#include "EdgeSetDatabase.h"
#include <Vertex.h>
#include<iostream>
#include <map>
#include <string.h>
#include <Edge.h>
using namespace std;

EdgeSetDatabase::EdgeSetDatabase(string graph_id_path, string edge_path, string node_identity_path, string edge_label_path)
{
    char line[100];
    FILE* node_label_file = fopen(node_identity_path.c_str(), "r");
    if (node_label_file == NULL)
    {
        cout << "Fehler beim lesen der node label.\n";
        exit(EXIT_FAILURE);
    }

    // create node_helper_map[node_id] -> node_label
    map<int, int> node_helper_map;
    int counter = 1;
    while(fgets(line, sizeof(line), node_label_file))
    {
        node_helper_map[counter] = atoi(line);
        counter++;
    }


    // create node_label_count_map[node_label] -> count (vertices with that label)
    map<int, int> node_label_count_map;

    // iterate over node_helper_map
    std::map<int, int>::iterator iterator0 = node_helper_map.begin();
    // Iterate over the map using Iterator till end.
    while (iterator0 != node_helper_map.end())
    {
        // Accessing KEY from element pointed by it.
        // Accessing VALUE from element pointed by it.
        int value = iterator0->second;
        if (node_label_count_map.find(value) != node_label_count_map.end())
        {
            // node_label gefunden
            node_label_count_map[value]++;
        }
        else{
            node_label_count_map[value] = 1;
        }
        // Increment the Iterator to point to next entry
        iterator0++;
    }

    // create node_label_v_map[node_id] -> Vertex
    map<int, Vertex> node_label_v_map;

    // iterate over node_label_count_map
    std::map<int, int>::iterator iterator1 = node_label_count_map.begin();
    // Iterate over the map using Iterator till end.
    while (iterator1 != node_label_count_map.end())
    {
        // Accessing KEY from element pointed by it.
        int key = iterator1->first;
        // Accessing VALUE from element pointed by it.

        Vertex new_vertex = Vertex(key);
        node_label_v_map[key] = new_vertex;

        // Increment the Iterator to point to next entry
        iterator1++;
    }


    FILE* graph_id_file = fopen(graph_id_path.c_str(), "r");
    if (graph_id_file == NULL)
    {
        cout << "Fehler beim lesen der graph id.\n";
        exit(EXIT_FAILURE);
    }
    // create node_graph_map[node_id]->graph_id
    std::map<int, int> node_graph_map;
    int node_id_counter = 1;
    while(fgets(line, sizeof(line), graph_id_file))
    {
        node_graph_map[node_id_counter] = atoi(line);
        node_id_counter++;
    }

    FILE* edge_file = fopen(edge_path.c_str(), "r");
    if (edge_file == NULL)
    {
        cout << "Fehler beim lesen der edges.\n";
        exit(EXIT_FAILURE);
    }
    FILE* edge_label_file = fopen(edge_label_path.c_str(), "r");
    if (edge_label_file == NULL)
    {
        cout << "Fehler beim lesen der edge labels.\n";
        exit(EXIT_FAILURE);
    }

    // create node_helper_map[node_id] -> node_label

   // create edge_helper_map[old_label] -> new_label
   std::map<std::string, std::string> edge_helper_map;
    while(fgets(line, sizeof(line), edge_file))
    {
        std::string old_label = line;
        char *token = strtok(line, ", ");
        std::string n1 = to_string(node_helper_map[atoi(token)]);
        token = strtok(NULL, " ");
        std::string n2 = to_string(node_helper_map[atoi(token)]);

        // get edge label
        char label_line [6];
        fgets(label_line, sizeof(label_line), edge_label_file);
        int edge_label_temporary;
        itoa(edge_label_temporary, label_line, 6);
        std::string edge_label_temporary2 = to_string(edge_label_temporary);

        // add edge label to old label
        old_label += ", ";
        old_label += edge_label_temporary2;

        // create new label
        std::string new_label = n1 + ", " + n2 + ", " + edge_label_temporary2;

        edge_helper_map[old_label] = new_label;
    }

    // create edge_label_count_map[new_label] -> count(edges with that label)
    std::map<std::string, int> edge_label_count_map;
    // iterate over edge_helper_map
    std::map<std::string, std::string>::iterator iterator2 = edge_helper_map.begin();
    // Iterate over the map using Iterator till end.
    while (iterator2 != edge_helper_map.end())
    {
        // Accessing KEY from element pointed by it.
        std::string key = iterator2->first;
        // Accessing VALUE from element pointed by it.
        std::string value = iterator2->second;

        if (edge_label_count_map.find(value) != edge_label_count_map.end())
        {
            // found existing new_label
            edge_label_count_map[value]++;
        }
        else
        {
            edge_label_count_map[value] = 1;
        }
        // Increment the Iterator to point to next entry
        iterator2++;
    }

    // create edge_label_id_map[new_label] -> unique id
    std::map<std::string, int> edge_label_id_map;

    // iterate over edge_label_count_map
    std::map<std::string, int>::iterator iterator3 = edge_label_count_map.begin();
    int edge_counter = 1;
    // Iterate over the map using Iterator till end.
    while (iterator3 != edge_label_count_map.end())
    {
        // Accessing KEY from element pointed by it.
        std::string key = iterator3->first;
        // Accessing VALUE from element pointed by it.

        if (edge_label_id_map.find(key) == edge_label_id_map.end())
        {
            edge_label_id_map[key] = edge_counter;
            edge_counter++;
        }
        // Increment the Iterator to point to next entry
        iterator3++;
    }

    // create edge_id_e_map[unique id] -> Edge
    std::unordered_map<int, Edge> edge_id_e_map;
    // iterate over edge_label_id_map
    std::map<std::string, int>::iterator iterator4 = edge_label_id_map.begin();
    while (iterator4 != edge_label_id_map.end())
    {
        // Accessing KEY from element pointed by it.
        std::string key = iterator4->first;
        char *old_label = new char[key.length() + 1];
        strcpy(old_label, key.c_str());
        char *token = strtok(old_label, ", ");
        int n1 = atoi(token);
        token = strtok(NULL, " ");
        int n2 = atoi(token);
        token = strtok(NULL, " ");
        int temp_label = atoi(token);

        // Accessing VALUE from element pointed by it.
        int value = iterator4->second;

        if (edge_id_e_map.find(value) == edge_id_e_map.end())
        {
            Edge new_edge = Edge(&node_label_v_map[n1], &node_label_v_map[n2], temp_label);
            edge_id_e_map[value] = new_edge;
        }
        // Increment the Iterator to point to next entry
        iterator4++;
    }

    // create edge_edgeset_edgeids_map[EdgeSetID] -> vec Edge IDs
    std::unordered_map<int, std::unordered_set<int>> edge_edgeset_edgeids_map;
    // iterate over edge_helper_map
    std::map<std::string, std::string>::iterator iterator5 = edge_helper_map.begin();
    // Iterate over the map using Iterator till end.
    while (iterator5 != edge_helper_map.end())
    {
        // Accessing KEY from element pointed by it.
        std::string key = iterator5->first;
        char *old_label = new char[key.length() + 1];
        strcpy(old_label, key.c_str());
        char *token = strtok(old_label, ", ");
        int n1 = atoi(token);

        // Accessing VALUE from element pointed by it.
        std::string value = iterator5->second;

        if (edge_edgeset_edgeids_map.find(node_graph_map[n1]) == edge_edgeset_edgeids_map.end())
        {
            // this EdgeSet does not exist
            std::unordered_set<int> new_edge_id_set = {edge_label_id_map[value]};
            edge_edgeset_edgeids_map[node_graph_map[n1]] = new_edge_id_set;
        }
        else
        {
            edge_edgeset_edgeids_map[node_graph_map[n1]].insert(edge_label_id_map[value]);
        }
        iterator5++;
    }


    // iterate over edge_id_e_map
    std::unordered_map<int, Edge>::iterator iterator6 = edge_id_e_map.begin();
    while (iterator6 != edge_id_e_map.end())
    {
        int key = iterator6->first;
        EdgeSetDatabase::all_edge_ids.push_back(key);
        iterator6++;
    }

    // iterate over edge_edgeset_edgeids_map
    std::unordered_map<int, std::unordered_set<int>>::iterator iterator7 = edge_edgeset_edgeids_map.begin();
    while (iterator7 != edge_edgeset_edgeids_map.end())
    {
        std:: unordered_set<int> value = iterator7->second;

        EdgeSetDatabase::all_edgesets.push_back(value);
        iterator7++;
    }
    EdgeSetDatabase::edge_map = edge_id_e_map;
}


EdgeSetDatabase::EdgeSetDatabase()
{
    //dtor
}
