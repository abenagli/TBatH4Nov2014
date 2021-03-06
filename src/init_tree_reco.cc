#include "init_tree_reco.h"



void InitRecoTree(TTree* nt, RecoTreeVars& treeVars)
{
  nt -> SetBranchStatus("*", 0);
  nt -> SetBranchStatus("runNumber",       1); nt -> SetBranchAddress("runNumber",       &treeVars.runNumber);
  nt -> SetBranchStatus("spillNumber",     1); nt -> SetBranchAddress("spillNumber",     &treeVars.spillNumber);
  nt -> SetBranchStatus("evtNumber",       1); nt -> SetBranchAddress("evtNumber",       &treeVars.evtNumber);
  nt -> SetBranchStatus("beamE",           1); nt -> SetBranchAddress("beamE",           &treeVars.beamE);
  nt -> SetBranchStatus("tableX",          1); nt -> SetBranchAddress("tableX",          &treeVars.tableX);
  nt -> SetBranchStatus("tableY",          1); nt -> SetBranchAddress("tableY",          &treeVars.tableY);
  nt -> SetBranchStatus("HV",              1); nt -> SetBranchAddress("HV",              &treeVars.HV);
  nt -> SetBranchStatus("ped_DQM",         1); nt -> SetBranchAddress("ped_DQM",         &treeVars.ped_DQM);
  nt -> SetBranchStatus("charge_DQM",      1); nt -> SetBranchAddress("charge_DQM",      &treeVars.charge_DQM);
  nt -> SetBranchStatus("amp_DQM",         1); nt -> SetBranchAddress("amp_DQM",         &treeVars.amp_DQM);
  nt -> SetBranchStatus("time_max_DQM",    1); nt -> SetBranchAddress("time_max_DQM",    &treeVars.time_max_DQM);
  nt -> SetBranchStatus("time_frac50_DQM", 1); nt -> SetBranchAddress("time_frac50_DQM", &treeVars.time_frac50_DQM);
  nt -> SetBranchStatus("ped",             1); nt -> SetBranchAddress("ped",             &treeVars.ped);
  nt -> SetBranchStatus("charge",          1); nt -> SetBranchAddress("charge",          &treeVars.charge);
  nt -> SetBranchStatus("amp_max",         1); nt -> SetBranchAddress("amp_max",         &treeVars.amp_max);
  nt -> SetBranchStatus("amp_fit",         1); nt -> SetBranchAddress("amp_fit",         &treeVars.amp_fit);
  nt -> SetBranchStatus("time_max",        1); nt -> SetBranchAddress("time_max",        &treeVars.time_max);
  nt -> SetBranchStatus("time_CF",         1); nt -> SetBranchAddress("time_CF",         &treeVars.time_CF);
  nt -> SetBranchStatus("time_fit",        1); nt -> SetBranchAddress("time_fit",        &treeVars.time_fit);
  nt -> SetBranchStatus("tdcX",            1); nt -> SetBranchAddress("tdcX",            &treeVars.tdcX);
  nt -> SetBranchStatus("tdcY",            1); nt -> SetBranchAddress("tdcY",            &treeVars.tdcY);
  nt -> SetBranchStatus("nHodoX1",         1); nt -> SetBranchAddress("nHodoX1",         &treeVars.nHodoX1);
  nt -> SetBranchStatus("nHodoY1",         1); nt -> SetBranchAddress("nHodoY1",         &treeVars.nHodoY1);
  nt -> SetBranchStatus("nHodoX2",         1); nt -> SetBranchAddress("nHodoX2",         &treeVars.nHodoX2);
  nt -> SetBranchStatus("nHodoY2",         1); nt -> SetBranchAddress("nHodoY2",         &treeVars.nHodoY2);
  nt -> SetBranchStatus("hodoX1",          1); nt -> SetBranchAddress("hodoX1",          &treeVars.hodoX1);
  nt -> SetBranchStatus("hodoY1",          1); nt -> SetBranchAddress("hodoY1",          &treeVars.hodoY1);
  nt -> SetBranchStatus("hodoX2",          1); nt -> SetBranchAddress("hodoX2",          &treeVars.hodoX2);
  nt -> SetBranchStatus("hodoY2",          1); nt -> SetBranchAddress("hodoY2",          &treeVars.hodoY2);
}

