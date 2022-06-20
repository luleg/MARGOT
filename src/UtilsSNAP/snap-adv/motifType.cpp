#include "motifType.h"

/******************************
      QUADRANGLE
*******************************/
const int nbNodes = 4;

// Utility function that allows to link id of a 4-node subgraph to valid quadrangle ids.
// Required to know if an induced subgraph is an instance of a quadrangle
void loadIdsWithAnchors(TStr Qfile,TIntV& cpt2id, TVec<TIntV>& orbs,int id){
  // Given an 4-node induced subgraph of Adjacency amtrix A, and idA equal to
  // e'*(A.*B)*e) with B = reshape(2.^[0:15],[4,4])'; we have
  // cpt2id[idA] = idQ with idQ the minimal id of the quadrangle represented by A
  // #cpt2id is equal to 2^15-1=32767

  // Binary have been built that contains the correspondances.

  // Also, the corresponding placement of orbits is indicated to know, when obtaining
  // a motif given a specific id, where the orbits lie
  FILE* FQ = fopen(Qfile.CStr(),"rb");
  if (FQ == NULL ) TExcept::Throw("Unable to open the binary file containing QUADRANGLEs.");

  int idMax,nbIds;

  fread(&nbIds,sizeof(nbIds),1,FQ);
  fread(&idMax,sizeof(idMax),1,FQ);

  cpt2id.Reserve(idMax+1,idMax+1);
  orbs.Reserve(idMax+1,idMax+1);

  for (int cpt_id = 0; cpt_id<nbIds;cpt_id++){
    int id_crt,id_min;
    fread(&id_crt,sizeof(id_crt),1,FQ);
    fread(&id_min,sizeof(id_min),1,FQ);
    if (id_min == id){
      cpt2id[id_crt] = id_min;
      TIntV& set_orbs = orbs[id_crt];
      set_orbs.Reserve(nbNodes,nbNodes);
      for (int cpt_node = 0;cpt_node <nbNodes;cpt_node++ ){
        int orb_pos;
        fread(&orb_pos,sizeof(orb_pos),1,FQ);
        set_orbs[cpt_node] = orb_pos;
      }
    }
    else{
      for (int cpt_node = 0;cpt_node <nbNodes;cpt_node++ ){
        int tmp;
        fread(&tmp,sizeof(tmp),1,FQ);
      }
    }
  }
}
// Dummy constructor
MotifTypeQuad::MotifTypeQuad() : MotifType(){
  cpt2id =TIntV(0);
  orbits =TVec<TIntV>(0);
}

