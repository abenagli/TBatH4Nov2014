/*******************************************************************************
THIS PROGRAM READS THE NTUPLES AND MAKES PLOTS FOR THE PLANACON CELLS
*******************************************************************************/

#include "analysis_tools.h"
#include "init_tree_reco.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "TFile.h"
#include "TChain.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TProfile2D.h"



int main (int argc, char** argv)
{  
  std::cout<<"--------> DUMPER: READ RECO DATA AND PRODUCE PROFILE PLOTS <--------"<<std::endl;
  
  
  //--------Read Options--------------------------------
  std::string inputFileList(argv[1]);
  std::string outputLabel = argv[2];
  int entriesMax = atoi(argv[3]);
  
  std::cout << "--------------------------------" << std::endl;
  std::cout << "inputFileList: "       << argv[1] << std::endl;
  std::cout << "outputLabel: "         << argv[2] << std::endl;
  std::cout << "entriesMax: "          << argv[3] << std::endl;
  std::cout << "--------------------------------" << std::endl;
  
  
  //-------start to read the input file list--------
  
  TChain* treeReco = new TChain("ntu");
  RecoTreeVars recoTV;
  InitRecoTree(treeReco,recoTV);
  FillChain(treeReco,inputFileList);
  
  
  //---------output histograms----------------
  TFile* outputFile = TFile::Open(Form("plots/plots_studyProfiles_%s.root",outputLabel.c_str()),"RECREATE");
  TH2F* h2_beamPosition_TDC = new TH2F("h2_beamPosition_TDC","",100,-240,-140.,100,-146,-46.);
  TH2F* h2_beamPosition_hodo11 = new TH2F("h2_beamPosition_hodo11","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_hodo22 = new TH2F("h2_beamPosition_hodo22","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_hodo12 = new TH2F("h2_beamPosition_hodo12","",160,-210.,-130.,160,-155.,-75.);
  TH2F* h2_beamPosition_hodo21 = new TH2F("h2_beamPosition_hodo21","",160,-210.,-130.,160,-155.,-75.);
  
  std::map<int,TProfile*> p_cellProfileX_TDC;
  std::map<int,TProfile*> p_cellProfileX_hodo12;
  std::map<int,TProfile*> p_cellProfileY_TDC;
  std::map<int,TProfile*> p_cellProfileY_hodo12;
  std::map<int,TH1F*> h_cell_charge;
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    p_cellProfileX_TDC[iCh]    = new TProfile(Form("p_cell%02dProfileX_TDC",iCh),"",   100,-240.,-140.);
    p_cellProfileX_hodo12[iCh] = new TProfile(Form("p_cell%02dProfileX_hodo12",iCh),"",160,-210.,-130.);
    p_cellProfileY_TDC[iCh]    = new TProfile(Form("p_cell%02dProfileY_TDC",iCh),"",   100,-146., -46.);
    p_cellProfileY_hodo12[iCh] = new TProfile(Form("p_cell%02dProfileY_hodo12",iCh),"",160,-155., -75.);
    h_cell_charge[iCh] = new TH1F(Form("h_cell%02d_charge",iCh),"",100000,0., 10000000.);
  }
  
  TH1F* h_total_charge = new TH1F("h_total_charge","",100000,0., 10000000.);
  TProfile2D* p2_cellPosition_TDC    = new TProfile2D("p2_cellPosition_TDC",   "",100,-240.,-140.,100,-152.,-52.);
  TProfile2D* p2_cellPosition_hodo12 = new TProfile2D("p2_cellPosition_hodo12","",160,-210.,-130.,160,-155.,-75.);
  
  
  //-----Data loop--------------------------------------------------------
  int nEntries = treeReco -> GetEntries();
  if( entriesMax < 0 ) entriesMax = nEntries;
  for(int iEntry = 0; iEntry < entriesMax; ++iEntry)
  {
    if( iEntry%1 == 0 ) std::cout << ">>> reading entry: " << iEntry << " / " << nEntries << "\r" << std::flush;
    
    
    //---Read the entry
    ClearRecoTreeVars(recoTV);
    treeReco->GetEntry(iEntry);
    
    
    //---Reconstruct beam position
    float beamX_TDC = -recoTV.tableX + recoTV.tdcX;
    float beamY_TDC = -recoTV.tableY + recoTV.tdcY;
    
    float hodoX1 = GetHodoWire(recoTV.nHodoX1,recoTV.hodoX1);
    float hodoY1 = GetHodoWire(recoTV.nHodoY1,recoTV.hodoY1);
    float hodoX2 = GetHodoWire(recoTV.nHodoX2,recoTV.hodoX2);
    float hodoY2 = GetHodoWire(recoTV.nHodoY2,recoTV.hodoY2);
    float beamX_hodo1 = hodoX1 >= 0 ? -recoTV.tableX + 0.5*hodoX1 : -999;
    float beamY_hodo1 = hodoY1 >= 0 ? -recoTV.tableY - 0.5*hodoY1 : -999;
    float beamX_hodo2 = hodoX2 >= 0 ? -recoTV.tableX + 0.5*hodoX2 : -999;
    float beamY_hodo2 = hodoY2 >= 0 ? -recoTV.tableY - 0.5*hodoY2 : -999;
    
    
    //---Fill histograms
    h2_beamPosition_TDC -> Fill(beamX_TDC,beamY_TDC);
    if( beamX_hodo1 != -999 && beamY_hodo1 != -999 ) h2_beamPosition_hodo11 -> Fill(beamX_hodo1,beamY_hodo1);
    if( beamX_hodo2 != -999 && beamY_hodo2 != -999 ) h2_beamPosition_hodo22 -> Fill(beamX_hodo2,beamY_hodo2);
    if( beamX_hodo1 != -999 && beamY_hodo2 != -999 ) h2_beamPosition_hodo12 -> Fill(beamX_hodo1,beamY_hodo2);
    if( beamX_hodo2 != -999 && beamY_hodo1 != -999 ) h2_beamPosition_hodo21 -> Fill(beamX_hodo2,beamY_hodo1);
    
    float total_charge = 0.;
    for(int iCh = 0; iCh < 32; ++iCh)
    {
      if( recoTV.amp_DQM[iCh] > 500 ) p2_cellPosition_TDC    -> Fill(beamX_TDC,  beamY_TDC,  32*(iCh%2)+pow(-1,iCh)*iCh);
      if( recoTV.amp_DQM[iCh] > 500 ) p2_cellPosition_hodo12 -> Fill(beamX_hodo1,beamY_hodo2,32*(iCh%2)+pow(-1,iCh)*iCh);
      if( recoTV.amp_DQM[iCh] > 0. && recoTV.amp_DQM[iCh] < 999999. )
      {
        p_cellProfileX_TDC[iCh]    -> Fill(beamX_TDC,  recoTV.amp_DQM[iCh]);
        p_cellProfileX_hodo12[iCh] -> Fill(beamX_hodo1,recoTV.amp_DQM[iCh]);
        p_cellProfileY_TDC[iCh]    -> Fill(beamY_TDC,  recoTV.amp_DQM[iCh]);
        p_cellProfileY_hodo12[iCh] -> Fill(beamY_hodo2,recoTV.amp_DQM[iCh]);
        h_cell_charge[iCh] -> Fill(recoTV.charge_DQM[iCh]);
        if(iCh==12 || iCh==13 || iCh==18 || iCh==19)
          total_charge += recoTV.charge_DQM[iCh];
      }
    }
    
    if( (fabs(beamX_hodo1+180.) < 5.) &&
        (fabs(beamY_hodo2+117.) < 5.) )
      h_total_charge -> Fill(total_charge);
  }
  std::cout << std::endl;
  
  
  // //-----close everything-----------------------------------------------------
  outputFile -> Write();
  outputFile -> Close();
  
  
  //---------Done-----------------------------------------------------------------
}
