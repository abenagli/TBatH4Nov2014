#include "init_tree_H4.h"



void InitTreeUnpacked(TChain* nt, UnpackedTreeVars& treeVars)
{
  nt -> SetBranchStatus("*", 0);
  nt ->SetBranchStatus("runNumber",       1); nt -> SetBranchAddress("runNumber",       &treeVars.runNumber);
  nt ->SetBranchStatus("spillNumber",     1); nt -> SetBranchAddress("spillNumber",     &treeVars.spillNumber);
  nt ->SetBranchStatus("evtNumber",       1); nt -> SetBranchAddress("evtNumber",       &treeVars.evtNumber);
  nt ->SetBranchStatus("nAdcChannels",    1); nt -> SetBranchAddress("nAdcChannels",    &treeVars.nAdcChannels);
  nt ->SetBranchStatus("adcBoard",        1); nt -> SetBranchAddress("adcBoard",        &treeVars.adcBoard);
  nt ->SetBranchStatus("adcChannel",      1); nt -> SetBranchAddress("adcChannel",      &treeVars.adcChannel);
  nt ->SetBranchStatus("adcData",         1); nt -> SetBranchAddress("adcData",         &treeVars.adcData);
  nt ->SetBranchStatus("nTdcChannels",    1); nt -> SetBranchAddress("nTdcChannels",    &treeVars.nTdcChannels);
  nt ->SetBranchStatus("tdcBoard",        1); nt -> SetBranchAddress("tdcBoard",        &treeVars.tdcBoard);
  nt ->SetBranchStatus("tdcChannel",      1); nt -> SetBranchAddress("tdcChannel",      &treeVars.tdcChannel);
  nt ->SetBranchStatus("tdcData",         1); nt -> SetBranchAddress("tdcData",         &treeVars.tdcData);
  nt ->SetBranchStatus("nDigiSamples",    1); nt -> SetBranchAddress("nDigiSamples",    &treeVars.nDigiSamples);
  nt ->SetBranchStatus("digiGroup",       1); nt -> SetBranchAddress("digiGroup",       &treeVars.digiGroup);
  nt ->SetBranchStatus("digiChannel",     1); nt -> SetBranchAddress("digiChannel",     &treeVars.digiChannel);
  nt ->SetBranchStatus("digiSampleIndex", 1); nt -> SetBranchAddress("digiSampleIndex", &treeVars.digiSampleIndex);
  nt ->SetBranchStatus("digiSampleValue", 1); nt -> SetBranchAddress("digiSampleValue", &treeVars.digiSampleValue);
}

void InitTreeDQM(TChain* nt, DQMTreeVars& treeVars)
{
  nt -> SetBranchStatus("*", 0);
  nt -> SetBranchStatus("TDCreco",                1); nt -> SetBranchAddress("TDCreco",                &treeVars.TDCreco);
  nt -> SetBranchStatus("runNumber",              1); nt -> SetBranchAddress("runNumber",              &treeVars.runNumber);
  nt -> SetBranchStatus("spillNumber",            1); nt -> SetBranchAddress("spillNumber",            &treeVars.spillNumber);
  nt -> SetBranchStatus("evtNumber",              1); nt -> SetBranchAddress("evtNumber",              &treeVars.evtNumber);
  nt -> SetBranchStatus("digi_charge_integrated", 1); nt -> SetBranchAddress("digi_charge_integrated", &treeVars.digi_charge_integrated);
  nt -> SetBranchStatus("digi_max_amplitude",     1); nt -> SetBranchAddress("digi_max_amplitude",     &treeVars.digi_max_amplitude);
  nt -> SetBranchStatus("digi_pedestal",          1); nt -> SetBranchAddress("digi_pedestal",          &treeVars.digi_pedestal);
  nt -> SetBranchStatus("digi_time_at_max",       1); nt -> SetBranchAddress("digi_time_at_max",       &treeVars.digi_time_at_max);
  nt -> SetBranchStatus("digi_time_at_frac50",    1); nt -> SetBranchAddress("digi_time_at_frac50",    &treeVars.digi_time_at_frac50);
  nt -> SetBranchStatus("HODOX1",                 1); nt -> SetBranchAddress("HODOX1",                 &treeVars.HODOX1);
  nt -> SetBranchStatus("HODOY1",                 1); nt -> SetBranchAddress("HODOY1",                 &treeVars.HODOY1);
  nt -> SetBranchStatus("HODOX2",                 1); nt -> SetBranchAddress("HODOX2",                 &treeVars.HODOX2);
  nt -> SetBranchStatus("HODOY2",                 1); nt -> SetBranchAddress("HODOY2",                 &treeVars.HODOY2);
}
