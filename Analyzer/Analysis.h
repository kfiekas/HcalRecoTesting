#ifndef Analysis_H
#define Analysis_H

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TFile.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMinuit.h"

// Include all of the other classes
#include "HcalPulseShapes.h"
#include "HcalPulseShape.h"
#include "HybridMinimizer.h"
#include "PulseShapeFitOOTPileupCorrection.h"
#include "HLTAnalyzer.h"
#include "HLTv2.h"

#include "inverseGaussCDF.hh"
#include "sampleQuantile.hh"
#include "PedestalSub.h"

#include <string>
#include <vector>
#include <math.h>

#include "analysistree.h"

using namespace std;
const double EL_CHARGE=1.60217657*pow(10,-19);
const double FEMTO=pow(10,-15);

double x[10],y[10],errory[10];

class Analysis : public analysistree
{
 public:

  enum HcalRegion {All, Barrel, Endcap};

  string Input_File;
  string Output_File;
  string Plot_Dir;
  int Entries;
  int Region;
  int Baseline;
  int Time_Slew;
  int Neg_Charges;
  float Threshold;
  float Quantile;

  int nevents =0;
  
  //Histograms

  TH1D* hPedSub;

  TH2D *h45vHLT;
  TProfile *p45vHLT;

  TH2D *hM2vHLT;
  TProfile *pM2vHLT;

  TH1D *a3, *a4, *a5;
  TH2D *a4v3, *a4v5, *a5v3;

  Analysis(TTree *tree);
  ~Analysis();

  void Init(char* paramfile);
  void DefineHistograms();
  void Process();
  void MakeCutflow();
  void FillHistograms();
  void Finish();

  void MakePedestalPlots();
  void useMethod2(){psFitOOTpuCorr_ = std::auto_ptr<PulseShapeFitOOTPileupCorrection>(new PulseShapeFitOOTPileupCorrection()); }
  std::auto_ptr<PedestalSub> pedSubFxn_= std::auto_ptr<PedestalSub>(new PedestalSub());
         
 private:
  TFile *fout;
  std::auto_ptr<PulseShapeFitOOTPileupCorrection> psFitOOTpuCorr_= std::auto_ptr<PulseShapeFitOOTPileupCorrection>(new PulseShapeFitOOTPileupCorrection());
  std::auto_ptr<HLTv2> hltv2_= std::auto_ptr<HLTv2>(new HLTv2());

  HcalPulseShapes theHcalPulseShapes_;

};
#endif // Analysis_H 
