#ifndef snap_fctor_triangle_h
#define snap_fctor_triangle_h
#include "Snap.h"

// Each kind of 3-node graphlet has its own FInstance, which is an functor
// containing a graph G and a function F. F return true if the induced subrgaph
// formed by (u,v,w) in G is an instance of the motif.

class Func_IsInstance {
  protected:
    int const uu;
    int const vv;
    int const ww;
    PNGraph graph;

    bool IsNoEdge(int u, int v){
      return !graph->IsEdge(u, v) && !graph->IsEdge(v, u);
    };
    bool IsUnidirEdge(int u, int v){
      return graph->IsEdge(u, v) && !graph->IsEdge(v, u);
    };
    bool IsBidirEdge(int u, int v){
      return graph->IsEdge(u, v) && graph->IsEdge(v, u);
    };
  public:
    virtual ~Func_IsInstance() {
      // printf("~Func_IsInstance destructor\n");
    };
    Func_IsInstance() : graph(NULL), uu(0), vv(1), ww(2) {};
    void SetGraph(const PNGraph& one_graph){
      graph = one_graph;
    };
    virtual bool operator()(int u, int v, int w, TIntV& orbs) = 0;
};

class Func_IsInstance_M1 : public Func_IsInstance {
  public:

    virtual ~Func_IsInstance_M1(){
      // printf("~Func_IsInstance_M1 destructor\n");
    };
    Func_IsInstance_M1() : Func_IsInstance() {};

    virtual bool operator()(int u, int v, int w, TIntV& orbs) {
      if ((IsUnidirEdge(u, v) && IsUnidirEdge(v, w) && IsUnidirEdge(w, u))
      || (IsUnidirEdge(u, w) && IsUnidirEdge(w, v) && IsUnidirEdge(v, u))){
        orbs[uu] = 1; orbs[vv] = 1; orbs[ww] = 1;
        return true;
      }
      return false;
    };
};

class Func_IsInstance_M2 : public Func_IsInstance {
  public:

  virtual ~Func_IsInstance_M2(){
    // printf("~Func_IsInstance_M2 destructor\n");
  };
  Func_IsInstance_M2() : Func_IsInstance() {};

  virtual bool operator()(int u, int v, int w, TIntV& orbs) {
    if (IsBidirEdge(u, v)){
      if (IsUnidirEdge( u, w) && IsUnidirEdge(w, v)) {
        orbs[uu] = 1; orbs[vv] = 3; orbs[ww] = 2;
        return true;
      }
      if (IsUnidirEdge( w, u) && IsUnidirEdge( v, w)) {
        orbs[uu] = 3; orbs[vv] = 1; orbs[ww] = 2;
        return true;
      }
      return false;
    }
    if (IsBidirEdge( u, w)){
      if (IsUnidirEdge( u, v) && IsUnidirEdge( v, w)) {
        orbs[uu] = 1; orbs[vv] = 2; orbs[ww] = 3;
        return true;
      }
      if (IsUnidirEdge( v, u) && IsUnidirEdge( w, v)){
        orbs[uu] = 3; orbs[vv] = 2; orbs[ww] = 1;
        return true;
      }
      return false;
    }
    if (IsBidirEdge( v, w)){
      if (IsUnidirEdge( v, u) && IsUnidirEdge( u, w)){
        orbs[uu] = 2; orbs[vv] = 1; orbs[ww] = 3;
        return true;
      }
      if (IsUnidirEdge( u, v) && IsUnidirEdge( w, u)){
        orbs[uu] = 2; orbs[vv] = 3; orbs[ww] = 1;
        return true;
      }
      return false;
    };
    return false;
  };
};

class Func_IsInstance_M3 : public Func_IsInstance {
public:

  virtual ~Func_IsInstance_M3(){
    // printf("~Func_IsInstance_M3 destructor\n");
  };
  Func_IsInstance_M3() : Func_IsInstance() {};

