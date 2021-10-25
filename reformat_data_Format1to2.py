# -*- coding: utf-8 -*-
"""

@author: Frederic Klein
"""
g_count = 50000
v_count = 20
edge_percent = 80
setName = "SD_" + str(g_count) + "graphs_" + str(v_count) + "vertices_" + str(edge_percent) + "edgeinclusionrate" 


# set paths correctly, please check the basepath!
basePath = "D:/Universität/Datasets/" + setName + "/"
graph_indicator_path = basePath + setName + "_graph_indicator.txt"
graph_label_path = basePath + setName + "_graph_labels.txt"
node_label_path = basePath + setName + "_node_labels.txt"
edges_path = basePath + setName + "_A.txt"
edgelabel_path = basePath + setName + "_edge_labels.txt"

gaston_path = basePath + setName + "_gaston_format.txt"

node_label_file = open(node_label_path, "w")
edge_file = open(edges_path, "w")
graph_indicator_file = open(graph_indicator_path, "w")
edge_label_file = open(edgelabel_path, "w")

with open(gaston_path, "r") as f:
    graph_id = 0
    node_number = 0
    node_dict = dict()
    while True:
        line = f.readline()

        if line == "":
            break

        
        splitted = line.split(" ")
        if splitted[0] == "t":
            graph_id += 1
            node_dict = dict()
            
        if splitted[0] == "v":
            # write the label in node_label_file
            node_number += 1
            node_label_file.write(splitted[2].strip("\n"))
            node_label_file.write("\n")
            
            # write the graph_id in graph_indicator_file
            graph_indicator_file.write(str(graph_id))
            graph_indicator_file.write("\n")
            
            # append node to node_dict
            node_dict[splitted[1]] = node_number
            
        if splitted[0] == "e":
            edge_file.write(str(node_dict[splitted[1]]))
            edge_file.write(", ")
            edge_file.write(str(node_dict[splitted[2]]))
            edge_file.write("\n")
            if splitted[3] != "0":
                print("Error!")
            edge_label_file.write(splitted[3])
            edge_label_file.write("\n")
        
        #print(splitted)
            
node_label_file.close()
edge_file.close()
graph_indicator_file.close()
edge_label_file.close()