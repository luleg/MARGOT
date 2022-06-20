#include "BensonGraphTriangle.h"

// SEQUENTIAL //////////////////////////////////////////////////////////////////
/******************************************************************************/
/*                         Some Utilities Functions                           */

BensonGraphTriangle::~BensonGraphTriangle(){
  motif = MotifTypeTriangle(); // To unhandle the motif, which is linked to a functor
}

// Dummy Constructor
BensonGraphTriangle::BensonGraphTriangle() : BensonGraph(), motif() {
}


BensonGraphTriangle::BensonGraphTriangle(PNGraph& one_graph,MotifTypeTriangle& one_motif,TIntV const& orbs, bool decomp,bool verb) : BensonGraph(one_graph,decomp,verb), motif(one_motif), orbits(orbs) {

  motif.SetGraph(graph);

  if (decomp){// if decomp is true, the MAM is computed in the constructor
    int tt = motif.getType();
    switch (tt){
      case TRIANGLE:
        TriangleMotifAdjacency();
        break;
      case WEDGE:
        WedgeMotifAdjacency();
        break;
      default:
        TExcept::Throw("Unknown triangle type.");
    }
  }
}

/******************************************************************************/
/*                        Closed Triangle Weighting                           */

void BensonGraphTriangle::TriangleProcOneNode(const TNGraph::TNodeI& NI, const int& src, const int& src_pos){
  // Algorithm from Chiba and NISHIZEKI for listing triangles
  TIntV neighbors_higher;
  for (int i = 0; i < NI.GetOutDeg(); i++) {
    int nbr = NI.GetOutNId(i);
    if (order[nbr] > src_pos) {
      neighbors_higher.Add(nbr);
    }
  }
  for (int i = 0; i < NI.GetInDeg(); i++) {
    int nbr = NI.GetInNId(i);
    if (!NI.IsOutNId(nbr) && order[nbr] > src_pos) {
      neighbors_higher.Add(nbr);
    }
  }

  for (int ind1 = 0; ind1 < neighbors_higher.Len(); ind1++) {
    for (int ind2 = ind1 + 1; ind2 < neighbors_higher.Len(); ind2++) {
      int dst1 = neighbors_higher[ind1];
      int dst2 = neighbors_higher[ind2];
      // Check for triangle formation
      if (graph->IsEdge(dst1, dst2) || graph->IsEdge(dst2, dst1)) {
        TIntV orb_places(3);
        if (motif.IsInstance(src, dst1, dst2, orb_places)) { // we update MAM if the ibnduced subgraph is an instance of the motif
          TIntV lnodes(3);
          if (orbits.Len()==0){
            lnodes[0] = src; lnodes[1] = dst1; lnodes[2] = dst2;
          }
          else{
            lnodes.Reserve(3,0);
            if (orbits.IsIn(orb_places[0])){
              lnodes.Add(src);
            }
            if (orbits.IsIn(orb_places[1])){
              lnodes.Add(dst1);
            }
            if (orbits.IsIn(orb_places[2])){
              lnodes.Add(dst2);
            }
          }
          IncrementWeight(lnodes);
        }
      }
    }
  }
}


void BensonGraphTriangle::TriangleMotifAdjacency() {
  // Algorithm from Chiba and NISHIZEKI for listing triangles
  if (verbose) {printf("Building the MAM of a closed triangle sequentially...\n");}
  int cpt = 0;
  for (TNGraph::TNodeI NI = graph->BegNI(); NI < graph->EndNI(); NI++) {
    if (cpt%100000 == 0 && verbose){
      printf("Processing node %d\n",cpt);
    }
    cpt++;
    int src = NI.GetId();
    int src_pos = order[src];
    TriangleProcOneNode(NI, src,src_pos);
  }
}

/******************************************************************************/
/*                            Wedges Weighting                               */

void BensonGraphTriangle::WedgeProcOneNode(const TNGraph::TNodeI& NI, const int& center){
  TIntV neighbors;
  for (int i = 0; i < NI.GetOutDeg(); i++) {
    int nbr = NI.GetOutNId(i);
    neighbors.Add(nbr);
  }
  for (int i = 0; i < NI.GetInDeg(); i++) {
    int nbr = NI.GetInNId(i);
    if (!NI.IsOutNId(nbr)) {
      neighbors.Add(nbr);
    }
  }

  for (int ind1 = 0; ind1 < neighbors.Len(); ind1++) {
    for (int ind2 = ind1 + 1; ind2 < neighbors.Len(); ind2++) {
      int dst1 = neighbors[ind1];
      int dst2 = neighbors[ind2];
      // Increment weights of (center, dst1, dst2) if it occurs.
      TIntV orb_places(3);
      if (motif.IsInstance(center, dst1, dst2, orb_places)) { // we update MAM if the ibnduced subgraph is an instance of the motif

        TIntV lnodes(3);
        if (orbits.Len()==0){
          lnodes[0] = center; lnodes[1] = dst1; lnodes[2] = dst2;
        }
        else{
          lnodes.Reserve(3,0);
          if (orbits.IsIn(orb_places[0])){
            lnodes.Add(center);
          }
          if (orbits.IsIn(orb_places[1])){
            lnodes.Add(dst1);
          }
          if (orbits.IsIn(orb_places[2])){
            lnodes.Add(dst2);
          }
        }
        IncrementWeight(lnodes);
      }
    }
  }
}


