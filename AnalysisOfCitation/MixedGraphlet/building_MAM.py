import scipy.sparse as sp
import pandas as pd
import networkx as nx
import os

nbNodes = 27770 ## Number of nodes in the initial graph (to get sparse matrices with consistent dimension, to make operations)

### Read the Partial MAMs with orbits
q204_orb1 = pd.read_csv(os.path.join('MAMs','HepTH_Q204_orb1.mam'),sep = ' ',header=None,names=['src','tgt','weight'])
q204_orb1 = sp.coo_matrix((q204_orb1['weight'].values,(q204_orb1['src'].values,q204_orb1['tgt'].values)),shape = (nbNodes,nbNodes))

q204_orb2 = pd.read_csv(os.path.join('MAMs','HepTH_Q204_orb2.mam'),sep = ' ',header=None,names=['src','tgt','weight'])
q204_orb2 = sp.coo_matrix((q204_orb2['weight'].values,(q204_orb2['src'].values,q204_orb2['tgt'].values)),shape = (nbNodes,nbNodes))

q206_orb12 = pd.read_csv(os.path.join('MAMs','HepTH_Q206_orb12.mam'),sep = ' ',header=None,names=['src','tgt','weight'])
q206_orb12  = sp.coo_matrix((q206_orb12['weight'].values,(q206_orb12['src'].values,q206_orb12['tgt'].values)),shape = (nbNodes,nbNodes))

q206_orb3 = pd.read_csv(os.path.join('MAMs','HepTH_Q206_orb3.mam'),sep = ' ',header=None,names=['src','tgt','weight'])
q206_orb3 = sp.coo_matrix((q206_orb3['weight'].values,(q206_orb3['src'].values,q206_orb3['tgt'].values)),shape = (nbNodes,nbNodes))

q2252_orb1 = pd.read_csv(os.path.join('MAMs','HepTH_Q2252_orb1.mam'),sep = ' ',header=None,names=['src','tgt','weight'])
q2252_orb1 = sp.coo_matrix((q2252_orb1['weight'].values,(q2252_orb1['src'].values,q2252_orb1['tgt'].values)),shape = (nbNodes,nbNodes))

q2252_orb23 = pd.read_csv(os.path.join('MAMs','HepTH_Q2252_orb23.mam'),sep = ' ',header=None,names=['src','tgt','weight'])
q2252_orb23 = sp.coo_matrix((q2252_orb23['weight'].values,(q2252_orb23['src'].values,q2252_orb23['tgt'].values)),shape = (nbNodes,nbNodes))

q2254_orb12 = pd.read_csv(os.path.join('MAMs','HepTH_Q2254_orb12.mam'),sep = ' ',header=None,names=['src','tgt','weight'])
q2254_orb12 = sp.coo_matrix((q2254_orb12['weight'].values,(q2254_orb12['src'].values,q2254_orb12['tgt'].values)),shape = (nbNodes,nbNodes))

q2254_orb34 = pd.read_csv(os.path.join('MAMs','HepTH_Q2254_orb34.mam'),sep = ' ',header=None,names=['src','tgt','weight'])
q2254_orb34 = sp.coo_matrix((q2254_orb34['weight'].values,(q2254_orb34['src'].values,q2254_orb34['tgt'].values)),shape = (nbNodes,nbNodes))

### Build the MAM
M  = sp.coo_matrix(q204_orb2).minimum(q204_orb1)
M += sp.coo_matrix(q204_orb2).minimum(q2252_orb1)
M += sp.coo_matrix(q206_orb3).minimum(q204_orb1)
M += sp.coo_matrix(q206_orb3).minimum(q2252_orb1)
M += sp.coo_matrix(q2252_orb23).minimum(q206_orb12)
M += sp.coo_matrix(q2252_orb23).minimum(q2254_orb12)
M += sp.coo_matrix(q2254_orb34).minimum(q206_orb12)
M += sp.coo_matrix(q2254_orb34).minimum(q2254_orb12)

### Threshold edges below 30
M = M.tocoo()
src    = M.row
tgt    = M.col
weight = M.data

ii     = weight>30
src    = src[ii]
tgt    = tgt[ii]
weight = weight[ii]

### Keep only the largest connected component
G = nx.Graph()
G.add_weighted_edges_from([ (src[i],tgt[i],weight[i]) for i in range(len(weight))])
lcc = max(nx.connected_components(G), key=len)
G = G.subgraph(lcc).copy()

### Do not save the networkx graph directly or edges will appear only once,
# so building a dataframe and saving it instead
# (besides, reading and writing dataframes are much more efficient)
mam = { 'src': [], 'tgt' : [], 'weight':[] }
for e in G.edges:
    mam['src'].append(e[0])
    mam['tgt'].append(e[1])
    mam['weight'].append(G.edges[e]['weight'])

src = mam['src'].copy()
mam['src'] += mam['tgt']
mam['tgt'] += src
mam['weight'] += mam['weight']

mam = pd.DataFrame(data = mam, dtype= int )
mam.to_csv('HepTh_lcc.mam',header = False,sep = ' ', index = False)

### And finally truncated the initial, directed network to this largest component
G = nx.read_edgelist(os.path.join('..','HepTh.nwk'),create_using=nx.DiGraph,nodetype = int)
G = G.subgraph(lcc).copy()
nx.write_edgelist(G,'HepTh_lcc.nwk',data=False)
