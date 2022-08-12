import argparse
import networkx as nx
from itertools import permutations

dico_nodes = {3:'T',4:'Q'}


def graphlet_id(path2graphlet):
    G = nx.read_edgelist(path2graphlet,create_using = nx.DiGraph)
    G = nx.convert_node_labels_to_integers(G)
    k = G.number_of_nodes()
    id_min = 32000
    for perm in permutations(G.nodes):
        id_crt = 0
        for e in G.edges:
            id_crt += 2**(k*perm[e[0]]+perm[e[1]])
        if id_crt < id_min:
            id_min = id_crt

    try:
        return dico_nodes[k] + str(id_min)
    except KeyError:
        return "Unknown Graphlet"


if __name__== "__main__":
    parser = argparse.ArgumentParser(description='Get the identifier of a graphlet passed as an edgelist.')
    parser.add_argument('GraphletFile', help='Path to the file containing the graphlet as an edgelist.')
    args = parser.parse_args()
    id_graphlet = graphlet_id(args.GraphletFile)
    print("Graphlet Identifier is", id_graphlet)
