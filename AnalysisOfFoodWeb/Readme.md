# Partitioning Florida Bay foodweb using motif T108


<img align="left" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/floridaBenson.png" width="35%">

We partitioned the Florida Bay network using the software and found a partitioning more consistent than the one originally found by [Benson et al.](https://snap.stanford.edu/higher-order), in the sense that our solution partitions their largest component into three blocks, that roughly separate fishes and gastropods from producers and flora.

## Partitioning the network

In this folder, just launch the shell script
```bash
./partition_and_gexf.sh
```

It partitions the network using the good setup, and creates a gexf file that contains the MAM and both partitionings (ours and Benson's).

## Observing the partitionings

This relies on the opensource software [Gephi](https://gephi.org/):

* Open Gephi, then `Ctrl+O` to load the gexf file saved in *Florida/Florida-bay-2clust.gexf*:
<img align="center" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/openFile.png" width="50%">

* On the left panel, choose the layout ***ForceAtlas 2*** with the parameters as in the figure. Click ***Run***, then ***Stop*** to layout the nodes.

<img align="center" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/forceatlas.png" width="50%">

* On the top of the left panel, choose ***Attribute*** in the ***Appearance*** window, then ***benson_clust*** in the list. Clicking ***Apply***, nodes will be coloured according to Benson's partitioning.

<img align="center" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/appearanceBenson.png" width="50%">

* Our clustering can also be observed, choosing ***our_clust*** from the list.

<img align="center" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/appearnceUs.png" width="50%">

* Finally, more insight can be gained in displaying nodes' labels, using the bottom part of the display window.

<img align="center" src="https://github.com/luleg/luleg.github.io/blob/master/AuxiliaryDoc/Displaylabels.png" width="50%">