  virtual bool operator()(int u, int v, int w, TIntV& orbs) {
    if (IsBidirEdge( u, v) && IsBidirEdge(  v, w)){
      if(IsUnidirEdge( u, w)){
        orbs[vv] = 1; orbs[uu] = 2;orbs[ww] = 3;
        return true;
      }
      if (IsUnidirEdge( w, u)){
        orbs[vv] = 1; orbs[uu] = 3;orbs[ww] = 2;
        return true;
      }
      return false;
    }
    if (IsBidirEdge(  u, w) && IsBidirEdge(  w, v)){
      if (IsUnidirEdge( u, v)){
        orbs[ww]=1; orbs[uu] = 2;orbs[vv] = 3;
        return true;
      }
      if(IsUnidirEdge( v, u)){
        orbs[ww]=1; orbs[uu] = 3; orbs[vv] = 2;
        return true;
      }
      return false;
    }
    if (IsBidirEdge( w, u) && IsBidirEdge( u, v)){
      if (IsUnidirEdge( w, v)){
        orbs[uu] = 1; orbs[vv] = 3;orbs[ww] = 2;
        return true;
      }
      if (IsUnidirEdge(v, w)){
        orbs[uu] = 1; orbs[vv] = 2;orbs[ww] = 3;
        return true;
      }
      return false;
    }
    return false;
  };
};

class Func_IsInstance_M4 : public Func_IsInstance {
public:
  virtual ~Func_IsInstance_M4(){
    // printf("~Func_IsInstance_M4 destructor\n");
  };
  Func_IsInstance_M4() : Func_IsInstance() {};

  virtual bool operator()(int u, int v, int w, TIntV& orbs) {
    if (IsBidirEdge(u, v) && IsBidirEdge( u, w) && IsBidirEdge(v, w)){
      orbs[0] = 1;orbs[1] = 1;orbs[2] = 1;
      return true;
    }
    return false;
  };
};

class Func_IsInstance_M5 : public Func_IsInstance {
public:

  virtual ~Func_IsInstance_M5(){
    // printf("~Func_IsInstance_M5 destructor\n");
  };
  Func_IsInstance_M5() : Func_IsInstance() {};

  virtual bool operator()(int u, int v, int w,  TIntV& orbs) {
    if (IsUnidirEdge(u, v) && IsUnidirEdge(u, w)){
      if (IsUnidirEdge(v, w)){
        orbs[uu] = 1; orbs[vv] = 2;orbs[ww] = 3;
        return true;
      }
      if(IsUnidirEdge(w, v)){
        orbs[uu] = 1; orbs[vv] = 3;orbs[ww] = 2;
        return true;
      }
      return false;
    }
    if (IsUnidirEdge(v, u) && IsUnidirEdge(v, w)){
      if (IsUnidirEdge(u, w)){
        orbs[vv] = 1; orbs[uu] = 2;orbs[ww]= 3;
        return true;
      }
      if (IsUnidirEdge(w, u)){
        orbs[vv] = 1; orbs[uu] = 3;orbs[ww]= 2;
        return true;
      }
      return false;
    }
    if (IsUnidirEdge(w, v) && IsUnidirEdge(w, u)){
      if (IsUnidirEdge(v, u)){
        orbs[ww] = 1; orbs[uu] = 3; orbs[vv] = 2;
        return true;
      }
      if(IsUnidirEdge(u, v)) {
        orbs[ww] = 1; orbs[uu] = 2;orbs[vv] = 3;
        return true;
      }
    }
    return false;
  };
};

class Func_IsInstance_M6 : public Func_IsInstance {
public:

  virtual ~Func_IsInstance_M6(){
    // printf("~Func_IsInstance_M6 destructor\n");
  };

  Func_IsInstance_M6() : Func_IsInstance() {};

  virtual bool operator()(int u, int v, int w, TIntV& orbs) {
    if(IsUnidirEdge(u, v) && IsUnidirEdge(u, w) && IsBidirEdge(v, w)){
      orbs[uu] = 1; orbs[vv] = 2; orbs[ww] = 2;
      return true;
    }
    if (IsUnidirEdge(v, u) && IsUnidirEdge(v, w) && IsBidirEdge(u, w)){
      orbs[uu] = 2; orbs[vv] = 1; orbs[ww] = 2;
      return true;
    }
    if (IsUnidirEdge(w, u) && IsUnidirEdge(w, v) && IsBidirEdge(u, v)){
      orbs[uu] = 2; orbs[vv] = 2; orbs[ww] = 1;
      return true;
    };
    return false;
  };
};

class Func_IsInstance_M7 : public Func_IsInstance {
public:

  virtual ~Func_IsInstance_M7(){
    // printf("~Func_IsInstance_M7 destructor\n");
  };

  Func_IsInstance_M7() : Func_IsInstance() {};

