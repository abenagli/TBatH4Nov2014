/*******************************************************************************
THIS PROGRAM READ THE RAW DATA AND PRODUCE THE RECO FILE USED FOR THE ANALYSIS
*******************************************************************************/

#include "analysis_tools.h"
#include "init_tree_H4.h"
#include "init_tree_reco.h"
#include "waveform.h"
#include "setTDRStyle.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "TFile.h"
#include "TChain.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TApplication.h"



int main (int argc, char** argv)
{  
  std::cout<<"--------> STUDYWAVEFORM: READ UNPACKED+DQM DATA AND PRODUCE RECO TREE <--------"<<std::endl;
  
  
  //--------Read Options--------------------------------
  ifstream inputCfg (argv[1], std::ios::in);
  std::string inputFolderUnpacked = argv[2];
  std::string inputFolderDQM = argv[3];
  std::string outputLabel = argv[4];
  int entry = atoi(argv[5]);
  setTDRStyle();
  
  std::cout << "--------------------------------" << std::endl;
  std::cout << "inputCfg: "            << argv[1] << std::endl;
  std::cout << "inputFolderUnpacked: " << argv[2] << std::endl;
  std::cout << "inputFolderDQM: "      << argv[3] << std::endl;
  std::cout << "outputLabel: "         << argv[4] << std::endl;
  std::cout << "entry: "               << argv[5] << std::endl;
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
    
    
    //-----Define variables--------------------------------------------------------
    std::map<int,Waveform*> waveforms_trg;
    std::map<int,Waveform*> waveforms;
    
    
    //-----Data loop--------------------------------------------------------
    int nEntries = treeUnpacked -> GetEntries();
    std::cout << ">>> reading entry: " << entry << " / " << nEntries << std::endl;
    
    //---Clear and initialize variables
    for(unsigned int iGr = 0; iGr < 4; ++iGr)
    {
      waveforms_trg[iGr] = new Waveform();
    }
    for(unsigned int iCh = 0; iCh < 32; ++iCh)
    {
      waveforms[iCh] = new Waveform();
    }
    
    //---Read the entry
    treeUnpacked->GetEntry(entry);
    treeDQM->GetEntry(entry);
    
    if( (unpackedTV.runNumber != DQMTV.runNumber) ||
        (unpackedTV.spillNumber != DQMTV.spillNumber) ||
        (unpackedTV.evtNumber != DQMTV.evtNumber) )
    {
      std::cout << "!!! ERROR: unpacked / DQM tree event mismatch. Continuing..." << std::endl;
      continue;
    }
    
    //---Read digitizer samples
    for(unsigned int iSample = 0; iSample < unpackedTV.nDigiSamples; ++iSample)
    {
      // digitized trigger
      if( unpackedTV.digiChannel[iSample] == 8 )
      {
        int triggerId = unpackedTV.digiGroup[iSample];
        
        if( waveforms_trg[triggerId]->getNSamples() < 1000 )
          waveforms_trg[triggerId] -> addTimeAndSample(waveforms_trg[triggerId]->getNSamples()/FSAMPLE,unpackedTV.digiSampleValue[iSample]);        
      }
      // digitizer channels
      else
      {
        int digiId = unpackedTV.digiGroup[iSample]*9 + unpackedTV.digiChannel[iSample] - unpackedTV.digiGroup[iSample];
        int planaconId = GetPlanaconId(digiId,runNumber);
        if( planaconId == -1 ) continue;
        
        if( waveforms[planaconId]->getNSamples() < 1000 )
          waveforms[planaconId] -> addTimeAndSample(waveforms[planaconId]->getNSamples()/FSAMPLE,unpackedTV.digiSampleValue[iSample]);
      }
    }
    
    //---Draw the waveform
    TApplication* theApp = new TApplication("App",&argc,argv);
    std::map<int,TCanvas*> c;
    
    for(unsigned int iGr = 0; iGr < 4; ++iGr)
    {
      // int sampleMin_ped = 5;
      // int sampleMax_ped = 54;
      // int sampleMax_sig = 250;
      // if( iGr == 0 ) { sampleMax_ped = 14; sampleMax_sig = 150; }
      // int sampleMin_sig = sampleMax_ped+1;
      
      // //---Compute quantities
      // Waveform::baseline_informations wave_ped;
      // Waveform::max_amplitude_informations wave_max;
      // wave_ped = waveforms[iGr] -> baseline(sampleMin_ped,sampleMax_ped); //use 50 samples between 5-54 to get pedestal and RMS
      // waveforms[iGr] -> offset(wave_ped.pedestal);
      // waveforms[iGr] -> rescale(-1);
      // wave_ped = waveforms[iGr] -> baseline(sampleMin_ped,sampleMax_ped); //use 50 samples between 5-54 to get pedestal and RMS
      // wave_max = waveforms[iGr] -> max_amplitude(sampleMin_sig,sampleMax_sig,5); //find max amplitude between 50 and 900 samples
      
      c[iGr] = new TCanvas(Form("c_trg_gr%02d",iGr),Form("c_trg_gr%02d",iGr));
      TGraph* graph = waveforms_trg[iGr] -> getGraph();
      graph -> SetMarkerSize(0.5);
      graph -> GetXaxis() -> SetRangeUser(0.,200.);
      graph -> Draw("APL");
      
      const float t1 = 140.;
      const float t2 = 180.;
      const float frac = 0.5;
      double trg_time = waveforms_trg[iGr]->trg_time_at_frac(t1,t2,frac,3);
    }
    
    // for(unsigned int iCh = 0; iCh < 32; ++iCh)
    // {
    //   int sampleMin_ped = 5;
    //   int sampleMax_ped = 54;
    //   int sampleMax_sig = 250;
    //   if( iCh == 0 ) { sampleMax_ped = 14; sampleMax_sig = 150; }
    //   int sampleMin_sig = sampleMax_ped+1;
      
    //   //---Compute quantities
    //   Waveform::baseline_informations wave_ped;
    //   Waveform::max_amplitude_informations wave_max;
    //   wave_ped = waveforms[iCh] -> baseline(sampleMin_ped,sampleMax_ped); //use 50 samples between 5-54 to get pedestal and RMS
    //   waveforms[iCh] -> offset(wave_ped.pedestal);
    //   waveforms[iCh] -> rescale(-1);
    //   wave_ped = waveforms[iCh] -> baseline(sampleMin_ped,sampleMax_ped); //use 50 samples between 5-54 to get pedestal and RMS
    //   wave_max = waveforms[iCh] -> max_amplitude(sampleMin_sig,sampleMax_sig,5); //find max amplitude between 50 and 900 samples
      
    //   c[iCh] = new TCanvas(Form("c_ch%02d",iCh),Form("c_ch%02d",iCh));
    //   TGraph* graph = waveforms[iCh] -> getGraph();
    //   graph -> SetMarkerSize(0.5);
    //   graph -> GetXaxis() -> SetRangeUser(0.,50.);
    //   graph -> Draw("APL");
      
    //   //---Draw lines
    //   c[iCh] -> cd();
      
    //   TLine* line_ped = new TLine(sampleMin_ped/FSAMPLE,wave_ped.pedestal,sampleMax_ped/FSAMPLE,wave_ped.pedestal);
    //   line_ped -> SetLineWidth(3);
    //   line_ped -> SetLineColor(kRed);
    //   line_ped -> Draw("same");
      
    //   float amp_DQM = DQMTV.digi_pedestal->at(iCh) - DQMTV.digi_max_amplitude->at(iCh);
    //   float time_max_DQM = DQMTV.digi_time_at_max->at(iCh);
    //   float time_frac50_DQM = DQMTV.digi_time_at_frac50->at(iCh);
      
    //   TLine* line_max = new TLine(sampleMin_sig/FSAMPLE,wave_max.max_amplitude,sampleMax_sig/FSAMPLE,wave_max.max_amplitude);
    //   line_max -> SetLineWidth(3);
    //   line_max -> SetLineColor(kBlue);
    //   line_max -> Draw("same");
      
    //   TLine* line_time_max = new TLine(wave_max.time_at_max,0.,wave_max.time_at_max,wave_max.max_amplitude);
    //   line_time_max -> SetLineWidth(3);
    //   line_time_max -> SetLineColor(kBlue);
    //   line_time_max -> Draw("same");
      
    //   // TLine* line_time_frac50 = new TLine(time_frac50_DQM,dummy.first,time_frac50_DQM,amp_DQM);
    //   // line_time_frac50 -> SetLineWidth(3);
    //   // line_time_frac50 -> SetLineColor(kGreen);
    //   // line_time_frac50 -> Draw("same");
    // }
    
    
    //---Get ready for next run
    theApp -> Run();
    treeUnpacked->Delete();
    treeDQM->Delete();
  }
  
  
  //---------Done-----------------------------------------------------------------
}