void BensonGraphTriangle::WedgeMotifAdjacency() {
  if (verbose) {printf("Building the MAM of a wedge sequentially...\n");}
  int cpt = 0;
  for (TNGraph::TNodeI NI = graph->BegNI(); NI < graph->EndNI(); NI++) {
    if (cpt%100000 == 0 && verbose){
      printf("Processing node %d\n",cpt);
    }
    cpt++;

    int center = NI.GetId();
    WedgeProcOneNode(NI, center);
  }
}

// MULTITHREADED ///////////////////////////////////////////////////////////////
/******************************************************************************/
/*                         Some Utilities Functions                           */

 // Destructor :  Destroy all the openMP locks
BensonGraphTriangleMP::~BensonGraphTriangleMP(){
  for (TNGraph::TNodeI VI = graph->BegNI(); VI < graph->EndNI(); VI++) {
    int vi = VI.GetId();
    omp_destroy_lock(&TLocks[vi]);
  }
}

BensonGraphTriangleMP::BensonGraphTriangleMP() : BensonGraphTriangle() {
  TLocks = TVec<omp_lock_t>(0);
}

BensonGraphTriangleMP::BensonGraphTriangleMP(PNGraph& one_graph,MotifTypeTriangle& one_motif, TIntV const& orbs, const TInt& nThreads, bool verb) : BensonGraphTriangle(one_graph,one_motif,orbs,false,verb), nbProc(nThreads) {

  weight = WeightVHM(graph->GetMxNId());
  TLocks = TVec<omp_lock_t>(graph->GetMxNId()); // Create and init one lock per node
  for (TNGraph::TNodeI VI = graph->BegNI(); VI < graph->EndNI(); VI++) {
    int vi = VI.GetId();
    weight[vi] = THash<TInt,TInt>();
    omp_lock_t one_lock;
    omp_init_lock(&one_lock);
    TLocks[vi] = one_lock;
  }

  int tt = motif.getType();
  switch (tt){
    case TRIANGLE:
      TriangleMotifAdjacency();
      break;
    case WEDGE:
      WedgeMotifAdjacency();
      break;
    default:
      TExcept::Throw("Unknown triangle type.");
  }

}

// For incrementing weight in the MAM avoiding concurrential accesses :
void BensonGraphTriangleMP::IncrementWeight(TIntV const& lnodes) {
  for (int id_node_pred = 0; id_node_pred < lnodes.Len(); id_node_pred++)
  {
    int node_pred = lnodes[id_node_pred];
    omp_lock_t& lock_node = TLocks[node_pred];
    omp_set_lock(&lock_node);
    THash<TInt, TInt>& edge_weights = weight[node_pred];
    for (int id_node_succ = 0; id_node_succ < lnodes.Len(); id_node_succ++){
      int node_succ = lnodes[id_node_succ];
      if (node_pred != node_succ){
        edge_weights(node_succ) += 1;
      }
    }
    omp_unset_lock(&lock_node);
  }
}


/******************************************************************************/
/*                        Closed Triangles Weighting                          */
void BensonGraphTriangleMP::TriangleMotifAdjacency() {
  if (verbose) {printf("Building MAM of closed triangle using %d threads...\n",nbProc);}
  int nbNodes = graph->GetMxNId()+1;

  omp_set_num_threads(nbProc);
  int tid(-1),cpt(0);

  #pragma omp parallel for firstprivate(cpt) private(tid) schedule(dynamic,1)
  for (int src=0;src<nbNodes;src++){ // One proc process one node, in parallel
    if (not graph->IsNode(src)){
      continue;
    }
    if (cpt%100000 == 0 && verbose){
      tid = omp_get_thread_num();
      printf("Thread %d processes its %dth Node...\n",tid,cpt);
    }
    cpt ++;

    TNGraph::TNodeI NI = graph->GetNI(src);
    int src_pos = order[src];
    TriangleProcOneNode(NI, src,src_pos);
  }
}


/******************************************************************************/
/*                            Wedges Weighting                               */

void BensonGraphTriangleMP::WedgeMotifAdjacency() {
  if (verbose) {printf("Building MAM of a wedge using %d threads...\n",nbProc);}

  int nbNodes = graph->GetMxNId()+1;

  omp_set_num_threads(nbProc);
  int tid(-1),cpt(0);

  #pragma omp parallel for private(tid) schedule(dynamic,1)
  for (int center=0;center<nbNodes;center++){ // One proc process one node, in parallel

    if (not graph->IsNode(center)){
      continue;
    }
    if (cpt%10000 == 0 && verbose){
      tid = omp_get_thread_num();
      printf("Thread %d processes its %dth Node...\n",tid,cpt);
    }
    cpt ++;

    TNGraph::TNodeI NI = graph->GetNI(center);
    WedgeProcOneNode(NI, center);
  }

}
