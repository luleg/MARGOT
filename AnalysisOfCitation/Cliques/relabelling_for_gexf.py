import pandas as pd
import networkx as nx
import os

G = nx.read_weighted_edgelist('HepTH_T238.mam',nodetype= int)
id2labels = pd.read_csv(os.path.join('..','id2labels.csv'),dtype=str)
id2labels = id2labels.to_dict()['label']
G = nx.relabel_nodes(G,id2labels)
nx.write_gexf(G,'HepTH_T238.gexf')
