void fitTrigger()
{
  gStyle -> SetOptStat(1111);
  gStyle -> SetOptFit(1110);
  
  TFile* inFile = TFile::Open("./plots/plots_studyPedestal_test_run1375.root");
  
  for(int iCh = 0; iCh < 4; ++iCh)
  {
    TGraph* g = (TGraph*)( inFile->Get(Form("evt0/g_trigger_waveform_ch%02d",iCh)) );
    g -> SetMarkerSize(0.7);
    g -> SetMarkerColor(1+iCh);
    g -> SetLineColor(1+iCh);
    if( iCh == 0 ) g -> Draw("APL");
    else           g -> Draw("PL,same");
    
    
    TF1* fitFunc = new TF1(Form("fitFunc_ch%02d",iCh),"[0]+[1]/(exp((x-[2])/[3])+1)",0.,200.);
    fitFunc -> SetParameters(0.,2200.,165.,1.);
    g -> Fit(Form("fitFunc_ch%02d",iCh),"Q");
    fitFunc -> SetLineWidth(2);
    fitFunc -> SetLineColor(1+iCh);
    //fitFunc -> Draw("sames");
  }
}
