from Node import Node
from Edge import Edge
from Graph import Graph
from random import randint, seed
from os import mkdir

# set seed
seed(42)
g_count = 50000
v_count = 20
edge_percent = 80
setName = "SD_" + str(g_count) + "graphs_" + str(v_count) + "vertices_" + str(edge_percent) + "edgeinclusionrate" 

# set paths
basePath = "D:/Universität/Datasets/" + setName + "/"
graph_indicator_path = basePath + setName + "_graph_indicator.txt"
graph_label_path = basePath + setName + "_graph_labels.txt"
node_label_path = basePath + setName + "_node_labels.txt"
edges_path = basePath + setName + "_A.txt"

gaston_path = basePath + setName + "_gaston_format.txt"

# creates Folder
try:
    mkdir(basePath)
except:
    pass

vertices = list()
for j in range(v_count):
    vertices.append(Node(j, str(j), str(j)))

graphs = list()
for i in range(g_count):
    # graph i
    g_edges = list()
    
    for v in vertices:
        for u in vertices:
            randominteger = randint(0, 101)
            if randominteger <= edge_percent and v.Node_Label > u.Node_Label:
                g_edges.append(Edge(v, u, "0"))
                
                
    graphs.append(Graph(vertices, g_edges))
    
with open(gaston_path, "w") as f:
    for i, g in enumerate(graphs):
        f.write("t # " + str(i) + "\n")
        for j, v in enumerate(vertices):
            f.write("v " + str(j) + " " + v.Node_Label + "\n")
        for e in g.Edges:
            f.write("e " + e.First_Node.Node_Label + " " + e.Second_Node.Node_Label + " 0 \n")