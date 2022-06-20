# Analysis of the citation network HepTh

Here, we analyse a citation network that covers all citations between papers published on *Arxiv* section *HEP-TH* from 1992 to 2003. Original dataset comes from [SNAP](https://snap.stanford.edu/data/cit-HepTh.html).
The directed network is stored in *HepTh.nwk*, in which nodes are identified by successive integers. Corresponding *Arxiv* identifiers are stored in *id2labels.csv*.

## Motif Adjacency Matrix of Graphlet T238

<img align="left" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/T238.png" width="5%">
Graphlet T238 is a graphlet highly unexpected in a citation network. Yet, some occurrences are found in the studied network. Looking at the MAM produced by T238 enables to observe some strange behaviours. Namely:
<img align="left" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/CitT238.png" width="40%">

* Cliques A, B, C, D, I, J, K are from co-authorship.

* Cliques E, F are from collaborations (papers' acknowledgement) and co-authorship for F.

* Cliques G, H are from co-authorship and revisions.

To observe this, go into the folder *Cliques* and run
```bash
./building_MAM.sh
python3 relabelling_for_gexf.py
```
This creates the MAM with the integer nodes' ids, and stores it in a file *HepTh_T238.gexf*, with nodes' labels corresponding to *Arxiv* identifiers.

Opening the *gexf* file with [Gephi](https://gephi.org/), one can observe the *Arxiv* identifiers of papers from a same clique, and thus track those paper from the *Arxiv* website by specifying the identifier in the url, e.g. [arxiv.org/abs/hep-th/9911193](https://arxiv.org/abs/hep-th/9911193) for example circled in blue.

<img align="left" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/CitT238_labs.png" width="100%">



## Partitioning using a mixture of grahplets

<img align="left" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/mixedGraphlets.png" width="10%"> Papers that share many in- and out-neighbours in common should be similar. In this example, we create a "MAM" which is a mixture of graphlets. Namely, the weight of an edge between two nodes is the number of times those nodes play the roles of blue nodes in an "occurrence" of the left graphlet, where the dotted edges may exist or not, and edges can exist between left and right white nodes, too. To build this MAM, go into the folder *MixedGraphlet* and run
```bash
./building_MAM.sh
```
This builds the described MAM, in which edges with values lower than 30 have been excised, and saves the largest component of this MAM into a file. It also saves the subgraph of the initial network induced by the nodes from this largest component.

Then, partition the network with the command
```bash
./partition.sh
```

It produces two * *.p* files, one partition is found by applying Louvain on the directed network, the other one is obtained from the MAM.

Finally, a brief comparison of those partitions is conducted by running
```bash
python3 analysing_partitions.py
```

It prints the modularity of both partitions on the directed network, its symmetrised version, and the MAM. The consistency as defined from the $\Phi$ measure from [page 12 here](https://hal.archives-ouvertes.fr/hal-03633062/document) is also displayed, as well as the contingency table of both partitions. They should look like the two left figures above, with some variations as the partitioning algorithms are random. From the top-left figure, it is clear that partitioning from the MAM is much more consistent than directly found on the network. From the top-right figure which is the middle one with rows sorted differently, we observe that the partitioning obtained from the MAM is a refinement from the one obtained on the network.

<img align="center" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/output_cit.png" width="90%">