//Constructor:
// given the id of the quadrangle, specify "type", "id", and cpt2id
// Since induced subgraphs to be tested as isomorphic to the quadrangle have the
// same type (ie non directed structure (from the algorithm)), cpt2id contains
//the ids of quandrangles of this type.
// There are 129 directed quadrangles, thus this function contains 129 ids.
MotifTypeQuad::MotifTypeQuad(const TStr& motif) {

  TStr motif_lc = motif.GetLc();
  if (motif_lc == "q204"){
      id=204;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q456"){
      id=456;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q460"){
      id=460;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q904"){
      id=904;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q908"){
      id=908;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q972"){
      id=972;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q4548"){
      id=4548;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q4556"){
      id=4556;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q4740"){
      id=4740;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q4748"){
      id=4748;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q4812"){
      id=4812;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q5004"){
      id=5004;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q5064"){
      id=5064;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q5068"){
      id=5068;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q13260"){
      id=13260;
      loadIdsWithAnchors("Quad/Q4WithAnchors.bin",cpt2id,orbits,id);
      type = 4;
  }
  else if (motif_lc == "q206"){
      id=206;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q222"){
      id=222;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q458"){
      id=458;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q462"){
      id=462;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q472"){
      id=472;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q474"){
      id=474;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q476"){
      id=476;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q478"){
      id=478;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q906"){
      id=906;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q910"){
      id=910;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q922"){
      id=922;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q924"){
      id=924;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q926"){
      id=926;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q974"){
      id=974;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q990"){
      id=990;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q2190"){
      id=2190;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q2204"){
      id=2204;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q2206"){
      id=2206;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q2252"){
      id=2252;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q2458"){
      id=2458;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q2462"){
      id=2462;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4546"){
      id=4546;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4550"){
      id=4550;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4558"){
      id=4558;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4562"){
      id=4562;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4564"){
      id=4564;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4566"){
      id=4566;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4572"){
      id=4572;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4574"){
      id=4574;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4742"){
      id=4742;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4750"){
      id=4750;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4758"){
      id=4758;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4764"){
      id=4764;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4766"){
      id=4766;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4814"){
      id=4814;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4830"){
      id=4830;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4994"){
      id=4994;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q4998"){
      id=4998;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5002"){
      id=5002;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5006"){
      id=5006;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5010"){
      id=5010;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5012"){
      id=5012;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5014"){
      id=5014;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5016"){
      id=5016;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5018"){
      id=5018;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5020"){
      id=5020;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5022"){
      id=5022;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5058"){
      id=5058;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5062"){
      id=5062;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5066"){
      id=5066;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5070"){
      id=5070;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5074"){
      id=5074;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5076"){
      id=5076;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5078"){
      id=5078;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5080"){
      id=5080;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5082"){
      id=5082;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5084"){
      id=5084;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q5086"){
      id=5086;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q6348"){
      id=6348;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q6550"){
      id=6550;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q6552"){
      id=6552;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q6554"){
      id=6554;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q6558"){
      id=6558;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q6604"){
      id=6604;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q6858"){
      id=6858;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q6874"){
      id=6874;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q13142"){
      id=13142;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q13146"){
      id=13146;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q13148"){
      id=13148;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q13150"){
      id=13150;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q13262"){
      id=13262;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q13278"){
      id=13278;
      loadIdsWithAnchors("Quad/Q5WithAnchors.bin",cpt2id,orbits,id);
      type = 5;
  }
  else if (motif_lc == "q2254"){
      id=2254;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q2270"){
      id=2270;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q2506"){
      id=2506;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q2510"){
      id=2510;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q2524"){
      id=2524;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q2526"){
      id=2526;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q3038"){
      id=3038;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6342"){
      id=6342;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6350"){
      id=6350;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6356"){
      id=6356;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6358"){
      id=6358;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6364"){
      id=6364;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6366"){
      id=6366;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6598"){
      id=6598;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6602"){
      id=6602;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6606"){
      id=6606;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6614"){
      id=6614;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6616"){
      id=6616;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6618"){
      id=6618;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6620"){
      id=6620;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6622"){
      id=6622;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6854"){
      id=6854;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6862"){
      id=6862;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6870"){
      id=6870;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6876"){
      id=6876;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q6878"){
      id=6878;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q7126"){
      id=7126;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q7128"){
      id=7128;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q7130"){
      id=7130;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q7134"){
      id=7134;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q14678"){
      id=14678;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q14686"){
      id=14686;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q14790"){
      id=14790;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q14798"){
      id=14798;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q14810"){
      id=14810;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q14812"){
      id=14812;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q14814"){
      id=14814;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q15258"){
      id=15258;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q15262"){
      id=15262;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q15310"){
      id=15310;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q15326"){
      id=15326;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else if (motif_lc == "q31710"){
      id=31710;
      loadIdsWithAnchors("Quad/Q6WithAnchors.bin",cpt2id,orbits,id);
      type = 6;
  }
  else {

     TExcept::Throw("Unknown motif");
   }

}


bool MotifTypeQuad::IsInstance(const int& cpt_id,TIntV& orbs) const{
  orbs = orbits[cpt_id];
  return (cpt2id[cpt_id] == id);
}
//

MotifTypeQuad::~MotifTypeQuad(){
}

/******************************
      TRIANGLE
*******************************/

MotifTypeTriangle::MotifTypeTriangle(): MotifType(){
  FInstance = NULL;
}

void MotifTypeTriangle::SetGraph(const PNGraph& one_graph){
  FInstance->SetGraph(one_graph); // Links FInstance to a graph (required to explore induced subgraphs)
}


MotifTypeTriangle::~MotifTypeTriangle(){
  delete FInstance; // This is a pointer, needs to be delete
}

// Constructor. Understands motif as in Benson's Thesis (M1,M2...) and also
// minimal graph id (T98, T12, etc)
MotifTypeTriangle::MotifTypeTriangle(const TStr& motif) {
  TStr motif_lc = motif.GetLc();
  if ((motif_lc == "m1")||(motif_lc == "t98"))          {
    id=1;
    type = TRIANGLE;
    FInstance = new Func_IsInstance_M1();
  }
  else if ((motif_lc == "m2")||(motif_lc == "t102"))         {
    id=2;
    type = TRIANGLE;
    FInstance = new Func_IsInstance_M2();
  }
  else if ((motif_lc == "m3")||(motif_lc == "t110"))          {
    id=3;
    type = TRIANGLE;
    FInstance = new Func_IsInstance_M3();
  }
  else if ((motif_lc == "m4")||(motif_lc == "t238"))          {
    id=4;
    type = TRIANGLE;
    FInstance = new Func_IsInstance_M4();
  }
  else if ((motif_lc == "m5")||(motif_lc == "t38"))          {
    id=5;
    type = TRIANGLE;
    FInstance = new Func_IsInstance_M5();
  }
  else if ((motif_lc == "m6")||(motif_lc == "t108"))          {
    id=6;
    type = TRIANGLE;
    FInstance = new Func_IsInstance_M6();
  }
  else if ((motif_lc == "m7")||(motif_lc == "t46"))          {
    id=7;
    type = TRIANGLE;
    FInstance = new Func_IsInstance_M7();
  }
  else if ((motif_lc == "m8")||(motif_lc == "t6"))          {
    id=8;
    type = WEDGE;
    FInstance = new Func_IsInstance_M8();
  }
  else if ((motif_lc == "m9")||(motif_lc == "t12"))          {
    id=9;
    type = WEDGE;
    FInstance = new Func_IsInstance_M9();
  }
  else if ((motif_lc == "m10")||(motif_lc == "t36"))         {
    id=10;
    type = WEDGE;
    FInstance = new Func_IsInstance_M10();
  }
  else if ((motif_lc == "m11")||(motif_lc == "t14"))         {
    id=11;
    type = WEDGE;
    FInstance = new Func_IsInstance_M11();
  }
  else if ((motif_lc == "m12")||(motif_lc == "t74"))         {
    id=12;
    type = WEDGE;
    FInstance = new Func_IsInstance_M12();
  }
  else if ((motif_lc == "m13")||(motif_lc == "t78"))         {
    id=13;
    type = WEDGE;
    FInstance = new Func_IsInstance_M13();
  }
  else { TExcept::Throw("Unknown motif"); }
}

bool MotifTypeTriangle::IsInstance(const int& u, const int& v, const int& w, TIntV& orbs) const{
  return (*FInstance)(u,v,w, orbs);
  // Each kind of 3-node graphlet has its own FInstance, which is an functor
  // containing a graph G and a function F. F return true if the induced subrgaph
  // formed by (u,v,w) in G is an instance of the motif
}

/******************************
      EDGES
*******************************/

MotifTypeEdge::MotifTypeEdge() : MotifType(){
}

MotifTypeEdge::MotifTypeEdge(const TStr& motif){
  if (motif[1] == '1'){
    type = DIR;
  }
  else if(motif[1] == '2'){
    type=SYM;
  }
}

MotifTypeEdge::~MotifTypeEdge(){
}
