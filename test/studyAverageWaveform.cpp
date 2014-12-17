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
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TChain.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLine.h"



int main (int argc, char** argv)
{  
  std::cout<<"--------> STUDYAVERAGEWAVEFORM: READ UNPACKED+DQM DATA AND PRODUCE RECO TREE <--------"<<std::endl;
  
  
  //--------Read Options--------------------------------
  ifstream inputCfg (argv[1], std::ios::in);
  std::string inputFolderUnpacked = argv[2];
  std::string inputFolderDQM = argv[3];
  std::string outputLabel = argv[4];
  int withMCP = atoi(argv[5]);
  int entriesMax = atoi(argv[6]);
  setTDRStyle();
  
  std::cout << "--------------------------------" << std::endl;
  std::cout << "inputCfg: "            << argv[1] << std::endl;
  std::cout << "inputFolderUnpacked: " << argv[2] << std::endl;
  std::cout << "inputFolderDQM: "      << argv[3] << std::endl;
  std::cout << "outputLabel: "         << argv[4] << std::endl;
  std::cout << "withMCP: "             << argv[5] << std::endl;
  std::cout << "entriesMax: "          << argv[6] << std::endl;
  std::cout << "--------------------------------" << std::endl;
  
  
  //-------start to read the cfg file--------
  int runNumber =-999, beamE = -999, HV = -999;
  float tableX = -999., tableY = -999.;
  
  
  //-------define output file and histograms--------
  TFile* outputFile = TFile::Open(Form("plots/plots_studyAverageWaveform_%s.root",outputLabel.c_str()),"RECREATE");  
  outputFile -> cd();
  for(int iEntry = 0; iEntry < 20; ++iEntry)
  {
    outputFile -> cd();
    outputFile -> mkdir(Form("evt%d",iEntry));
    outputFile -> cd(Form("evt%d",iEntry));
  }
  outputFile -> cd();
  
  std::map<int,TH1F*> h_ped;
  std::map<int,TH1F*> h_charge;
  std::map<int,TH1F*> h_amp;
  std::map<int,TH1F*> h_time;
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    h_ped[iCh]    = new TH1F(Form("h_ped_ch%02d",iCh),   "",4000.,    0., 4000.);
    h_charge[iCh] = new TH1F(Form("h_charge_ch%02d",iCh),"",2500.,-5000.,20000.);
    h_amp[iCh]    = new TH1F(Form("h_amp_ch%02d",iCh),"",   4000.,    0., 4000.);
    h_time[iCh]   = new TH1F(Form("h_time_ch%02d",iCh),  "",1000.,0.,200.);
  }
  
  TH2F* h2_beamPosition_TDC = new TH2F("h2_beamPosition_TDC","",100,-240,-140.,100,-146,-46.);
  TH2F* h2_beamPosition_hodo11 = new TH2F("h2_beamPosition_hodo11","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_hodo22 = new TH2F("h2_beamPosition_hodo22","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_hodo12 = new TH2F("h2_beamPosition_hodo12","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_hodo21 = new TH2F("h2_beamPosition_hodo21","",160,-210.,-130.,160,-155.,-75.);
  
  TH2F* h2_beamPosition_MCP_TDC = new TH2F("h2_beamPosition_MCP_TDC","",100,-240,-140.,100,-146,-46.);
  TH2F* h2_beamPosition_MCP_hodo11 = new TH2F("h2_beamPosition_MCP_hodo11","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_MCP_hodo22 = new TH2F("h2_beamPosition_MCP_hodo22","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_MCP_hodo12 = new TH2F("h2_beamPosition_MCP_hodo12","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_MCP_hodo21 = new TH2F("h2_beamPosition_MCP_hodo21","",160,-210.,-130.,160,-155.,-75.);
  
  std::map<int,TProfile*> p_aveWaveform;
  std::map<int,TProfile*> p_aveWaveform_ampNorm1;
  std::map<int,TProfile*> p_aveWaveform_chargeNorm1;
  std::map<int,TProfile*> p_aveWaveform_trgTimeShift;
  std::map<int,TProfile*> p_aveWaveform_trgTimeShift_ampNorm1;
  std::map<int,TProfile*> p_aveWaveform_trgTimeShift_chargeNorm1;
  std::map<int,TProfile*> p_aveWaveform_trgTimeFitShift;
  std::map<int,TProfile*> p_aveWaveform_trgTimeFitShift_ampNorm1;
  std::map<int,TProfile*> p_aveWaveform_trgTimeFitShift_chargeNorm1;
  std::map<int,TProfile*> p_aveWaveform_MCPTimeShift;
  std::map<int,TProfile*> p_aveWaveform_MCPTimeShift_ampNorm1;
  std::map<int,TProfile*> p_aveWaveform_MCPTimeShift_chargeNorm1;
  for(unsigned int iCh = 0; iCh < 32; ++iCh)
  {
    p_aveWaveform[iCh]             = new TProfile(Form("p_aveWaveform_ch%02d",iCh),            "",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_ampNorm1[iCh]    = new TProfile(Form("p_aveWaveform_ampNorm1_ch%02d",iCh),   "",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_chargeNorm1[iCh] = new TProfile(Form("p_aveWaveform_chargeNorm1_ch%02d",iCh),"",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_trgTimeShift[iCh]             = new TProfile(Form("p_aveWaveform_trgTimeShift_ch%02d",iCh),            "",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_trgTimeShift_ampNorm1[iCh]    = new TProfile(Form("p_aveWaveform_trgTimeShift_ampNorm1_ch%02d",iCh),   "",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_trgTimeShift_chargeNorm1[iCh] = new TProfile(Form("p_aveWaveform_trgTimeShift_chargeNorm1_ch%02d",iCh),"",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_trgTimeFitShift[iCh]             = new TProfile(Form("p_aveWaveform_trgTimeFitShift_ch%02d",iCh),            "",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_trgTimeFitShift_ampNorm1[iCh]    = new TProfile(Form("p_aveWaveform_trgTimeFitShift_ampNorm1_ch%02d",iCh),   "",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_trgTimeFitShift_chargeNorm1[iCh] = new TProfile(Form("p_aveWaveform_trgTimeFitShift_chargeNorm1_ch%02d",iCh),"",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_MCPTimeShift[iCh]             = new TProfile(Form("p_aveWaveform_MCPTimeShift_ch%02d",iCh),            "",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_MCPTimeShift_ampNorm1[iCh]    = new TProfile(Form("p_aveWaveform_MCPTimeShift_ampNorm1_ch%02d",iCh),   "",2000,-1000./FSAMPLE,1000./FSAMPLE);
    p_aveWaveform_MCPTimeShift_chargeNorm1[iCh] = new TProfile(Form("p_aveWaveform_MCPTimeShift_chargeNorm1_ch%02d",iCh),"",2000,-1000./FSAMPLE,1000./FSAMPLE);
  }
  
  
  //-------loop over runs--------
  std::string line, buffer;
  std::map<int,int> savedEntries;
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
    if( entriesMax >= 0 ) nEntries = entriesMax;
    for(int iEntry = 0; iEntry < nEntries; ++iEntry)
    {
      if( iEntry%100 == 0 ) std::cout << ">>> reading entry: " << iEntry << " / " << nEntries << std::endl;
      
      
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
      treeUnpacked->GetEntry(iEntry);
      treeDQM->GetEntry(iEntry);
      
      if( (unpackedTV.runNumber != DQMTV.runNumber) ||
          (unpackedTV.spillNumber != DQMTV.spillNumber) ||
          (unpackedTV.evtNumber != DQMTV.evtNumber) )
      {
        std::cout << "!!! ERROR: unpacked / DQM tree event mismatch. Continuing..." << std::endl;
        continue;
      }
      
      
      //---Reconstruct beam position
      float beamX_TDC = -tableX + (*DQMTV.TDCreco)[0];
      float beamY_TDC = -tableY + (*DQMTV.TDCreco)[1];
      h2_beamPosition_TDC -> Fill(beamX_TDC,beamY_TDC);
      
      unsigned int nHodoX1 = 0;
      unsigned int nHodoY1 = 0;
      unsigned int nHodoX2 = 0;
      unsigned int nHodoY2 = 0;
      int* vHodoX1 = new int[64];
      int* vHodoY1 = new int[64];
      int* vHodoX2 = new int[64];
      int* vHodoY2 = new int[64];
      for(int iCh = 0; iCh < 64; ++iCh)
      {
        if( DQMTV.HODOX1->at(iCh) ) { vHodoX1[nHodoX1] = iCh; ++nHodoX1; }
        if( DQMTV.HODOY1->at(iCh) ) { vHodoY1[nHodoY1] = iCh; ++nHodoY1; }
        if( DQMTV.HODOX2->at(iCh) ) { vHodoX2[nHodoX2] = iCh; ++nHodoX2; }
        if( DQMTV.HODOY2->at(iCh) ) { vHodoY2[nHodoY2] = iCh; ++nHodoY2; }
      }
      float hodoX1 = GetHodoWire(nHodoX1,vHodoX1);
      float hodoY1 = GetHodoWire(nHodoY1,vHodoY1);
      float hodoX2 = GetHodoWire(nHodoX2,vHodoX2);
      float hodoY2 = GetHodoWire(nHodoY2,vHodoY2);
      float beamX_hodo1 = hodoX1 >= 0 ? -tableX + 0.5*hodoX1 : -999;
      float beamY_hodo1 = hodoY1 >= 0 ? -tableY - 0.5*hodoY1 : -999;
      float beamX_hodo2 = hodoX2 >= 0 ? -tableX + 0.5*hodoX2 : -999;
      float beamY_hodo2 = hodoY2 >= 0 ? -tableY - 0.5*hodoY2 : -999;
      h2_beamPosition_hodo11 -> Fill(beamX_hodo1,beamY_hodo1);
      h2_beamPosition_hodo22 -> Fill(beamX_hodo2,beamY_hodo2);
      h2_beamPosition_hodo12 -> Fill(beamX_hodo1,beamY_hodo2);
      h2_beamPosition_hodo21 -> Fill(beamX_hodo2,beamY_hodo1);
      
      
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
      
      std::map<int,int> channelSignal;
      std::map<int,double> amps;
      std::map<int,double> charges;
      std::map<int,double> times;
      for(unsigned int iCh = 0; iCh < 32; ++iCh)
      {
        int sampleMin_ped = 5;
        int sampleMax_ped = 54;
        int sampleMax_sig = 250;
        if( withMCP == 1 && iCh == 0 ) { sampleMax_ped = 14; sampleMax_sig = 150; }
        int sampleMin_sig = sampleMax_ped+1;
        
        //---Compute quantities
        Waveform::baseline_informations wave_ped;
        Waveform::max_amplitude_informations wave_max;
        wave_ped = waveforms[iCh] -> baseline(sampleMin_ped,sampleMax_ped); //use 15 samples between 5-14 to get pedestal and RMS
        
        h_ped[iCh] -> Fill( wave_ped.pedestal );
        
        waveforms[iCh] -> offset(wave_ped.pedestal);
        waveforms[iCh] -> rescale(-1);
        wave_ped = waveforms[iCh] -> baseline(sampleMin_ped,sampleMax_ped);
        wave_max = waveforms[iCh] -> max_amplitude(sampleMin_sig,sampleMax_sig,5); //find max amplitude between 15 and 150 samples
        
        amps[iCh] = wave_max.max_amplitude;
        charges[iCh] = waveforms[iCh]->charge_integrated(sampleMin_sig,sampleMax_sig);
        times[iCh] = wave_max.time_at_max;
        h_amp[iCh]    -> Fill( amps[iCh]  );
        h_charge[iCh] -> Fill( charges[iCh] );
        h_time[iCh]   -> Fill( times[iCh] );
        
        if( withMCP && iCh == 0 )
        {
          if( charges[iCh] > 1000. ) channelSignal[iCh] = 1;
        }
        else
        {
          if( amps[iCh] > 300. && amps[iCh] < 3000. ) channelSignal[iCh] = 1;
        }
        
        
        //---Save single waveforms for the first 20 events
        if( channelSignal[iCh] == 1 && savedEntries[iCh] < 20 )
        {
          outputFile -> cd(Form("evt%d",savedEntries[iCh]));
          TGraph* graph = waveforms[iCh] -> getGraph();
          graph -> Write(Form("g_waveform_ch%02d",iCh));
          delete graph;
          
          savedEntries[iCh] += 1;
          outputFile -> cd();
        }
      }
      
      
      
      //---Fit trigger times
      std::map<int,double> trgTime;
      std::map<int,double> trgTimeFit;
      for(int iGr = 0; iGr < 4; ++iGr)
      {
        const float t1 = 140.;
        const float t2 = 180.;
        const float frac = 0.5;
        trgTime[iGr] = waveforms_trg[iGr]->trg_time_at_frac(t1,t2,frac,3) - 165.;
        
        TF1* fitFunc = new TF1(Form("trgFitFunc_gr%02d",iGr),"[0]+[1]/(exp((x-[2])/[3])+1)",0.,200.);
        fitFunc -> SetParameters(0.,2200.,165.,1.);
        TGraph* graph = waveforms_trg[iGr] -> getGraph();
        graph -> Fit(Form("trgFitFunc_gr%02d",iGr),"QNRS+");
        trgTimeFit[iGr] = fitFunc -> GetParameter(2) - 165;
      }
      
      
      //---Shift signals with trigger time
      for(unsigned int iCh = 0; iCh < 32; ++iCh)
      {        
        if( channelSignal[iCh] )
        {
          std::vector<double> x = waveforms[iCh] -> _times;
          std::vector<double> y = waveforms[iCh] -> _samples;
          
          for(unsigned int sampleIt = 0; sampleIt < x.size(); ++sampleIt)
          {
            p_aveWaveform[iCh]             -> Fill(x[sampleIt],y[sampleIt]);
            p_aveWaveform_ampNorm1[iCh]    -> Fill(x[sampleIt],y[sampleIt]/amps[iCh]);
            p_aveWaveform_chargeNorm1[iCh] -> Fill(x[sampleIt],y[sampleIt]/charges[iCh]);
            p_aveWaveform_trgTimeShift[iCh]             -> Fill(x[sampleIt]-trgTime[iCh/8],y[sampleIt]);
            p_aveWaveform_trgTimeShift_ampNorm1[iCh]    -> Fill(x[sampleIt]-trgTime[iCh/8],y[sampleIt]/amps[iCh]);
            p_aveWaveform_trgTimeShift_chargeNorm1[iCh] -> Fill(x[sampleIt]-trgTime[iCh/8],y[sampleIt]/charges[iCh]);
            p_aveWaveform_trgTimeFitShift[iCh]             -> Fill(x[sampleIt]-trgTimeFit[iCh/8],y[sampleIt]);
            p_aveWaveform_trgTimeFitShift_ampNorm1[iCh]    -> Fill(x[sampleIt]-trgTimeFit[iCh/8],y[sampleIt]/amps[iCh]);
            p_aveWaveform_trgTimeFitShift_chargeNorm1[iCh] -> Fill(x[sampleIt]-trgTimeFit[iCh/8],y[sampleIt]/charges[iCh]);
          }
        }
      }
      
      
      //---Shift signals with MCP time
      if( withMCP && channelSignal[0] )
      {
        h2_beamPosition_MCP_TDC -> Fill(beamX_TDC,beamY_TDC);
        h2_beamPosition_MCP_hodo11 -> Fill(beamX_hodo1,beamY_hodo1);
        h2_beamPosition_MCP_hodo22 -> Fill(beamX_hodo2,beamY_hodo2);
        h2_beamPosition_MCP_hodo12 -> Fill(beamX_hodo1,beamY_hodo2);
        h2_beamPosition_MCP_hodo21 -> Fill(beamX_hodo2,beamY_hodo1);
        
        for(unsigned int iCh = 0; iCh < 32; ++iCh)
        {        
          std::vector<double> x = waveforms[iCh] -> _times;
          std::vector<double> y = waveforms[iCh] -> _samples;
          for(unsigned int sampleIt = 0; sampleIt < x.size(); ++sampleIt)
          {
            p_aveWaveform_MCPTimeShift[iCh]             -> Fill(x[sampleIt]-times[0],y[sampleIt]);
            p_aveWaveform_MCPTimeShift_ampNorm1[iCh]    -> Fill(x[sampleIt]-times[0],y[sampleIt]/amps[iCh]);
            p_aveWaveform_MCPTimeShift_chargeNorm1[iCh] -> Fill(x[sampleIt]-times[0],y[sampleIt]/charges[iCh]);
          }
        }
      }
      
      //---Clear and initialize variables
      for(unsigned int iGr = 0; iGr < 4; ++iGr)
      {
        delete waveforms_trg[iGr];
      }
      for(unsigned int iCh = 0; iCh < 32; ++iCh)
      {
        delete waveforms[iCh];
      }
    }
    
    //---Get ready for next run
    treeUnpacked->Delete();
    treeDQM->Delete();
  }
  
  //---------Done-----------------------------------------------------------------
  outputFile -> Write();
  outputFile -> Close();
}