void SetRecoTree(TTree* nt, RecoTreeVars& treeVars)
{
  nt -> Branch("runNumber",       &treeVars.runNumber,                 "runNumber/I");
  nt -> Branch("spillNumber",     &treeVars.spillNumber,             "spillNumber/I");
  nt -> Branch("evtNumber",       &treeVars.evtNumber,                 "evtNumber/I");
  nt -> Branch("beamE",           &treeVars.beamE,                         "beamE/I");
  nt -> Branch("tableX",          &treeVars.tableX,                       "tableX/F");
  nt -> Branch("tableY",          &treeVars.tableY,                       "tableY/F");
  nt -> Branch("HV",              &treeVars.HV,                               "HV/I");
  nt -> Branch("ped_DQM",         &treeVars.ped_DQM,                 "ped_DQM[32]/F");
  nt -> Branch("charge_DQM",      &treeVars.charge_DQM,           "charge_DQM[32]/F"); 
  nt -> Branch("amp_DQM",         &treeVars.amp_DQM,                 "amp_DQM[32]/F");
  nt -> Branch("time_max_DQM",    &treeVars.time_max_DQM,       "time_max_DQM[32]/F");
  nt -> Branch("time_frac50_DQM", &treeVars.time_frac50_DQM, "time_frac50_DQM[32]/F");
  nt -> Branch("ped",             &treeVars.ped,                         "ped[32]/F");
  nt -> Branch("charge",          &treeVars.charge,                   "charge[32]/F"); 
  nt -> Branch("amp_max",         &treeVars.amp_max,                 "amp_max[32]/F");
  nt -> Branch("amp_fit",         &treeVars.amp_fit,                 "amp_fit[32]/F");
  nt -> Branch("time_max",        &treeVars.time_max,               "time_max[32]/F");
  nt -> Branch("time_CF",         &treeVars.time_CF,                 "time_CF[32]/F");
  nt -> Branch("time_fit",        &treeVars.time_fit,               "time_fit[32]/F");
  nt -> Branch("tdcX",            &treeVars.tdcX,                           "tdcX/F");
  nt -> Branch("tdcY",            &treeVars.tdcY,                           "tdcY/F");
  nt -> Branch("nHodoX1",         &treeVars.nHodoX1,                     "nHodoX1/i");
  nt -> Branch("nHodoY1",         &treeVars.nHodoY1,                     "nHodoY1/i");
  nt -> Branch("nHodoX2",         &treeVars.nHodoX2,                     "nHodoX2/i");
  nt -> Branch("nHodoY2",         &treeVars.nHodoY2,                     "nHodoY2/i");
  nt -> Branch("hodoX1",          &treeVars.hodoX1[0],                "hodoX1[64]/I");
  nt -> Branch("hodoY1",          &treeVars.hodoY1[0],                "hodoY1[64]/I");
  nt -> Branch("hodoX2",          &treeVars.hodoX2[0],                "hodoX2[64]/I");
  nt -> Branch("hodoY2",          &treeVars.hodoY2[0],                "hodoY2[64]/I");
}

void ClearRecoTreeVars(RecoTreeVars& treeVars)
{
  treeVars.runNumber = -999;
  treeVars.spillNumber = -999;
  treeVars.evtNumber = -999;
  treeVars.beamE = -999;
  treeVars.tableX = -999.;
  treeVars.tableY = -999.;
  treeVars.HV = -999;
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    treeVars.ped_DQM[iCh] = -999.;
    treeVars.charge_DQM[iCh] = -999.;
    treeVars.amp_DQM[iCh] = -999.;
    treeVars.time_max_DQM[iCh] = -999.;
    treeVars.time_frac50_DQM[iCh] = -999.;
    treeVars.ped[iCh] = -999.;
    treeVars.charge[iCh] = -999.;
    treeVars.amp_max[iCh] = -999.;
    treeVars.amp_fit[iCh] = -999.;
    treeVars.time_max[iCh] = -999.;
    treeVars.time_CF[iCh] = -999.;
    treeVars.time_fit[iCh] = -999.;
  }
  treeVars.tdcX = -999.;
  treeVars.tdcY = -999.;
  treeVars.nHodoX1 = 0;
  treeVars.nHodoY1 = 0;
  treeVars.nHodoX2 = 0;
  treeVars.nHodoY2 = 0;
  for(int iCh = 0; iCh < 64; ++iCh)
  {
    treeVars.hodoX1[iCh] = -999;
    treeVars.hodoY1[iCh] = -999;
    treeVars.hodoX2[iCh] = -999;
    treeVars.hodoY2[iCh] = -999;
  }
}
