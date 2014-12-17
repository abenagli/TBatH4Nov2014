void drawBeamPosition(const std::string& inFileName)
{
  TFile* inFile = TFile::Open(inFileName.c_str(),"READ");
  
  
  double X0 = -194.64; double DX = 6.03;
  double Y0 = -138.08; double DY = 6.08;
  
  
  TCanvas* c1 = new TCanvas("c_beamPosition_hodo12","c_beamPosition_hodo12");
  
  TH2F* h2 = (TH2F*)( inFile->Get("h2_beamPosition_hodo12") );
  h2 -> SetTitle(";beam x_{hodo1};beam y_{hodo2}");
  h2 -> Draw("colz");
  
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    double x0 = X0 + GetChannelX(iCh)*DX;
    double y0 = Y0 + GetChannelY(iCh)*DY;
    double x1 = x0 - 0.5*DX;
    double x2 = x0 + 0.5*DX;
    double y1 = y0 - 0.5*DY;
    double y2 = y0 + 0.5*DY;
    TBox* box = new TBox(x1,y1,x2,y2);
    box -> SetLineColor(kBlack);
    box -> SetLineWidth(1);
    box -> SetFillStyle(0);
    box -> Draw("same");
  }
  
  c1 -> Print("c1_beamPosition_hodo12.png","png");
  
  
  
  c1 = new TCanvas("c_beamPosition_MCP_hodo12","c_beamPosition_MCP_hodo12");
  
  h2 = (TH2F*)( inFile->Get("h2_beamPosition_MCP_hodo12") );
  h2 -> SetTitle(";beam x_{hodo1};beam y_{hodo2}");
  h2 -> Draw("colz");
  
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    double x0 = X0 + GetChannelX(iCh)*DX;
    double y0 = Y0 + GetChannelY(iCh)*DY;
    double x1 = x0 - 0.5*DX;
    double x2 = x0 + 0.5*DX;
    double y1 = y0 - 0.5*DY;
    double y2 = y0 + 0.5*DY;
    TBox* box = new TBox(x1,y1,x2,y2);
    box -> SetLineColor(kBlack);
    box -> SetLineWidth(1);
    box -> SetFillStyle(0);
    box -> Draw("same");
  }
  
  c1 -> Print("c1_beamPosition_MCP_hodo12.png","png");
}



int GetChannelX(const int& chId)
{
  if( chId == 0 ) return 0;
  if( chId == 1 ) return 1;
  if( chId == 2 ) return 3;
  if( chId == 3 ) return 4;
  if( chId == 4 ) return 6;
  if( chId == 5 ) return 7;
  if( chId == 6 ) return 2;
  if( chId == 7 ) return 3;
  if( chId == 8 ) return 4;
  if( chId == 9 ) return 5;
  if( chId == 10 ) return 0;
  if( chId == 11 ) return 2;
  if( chId == 12 ) return 3;
  if( chId == 13 ) return 4;
  if( chId == 14 ) return 5;
  if( chId == 15 ) return 7;
  if( chId == 16 ) return 0;
  if( chId == 17 ) return 2;
  if( chId == 18 ) return 3;
  if( chId == 19 ) return 4;
  if( chId == 20 ) return 5;
  if( chId == 21 ) return 7;
  if( chId == 22 ) return 2;
  if( chId == 23 ) return 3;
  if( chId == 24 ) return 4;
  if( chId == 25 ) return 5;
  if( chId == 26 ) return 0;
  if( chId == 27 ) return 1;
  if( chId == 28 ) return 3;
  if( chId == 29 ) return 4;
  if( chId == 30 ) return 6;
  if( chId == 31 ) return 7;
  return -1;
}



int GetChannelY(const int& chId)
{
  if( chId == 0 ) return 7;
  if( chId == 1 ) return 7;
  if( chId == 2 ) return 7;
  if( chId == 3 ) return 7;
  if( chId == 4 ) return 7;
  if( chId == 5 ) return 7;
  if( chId == 6 ) return 5;
  if( chId == 7 ) return 5;
  if( chId == 8 ) return 5;
  if( chId == 9 ) return 5;
  if( chId == 10 ) return 4;
  if( chId == 11 ) return 4;
  if( chId == 12 ) return 4;
  if( chId == 13 ) return 4;
  if( chId == 14 ) return 4;
  if( chId == 15 ) return 4;
  if( chId == 16 ) return 3;
  if( chId == 17 ) return 3;
  if( chId == 18 ) return 3;
  if( chId == 19 ) return 3;
  if( chId == 20 ) return 3;
  if( chId == 21 ) return 3;
  if( chId == 22 ) return 2;
  if( chId == 23 ) return 2;
  if( chId == 24 ) return 2;
  if( chId == 25 ) return 2;
  if( chId == 26 ) return 0;
  if( chId == 27 ) return 0;
  if( chId == 28 ) return 0;
  if( chId == 29 ) return 0;
  if( chId == 30 ) return 0;
  if( chId == 31 ) return 0;
  return -1;
}

