#ifndef __init_tree_reco__
#define __init_tree_reco__

#include "TTree.h"
#include "TChain.h"



//**************************
// Declaration of leaf types

// reco tree
struct RecoTreeVars
{
  int          runNumber; 
  int          spillNumber;
  int          evtNumber;
  int          beamE;
  float        tableX;
  float        tableY;
  int          HV;   
  float        ped_DQM[32];
  float        charge_DQM[32];
  float        amp_DQM[32];
  float        time_max_DQM[32];
  float        time_frac50_DQM[32];
  float        ped[32];
  float        charge[32];
  float        amp_max[32];
  float        amp_fit[32];
  float        time_max[32];
  float        time_CF[32];
  float        time_fit[32];
  float        tdcX;
  float        tdcY;
  unsigned int nHodoX1;
  unsigned int nHodoY1;
  unsigned int nHodoX2;
  unsigned int nHodoY2;
  int hodoX1[64];
  int hodoY1[64];
  int hodoX2[64];
  int hodoY2[64];
};



//*************************
// Initialization functions

void InitRecoTree(TTree* nt, RecoTreeVars& treeVars);

void SetRecoTree(TTree* nt, RecoTreeVars& treeVars);

void ClearRecoTreeVars(RecoTreeVars& treeVars);

#endif
