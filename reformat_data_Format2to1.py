# -*- coding: utf-8 -*-
"""

@author: Frederic Klein
"""
from Graph import *
g = Graph()

def tiefensuche(graph, neighbours, v, new_graph):
    if v not in graph.dfs_ordered_V:
        #print(v)
        graph.dfs_ordered_V.append(v)
        new_graph.dfs_ordered_V.append(v)
        local_edges = list()
        try:
            unused_edges = neighbours[v]
            has_neighbours = True
        except KeyError:
            has_neighbours = False
        if has_neighbours:
            for e in neighbours[v]:
                if e not in graph.dfs_ordered_E:
                    if e.Second_Node not in graph.dfs_ordered_V:
                        graph.dfs_ordered_E.append(e)
                        new_graph.dfs_ordered_E.append(e)
                        tiefensuche(graph, neighbours, e.Second_Node, new_graph)
                    else:
                        local_edges.append(e)
            for le in local_edges:
                appending = True
                for edge in graph.dfs_ordered_E:
                    if le.First_Node.Node_ID == edge.First_Node.Node_ID and le.Second_Node.Node_ID == edge.Second_Node.Node_ID:
                        appending = False
                        break
                    elif le.First_Node.Node_ID == edge.Second_Node.Node_ID and le.Second_Node.Node_ID == edge.First_Node.Node_ID:
                        appending = False
                        break
                if appending:
                    # there hasnt been an Edge between x and y (x->y or y->x)
                    graph.dfs_ordered_E.append(le)
                    new_graph.dfs_ordered_E.append(le)
                    tiefensuche(graph, neighbours, le.Second_Node, new_graph)
            
            
setName = "LyonSchool"


# set paths
basePath = "D:/Universität/Bachelorarbeit/Datasets/" + setName + "/"
graph_indicator_path = basePath + setName + "_graph_indicator.txt"
graph_label_path = basePath + setName + "_graph_labels.txt"
node_label_path = basePath + setName + "_node_labels.txt"
edges_path = basePath + setName + "_A.txt"
edgeLabelsPath = basePath + setName  + "_edge_labels.txt"

graphData, edges = g.readGraphWithConstantVertexsetFromFile(graph_indicator_path, graph_label_path, edges_path, node_label_path)         




pascal_path = basePath + setName + "_format3.txt"
#for e in graphData[0].Edges:
#    print(str(e.First_Node) + "-" + str(e.Second_Node))
global_graphs = list()
with open(pascal_path, "w") as f:
    graph_counter = 0
    for g in graphData:
        
        
        # rename Node_Number so it starts with 0 for every Graph
        minimum_nn = None
        for v in g.Vertices:
            if minimum_nn == None or v.Node_Number <= minimum_nn:
                minimum_nn = v.Node_Number
        
        # reorder Vertices with dfs, input should be chemical graph so all graphs are connected
        neighbourhood = dict()
        for e in g.Edges:
            try:
                neighbourhood[e.First_Node].append(e)
            except KeyError:
                neighbourhood[e.First_Node] = [e]
        
        # construct connected Subgraphs
        local_graphs = list()
        for v in g.Vertices:
            if v not in g.dfs_ordered_V:
                new_graph = Graph()
                tiefensuche(g, neighbourhood, v, new_graph)
                
                if len(new_graph.dfs_ordered_E) > 0:
                    local_graphs.append(new_graph)
        for mlg in local_graphs:
            global_graphs.append(mlg)
        # in case the graph is connected a simple call of tiefensuche is okay
        # tiefensuche(g, neighbourhood, g.Vertices[0])
        
        # for each local_graph:
        for mlg in local_graphs:
            graph_counter += 1
            f.write("# " + str(graph_counter).strip("\n") + ' 0 ' + str(len(mlg.dfs_ordered_V)).strip("\n") + ' ' + str(len(mlg.dfs_ordered_E)).strip("\n") + '\n')
            # write Vertices
            for v in mlg.dfs_ordered_V:
                f.write(str(v.Node_ID).strip("\n") + " ")
                temp = mlg.node_counter
                mlg.IDict[v.Node_ID] = temp
                mlg.node_counter += 1
            f.write("\n")
            
            #write edges
            for e in mlg.dfs_ordered_E:
                try:
                    f.write(str(mlg.IDict[e.First_Node.Node_ID]).strip("\n") + " ")
                    f.write(str(mlg.IDict[e.Second_Node.Node_ID]).strip("\n") + " ")
                    f.write(str(e.Edge_Label).strip("\n") + " ")
                except KeyError:
                    print("keyerror")   
                    
            f.write("\n")

print(len(global_graphs))

#%%
gaston_path = basePath + setName + "_format1.txt"
node_dict = {}
out = open(gaston_path, "w")
with open(graph_indicator_path, "r") as gi:
    with open(node_label_path, "r") as nl:
        with open(edges_path, "r") as e:
            node_count = 0
            while True:
                line = gi.readline()
                if line == "":
                    break
                node_count += 1
                node_dict[node_count] = line
            
            current_graph_id = 0
            while True:
                line = e.readline()
                if line == "":
                    break
                first_node, second_node = line.split(" ")
                


    header = f.readline()
    vertices = f.readline()
    edges = f.readline()
    while header.startswith("#"):
        #print(header)
        out.write('t # ' + header.split()[1] + '\n')
        vlabels = vertices.strip().split(' ')
        for v in range(len(vlabels)):
            out.write(' '.join(['v', str(v), vlabels[v], '\n']))
        es = edges.strip().split(' ')

        if len(es) >= 3:
            for e in range(0, len(es) - 1, 3):
                out.write(' '.join(['e', str(int(es[e])), str(int(es[e+1])), es[e+2], '\n']))
    
        header = f.readline()
        vertices = f.readline()
        edges = f.readline()

out.close()

for mgg in global_graphs:
    print(len(mgg.dfs_ordered_E))
 