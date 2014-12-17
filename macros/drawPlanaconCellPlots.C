TH1F* fitHisto;



double gausBkg(double* x, double* par)
{
  double xx = x[0];
  
  int bin = fitHisto -> FindBin(xx);
  //if( fitHisto->GetBinError(bin) > 30. || fitHisto->GetBinContent(bin) > 400. )
  if( fitHisto->GetBinError(bin) < 0.75 || fitHisto->GetBinError(bin) > 30. || fitHisto->GetBinContent(bin) > 400. )
  {
    TF1::RejectPoint();
    return 0;
  }
  
  return par[0]+par[1]*(xx-par[2])*(xx-par[2]) + par[3]*exp(-1.*(xx-par[4])*(xx-par[4])/(2.*par[5]*par[5]));
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



void drawPlanaconCellPlots()
{
  TFile* inFile = TFile::Open("plots/plots_studyPlanaconCells_test.root","READ");
  TCanvas* c1;
  TLatex* latex;
  gStyle -> SetPadRightMargin(0.15);
  
  
  
  c1 = new TCanvas("c_beamPosition_TDC","c_beamPosition_TDC");
  
  TH2F* h2_beamPosition_TDC = (TH2F*)( inFile->Get("h2_beamPosition_TDC") );
  h2_beamPosition_TDC -> Draw("COLZ");
  h2_beamPosition_TDC -> SetTitle(";beam x_{TDC} (mm);beam y_{TDC} (mm)");
  h2_beamPosition_TDC -> GetZaxis() -> SetRangeUser(0.,100.);
  
  latex = new TLatex(0.13,0.96,Form("eff: %.1f%%",100.*h2_beamPosition_TDC->Integral()/h2_beamPosition_TDC->GetEntries()));
  latex -> SetNDC();
  latex -> SetTextFont(42);
  latex -> SetTextSize(0.04);
  latex -> Draw("same");
  
  c1 -> Print("c_beamPosition_TDC.png","png");
  
  
  
  c1 = new TCanvas("c_beamPosition_hodo12","c_beamPosition_hodo12");
  
  TH2F* h2_beamPosition_hodo12 = (TH2F*)( inFile->Get("h2_beamPosition_hodo12") );
  h2_beamPosition_hodo12 -> Draw("COLZ");
  h2_beamPosition_hodo12 -> SetTitle(";beam x_{hodo1} (mm);beam y_{hodo2} (mm)");
  h2_beamPosition_hodo12 -> GetZaxis() -> SetRangeUser(0.,30.);
  
  latex = new TLatex(0.13,0.96,Form("eff: %.1f%%",100.*h2_beamPosition_hodo12->Integral()/h2_beamPosition_TDC->GetEntries()));
  latex -> SetNDC();
  latex -> SetTextFont(42);
  latex -> SetTextSize(0.04);
  latex -> Draw("same");
  
  c1 -> Print("c_beamPosition_hodo12.png","png");
  
  
  
  c1 = new TCanvas("c_cellPosition_TDC","c_cellPosition_TDC");
  
  TProfile2D* p2_cellPosition_TDC = (TProfile2D*)( inFile->Get("p2_cellPosition_TDC") );
  p2_cellPosition_TDC -> Draw("COLZ");
  p2_cellPosition_TDC -> SetTitle(";beam x_{TDC} (mm);beam y_{TDC} (mm)");
  p2_cellPosition_TDC -> GetZaxis() -> SetRangeUser(0.,30.);
  p2_cellPosition_TDC -> GetYaxis() -> SetRangeUser(-145.,-55.);
  
  c1 -> Print("c_cellPosition_TDC.png","png");
  
  
  
  c1 = new TCanvas("c_cellPosition_hodo12","c_cellPosition_hodo12");
  
  TProfile2D* p2_cellPosition_hodo12 = (TProfile2D*)( inFile->Get("p2_cellPosition_hodo12") );
  p2_cellPosition_hodo12 -> Draw("COLZ");
  p2_cellPosition_hodo12 -> SetTitle(";beam x_{hodo1} (mm);beam y_{hodo2} (mm)");
  p2_cellPosition_hodo12 -> GetZaxis() -> SetRangeUser(0.,30.);
  
  c1 -> Print("c_cellPosition_hodo12.png","png");
  
  
  
  c1 = new TCanvas("c_cellProfileX_hodo12","c_cellProfileX_hodo12");
  
  TProfile* p_cell16ProfileX_hodo12 = (TProfile*)( inFile->Get("p_cell16ProfileX_hodo12") );
  p_cell16ProfileX_hodo12 -> SetMarkerColor(kBlack);
  p_cell16ProfileX_hodo12 -> SetLineColor(kBlack);
  p_cell16ProfileX_hodo12 -> GetYaxis() -> SetRangeUser(0.,400.);
  p_cell16ProfileX_hodo12 -> Draw();
  p_cell16ProfileX_hodo12 -> Draw("hist,same");
  p_cell16ProfileX_hodo12 -> SetTitle(";beam x_{hodo1} (mm);");
  TProfile* p_cell17ProfileX_hodo12 = (TProfile*)( inFile->Get("p_cell17ProfileX_hodo12") );
  p_cell17ProfileX_hodo12 -> SetMarkerColor(kRed+3);
  p_cell17ProfileX_hodo12 -> SetLineColor(kRed+3);
  p_cell17ProfileX_hodo12 -> Draw("same");
  p_cell17ProfileX_hodo12 -> Draw("hist,same");
  TProfile* p_cell18ProfileX_hodo12 = (TProfile*)( inFile->Get("p_cell18ProfileX_hodo12") );
  p_cell18ProfileX_hodo12 -> SetMarkerColor(kRed+2);
  p_cell18ProfileX_hodo12 -> SetLineColor(kRed+2);
  p_cell18ProfileX_hodo12 -> Draw("same");
  p_cell18ProfileX_hodo12 -> Draw("hist,same");
  TProfile* p_cell19ProfileX_hodo12 = (TProfile*)( inFile->Get("p_cell19ProfileX_hodo12") );
  p_cell19ProfileX_hodo12 -> SetMarkerColor(kRed+1);
  p_cell19ProfileX_hodo12 -> SetLineColor(kRed+1);
  p_cell19ProfileX_hodo12 -> Draw("same");
  p_cell19ProfileX_hodo12 -> Draw("hist,same");
  TProfile* p_cell20ProfileX_hodo12 = (TProfile*)( inFile->Get("p_cell20ProfileX_hodo12") );
  p_cell20ProfileX_hodo12 -> SetMarkerColor(kRed);
  p_cell20ProfileX_hodo12 -> SetLineColor(kRed);
  p_cell20ProfileX_hodo12 -> Draw("same");
  p_cell20ProfileX_hodo12 -> Draw("hist,same");
  TProfile* p_cell21ProfileX_hodo12 = (TProfile*)( inFile->Get("p_cell21ProfileX_hodo12") );
  p_cell21ProfileX_hodo12 -> SetMarkerColor(kRed-7);
  p_cell21ProfileX_hodo12 -> SetLineColor(kRed-7);
  p_cell21ProfileX_hodo12 -> Draw("same");
  p_cell21ProfileX_hodo12 -> Draw("hist,same");
  
  c1 -> Print("c_cellProfileX_hodo12.png","png");
  
  
  
  c1 = new TCanvas("c_cellProfileY_hodo12","c_cellProfileY_hodo12");
  
  TProfile* p_cell03ProfileY_hodo12 = (TProfile*)( inFile->Get("p_cell03ProfileY_hodo12") );
  p_cell03ProfileY_hodo12 -> SetMarkerColor(kBlack);
  p_cell03ProfileY_hodo12 -> SetLineColor(kBlack);
  p_cell03ProfileY_hodo12 -> GetYaxis() -> SetRangeUser(0.,400.);
  p_cell03ProfileY_hodo12 -> Draw();
  p_cell03ProfileY_hodo12 -> Draw("hist,same");
  p_cell03ProfileY_hodo12 -> SetTitle(";beam y_{hodo2} (mm);");
  TProfile* p_cell08ProfileY_hodo12 = (TProfile*)( inFile->Get("p_cell08ProfileY_hodo12") );
  p_cell08ProfileY_hodo12 -> SetMarkerColor(kRed+3);
  p_cell08ProfileY_hodo12 -> SetLineColor(kRed+3);
  p_cell08ProfileY_hodo12 -> Draw("same");
  p_cell08ProfileY_hodo12 -> Draw("hist,same");
  TProfile* p_cell13ProfileY_hodo12 = (TProfile*)( inFile->Get("p_cell13ProfileY_hodo12") );
  p_cell13ProfileY_hodo12 -> SetMarkerColor(kRed+2);
  p_cell13ProfileY_hodo12 -> SetLineColor(kRed+2);
  p_cell13ProfileY_hodo12 -> Draw("same");
  p_cell13ProfileY_hodo12 -> Draw("hist,same");
  TProfile* p_cell19ProfileY_hodo12 = (TProfile*)( inFile->Get("p_cell19ProfileY_hodo12") );
  p_cell19ProfileY_hodo12 -> SetMarkerColor(kRed+1);
  p_cell19ProfileY_hodo12 -> SetLineColor(kRed+1);
  p_cell19ProfileY_hodo12 -> Draw("same");
  p_cell19ProfileY_hodo12 -> Draw("hist,same");
  TProfile* p_cell24ProfileY_hodo12 = (TProfile*)( inFile->Get("p_cell24ProfileY_hodo12") );
  p_cell24ProfileY_hodo12 -> SetMarkerColor(kRed);
  p_cell24ProfileY_hodo12 -> SetLineColor(kRed);
  p_cell24ProfileY_hodo12 -> Draw("same");
  p_cell24ProfileY_hodo12 -> Draw("hist,same");
  TProfile* p_cell29ProfileY_hodo12 = (TProfile*)( inFile->Get("p_cell29ProfileY_hodo12") );
  p_cell29ProfileY_hodo12 -> SetMarkerColor(kRed-7);
  p_cell29ProfileY_hodo12 -> SetLineColor(kRed-7);
  p_cell29ProfileY_hodo12 -> Draw("same");
  p_cell29ProfileY_hodo12 -> Draw("hist,same");
  
  c1 -> Print("c_cellProfileY_hodo12.png","png");
  
  
  double x[32];
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    std::cout << ">>> Fitting x for channel " << iCh << std::endl;
    //c1 = new TCanvas(Form("c_cell%02dProfileX_hodo12",iCh),Form("c_cell%02dProfileX_hodo12",iCh));
    
    TProfile* p_cellProfileX_hodo12 = (TProfile*)( inFile->Get(Form("p_cell%02dProfileX_hodo12",iCh)) );
    p_cellProfileX_hodo12 -> GetYaxis() -> SetRangeUser(0.,400.);
    //p_cellProfileX_hodo12 -> Draw();
    //p_cellProfileX_hodo12 -> Draw("hist,same");
    p_cellProfileX_hodo12 -> SetTitle(";beam x_{hodo1} (mm);");
    
    TF1* fitFunc = new TF1("fitFunc",gausBkg,-205.,-140.,6);
    fitFunc -> SetNpx(10000);
    fitFunc -> SetParameters(25.,-0.01,-170.,100.,-195+6.*GetChannelX(iCh),5.);
    fitHisto = (TH1F*)(p_cellProfileX_hodo12);
    fitHisto -> Fit("fitFunc","QNRS+");
    //fitFunc -> Draw("same");
    x[iCh] = fitFunc->GetParameter(4);
  }
  
  double y[32];
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    std::cout << ">>> Fitting y for channel " << iCh << std::endl;
    //c1 = new TCanvas(Form("c_cell%02dProfileY_hodo12",iCh),Form("c_cell%02dProfileY_hodo12",iCh));
    
    TProfile* p_cellProfileY_hodo12 = (TProfile*)( inFile->Get(Form("p_cell%02dProfileY_hodo12",iCh)) );
    p_cellProfileY_hodo12 -> GetYaxis() -> SetRangeUser(0.,400.);
    //p_cellProfileY_hodo12 -> Draw();
    //p_cellProfileY_hodo12 -> Draw("hist,same");
    p_cellProfileY_hodo12 -> SetTitle(";beam y_{hodo2} (mm);");
    
    TF1* fitFunc = new TF1("fitFunc",gausBkg,-150.,-80.,6);
    fitFunc -> SetNpx(10000);
    fitFunc -> SetParameters(25.,-0.01,-120.,100.,-138+6.*GetChannelY(iCh),5.);
    fitHisto = (TH1F*)(p_cellProfileY_hodo12);
    fitHisto -> Fit("fitFunc","QNRS+");
    //fitFunc -> Draw("same");
    y[iCh] = fitFunc->GetParameter(4);
  }
  
  
  
  c1 = new TCanvas("c_cellXY_hodo12","c_cellXY_hodo12",1800,600);
  c1 -> Divide(3,1);
  
  TGraph* g_xy = new TGraph();
  TGraph* g_x = new TGraph();
  TGraph* g_y = new TGraph();
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    g_xy -> SetPoint(iCh,x[iCh],y[iCh]);
    g_x -> SetPoint(iCh,GetChannelX(iCh),x[iCh]);
    g_y -> SetPoint(iCh,GetChannelY(iCh),y[iCh]);
  }
  
  c1 -> cd(1);
  g_x -> Draw("AP");
  g_x -> SetTitle(";iX;beam x_{hodo1}");
  TF1* linFitX = new TF1("linFitX","[0]+[1]*x",-1.,8.);
  g_x -> Fit("linFitX","QNS+","",-1.,5.5);
  linFitX -> SetLineColor(kRed);
  linFitX -> SetLineWidth(2);
  linFitX -> Draw("same");
  
  latex = new TLatex(0.20,0.80,Form("x_{0} = %.2f",linFitX->GetParameter(0)));
  latex -> SetNDC();
  latex -> SetTextFont(42);
  latex -> SetTextSize(0.04);
  latex -> Draw("same");
  latex = new TLatex(0.20,0.70,Form("#Deltax = %.2f",linFitX->GetParameter(1)));
  latex -> SetNDC();
  latex -> SetTextFont(42);
  latex -> SetTextSize(0.04);
  latex -> Draw("same");
  
  
  c1 -> cd(2);
  g_y -> Draw("AP");
  g_y -> SetTitle(";iY;beam y_{hodo2}");
  TF1* linFitY = new TF1("linFitY","[0]+[1]*x",-1.,8.);
  g_y -> Fit("linFitY","QNRS+");
  linFitY -> SetLineColor(kRed);
  linFitY -> SetLineWidth(2);
  linFitY -> Draw("same");
                     
  latex = new TLatex(0.20,0.80,Form("y_{0} = %.2f",linFitY->GetParameter(0)));
  latex -> SetNDC();
  latex -> SetTextFont(42);
  latex -> SetTextSize(0.04);
  latex -> Draw("same");
  latex = new TLatex(0.20,0.70,Form("#Deltay = %.2f",linFitY->GetParameter(1)));
  latex -> SetNDC();
  latex -> SetTextFont(42);
  latex -> SetTextSize(0.04);
  latex -> Draw("same");
  
  
  c1 -> cd(3);
  g_xy -> SetTitle(";beam x_{hodo1};beam y_{hodo2}");
  g_xy -> Draw("AP");
  
  for(int iCh = 0; iCh < 32; ++iCh)
  {
    double x0 = linFitX->GetParameter(0) + GetChannelX(iCh)*linFitX->GetParameter(1);
    double y0 = linFitY->GetParameter(0) + GetChannelY(iCh)*linFitY->GetParameter(1);
    double x1 = x0 - 0.5*linFitX->GetParameter(1);
    double x2 = x0 + 0.5*linFitX->GetParameter(1);
    double y1 = y0 - 0.5*linFitY->GetParameter(1);
    double y2 = y0 + 0.5*linFitY->GetParameter(1);
    TBox* box = new TBox(x1,y1,x2,y2);
    box -> SetLineColor(kRed);
    box -> SetLineWidth(2);
    box -> SetFillStyle(0);
    box -> Draw("same");
  }
  
  c1 -> Print("c_cellXY_hodo12.png","png");
}
