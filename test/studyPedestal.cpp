/*******************************************************************************
THIS PROGRAM READ THE RAW DATA AND PRODUCE THE RECO FILE USED FOR THE ANALYSIS
*******************************************************************************/

#include "analysis_tools.h"
#include "init_tree_H4.h"
#include "init_tree_reco.h"
#include "waveform.h"

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
  std::cout<<"--------> STUDYPEDESTAL: READ UNPACKED+DQM DATA AND PRODUCE RECO TREE <--------"<<std::endl;
  
  
  //--------Read Options--------------------------------
  ifstream inputCfg (argv[1], std::ios::in);
  std::string inputFolderUnpacked = argv[2];
  std::string inputFolderDQM = argv[3];
  std::string outputLabel = argv[4];
  int entriesMax = atoi(argv[5]);
  
  std::cout << "--------------------------------" << std::endl;
  std::cout << "inputCfg: "            << argv[1] << std::endl;
  std::cout << "inputFolderUnpacked: " << argv[2] << std::endl;
  std::cout << "inputFolderDQM: "      << argv[3] << std::endl;
  std::cout << "outputLabel: "         << argv[4] << std::endl;
  std::cout << "entriesMax: "          << argv[5] << std::endl;
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
    
    
    //---------output file----------------
    TFile* outputFile = TFile::Open(Form("plots/plots_studyPedestal_%s_run%d.root",outputLabel.c_str(),runNumber),"RECREATE");  
    outputFile -> cd();
    
    std::map<int,TH1F*> h_ped;
    std::map<int,TH1F*> h_rms;
    std::map<int,TGraph*> g_ped_vs_entry;
    std::map<int,TGraph*> g_rms_vs_entry;
    std::map<int,TGraph*> g_aveWaveform;
    std::map<int,int> n_aveWaveform;
    std::map<int,TGraph*> g_aveWaveform_highNoise;
    std::map<int,int> n_aveWaveform_highNoise;
    for(unsigned int iCh = 0; iCh < 32; ++iCh)
    {
      h_ped[iCh] = new TH1F(Form("h_ped_ch%02d",iCh),"",1600,3300.,3700.);
      h_rms[iCh] = new TH1F(Form("h_rms_ch%02d",iCh),"",1000,0.,10.);
      g_ped_vs_entry[iCh] = new TGraph();
      g_ped_vs_entry[iCh] -> SetName(Form("g_ped_vs_entry_ch%02d",iCh));
      g_rms_vs_entry[iCh] = new TGraph();
      g_rms_vs_entry[iCh] -> SetName(Form("g_rms_vs_entry_ch%02d",iCh));
      g_aveWaveform[iCh] = new TGraph();
      g_aveWaveform[iCh] -> SetName(Form("g_aveWaveform_ch%02d",iCh));
      g_aveWaveform_highNoise[iCh] = new TGraph();
      g_aveWaveform_highNoise[iCh] -> SetName(Form("g_aveWaveform_highNoise_ch%02d",iCh));
    }
    
    
    //-----Define variables--------------------------------------------------------    
    std::map<int,Waveform*> waveforms_trg;
    std::map<int,Waveform*> waveforms;
    
    
    //-----Data loop--------------------------------------------------------
    int nEntries = treeUnpacked -> GetEntries();
    if( entriesMax < 0 ) entriesMax = nEntries;
    for(int iEntry = 0; iEntry < entriesMax; ++iEntry)
    {
      if( iEntry%100 == 0 ) std::cout << ">>> reading entry: " << iEntry << " / " << nEntries << std::endl;
      
      //---Clear and initialize variables
      for(unsigned int iCh = 0; iCh < 4; ++iCh)
      {
        waveforms_trg[iCh] = new Waveform();
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
      
      for(unsigned int iCh = 0; iCh < 32; ++iCh)
      {
        if( waveforms[iCh]->getNSamples() == 0 ) continue;
        
        int sampleMin_ped = 5;
        int sampleMax_ped = 54;
        int sampleMax_sig = 250;
        if( iCh == 0 ) { sampleMax_ped = 14; sampleMax_sig = 150; }
        int sampleMin_sig = sampleMax_ped+1;
        
        //---Compute quantities
        Waveform::baseline_informations wave_ped;
        Waveform::max_amplitude_informations wave_max;
        wave_ped = waveforms[iCh] -> baseline(sampleMin_ped,sampleMax_ped); //use 50 samples between 5-54 to get pedestal and RMS
        
        h_ped[iCh] -> Fill( wave_ped.pedestal );
        h_rms[iCh] -> Fill( wave_ped.rms );
        g_ped_vs_entry[iCh] -> SetPoint(g_ped_vs_entry[iCh]->GetN(),iEntry,wave_ped.pedestal);
        g_rms_vs_entry[iCh] -> SetPoint(g_ped_vs_entry[iCh]->GetN(),iEntry,wave_ped.rms);
        
        waveforms[iCh] -> offset(wave_ped.pedestal);
        waveforms[iCh] -> rescale(-1);
        wave_ped = waveforms[iCh] -> baseline(sampleMin_ped,sampleMax_ped); //use 50 samples between 5-54 to get pedestal and RMS
        wave_max = waveforms[iCh] -> max_amplitude(sampleMin_sig,sampleMax_sig,5); //find max amplitude between 50 and 900 samples
        
        // //---Compute average waveform
        // AddWaveform(g_aveWaveform[iCh],&samples[iCh],true);
        // n_aveWaveform[iCh] += 1;
        // if( dummy.second > 4.25 )
        // {
        //   AddWaveform(g_aveWaveform_highNoise[iCh],&samples[iCh],true);
        //   n_aveWaveform_highNoise[iCh] += 1;
        // }
      }
      
      //---Save 10 waveforms for each channel
      if( iEntry < 10 )
      {
        outputFile -> cd();
        outputFile -> mkdir(Form("evt%d",iEntry));
        outputFile -> cd(Form("evt%d",iEntry));
        for(unsigned int iCh = 0; iCh < 4; ++iCh)
        {
          if( waveforms_trg[iCh]->getNSamples() == 0 ) continue;
          std::cout << "trg ch: " << iCh << std::endl;
          
          TGraph* graph = waveforms_trg[iCh] -> getGraph();
          graph -> Write(Form("g_trigger_waveform_ch%02d",iCh));
          delete graph;
        }
        for(unsigned int iCh = 0; iCh < 32; ++iCh)
        {
          if( waveforms[iCh]->getNSamples() == 0 ) continue;
          std::cout << "ch: " << iCh << std::endl;
          
          TGraph* graph = waveforms[iCh] -> getGraph();
          graph -> Write(Form("g_waveform_ch%02d",iCh));
          delete graph;
          
          TGraph* graph2 = waveforms[iCh] -> getDFTPowerSpectrumGraph();
          graph2 -> Write(Form("g_waveformPowerSpectrum_ch%02d",iCh));
          graph2 -> Fit("pol8","Q+","",1.,100.);
          delete graph2;
          
          waveforms[iCh] -> setIDFTWaveform();
          
          TGraph* graph3 = waveforms[iCh] -> getGraph();
          graph3 -> Write(Form("g_waveformFiltered_ch%02d",iCh));
          delete graph3;
        }
      }
    }
    
    
    //-----close everything-----------------------------------------------------
    outputFile -> cd();
    for(unsigned int iCh = 0; iCh < 32; ++iCh)
    {
      g_ped_vs_entry[iCh] -> Write();
      g_rms_vs_entry[iCh] -> Write();
      // NormalizeGraph(g_aveWaveform[iCh],n_aveWaveform[iCh]);
      // g_aveWaveform[iCh] -> Write();
      // NormalizeGraph(g_aveWaveform_highNoise[iCh],n_aveWaveform_highNoise[iCh]);
      // g_aveWaveform_highNoise[iCh] -> Write();
    }
    outputFile -> Write();
    outputFile -> Close();
    
    
    //---Get ready for next run
    treeUnpacked->Delete();
    treeDQM->Delete();
  }
  
  
  //---------Done-----------------------------------------------------------------
}
