/*******************************************************************************
THIS PROGRAM READ THE RAW DATA AND PRODUCE THE RECO FILE USED FOR THE ANALYSIS
*******************************************************************************/

#include "analysis_tools.h"
#include "init_tree_H4.h"
#include "init_tree_reco.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "TFile.h"
#include "TChain.h"
#include "TGraph.h"



int main (int argc, char** argv)
{  
  std::cout<<"--------> DUMPER: READ UNPACKED+DQM DATA AND PRODUCE RECO TREE <--------"<<std::endl;
  
  
  //--------Read Options--------------------------------
  ifstream inputCfg (argv[1], std::ios::in);
  std::string inputFolderUnpacked = argv[2];
  std::string inputFolderDQM = argv[3];
  std::string outputLabel = argv[4];
  int entriesMax = atoi(argv[5]);
  int saveWaveforms = atoi(argv[6]);
  
  std::cout << "--------------------------------" << std::endl;
  std::cout << "inputCfg: "            << argv[1] << std::endl;
  std::cout << "inputFolderUnpacked: " << argv[2] << std::endl;
  std::cout << "inputFolderDQM: "      << argv[3] << std::endl;
  std::cout << "outputLabel: "         << argv[4] << std::endl;
  std::cout << "entriesMax: "          << argv[5] << std::endl;
  std::cout << "saveWaveforms: "       << argv[6] << std::endl;
  std::cout << "--------------------------------" << std::endl;
  
  
  //-------start to read the cfg file--------
  int runNumber =-999, beamE = -999, HV = -999;
  float tableX = -999., tableY = -999.;
  
  std::string line, buffer;
  while( !inputCfg.eof() )
  {
    getline(inputCfg,line,'\n');
    if( !inputCfg.good() ) break;
    if( line.at(0) == '#' ) continue;
    
    stringstream ss(line);
    ss >> runNumber >> beamE >> tableX >> tableY >> HV;
    
    TChain* treeUnpacked = new TChain("H4tree");
    TChain* treeDQM = new TChain("outputTree");
    UnpackedTreeVars unpackedTV;
    DQMTreeVars DQMTV;
    InitTreeUnpacked(treeUnpacked,unpackedTV);
    InitTreeDQM(treeDQM,DQMTV);
    
    char command1[300];
    sprintf(command1, "find  %s/%d/[0-9]*.root > listUnpacked.txt", (inputFolderUnpacked).c_str(), runNumber);
    system(command1);
    char command2[300];
    sprintf(command2, "find  %s/%d/dqmPlotstotal_*.root > listDQM.txt", (inputFolderDQM).c_str(), runNumber);
    system(command2);
    
    ifstream rootListUnpacked ("listUnpacked.txt");
    ifstream rootListDQM ("listDQM.txt");
    
    while( !rootListUnpacked.eof() && !rootListDQM.eof() )
    {
      std::string fileUnpacked;
      std::string fileDQM;
      rootListUnpacked >> fileUnpacked;
      rootListDQM >> fileDQM;
      
      if( !(rootListUnpacked.good() && rootListDQM.good()) ) break;
      
      TChain* treeUnpacked_temp = new TChain("H4tree");
      treeUnpacked_temp->Add(fileUnpacked.c_str());
      TChain* treeDQM_temp = new TChain("outputTree");
      treeDQM_temp->Add(fileDQM.c_str());
      
      if( treeDQM_temp->GetEntries() == treeUnpacked_temp->GetEntries() )
      {
        treeUnpacked->Add(fileUnpacked.c_str());
        treeDQM->Add(fileDQM.c_str());
        std::cout << "added file unpacked: " << fileUnpacked << std::endl;
        std::cout << "added file      DQM: " << fileDQM      << std::endl;
      }
      else
      {
        std::cout << "!!! Bad spill found... Skipped !!!" << std::endl;
      }
      
      treeUnpacked_temp->Delete();
      treeDQM_temp->Delete();
    }
    
    system("rm listUnpacked.txt");
    system("rm listDQM.txt");
    
    std::cout << "start reading run  " << runNumber << std::endl;
    
    
    //---------output tree----------------
    TFile* outputFileTree = TFile::Open(Form("ntuples/reco_%s_run%d.root",outputLabel.c_str(),runNumber),"RECREATE");  
    TFile* outputFileWaveforms;
    if( saveWaveforms ) outputFileWaveforms = TFile::Open(Form("ntuples/waveforms_%s_run%d.root",outputLabel.c_str(),runNumber),"RECREATE");  
    
    outputFileTree->cd();
    TTree* recoTree = new TTree("ntu","ntu");
    recoTree -> SetDirectory(0);
    RecoTreeVars recoTV;
    SetRecoTree(recoTree,recoTV);
    
    
    //-----Data loop--------------------------------------------------------
    int nEntries = treeUnpacked -> GetEntries();
    if( entriesMax < 0 ) entriesMax = nEntries;
    for(int iEntry = 0; iEntry < entriesMax; ++iEntry)
    {
      if( iEntry%100 == 0 ) std::cout << ">>> reading entry: " << iEntry << " / " << nEntries << std::endl;
      
      //---Read the entry
      treeUnpacked->GetEntry(iEntry);
      treeDQM->GetEntry(iEntry);
      
      if( (unpackedTV.runNumber != DQMTV.runNumber) ||
          (unpackedTV.spillNumber != DQMTV.spillNumber) ||
          (unpackedTV.evtNumber != DQMTV.evtNumber) )
      {
        std::cout << "!!! ERROR: unpacked / DQM tree event mismatch. Continuing..." << std::endl;
        continue;
      }
      
      ClearRecoTreeVars(recoTV);
      
      recoTV.runNumber = unpackedTV.runNumber;
      recoTV.spillNumber = unpackedTV.spillNumber;
      recoTV.evtNumber = unpackedTV.evtNumber;
      recoTV.beamE = beamE;
      recoTV.tableX = tableX;
      recoTV.tableY = tableY;
      recoTV.HV = HV;
      
      if( iEntry < 10 && saveWaveforms )
      {
        TGraph** g_waveform = new TGraph*[32];
        for(unsigned int iCh = 0; iCh < 32; ++iCh)
        {
          g_waveform[iCh] = new TGraph();
        }
        
        //---Read digitizer samples
        for(unsigned int iSample = 0; iSample < unpackedTV.nDigiSamples; ++iSample)
        {
          if( unpackedTV.digiChannel[iSample] == 8 ) continue; // skip digitized trigger
          int digiId = unpackedTV.digiGroup[iSample]*9 + unpackedTV.digiChannel[iSample] - unpackedTV.digiGroup[iSample];
          int planaconId = GetPlanaconId(digiId,runNumber);
          if( planaconId == -1 ) continue;
          g_waveform[planaconId] -> SetPoint(g_waveform[planaconId]->GetN(),g_waveform[planaconId]->GetN()*0.2,unpackedTV.digiSampleValue[iSample]);
        }
        
        outputFileWaveforms -> cd();
        outputFileWaveforms -> mkdir(Form("evt%d",recoTV.evtNumber));
        outputFileWaveforms -> cd(Form("evt%d",recoTV.evtNumber));
        for(unsigned int iCh = 0; iCh < 32; ++iCh)
        {
          g_waveform[iCh] -> Write(Form("g_waveform_ch%02d",iCh));
          delete g_waveform[iCh];
        }
      }
      
      for(int iCh = 0; iCh < 32; ++iCh)
      {
        int planaconId = GetPlanaconId(iCh,runNumber);
        if( planaconId == -1 ) continue;
        recoTV.ped_DQM[planaconId]         = DQMTV.digi_pedestal->at(iCh);
        recoTV.charge_DQM[planaconId]      = DQMTV.digi_charge_integrated->at(iCh);
        recoTV.amp_DQM[planaconId]         = DQMTV.digi_max_amplitude->at(iCh);
        recoTV.time_max_DQM[planaconId]    = DQMTV.digi_time_at_max->at(iCh);
        recoTV.time_frac50_DQM[planaconId] = DQMTV.digi_time_at_frac50->at(iCh);
      }
      
      recoTV.tdcX = (*DQMTV.TDCreco)[0];
      recoTV.tdcY = (*DQMTV.TDCreco)[1];
      
      unsigned int nHodoX1 = 0;
      unsigned int nHodoY1 = 0;
      unsigned int nHodoX2 = 0;
      unsigned int nHodoY2 = 0;
      for(int iCh = 0; iCh < 64; ++iCh)
      {
        if( DQMTV.HODOX1->at(iCh) ) { recoTV.hodoX1[nHodoX1] = iCh; ++nHodoX1; }
        if( DQMTV.HODOY1->at(iCh) ) { recoTV.hodoY1[nHodoY1] = iCh; ++nHodoY1; }
        if( DQMTV.HODOX2->at(iCh) ) { recoTV.hodoX2[nHodoX2] = iCh; ++nHodoX2; }
        if( DQMTV.HODOY2->at(iCh) ) { recoTV.hodoY2[nHodoY2] = iCh; ++nHodoY2; }
      }
      recoTV.nHodoX1 = nHodoX1;
      recoTV.nHodoY1 = nHodoY1;
      recoTV.nHodoX2 = nHodoX2;
      recoTV.nHodoY2 = nHodoY2;
      
      recoTree->Fill();
    }
    
    
    //-----close everything-----------------------------------------------------
    recoTree->Write();
    outputFileTree->Close();
    if( saveWaveforms ) outputFileWaveforms->Close();
    
    
    //---Get ready for next run
    treeUnpacked->Delete();
    treeDQM->Delete();
  }
  
  
  //---------Done-----------------------------------------------------------------
}