  virtual bool operator()(int u, int v, int w, TIntV& orbs) {
    if (IsUnidirEdge(v, u) && IsUnidirEdge(w, u) && IsBidirEdge(v, w)){
      orbs[uu] = 2; orbs[vv] = 1; orbs[ww] = 1;
      return true;
    }
    if (IsUnidirEdge(u, v) && IsUnidirEdge(w, v) && IsBidirEdge(u, w)){
      orbs[uu] = 1; orbs[vv] = 2; orbs[ww] = 1;
      return true;
    }
    if (IsUnidirEdge(u, w) && IsUnidirEdge(v, w) && IsBidirEdge(u, v)){
      orbs[uu] = 1; orbs[vv] = 1; orbs[ww] = 2;
      return true;
    }
    return false;
  };
};

class Func_IsInstance_M8 : public Func_IsInstance {
public:

  virtual ~Func_IsInstance_M8(){
    // printf("~Func_IsInstance_M8 destructor\n");
  };
  Func_IsInstance_M8() : Func_IsInstance() {};

  virtual bool operator()(int center, int v, int w, TIntV& orbs) {

    if (IsNoEdge(v, w) && IsUnidirEdge(center, v) && IsUnidirEdge(center, w)){
      orbs[uu] = 1;orbs[vv] = 2;orbs[ww] = 2;
      return true;
    }
    return false;
  };
};

class Func_IsInstance_M9 : public Func_IsInstance {
public:

  virtual ~Func_IsInstance_M9(){
    // printf("~Func_IsInstance_M9 destructor\n");
  };
  Func_IsInstance_M9() : Func_IsInstance() {};

  virtual bool operator()(int center, int v, int w,TIntV& orbs) {
    if (IsNoEdge(v, w)) {
      if (IsUnidirEdge(center, v) && IsUnidirEdge(w, center)) {
        orbs[uu] = 1;orbs[vv]=3;orbs[ww]=2;
        return true;
      }
      if (IsUnidirEdge(center, w) && IsUnidirEdge(v, center)){
        orbs[uu] = 1;orbs[vv]=2;orbs[ww]=3;
        return true;
      }
    }
    return false;
  };
};

class Func_IsInstance_M10 : public Func_IsInstance {
public:

  virtual ~Func_IsInstance_M10(){
    // printf("~Func_IsInstance_M10 destructor\n");
  };
  Func_IsInstance_M10() : Func_IsInstance() {};

  virtual bool operator()(int center, int v, int w, TIntV& orbs) {
    if (IsNoEdge(v, w) && IsUnidirEdge(v, center) && IsUnidirEdge(w, center)){
      orbs[uu]=1;orbs[vv]=2;orbs[ww]=2;
      return true;
    }
    return false;
  };
};

class Func_IsInstance_M11 : public Func_IsInstance {
public:
  virtual ~Func_IsInstance_M11(){
    // printf("~Func_IsInstance_M11 destructor\n");
  };
  Func_IsInstance_M11() : Func_IsInstance() {};

  virtual bool operator()(int center, int v, int w, TIntV& orbs) {
    if (IsNoEdge(v, w)){
      if (IsBidirEdge(center, v) && IsUnidirEdge(center, w)){
        orbs[uu]=1;orbs[vv]=2;orbs[ww]=3;
        return true;
      }
      if (IsBidirEdge(center, w) && IsUnidirEdge(center, v)){
        orbs[uu]=1;orbs[vv]=3;orbs[ww]=2;
        return true;
      }
     };
     return false;
  };
};

class Func_IsInstance_M12 : public Func_IsInstance {
public:
  virtual ~Func_IsInstance_M12(){
    // printf("~Func_IsInstance_M12 destructor\n");
  };
  Func_IsInstance_M12() : Func_IsInstance() {};

  virtual bool operator()(int center, int v, int w, TIntV& orbs) {
    if (IsNoEdge(v, w)){
      if (IsBidirEdge(center, v) && IsUnidirEdge(w, center)){
        orbs[uu]=1;orbs[vv]=2;orbs[ww]=3;
        return true;
      }
      if (IsBidirEdge(center, w) && IsUnidirEdge(v, center)){
        orbs[uu]=1;orbs[vv]=3;orbs[ww]=2;
        return true;
      }
    };
    return false;
  };
};

class Func_IsInstance_M13 : public Func_IsInstance {
public:
  virtual ~Func_IsInstance_M13(){
    // printf("~Func_IsInstance_M13 destructor\n");
  };
  Func_IsInstance_M13() : Func_IsInstance() {};

  virtual bool operator()(int center, int v, int w, TIntV& orbs) {
    if (IsNoEdge(v, w) && IsBidirEdge(center, v) && IsBidirEdge(center, w)){
      orbs[uu]=1;orbs[vv]=2;orbs[ww]=2;
      return true;
    }
    return false;
  };

};
#endif //snap_fctor_triangle_h
