#ifndef __init_tree_H4__
#define __init_tree_H4__

#include "TTree.h"
#include "TChain.h"



//**************************
// Declaration of leaf types

// unpacked tree
struct UnpackedTreeVars
{
  unsigned int runNumber;
  unsigned int spillNumber;
  unsigned int evtNumber;
  unsigned int nAdcChannels;
  unsigned int adcBoard[100];   
  unsigned int adcChannel[100];   
  unsigned int adcData[100];   
  unsigned int nTdcChannels;
  unsigned int tdcBoard[10];   
  unsigned int tdcChannel[10];  
  unsigned int tdcData[10];  
  unsigned int nDigiSamples;
  unsigned int digiGroup[100000];   
  unsigned int digiChannel[100000];   
  unsigned int digiSampleIndex[100000];   
  float        digiSampleValue[100000];   
};

// DQM tree
struct DQMTreeVars
{
  unsigned int        runNumber;
  unsigned int        spillNumber;
  unsigned int        evtNumber;
  std::vector<float>* TDCreco;
  std::vector<float>* digi_charge_integrated;
  std::vector<float>* digi_max_amplitude;
  std::vector<float>* digi_pedestal;
  std::vector<float>* digi_time_at_frac50;
  std::vector<float>* digi_time_at_max;
  std::vector<bool>* HODOX1;
  std::vector<bool>* HODOX2;
  std::vector<bool>* HODOY1;
  std::vector<bool>* HODOY2;
};



//*************************
// Initialization functions

void InitTreeUnpacked(TChain* nt, UnpackedTreeVars& treeVars);
void InitTreeDQM(TChain* nt, DQMTreeVars& treeVars);

#endif
