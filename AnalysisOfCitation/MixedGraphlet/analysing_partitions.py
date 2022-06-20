import networkx as nx
import pandas as pd
import matplotlib.pyplot as plt
import networkx.algorithms.community as nx_comm
import numpy as np
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay

## Function that defines the consistency of a partitioning
def PhiConsistency(G,clust):
    lscores = []
    for crt,one_clust in enumerate(clust):
        cardC = len(one_clust)
        in_deg  = G.subgraph(one_clust).degree(weight='weight')
        tot_deg = G.degree(one_clust,weight='weight')
        sc_in   = 1/cardC*sum([in_deg[n]/tot_deg[n] for n in one_clust],0)
        sc_out = 0
        for tmp,oth_clust in enumerate(clust):
            if tmp == crt:
                continue
            sc_out  += 1/len(oth_clust)*sum([nx.cut_size(G,[n],oth_clust,weight='weight')/tot_deg[n] for n in one_clust],0)
        lscores.append(np.array([sc_in,sc_out]))
    return np.array(lscores)

## reading the truncated network and mam
G_m = nx.read_weighted_edgelist('HepTh_lcc.mam',nodetype=int)
G = nx.read_edgelist('HepTh_lcc.nwk',nodetype=int,create_using = nx.DiGraph)

## Creating the undirected version of the directed network
ledges = {}
for e in G.edges:
    try:
        ledges[e]+=1
    except KeyError:
        ledges[e] =1
G_u = nx.Graph()
G_u.add_weighted_edges_from( [(e[0],e[1],w) for e,w in ledges.items()] )

## Reading the clusterings as pandas files...
set_nodes = [n for n in G.nodes()]
clust_raw = pd.read_csv('HepTh_nwk.p',header = None,names = ['node','clust'],delimiter=' ')
clust_raw = clust_raw.loc[set_nodes]
clust_mam = pd.read_csv('HepTh_mam.p',header = None,names = ['node','clust'],delimiter=' ')
clust_mam = clust_mam.loc[set_nodes]

### ... and translating them as regular community structures for networkx
clust_raw = clust_raw.groupby('clust')['node'].apply(list)
cties = []
for cty in clust_raw.index:
    cties.append(clust_raw[cty])
clust_raw = cties

clust_mam = clust_mam.groupby('clust')['node'].apply(list)
cties = []
for cty in clust_mam.index:
    cties.append(clust_mam[cty])
clust_mam = cties

## Plot the modularities of the two partitionings on different networks
print('---------Modularity of the clustering found on the directed graph---------')
print('on the directed graph    :',nx_comm.modularity(G,clust_raw))
print('on the symmetrised graph :',nx_comm.modularity(G_u,clust_raw))
print('on the MAM               :',nx_comm.modularity(G_m,clust_raw))


print('---------Modularity of the clustering found on the MAM--------------------')
print('on the directed graph    :',nx_comm.modularity(G,clust_mam))
print('on the symmetrised graph :',nx_comm.modularity(G_u,clust_mam))
print('on the MAM               :',nx_comm.modularity(G_m,clust_mam))

## Compute the consistency of the scores using Phi matrix
lscores_mam = PhiConsistency(G_m,clust_mam)
lscores_raw = PhiConsistency(G_u,clust_raw)

## And plot the figs
plt.plot(lscores_mam[:,0],lscores_mam[:,1],'bo')
plt.plot(lscores_raw[:,0],lscores_raw[:,1],'r*')

plt.legend(['Raw','MAM'])
plt.xlabel('$\Phi$\'s diag values')
plt.ylabel('$\sum\Phi$\'s off-diag values')
plt.show()

## Plot the contingency matrix
pred_mam = { n:-1 for n in set_nodes }
for lab,clust in enumerate(clust_mam):
    for n in clust:
        pred_mam[n] = lab
pred_mam = [(n,lab) for n,lab in pred_mam.items()]
pred_mam.sort(key = lambda a:a[0] )
pred_mam = [lab for u,lab in pred_mam]


pred_raw = { n:-1 for n in set_nodes }
for lab,clust in enumerate(clust_raw):
    for n in clust:
        pred_raw[n] = lab
pred_raw = [(n,lab) for n,lab in pred_raw.items()]
pred_raw.sort(key = lambda a:a[0] )
pred_raw = [lab for u,lab in pred_raw]

ConfusionMatrixDisplay.from_predictions(pred_mam,pred_raw,include_values=False,xticks_rotation='vertical',normalize='true',cmap='PuRd')
plt.xlim([-0.5,max(pred_raw)+0.5])
plt.ylim([-0.5,max(pred_mam)+0.5])
plt.ylabel('parts. from MAM')
plt.xlabel('parts. from Raw')

plt.show()
