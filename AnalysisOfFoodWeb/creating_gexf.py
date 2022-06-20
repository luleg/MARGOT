import networkx as nx
import pandas as pd

nodes = pd.read_csv('Florida-bay-meta.csv',header = [0],index_col = 0)
obs_part = pd.read_csv('Florida-bay_T108.p',header = None,index_col = 0,delimiter=' ')


G = nx.read_weighted_edgelist('Florida-bay_T108.mam', nodetype = int)
labels = {}
for node in G.nodes:
    G.nodes[node]['benson_clust'] = nodes['benson_clustering'][node]
    G.nodes[node]['our_clust'] = obs_part[1][node]
    labels[node] = nodes['name'][node]

G = nx.relabel_nodes(G,labels)
nx.write_gexf(G,'Florida-bay-2clust.gexf')
