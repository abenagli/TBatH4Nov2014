void drawRMS(const std::string& inFileName)
{
  TFile* inFile = TFile::Open(inFileName.c_str());
  
  for(unsigned int iCh = 0; iCh < 32; ++iCh)
  {
    TCanvas* c = new TCanvas(Form("c_%02d",iCh),Form("c_%02d",iCh));
    TH1F* histo = (TH1F*)( inFile->Get(Form("h_rms_ch%02d",iCh)) );
    histo -> Rebin(2);
    histo -> Draw();
    
    TSpectrum* s = new TSpectrum(4);
    int nfound = s -> Search(histo,0.2,"",0.01);
    float* peakX = s -> GetPositionX();
    
    TF1* fitFunc1 = new TF1(Form("fitFunc1_%02d",iCh),"[0]*exp(-1.*(x-[1])*(x-[1])/(2*[2]*[2]))",0.,6.);
    fitFunc1 -> SetParameters(1.,3.,0.5);
    fitFunc1 -> SetParLimits(1,2.,3.5);
    fitFunc1 -> SetParLimits(2,0.,1.);
    histo -> Fit(Form("fitFunc1_%02d",iCh),"QNRS+","",0.,3.5);
    fitFunc1 -> SetNpx(10000);
    fitFunc1 -> SetLineWidth(2);
    fitFunc1 -> SetLineColor(kRed);
    fitFunc1 -> Draw("same");
    
    TF1* fitFunc2 = new TF1(Form("fitFunc2_%02d",iCh),"[0]*exp(-1.*(x-[1])*(x-[1])/(2*[2]*[2]))",0.,6.);
    fitFunc2 -> SetParameters(10.,6.,0.2);
    fitFunc2 -> SetParLimits(1,4.,6.);
    fitFunc2 -> SetParLimits(2,0.,0.5);
    histo -> Fit(Form("fitFunc2_%02d",iCh),"QNRS+","",4.,6.);
    fitFunc2 -> SetNpx(10000);
    fitFunc2 -> SetLineWidth(2);
    fitFunc2 -> SetLineColor(kBlue);
    fitFunc2 -> Draw("same");
    
    TF1* fitFunc3 = new TF1(Form("fitFunc3_%02d",iCh),"[0]*exp(-1.*(x-[1])*(x-[1])/(2*[2]*[2]))+[3]*exp(-1.*(x-[4])*(x-[4])/(2*[5]*[5]))",0.,6.);
    fitFunc3 -> SetParameters(fitFunc1->GetParameter(0),fitFunc1->GetParameter(1),fitFunc1->GetParameter(2),fitFunc2->GetParameter(0),fitFunc2->GetParameter(1),fitFunc2->GetParameter(2));
    //fitFunc3 -> SetParLimits(1,4.,6.);
    //fitFunc3 -> SetParLimits(2,0.,0.5);
    histo -> Fit(Form("fitFunc3_%02d",iCh),"QNRS+","",0.,6.);
    fitFunc3 -> SetNpx(10000);
    fitFunc3 -> SetLineWidth(2);
    fitFunc3 -> SetLineColor(kGreen);
    fitFunc3 -> Draw("same");
  }
}
