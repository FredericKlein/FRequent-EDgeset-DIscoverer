#ifndef GRAPH_H
#define GRAPH_H
#include <Vertex.h>
#include <Edge.h>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <EdgeSetDatabase.h>
#include <fstream>
using namespace std;

class Graph
{
    public:
        int smallest_edgeid;
        std::unordered_set<int> vertex_ids;
        std::unordered_set<int> edge_ids;
        Graph(std::unordered_set<int> in_v, std::unordered_set<int> in_e, int in_small_id);
        void show(EdgeSetDatabase *D)
        {
            cout << "G = {";
            int counter = 0;
            for (auto & e:Graph::edge_ids)
            {
                D->edge_map[e].show();
                if (counter < Graph::edge_ids.size() - 1)
                {
                    cout << ", ";
                }
                counter++;
            }
            cout << "}\n";
        }

        void output(EdgeSetDatabase *D, FILE* f)
        {
            fprintf(f, "G = {");

            int counter = 0;
            for (auto & e: Graph::edge_ids)
            {
                int i = 1;
                std::unordered_map<int, Edge>::iterator it;
                it = D->edge_map.find(e);
                if (it == D->edge_map.end())
                {
                    cout << "Thats the problem!!! \n\n";
                }
                fprintf(f, "(%d, %d, %d)", D->edge_map[e].vertex[0]->id, D->edge_map[e].vertex[1]->id, D->edge_map[e].label);
                if (counter < Graph::edge_ids.size() - 1)
                {
                    fprintf(f, ", ");
                }
                counter++;
            }
            fprintf(f, "}\n\n");
        }

        bool has_edgeid(int e)
        {
            if (Graph::edge_ids.find(e) == Graph::edge_ids.end())
            {
                return false;
            }
            return true;
        }


};

#endif // GRAPH_H
