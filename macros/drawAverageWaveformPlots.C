void drawAverageWaveformPlots()
{
  TFile* inFile_germanModulePlasticMCP_100GeV = TFile::Open("plots/plots_studyAverageWaveform_PWOModule_100GeV.root","READ");
  TCanvas* c1;
  TLatex* latex;
  TF1* fitFunc;
  gStyle -> SetPadRightMargin(0.15);
  
  
  
  c1 = new TCanvas("c_aveWaveform_trgTimeShift_ch18","c_aveWaveform_trgTimeShift_ch18");
  c1 -> SetGridx();
  c1 -> SetGridy();
  
  TProfile* p_aveWaveform_trgTimeShift_ch18_100GeV = (TProfile*)( inFile_germanModulePlasticMCP_100GeV->Get("p_aveWaveform_trgTimeShift_ch18") );
  p_aveWaveform_trgTimeShift_ch18_100GeV -> SetTitle(";time (ns);ADC");
  p_aveWaveform_trgTimeShift_ch18_100GeV -> GetXaxis() -> SetRangeUser(-10.,100.);
  p_aveWaveform_trgTimeShift_ch18_100GeV -> SetMarkerColor(kBlack);
  p_aveWaveform_trgTimeShift_ch18_100GeV -> SetLineColor(kBlack);
  p_aveWaveform_trgTimeShift_ch18_100GeV -> Draw("");
  p_aveWaveform_trgTimeShift_ch18_100GeV -> Draw("hist,same");
  
  fitFunc = new TF1("fitFunc","[4]+[0]*exp(-x/[1])+[2]*exp(-x/[3])",5.,100.);
  fitFunc -> SetParameters(17260,6.47,1000.,10.,-10.);
  //fitFunc -> FixParameter(2,0.);
  //fitFunc -> FixParameter(3,1.);
  fitFunc -> SetNpx(10000);
  fitFunc -> SetLineWidth(2);
  p_aveWaveform_trgTimeShift_ch18_100GeV -> Fit("fitFunc","NS+","",20.,100.);
  fitFunc -> Draw("same");
  
  latex = new TLatex(0.50,0.80,Form("#tau_{1} = %.2f ns",fitFunc->GetParameter(1)));
  latex -> SetNDC();
  latex -> SetTextFont(42);
  latex -> SetTextSize(0.04);
  latex -> SetTextColor(kRed);
  latex -> Draw("same");
  latex = new TLatex(0.50,0.70,Form("#tau_{2} = %.2f ns",fitFunc->GetParameter(3)));
  latex -> SetNDC();
  latex -> SetTextFont(42);
  latex -> SetTextSize(0.04);
  latex -> SetTextColor(kRed);
  latex -> Draw("same");

  c1 -> Print("c_aveWaveform_trgTimeShift_ch18_PWOModule.png","png");
  
  
  
  
  
  // c1 = new TCanvas("c_beamPosition_TDC","c_beamPosition_TDC");
  
  // TH2F* h2_beamPosition_TDC = (TH2F*)( inFile->Get("h2_beamPosition_TDC") );
  // h2_beamPosition_TDC -> Draw("COLZ");
  // h2_beamPosition_TDC -> SetTitle(";beam x_{TDC} (mm);beam y_{TDC} (mm)");
  // h2_beamPosition_TDC -> GetZaxis() -> SetRangeUser(0.,50.);
  
  // latex = new TLatex(0.13,0.96,Form("eff: %.1f%%",100.*h2_beamPosition_TDC->Integral()/h2_beamPosition_TDC->GetEntries()));
  // latex -> SetNDC();
  // latex -> SetTextFont(42);
  // latex -> SetTextSize(0.04);
  // latex -> Draw("same");
  
  // c1 -> Print("c_beamPosition_TDC.png","png");
  
  
  
  // c1 = new TCanvas("c_beamPosition_hodo12","c_beamPosition_hodo12");
  
  // TH2F* h2_beamPosition_hodo12 = (TH2F*)( inFile->Get("h2_beamPosition_hodo12") );
  // h2_beamPosition_hodo12 -> Draw("COLZ");
  // h2_beamPosition_hodo12 -> SetTitle(";beam x_{hodo1} (mm);beam y_{hodo2} (mm)");
  // h2_beamPosition_hodo12 -> GetZaxis() -> SetRangeUser(0.,15.);
  
  // latex = new TLatex(0.13,0.96,Form("eff: %.1f%%",100.*h2_beamPosition_hodo12->Integral()/h2_beamPosition_TDC->GetEntries()));
  // latex -> SetNDC();
  // latex -> SetTextFont(42);
  // latex -> SetTextSize(0.04);
  // latex -> Draw("same");
  
  // c1 -> Print("c_beamPosition_hodo12.png","png");
  
  
  
  // c1 = new TCanvas("c_beamPosition_MCP_TDC","c_beamPosition_MCP_TDC");
  
  // TH2F* h2_beamPosition_MCP_TDC = (TH2F*)( inFile->Get("h2_beamPosition_MCP_TDC") );
  // h2_beamPosition_MCP_TDC -> Draw("COLZ");
  // h2_beamPosition_MCP_TDC -> SetTitle(";beam x_{TDC} (mm);beam y_{TDC} (mm)");
  // h2_beamPosition_MCP_TDC -> GetZaxis() -> SetRangeUser(0.,50.);
  
  // latex = new TLatex(0.13,0.96,Form("eff: %.1f%%",100.*h2_beamPosition_MCP_TDC->Integral()/h2_beamPosition_MCP_TDC->GetEntries()));
  // latex -> SetNDC();
  // latex -> SetTextFont(42);
  // latex -> SetTextSize(0.04);
  // latex -> Draw("same");
  
  // c1 -> Print("c_beamPosition_MCP_TDC.png","png");
  
  
  
  // c1 = new TCanvas("c_beamPosition_MCP_hodo12","c_beamPosition_MCP_hodo12");
  
  // TH2F* h2_beamPosition_MCP_hodo12 = (TH2F*)( inFile->Get("h2_beamPosition_MCP_hodo12") );
  // h2_beamPosition_MCP_hodo12 -> Draw("COLZ");
  // h2_beamPosition_MCP_hodo12 -> SetTitle(";beam x_{hodo1} (mm);beam y_{hodo2} (mm)");
  // h2_beamPosition_MCP_hodo12 -> GetZaxis() -> SetRangeUser(0.,15.);
  
  // latex = new TLatex(0.13,0.96,Form("eff: %.1f%%",100.*h2_beamPosition_MCP_hodo12->Integral()/h2_beamPosition_MCP_TDC->GetEntries()));
  // latex -> SetNDC();
  // latex -> SetTextFont(42);
  // latex -> SetTextSize(0.04);
  // latex -> Draw("same");
  
  // c1 -> Print("c_beamPosition_MCP_hodo12.png","png");
  
  
  
  // c1 = new TCanvas("c_aveWaveform_MCPTimeShift_ampNorm1_ch00","c_aveWaveform_MCPTimeShift_ampNorm1_ch00");
  // c1 -> SetGridx();
  // c1 -> SetGridy();
  
  // TProfile* p_aveWaveform_MCPTimeShift_ampNorm1_ch00 = (TProfile*)( inFile->Get("p_aveWaveform_MCPTimeShift_ampNorm1_ch00") );
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch00 -> Draw("");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch00 -> Draw("hist,same");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch00 -> SetTitle(";time (ns);ADC");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch00 -> GetXaxis() -> SetRangeUser(-10.,20.);
  
  // c1 -> Print("c_aveWaveform_MCPTimeShift_ampNorm1_ch00.png","png");
  
  
  
  // c1 = new TCanvas("c_aveWaveform_MCPTimeShift_ampNorm1_ch19","c_aveWaveform_MCPTimeShift_ampNorm1_ch19");
  // c1 -> SetGridx();
  // c1 -> SetGridy();
  
  // TProfile* p_aveWaveform_MCPTimeShift_ampNorm1_ch19 = (TProfile*)( inFile->Get("p_aveWaveform_MCPTimeShift_ampNorm1_ch19") );
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch19 -> Draw("");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch19 -> Draw("hist,same");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch19 -> SetTitle(";time (ns);ADC");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch19 -> GetXaxis() -> SetRangeUser(-10.,100.);
  
  // c1 -> Print("c_aveWaveform_MCPTimeShift_ampNorm1_ch19.png","png");
  
  
  
  // c1 = new TCanvas("c_aveWaveform_ampNorm1_ch19","c_aveWaveform_ampNorm1_ch19");
  // c1 -> SetGridx();
  // c1 -> SetGridy();
  
  // TProfile* p_aveWaveform_ampNorm1_ch19 = (TProfile*)( inFile->Get("p_aveWaveform_ampNorm1_ch19") );
  // p_aveWaveform_ampNorm1_ch19 -> Draw("");
  // p_aveWaveform_ampNorm1_ch19 -> SetTitle(";time (ns);ADC");
  // p_aveWaveform_ampNorm1_ch19 -> GetXaxis() -> SetRangeUser(-10.,100.);
  
  // c1 -> Print("c_aveWaveform_ampNorm1_ch19.png","png");
  
  
  
  // c1 = new TCanvas("c_aveWaveform_ampNorm1_cfr","c_aveWaveform_ampNorm1_cfr");
  // c1 -> SetGridx();
  // c1 -> SetGridy();
  
  // TProfile* p_aveWaveform_ampNorm1_ch08 = (TProfile*)( inFile->Get("p_aveWaveform_ampNorm1_ch08") );
  // p_aveWaveform_ampNorm1_ch08 -> SetMarkerColor(kGreen+1);
  // p_aveWaveform_ampNorm1_ch08 -> Draw("");
  // p_aveWaveform_ampNorm1_ch08 -> SetTitle(";time (ns);ADC");
  // p_aveWaveform_ampNorm1_ch08 -> GetXaxis() -> SetRangeUser(-10.,100.);
  
  // TProfile* p_aveWaveform_ampNorm1_ch14 = (TProfile*)( inFile->Get("p_aveWaveform_ampNorm1_ch14") );
  // p_aveWaveform_ampNorm1_ch14 -> SetMarkerColor(kBlue);
  // p_aveWaveform_ampNorm1_ch14 -> Draw("same");
  
  // TProfile* p_aveWaveform_ampNorm1_ch19 = (TProfile*)( inFile->Get("p_aveWaveform_ampNorm1_ch19") );
  // p_aveWaveform_ampNorm1_ch19 -> SetMarkerColor(kRed);
  // p_aveWaveform_ampNorm1_ch19 -> Draw("same");
  
  // c1 -> Print("c_aveWaveform_ampNorm1_cfr.png","png");
  
  
  
  // c1 = new TCanvas("c_aveWaveform_MCPTimeShift_ampNorm1_cfr","c_aveWaveform_MCPTimeShift_ampNorm1_cfr");
  // c1 -> SetGridx();
  // c1 -> SetGridy();
  
  // TProfile* p_aveWaveform_MCPTimeShift_ampNorm1_ch08 = (TProfile*)( inFile->Get("p_aveWaveform_MCPTimeShift_ampNorm1_ch08") );
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch08 -> SetMarkerColor(kGreen+1);
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch08 -> SetLineColor(kGreen+1);
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch08 -> Draw("");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch08 -> Draw("hist,same");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch08 -> SetTitle(";time (ns);ADC");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch08 -> GetXaxis() -> SetRangeUser(-10.,100.);
  
  // TProfile* p_aveWaveform_MCPTimeShift_ampNorm1_ch14 = (TProfile*)( inFile->Get("p_aveWaveform_MCPTimeShift_ampNorm1_ch14") );
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch14 -> SetMarkerColor(kBlue);
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch14 -> SetLineColor(kBlue);
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch14 -> Draw("same");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch14 -> Draw("hist,same");
  
  // TProfile* p_aveWaveform_MCPTimeShift_ampNorm1_ch19 = (TProfile*)( inFile->Get("p_aveWaveform_MCPTimeShift_ampNorm1_ch19") );
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch19 -> SetMarkerColor(kRed);
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch19 -> SetLineColor(kRed);
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch19 -> Draw("same");
  // p_aveWaveform_MCPTimeShift_ampNorm1_ch19 -> Draw("hist,same");
  
  // c1 -> Print("c_aveWaveform_MCPTimeShift_ampNorm1_cfr.png","png");
}
