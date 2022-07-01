/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

//include root libraries
#include <TCanvas.h>

#include <TList.h>

#include <TH1.h>

#include <TH2.h>

#include <TH3.h>

#include <TProfile.h>

#include <TChain.h>

#include "TMath.h"

#include <TObjArray.h>

#include <TRandom3.h>

#include <THnSparse.h>
 //include aliroot libraries
#include "AliLog.h"

#include "AliAnalysisManager.h"

#include "AliAODv0.h"

#include "AliVEvent.h"

#include "AliESDEvent.h"

#include "AliAODEvent.h"

#include "AliVVZERO.h"

#include "AliESDVZERO.h"

#include "AliAODVZERO.h"

#include "AliVVertex.h"

#include "AliESDVertex.h"

#include "AliAODVertex.h"

#include "AliAnalysisMuonUtility.h"

#include "AliAnalysisUtils.h"

#include "AliMuonTrackCuts.h"

#include "AliMuonEventCuts.h"

#include "AliOADBMuonTrackCutsParam.h"

#include "AliCentrality.h"

#include "AliVTrack.h"

#include "AliAODTrack.h"

#include "AliAODTracklets.h"

#include "AliAODHeader.h"

#include "AliESDMuonTrack.h"

#include "AliInputEventHandler.h"

#include "AliAnalysisManager.h"

#include "AliAODMCParticle.h"

#include "AliVertexingHFUtils.h"

#include "AliCounterCollection.h"

#include "AliTriggerAnalysis.h"
 //include the class header file
#include "AliAnalysisTaskMuonVsMult.h"
#include  "AliMultSelection.h"

#include "AliAODMCHeader.h"

#include "AliGenEventHeader.h"

#include "AliGenHijingEventHeader.h"

#include "AliGenDPMjetEventHeader.h"

#include "AliGenPythiaEventHeader.h"

#include "AliGenCocktailEventHeader.h"


ClassImp(AliAnalysisTaskMuonVsMult)

//====================================================================================================================================================================
AliAnalysisTaskMuonVsMult::AliAnalysisTaskMuonVsMult(): AliAnalysisTaskSE(),
  fUtils(0x0),
  fMuonTrackCuts(0x0),
  hEventsPerRun(0x0),
  hMBEventsCounter(0x0),
  hSingleMu(0x0),
  hAcceptedMuons(0x0),
  hPtEta(0x0),
  hPtThetaAbs(0x0),
  hMatchTrigger(0x0),
  hPdca(0x0),
  hEtaAcceptedMuons(0x0),
  hEta(0x0),
  hEtaThetaAbs(0x0),
  hEtaMatchTrigger(0x0),
  hEtaPdca(0x0),

  // tracklets
  hTrackletsPerEvent(0x0),
  hTrackletsVsZVertex(0x0),
  hMeanTrackletsVsZVertex(0x0),
  hMBTrackletsVsZVertex(0x0),
  hMBMeanTrackletsVsZVertex(0x0),
  hMBTrackletsPerEvent(0x0),
  // vertexZ
  fSPDMeanTracklets(0x0),
  hReferenceProfile(0x0),
  // raw tracklets
  hRawTrackletsPerEvent(0x0),
  hRawTrackletsVsZVertex(0x0),
  hMBRawTrackletsVsZVertex(0x0),
  hMeanRawTrackletsVsZVertex(0x0),
  hMBMeanRawTrackletsVsZVertex(0x0),
  hMBRawTrackletsPerEvent(0x0),
  //
  hCorrectedVsRawTracklets(0x0),
  hMBCorrectedVsRawTracklets(0x0),
  
  fMinEtaForTracklets(-1.),
  fMaxEtaForTracklets(1.),
  
  ////
  listPhysics(0x0),
  listEvents(0x0),
  listSPDTracklets(0x0),
  fRand(0x0)
{
  // Dummy constructor ALWAYS needed for I/O.
}

//====================================================================================================================================================================
AliAnalysisTaskMuonVsMult::AliAnalysisTaskMuonVsMult(const char * name): AliAnalysisTaskSE(name),
  fUtils(0x0),

  hEventsPerRun(0x0),
  hMBEventsCounter(0x0),
  hSingleMu(0x0),
  hAcceptedMuons(0x0),
  hPtEta(0x0),
  hPtThetaAbs(0x0),
  hMatchTrigger(0x0),
  hPdca(0x0),
  hEtaAcceptedMuons(0x0),
  hEta(0x0),
  hEtaThetaAbs(0x0),
  hEtaMatchTrigger(0x0),
  hEtaPdca(0x0),

  // tracklets
  hTrackletsPerEvent(0x0),
  hTrackletsVsZVertex(0x0),
  hMeanTrackletsVsZVertex(0x0),
  hMBTrackletsVsZVertex(0x0),
  hMBMeanTrackletsVsZVertex(0x0),
  hMBTrackletsPerEvent(0x0),
  // vertexZ
  fSPDMeanTracklets(0x0),
  hReferenceProfile(0x0),
  // raw tracklets
  hRawTrackletsPerEvent(0x0),
  hRawTrackletsVsZVertex(0x0),
  hMBRawTrackletsVsZVertex(0x0),
  hMeanRawTrackletsVsZVertex(0x0),
  hMBMeanRawTrackletsVsZVertex(0x0),
  hMBRawTrackletsPerEvent(0x0),
  hCorrectedVsRawTracklets(0x0),
  hMBCorrectedVsRawTracklets(0x0),
  
  fMinEtaForTracklets(-1.),
  fMaxEtaForTracklets(1.),
  
  listPhysics(0x0),
  listEvents(0x0),
  listSPDTracklets(0x0),
  //
  fMuonTrackCuts(new AliMuonTrackCuts("stdMuonCuts", "stdMuonCuts")),
  fRand(0x0)
  //
{
  fUtils = new AliAnalysisUtils();
  // Input slot #0 works with a TChain - it is connected to the default input container
  DefineInput(0, TChain::Class());
  DefineOutput(1, TList::Class()); // for output objarray
  DefineOutput(2, TList::Class()); // for output objarray
  DefineOutput(3, TList::Class());

}

//====================================================================================================================================================================
AliAnalysisTaskMuonVsMult::~AliAnalysisTaskMuonVsMult() {
  // Destructor. Clean-up the output list, but not the histograms that are put inside
  // (the list is owner and will clean-up these histograms). Protect in PROOF case.
  if (!AliAnalysisManager::GetAnalysisManager() -> IsProofMode()) {
    if (listPhysics) delete listPhysics;
    if (listEvents) delete listEvents;
    if (listSPDTracklets) delete listSPDTracklets;
  }

  if (fUtils) delete fUtils;
  delete fRand;
  delete fSPDMeanTracklets;

  delete fMuonTrackCuts;
}

//====================================================================================================================================================================
void AliAnalysisTaskMuonVsMult::NotifyRun() {
  /// Set run number for cuts
  fMuonTrackCuts -> SetRun(fInputHandler);
}

//====================================================================================================================================================================
void AliAnalysisTaskMuonVsMult::UserCreateOutputObjects() {
  listEvents = new TList();
  listEvents -> SetOwner();

  listPhysics = new TList();
  listPhysics -> SetOwner();

  listSPDTracklets = new TList();
  listSPDTracklets -> SetOwner();

  Int_t pTNBins = 80;
  Float_t pTMinBin = 0.;
  Float_t pTMaxBin = 80.;

  Int_t yNBins = 15;
  Float_t yMinBin = -4;
  Float_t yMaxBin = -2.5;

  Float_t nTrackMax = 350;
  float zmax = 20;
  float zNbins = 10 * zmax; //200;
  float zcut = 10;

  //definition of Events histograms
  Int_t runFirst = /* 266437 */ 265594;
  Int_t runLast = /*267131 */ 266318;
  Int_t nRuns = runLast - runFirst;

  hEventsPerRun = new TH1I("hEventsPerRun", "Events per run", nRuns, runFirst, runLast);
  hEventsPerRun -> SetStats(kTRUE);
  hEventsPerRun -> GetYaxis() -> SetTitle("Events");
  hEventsPerRun -> Sumw2();
  listEvents -> Add(hEventsPerRun);

//   TString trigString = "CMSH7-B-NOPF-MUFAST";
//   hEventsCounter = new TH1I("hEventsCounter", "hEventsCounter CMSH", 9, 0, 9);
//   hEventsCounter -> SetStats(kTRUE);
//   hEventsCounter -> Sumw2();
//   TString counterLabel[] = {
//     "All evts",
//     trigString,
//     trigString + " after PS",
//     "IsPrimaryVertex",
//     "IsSPDVertex",
//     "nContrib(SPD) > 0",
//     "#sigma_{z}^{SPD} < 0.25 cm",
//     "|zVertex| < 10 cm",
//     "Acc tracklet evnts"
//   };
//   for (int i = 0; i < 9; i++) {
//     hEventsCounter -> GetXaxis() -> SetBinLabel(i + 1, counterLabel[i].Data());
//   }
//   listEvents -> Add(hEventsCounter);
  
  hMBEventsCounter = new TH1I("hMBEventsCounter", "EventsCounter CINT7", 9, 0, 9);
  hMBEventsCounter -> SetStats(kTRUE);
  hMBEventsCounter -> Sumw2();
  TString MBcounterLabel[] = {
    "All evts",
    " + PS",
    "+ nContrib(SPD) > 0",
    "+ |zVertex| < 10 cm",
    "+ CINT7-B-NOPF-MUFAST",
    "+ #sigma_{z}^{SPD} < 0.25 cm",
    "PS + Good vertex + CINT7-B-NOPF-CENT",
    "PS + Good vertex + CMSL7-B-NOPF-MUFAST",
    "PS + Good vertex + CMSH7-B-NOPF-MUFAST"
  };
  for (int i = 0; i < 9; i++) {
    hMBEventsCounter -> GetXaxis() -> SetBinLabel(i+1, MBcounterLabel[i].Data());
  }
  listEvents -> Add(hMBEventsCounter);

  //    //definition of Physics histograms

  //pt, eta, zv, mult, charge
  Int_t bins[kNvars] = {
    80,
    15,
    200,
    350,
    2
  };
  Double_t min[kNvars] = {
    0,
    -4,
    -10,
    0,
    -2
  };
  Double_t max[kNvars] = {
    80,
    -2.5,
    10,
    350,
    2
  };

  hSingleMu = new THnSparseD("hn", "hn", kNvars, bins, min, max);
  listPhysics -> Add(hSingleMu);

  Float_t Nptbins = 80;
  Float_t ptmin = 0;
  Float_t ptmax = 80;

  Float_t Netabins = 15;
  Float_t etamin = -4;
  Float_t etamax = -2.5;

  hAcceptedMuons = new TH1F("hAcceptedMuons", "", Nptbins, ptmin, ptmax);
  AliAnalysisTaskMuonVsMult::SetHisto(hAcceptedMuons, "#it{p}_{T} (GeV/c)", "", listPhysics);

  hEtaAcceptedMuons = new TH1F("hEtaAcceptedMuons", "", Netabins, etamin, etamax);
  AliAnalysisTaskMuonVsMult::SetHisto(hEtaAcceptedMuons, "#eta", "", listPhysics);

  hPtEta = new TH1F("hPtEta", "", Nptbins, ptmin, ptmax);
  AliAnalysisTaskMuonVsMult::SetHisto(hPtEta, "#it{p}_{T} (GeV/c)", "", listPhysics);

  hPtThetaAbs = new TH1F("hPtThetaAbs", "", Nptbins, ptmin, ptmax);
  AliAnalysisTaskMuonVsMult::SetHisto(hPtThetaAbs, "#it{p}_{T} (GeV/c)", "", listPhysics);

  hMatchTrigger = new TH1F("hMatchTrigger", "", Nptbins, ptmin, ptmax);
  AliAnalysisTaskMuonVsMult::SetHisto(hMatchTrigger, "#it{p}_{T} (GeV/c)", "", listPhysics);

  hPdca = new TH1F("hPdca", "", Nptbins, ptmin, ptmax);
  AliAnalysisTaskMuonVsMult::SetHisto(hPdca, "#it{p}_{T} (GeV/c)", "", listPhysics);

  hEta = new TH1F("hEta", "", Netabins, etamin, etamax);
  AliAnalysisTaskMuonVsMult::SetHisto(hEta, "#eta", "", listPhysics);

  hEtaThetaAbs = new TH1F("hEtaThetaAbs", "", Netabins, etamin, etamax);
  AliAnalysisTaskMuonVsMult::SetHisto(hEtaThetaAbs, "#eta", "", listPhysics);

  hEtaMatchTrigger = new TH1F("hEtaMatchTrigger", "", Netabins, etamin, etamax);
  AliAnalysisTaskMuonVsMult::SetHisto(hEtaMatchTrigger, "#eta", "", listPhysics);

  hEtaPdca = new TH1F("hEtaPdca", "", Netabins, etamin, etamax);
  AliAnalysisTaskMuonVsMult::SetHisto(hEtaPdca, "#eta", "", listPhysics);

  // TRACKLETS histograms

  if (fSPDMeanTracklets) {
    hReferenceProfile = (TProfile * ) fSPDMeanTracklets -> Clone();
    listSPDTracklets -> Add(hReferenceProfile);
  }

  hTrackletsPerEvent = new TH1F("hTrackletsPerEvent", "", nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hTrackletsPerEvent, "N^{corr}", "", listSPDTracklets);

  hRawTrackletsPerEvent = new TH1F("hRawTrackletsPerEvent", "N^{raw}", nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hRawTrackletsPerEvent, "N^{raw}", "", listSPDTracklets);

  hMeanTrackletsVsZVertex = new TProfile("hMeanTrackletsVsZVertex", "", TMath::Nint(2 * zcut / 0.25), -zcut, zcut);
  AliAnalysisTaskMuonVsMult::SetHisto(hMeanTrackletsVsZVertex, "zVertex (cm)", "<N^{corr}>", listSPDTracklets);

  hMeanRawTrackletsVsZVertex = new TProfile("hMeanRawTrackletsVsZVertex", "", TMath::Nint(2 * zcut / 0.25), -zcut, zcut);
  AliAnalysisTaskMuonVsMult::SetHisto(hMeanRawTrackletsVsZVertex, "zVertex (cm)", "<N^{raw}>", listSPDTracklets);

  hTrackletsVsZVertex = new TH2F("hTrackletsVsZVertex", "", TMath::Nint(2 * zcut / 0.25), -zcut, zcut, nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hTrackletsVsZVertex, "zVertex (cm)", "N^{corr}", listSPDTracklets);

  hRawTrackletsVsZVertex = new TH2F("hRawTrackletsVsZVertex", "", TMath::Nint(2 * zcut / 0.25), -zcut, zcut, nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hRawTrackletsVsZVertex, "zVertex (cm)", "nTracklets^{raw}", listSPDTracklets);

  fRand = new TRandom3(0);

  // MB histograms

  hMBRawTrackletsPerEvent = new TH1F("hMBRawTrackletsPerEvent", "N^{raw}", nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hMBRawTrackletsPerEvent, "N^{raw}", "", listSPDTracklets);

  hMBTrackletsVsZVertex = new TH2F("hMBTrackletsVsZVertex", "", zNbins, -zcut, zcut, nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hMBTrackletsVsZVertex, "zVertex (cm)", "nTracklets^{corr}", listSPDTracklets);

  hMBRawTrackletsVsZVertex = new TH2F("hMBRawTrackletsVsZVertex", "corrected N_tr vs zVertex (CINT)", zNbins, -zcut, zcut, nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hMBRawTrackletsVsZVertex, "zVertex (cm)", "nTracklets^{raw}", listSPDTracklets);

  hCorrectedVsRawTracklets = new TH2F("hCorrectedVsRawTracklets", "N^{corr} - N^{raw}", nTrackMax, 0, nTrackMax, nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hCorrectedVsRawTracklets, "N^{raw}", "N^{corr}", listSPDTracklets);

  hMBCorrectedVsRawTracklets = new TH2F("hMBCorrectedVsRawTracklets", "N^{corr} - N^{raw} (CINT)", nTrackMax, 0, nTrackMax, nTrackMax, 0, nTrackMax);
  AliAnalysisTaskMuonVsMult::SetHisto(hMBCorrectedVsRawTracklets, "N^{raw}", "N^{corr}", listSPDTracklets);

  hMBMeanTrackletsVsZVertex = new TProfile("hMBMeanTrackletsVsZVertex", "", TMath::Nint(2 * zcut / 0.25), -zcut, zcut);
  hMBMeanTrackletsVsZVertex -> GetXaxis() -> SetTitle("zVertex (cm)");
  hMBMeanTrackletsVsZVertex -> GetYaxis() -> SetTitle("<N^{corr}>");
  listSPDTracklets -> Add(hMBMeanTrackletsVsZVertex);

  hMBMeanRawTrackletsVsZVertex = new TProfile("hMBMeanRawTrackletsVsZVertex", "", TMath::Nint(2 * zcut / 0.25), -zcut, zcut);
  hMBMeanRawTrackletsVsZVertex -> GetXaxis() -> SetTitle("zVertex (cm)");
  hMBMeanRawTrackletsVsZVertex -> GetYaxis() -> SetTitle("<N^{raw}>");
  listSPDTracklets -> Add(hMBMeanRawTrackletsVsZVertex);

  hMBTrackletsPerEvent = new TH1F("hMBTrackletsPerEvent", "", nTrackMax, 0, nTrackMax);
  hMBTrackletsPerEvent -> SetStats(kTRUE);
  hMBTrackletsPerEvent -> GetXaxis() -> SetTitle("nTracklets^{corr}");
  hMBTrackletsPerEvent -> Sumw2();
  listSPDTracklets -> Add(hMBTrackletsPerEvent);
  
//     fHistZvtx         = new TH1F("fHistZvtx", "Z - vtx distribution with all events", 300, -15.0, 15.0);
//     fHistZvtxWPS      = new TH1F("fHistZvtxWPS", "Z - vtx distribution with PS", 300, -15.0, 15.0);
//     fHistZvtxMSL      = new TH1F("fHistZvtxMSL", "Z - vtx distribution with CMSL7 Trigger selected", 300, -15.0, 15.0);
//     fHistZvtxNContMSL = new TH1F("fHistZvtxNContMSL", "Z - vtx distribution with with Ncontributors (MSL)", 300, -15.0, 15.0);
//     fHistGoodVtxMSL   = new TH1F("fHistGoodVtxMSL", "Z - vtx distribution |zvtx| < 10 cm (MSH)", 300, -15.0, 15.0);
  

   TString CentInterval[9] = {
        "0_100",
        "0_10",
        "10_20",
        "20_30",
        "30_40",
        "40_50",
        "50_60",
        "60_70",
        "70_100"
        
    };
    
    TString MultInterval[6] = {
        "0_300",
        "1_37",
        "38_54",
        "55_94",
        "95_121",
        "121_300"
        
    }; 
    
  //vars: Pt, eta, Z-vtx, centrality, charge
    Int_t nBins[5] = {80, 25, 40, 100, 2};
    Double_t binMin[5] = {0, -4.5, -20, 0, -2};
    Double_t binMax[5] = {80, -2, 20, 100, 2};
    
    TString nameSparse= " ";
    THnSparseF *fHistSingleMuCENT[9];
    for (Int_t i = 0; i < 9; i++){
         nameSparse = "fHistSingleMuCENT";
         nameSparse +=CentInterval[i];
         fHistSingleMuCENT[i]= new THnSparseF(nameSparse.Data()," ",5, nBins,binMin,binMax);
         fHistSingleMuCENT[i]->Sumw2();
         listPhysics->Add(fHistSingleMuCENT[i]);
     }
     
        TString nameSparseMSL= " ";
   THnSparseF *fHistSingleMuCENTMSL[9];
   for (Int_t i = 0; i < 9; i++){
        nameSparseMSL = "fHistSingleMuCENTMSL";
        nameSparseMSL +=CentInterval[i];
        fHistSingleMuCENTMSL[i]= new THnSparseF(nameSparseMSL.Data()," ",5, nBins,binMin,binMax);
        fHistSingleMuCENTMSL[i]->Sumw2();
        listPhysics->Add(fHistSingleMuCENTMSL[i]);
    }
     
     //vars: Pt, eta, Z-vtx, centrality, charge
    Int_t nBinsMult[5] = {80, 25, 40, 300, 2};
    Double_t binMinMult[5] = {0, -4.5, -20, 0, -2};
    Double_t binMaxMult[5] = {80, -2, 20, 300, 2};
    
    TString nameSparseMult= " ";
    THnSparseF *fHistSingleMuMULT[6];
    for (Int_t i = 0; i < 6; i++){
         nameSparse = "fHistSingleMuMULT";
         nameSparse +=MultInterval[i];
         fHistSingleMuMULT[i]= new THnSparseF(nameSparse.Data()," ",5, nBinsMult,binMinMult,binMaxMult);
         fHistSingleMuMULT[i]->Sumw2();
         listPhysics->Add(fHistSingleMuMULT[i]);
     }
     
      TString nameSparseMultMSL= " ";
 THnSparseF *fHistSingleMuMULTMSL[6];
 for (Int_t i = 0; i < 6; i++){
      nameSparseMSL = "fHistSingleMuMULTMSL";
      nameSparseMSL +=MultInterval[i];
      fHistSingleMuMULTMSL[i]= new THnSparseF(nameSparseMSL.Data()," ",5, nBinsMult,binMinMult,binMaxMult);
      fHistSingleMuMULTMSL[i]->Sumw2();
      listPhysics->Add(fHistSingleMuMULTMSL[i]);
  }
  
  PostData(1, listEvents);
  PostData(2, listSPDTracklets);
  PostData(3, listPhysics);

}

//=====================================================================================================================
void AliAnalysisTaskMuonVsMult::UserExec(Option_t * ) {
  AliAODEvent * aod = 0;
  AliAODVertex * vertex = NULL;
  AliAODVertex * vertexSPD = NULL;
  
  Float_t fPercent=-1;
  
  //Check if the event is AOD or ESD
  aod = dynamic_cast<AliAODEvent*>(InputEvent());   
                                                    
    if(!aod) {
        AliError ("AOD event not found. Nothing done!");
        return;
    }
    
    if (aod) hMBEventsCounter -> Fill(0);
    
    vertex = const_cast < AliAODVertex * > (aod -> GetPrimaryVertex()); // gives primary vertex!!!
    vertexSPD = const_cast < AliAODVertex * > (aod -> GetPrimaryVertexSPD()); //gives SPD vertex 

  //return;
  int nContributorsPrimary = vertex -> GetNContributors();
  double zVertex = vertexSPD -> GetZ();
  int nContributors = vertexSPD -> GetNContributors();
  double cov[6] = {0};
  vertexSPD -> GetCovarianceMatrix(cov);
  double zRes = TMath::Sqrt(cov[5]);
  
  int runNumber = aod -> GetRunNumber();
  
  AliAODHeader *aodheader=dynamic_cast<AliAODHeader*>(aod->GetHeader());
    TString firedtrigger = aodheader->GetFiredTriggerClasses();
  
    Bool_t TriggerSelected=kFALSE;
    Bool_t TriggerSelected_CINT7=kFALSE;
    Bool_t TriggerSelected_CMSL7=kFALSE;
    Bool_t TriggerSelected_CMSH7=kFALSE;
    Bool_t TriggerSelected_CINT7_CENT=kFALSE;
    
    
    if(firedtrigger.Contains("CINT7-B-NOPF-MUFAST")) TriggerSelected_CINT7 = kTRUE;
    else TriggerSelected_CINT7 = kFALSE;
    if(firedtrigger.Contains("CMSL7-B-NOPF-MUFAST")) TriggerSelected_CMSL7 = kTRUE;
    else TriggerSelected_CMSL7 = kFALSE;
    if(firedtrigger.Contains("CMSH7-B-NOPF-MUFAST")) TriggerSelected_CMSH7 = kTRUE;
    else TriggerSelected_CMSH7 = kFALSE;
    if(firedtrigger.Contains("CINT7-B-NOPF-CENT")) TriggerSelected_CINT7_CENT = kTRUE;
    else TriggerSelected_CINT7_CENT = kFALSE;

  UInt_t fSelectMask = ((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected();
    Bool_t IsPhysSelected = fSelectMask & (AliVEvent::kINT7 | AliVEvent::kMuonUnlikeLowPt7 | AliVEvent::kMuonLikeLowPt7 | AliVEvent::kMuonSingleLowPt7 | AliVEvent::kMuonSingleHighPt7 | AliVEvent::kINT7inMUON);
    
    Float_t Perc = 300;
    
      AliMultSelection *MultSelection = 0x0;
    MultSelection = (AliMultSelection * ) aod -> FindListObject("MultSelection");
    
    if (!MultSelection) {
        // If you get this warning (and lPercentiles 300) please check that the AliMultSelectionTask actually ran (before your task)
        AliWarning("AliMultSelection object not found!");
        
    }
    else{
            Perc = MultSelection->GetMultiplicityPercentile("SPDTracklets");
            fPercent = Perc;
            }
    
    if(IsPhysSelected){
        
        hMBEventsCounter -> Fill(1);
    
  if (!(nContributors >1)) return;
 hMBEventsCounter -> Fill(2);
 
 if (!(TMath::Abs(zVertex) <10)) return;
 hMBEventsCounter -> Fill(3);
 
 
// 
 
//  
 if(TriggerSelected_CINT7){
     hMBEventsCounter -> Fill(4);
//     cout << " ******************************************************** "<<  endl; 
   if (!(zRes > 0.25))
   hMBEventsCounter -> Fill(5);
     
}
 
if(TriggerSelected_CINT7_CENT){
     hMBEventsCounter -> Fill(6);     
     
}
 
if(TriggerSelected_CMSL7){
     hMBEventsCounter -> Fill(7);
     
}

if(TriggerSelected_CMSH7){
     hMBEventsCounter -> Fill(8);
//     cout << " ******************************************************** "<<  endl;  
}

int count = 0;
double correctedCount = 0;
 if(TriggerSelected_CINT7){
 
 int ncorr = -1; // this way if not accepted and thus no correction -> will be excluded from counting
 
 double Nref, MeanNtrkl;
 
 
 
    // SPD analysis get tracklet counts
  AliAODTracklets * trackletsData = (AliAODTracklets * ) aod -> GetTracklets();
  int nSPDTracklets = trackletsData -> GetNumberOfTracklets();
  

    count = AliVertexingHFUtils::GetNumberOfTrackletsInEtaRange(aod, fMinEtaForTracklets, fMaxEtaForTracklets);

    Double_t corrfactor = 1.;
    
    MeanNref = fSPDMeanTracklets -> GetMaximum();
    MeanNtrkl = fSPDMeanTracklets -> GetBinContent(fSPDMeanTracklets -> FindBin(vertexSPD -> GetZ());
    
    
    if (fSPDMeanTracklets) corrfactor = count - PoissonD(count * ((MeanNref/MeanNtrkl)-1);
        
//         fSPDMeanTracklets -> GetMaximum() / fSPDMeanTracklets -> GetBinContent(fSPDMeanTracklets -> FindBin(vertexSPD -> GetZ()));
//     Double_t deltaN = (corrfactor * count) - count;
//     Int_t missingtracklets = fRand -> PoissonD(TMath::Abs(deltaN));

    correctedCount = count + missingtracklets;
    if (correctedCount < 0) correctedCount = 0;

      hMBTrackletsPerEvent -> Fill(correctedCount);
      hMBRawTrackletsPerEvent -> Fill(count);

      hMBTrackletsVsZVertex -> Fill(zVertex, correctedCount);
      hMBRawTrackletsVsZVertex -> Fill(zVertex, count);
      hMBCorrectedVsRawTracklets -> Fill(count, correctedCount);

      hMBMeanTrackletsVsZVertex -> Fill(zVertex, correctedCount);
      hMBMeanRawTrackletsVsZVertex -> Fill(zVertex, count);
      //
   }
if(TriggerSelected_CMSH7){
   

      hTrackletsPerEvent -> Fill(correctedCount);
      hRawTrackletsPerEvent -> Fill(count);

      hTrackletsVsZVertex -> Fill(zVertex, correctedCount);
      hRawTrackletsVsZVertex -> Fill(zVertex, count);
      hCorrectedVsRawTracklets -> Fill(count, correctedCount);

      hMeanTrackletsVsZVertex -> Fill(zVertex, correctedCount);
      hMeanRawTrackletsVsZVertex -> Fill(zVertex, count);

    }


  // HF Muon analysis 
    Double_t data[kNvars];
    Double_t data0_100[5];
    Double_t data0_10[5];
    Double_t data10_20[5];
    Double_t data20_30[5];
    Double_t data30_40[5];
    Double_t data40_50[5];
    Double_t data50_60[5];
    Double_t data60_70[5];
    Double_t data70_100[5];
    
    Double_t data0_300[5];
    Double_t data1_37[5];
    Double_t data38_54[5];
    Double_t data55_94[5];
    Double_t data95_121[5];
    Double_t data121_300[5];
    
    Double_t dataMSL[kNvars];
    Double_t dataMSL0_100[5];
    Double_t dataMSL0_10[5];
    Double_t dataMSL10_20[5];
    Double_t dataMSL20_30[5];
    Double_t dataMSL30_40[5];
    Double_t dataMSL40_50[5];
    Double_t dataMSL50_60[5];
    Double_t dataMSL60_70[5];
    Double_t dataMSL70_100[5];
    
    Double_t dataMSL0_300[5];
    Double_t dataMSL1_37[5];
    Double_t dataMSL38_54[5];
    Double_t dataMSL55_94[5];
    Double_t dataMSL95_121[5];
    Double_t dataMSL121_300[5];
    
    if(TriggerSelected_CMSH7){

    for (Int_t iTracks = 0; iTracks < aod -> GetNumberOfTracks(); iTracks++) {
      AliAODTrack * track = dynamic_cast < AliAODTrack * > (aod -> GetTrack(iTracks));
      if (!track) {
        printf("ERROR: Could not receive track %d\n", iTracks);
        continue;

      }
      if (!track -> IsMuonTrack()) continue;

      hAcceptedMuons -> Fill(track -> Pt());
      hEtaAcceptedMuons -> Fill(track -> Eta());

      if (track -> Eta() < -4 || track -> Eta() > -2.5) continue;

      hPtEta -> Fill(track -> Pt());
      hEta -> Fill(track -> Eta());

      if (track -> GetRAtAbsorberEnd() < 17.6 || track -> GetRAtAbsorberEnd() > 89.5) continue;

      hPtThetaAbs -> Fill(track -> Pt());
      hEtaThetaAbs -> Fill(track -> Eta());

      if (track -> GetMatchTrigger() <= 2) continue; // <=1 for match low pt, <=2 for match high pt

      hMatchTrigger -> Fill(track -> Pt());
      hEtaMatchTrigger -> Fill(track -> Eta());

      if (!fMuonTrackCuts -> IsSelected(track)) continue;

      hPdca -> Fill(track -> Pt());
      hEtaPdca -> Fill(track -> Eta());

      data[kPt] = track -> Pt();
      data[kEta] = track -> Eta();
      data[kCharge] = track -> Charge() / 3;
      data[kMult] = correctedCount;
      data[kVz] = vertex -> GetZ();

      hSingleMu -> Fill(data);
      
      if(fPercent > 0 && fPercent <= 100) {
//                         cout << "fPercent0_100=" << " " << fPercent << endl;
                        data0_100[kPt0_100]     = track->Pt();
                        data0_100[kEta0_100]     = track->Eta();
                        data0_100[kCharge0_100] = track->Charge()/3;
                        data0_100[kPercent0_100] = fPercent;
                        data0_100[kVz0_100] = vertex->GetZ();
                        
                        ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT0_100"))-> Fill(data0_100);
                    }

                    
       if(fPercent > 0 && fPercent <= 10) {
//                          cout << "fPercent0_10=" << " " << fPercent << endl;
                       data0_10[kPt0_10]     = track->Pt();
                       data0_10[kEta0_10]     = track->Eta();
                       data0_10[kCharge0_10] = track->Charge()/3;
                       data0_10[kPercent0_10] = fPercent;
                       data0_10[kVz0_10] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT0_10")) -> Fill(data0_10);
                   }    
    if(fPercent > 10 && fPercent <= 20) {
//                          cout << "fPercent0_10=" << " " << fPercent << endl;
                    data10_20[kPt10_20]     = track->Pt();
                    data10_20[kEta10_20]     = track->Eta();
                    data10_20[kCharge10_20] = track->Charge()/3;
                    data10_20[kPercent10_20] = fPercent;
                    data10_20[kVz10_20] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT10_20")) -> Fill(data10_20);
                }    

  
      if(fPercent > 20 && fPercent <= 30) {
//                          cout << "fPercent20_30=" << " " << fPercent << endl;
                       data20_30[kPt20_30]     = track->Pt();
                       data20_30[kEta20_30]     = track->Eta();
                       data20_30[kCharge20_30] = track->Charge()/3;
                       data20_30[kPercent20_30] = fPercent;
                       data20_30[kVz20_30] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT20_30")) -> Fill(data20_30);
                   }    
  
  
      if(fPercent > 30 && fPercent <= 40) {
//                         cout << "fPercent30_40=" << " " << fPercent << endl;
                       data30_40[kPt30_40]     = track->Pt();
                       data30_40[kEta30_40]     = track->Eta();
                       data30_40[kCharge30_40] = track->Charge()/3;
                       data30_40[kPercent30_40] = fPercent;
                       data30_40[kVz30_40] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT30_40")) -> Fill(data30_40);
                   }    
  
       if(fPercent > 40 && fPercent <= 50) {
//                         cout << "fPercent40_50=" << " " << fPercent << endl;
                       data40_50[kPt40_50]     = track->Pt();
                       data40_50[kEta40_50]     = track->Eta();
                       data40_50[kCharge40_50] = track->Charge()/3;
                       data40_50[kPercent40_50] = fPercent;
                       data40_50[kVz40_50] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT40_50")) -> Fill(data40_50);
                   } 
    
         if(fPercent > 50 && fPercent <= 60) {
//                         cout << "fPercent50_60=" << " " << fPercent << endl;
                       data50_60[kPt50_60]     = track->Pt();
                       data50_60[kEta50_60]     = track->Eta();
                       data50_60[kCharge50_60] = track->Charge()/3;
                       data50_60[kPercent50_60] = fPercent;
                       data50_60[kVz50_60] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT50_60")) -> Fill(data50_60);
                   }    
  
       if(fPercent > 60 && fPercent <= 70) {
//                         cout << "fPercent60_70=" << " " << fPercent << endl;
                       data60_70[kPt60_70]     = track->Pt();
                       data60_70[kEta60_70]     = track->Eta();
                       data60_70[kCharge60_70] = track->Charge()/3;
                       data60_70[kPercent60_70] = fPercent;
                       data60_70[kVz60_70] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT60_70")) -> Fill(data60_70);
                   }    
  
       if(fPercent > 70 && fPercent <= 100) {
//                         cout << "fPercent70_100=" << " " << fPercent << endl;
                       data70_100[kPt70_100]     = track->Pt();
                       data70_100[kEta70_100]     = track->Eta();
                       data70_100[kCharge70_100] = track->Charge()/3;
                       data70_100[kPercent70_100] = fPercent;
                       data70_100[kVz70_100] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENT70_100")) -> Fill(data70_100);
                   }    
  
  
             if(correctedCount > 0 && correctedCount <= 350) {
                       data0_300[kPt0_300]     = track->Pt();
                       data0_300[kEta0_300]     = track->Eta();
                       data0_300[kCharge0_300] = track->Charge()/3;
                       data0_300[kPercent0_300] = correctedCount;
                       data0_300[kVz0_300] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULT0_300")) -> Fill(data0_300);
             }
            if(correctedCount > 1 && correctedCount <= 37) {
                    data1_37[kPt1_37]     = track->Pt();
                    data1_37[kEta1_37]     = track->Eta();
                    data1_37[kCharge1_37] = track->Charge()/3;
                    data1_37[kPercent1_37] = correctedCount;
                    data1_37[kVz1_37] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULT1_37")) -> Fill(data1_37); 
            }    
                       if(correctedCount > 38 && correctedCount <= 54) {
                    data38_54[kPt38_54]     = track->Pt();
                    data38_54[kEta38_54]     = track->Eta();
                    data38_54[kCharge38_54] = track->Charge()/3;
                    data38_54[kPercent38_54] = correctedCount;
                    data38_54[kVz38_54] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULT38_54")) -> Fill(data38_54); 
                       }

                              if(correctedCount > 55 && correctedCount <= 94) {
                    data55_94[kPt55_94]     = track->Pt();
                    data55_94[kEta55_94]     = track->Eta();
                    data55_94[kCharge55_94] = track->Charge()/3;
                    data55_94[kPercent55_94] = correctedCount;
                    data55_94[kVz55_94] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULT55_94")) -> Fill(data55_94);
                  }
                           if(correctedCount > 95 && correctedCount <= 121) {
                    data95_121[kPt95_121]     = track->Pt();
                    data95_121[kEta95_121]     = track->Eta();
                    data95_121[kCharge95_121] = track->Charge()/3;
                    data95_121[kPercent95_121] = correctedCount;
                    data95_121[kVz95_121] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULT95_121")) -> Fill(data95_121);   
                           }
                             if(correctedCount > 121 && correctedCount <= 350) {
                    data121_300[kPt121_300]     = track->Pt();
                    data121_300[kEta121_300]     = track->Eta();
                    data121_300[kCharge121_300] = track->Charge()/3;
                    data121_300[kPercent121_300] = correctedCount;
                    data121_300[kVz121_300] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULT121_300")) -> Fill(data121_300); 
                             }
    }
 }
 
 if(TriggerSelected_CMSL7){
    for (Int_t iTracks = 0; iTracks < aod -> GetNumberOfTracks(); iTracks++) {
      AliAODTrack * track = dynamic_cast < AliAODTrack * > (aod -> GetTrack(iTracks));
      if (!track) {
        printf("ERROR: Could not receive track %d\n", iTracks);
        continue;

      }
      
       if (!track -> IsMuonTrack()) continue;

 if (track -> Eta() < -4 || track -> Eta() > -2.5) continue;
 if (track -> GetRAtAbsorberEnd() < 17.6 || track -> GetRAtAbsorberEnd() > 89.5) continue;
 if (track -> GetMatchTrigger() <= 1) continue; // <=1 for match low pt, <=2 for match high pt

 if (!fMuonTrackCuts -> IsSelected(track)) continue;
           
      if(fPercent > 0 && fPercent <= 100) {
//                         cout << "fPercent0_100=" << " " << fPercent << endl;
                        dataMSL0_100[kPt0_100]     = track->Pt();
                        dataMSL0_100[kEta0_100]     = track->Eta();
                        dataMSL0_100[kCharge0_100] = track->Charge()/3;
                        dataMSL0_100[kPercent0_100] = fPercent;
                        dataMSL0_100[kVz0_100] = vertex->GetZ();
                        
                        ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL0_100"))-> Fill(dataMSL0_100);
                    }

                    
       if(fPercent > 0 && fPercent <= 10) {
//                          cout << "fPercent0_10=" << " " << fPercent << endl;
                       dataMSL0_10[kPt0_10]     = track->Pt();
                       dataMSL0_10[kEta0_10]     = track->Eta();
                       dataMSL0_10[kCharge0_10] = track->Charge()/3;
                       dataMSL0_10[kPercent0_10] = fPercent;
                       dataMSL0_10[kVz0_10] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL0_10")) -> Fill(dataMSL0_10);
                   }    
    if(fPercent > 10 && fPercent <= 20) {
//                          cout << "fPercent0_10=" << " " << fPercent << endl;
                    dataMSL10_20[kPt10_20]     = track->Pt();
                    dataMSL10_20[kEta10_20]     = track->Eta();
                    dataMSL10_20[kCharge10_20] = track->Charge()/3;
                    dataMSL10_20[kPercent10_20] = fPercent;
                    dataMSL10_20[kVz10_20] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL10_20")) -> Fill(dataMSL10_20);
                }    

  
      if(fPercent > 20 && fPercent <= 30) {
//                          cout << "fPercent20_30=" << " " << fPercent << endl;
                       dataMSL20_30[kPt20_30]     = track->Pt();
                       dataMSL20_30[kEta20_30]     = track->Eta();
                       dataMSL20_30[kCharge20_30] = track->Charge()/3;
                       dataMSL20_30[kPercent20_30] = fPercent;
                       dataMSL20_30[kVz20_30] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL20_30")) -> Fill(dataMSL20_30);
                   }    
  
  
      if(fPercent > 30 && fPercent <= 40) {
//                         cout << "fPercent30_40=" << " " << fPercent << endl;
                       dataMSL30_40[kPt30_40]     = track->Pt();
                       dataMSL30_40[kEta30_40]     = track->Eta();
                       dataMSL30_40[kCharge30_40] = track->Charge()/3;
                       dataMSL30_40[kPercent30_40] = fPercent;
                       dataMSL30_40[kVz30_40] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL30_40")) -> Fill(dataMSL30_40);
                   }    
  
       if(fPercent > 40 && fPercent <= 50) {
//                         cout << "fPercent40_50=" << " " << fPercent << endl;
                       dataMSL40_50[kPt40_50]     = track->Pt();
                       dataMSL40_50[kEta40_50]     = track->Eta();
                       dataMSL40_50[kCharge40_50] = track->Charge()/3;
                       dataMSL40_50[kPercent40_50] = fPercent;
                       dataMSL40_50[kVz40_50] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL40_50")) -> Fill(dataMSL40_50);
                   } 
    
         if(fPercent > 50 && fPercent <= 60) {
//                         cout << "fPercent50_60=" << " " << fPercent << endl;
                       dataMSL50_60[kPt50_60]     = track->Pt();
                       dataMSL50_60[kEta50_60]     = track->Eta();
                       dataMSL50_60[kCharge50_60] = track->Charge()/3;
                       dataMSL50_60[kPercent50_60] = fPercent;
                       dataMSL50_60[kVz50_60] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL50_60")) -> Fill(dataMSL50_60);
                   }    
  
       if(fPercent > 60 && fPercent <= 70) {
//                         cout << "fPercent60_70=" << " " << fPercent << endl;
                       dataMSL60_70[kPt60_70]     = track->Pt();
                       dataMSL60_70[kEta60_70]     = track->Eta();
                       dataMSL60_70[kCharge60_70] = track->Charge()/3;
                       dataMSL60_70[kPercent60_70] = fPercent;
                       dataMSL60_70[kVz60_70] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL60_70")) -> Fill(dataMSL60_70);
                   }    
  
       if(fPercent > 70 && fPercent <= 100) {
//                         cout << "fPercent70_100=" << " " << fPercent << endl;
                       dataMSL70_100[kPt70_100]     = track->Pt();
                       dataMSL70_100[kEta70_100]     = track->Eta();
                       dataMSL70_100[kCharge70_100] = track->Charge()/3;
                       dataMSL70_100[kPercent70_100] = fPercent;
                       dataMSL70_100[kVz70_100] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuCENTMSL70_100")) -> Fill(dataMSL70_100);
                   }    
  
  
             if(correctedCount > 0 && correctedCount <= 350) {
                       dataMSL0_300[kPt0_300]     = track->Pt();
                       dataMSL0_300[kEta0_300]     = track->Eta();
                       dataMSL0_300[kCharge0_300] = track->Charge()/3;
                       dataMSL0_300[kPercent0_300] = correctedCount;
                       dataMSL0_300[kVz0_300] = vertex->GetZ();
                       
                       ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULTMSL0_300")) -> Fill(dataMSL0_300);
             }
            if(correctedCount > 1 && correctedCount <= 37) {
                    dataMSL1_37[kPt1_37]     = track->Pt();
                    dataMSL1_37[kEta1_37]     = track->Eta();
                    dataMSL1_37[kCharge1_37] = track->Charge()/3;
                    dataMSL1_37[kPercent1_37] = correctedCount;
                    dataMSL1_37[kVz1_37] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULTMSL1_37")) -> Fill(dataMSL1_37); 
            }    
                       if(correctedCount > 38 && correctedCount <= 54) {
                    dataMSL38_54[kPt38_54]     = track->Pt();
                    dataMSL38_54[kEta38_54]     = track->Eta();
                    dataMSL38_54[kCharge38_54] = track->Charge()/3;
                    dataMSL38_54[kPercent38_54] = correctedCount;
                    dataMSL38_54[kVz38_54] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULTMSL38_54")) -> Fill(dataMSL38_54); 
                       }

                              if(correctedCount > 55 && correctedCount <= 94) {
                    dataMSL55_94[kPt55_94]     = track->Pt();
                    dataMSL55_94[kEta55_94]     = track->Eta();
                    dataMSL55_94[kCharge55_94] = track->Charge()/3;
                    dataMSL55_94[kPercent55_94] = correctedCount;
                    dataMSL55_94[kVz55_94] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULTMSL55_94")) -> Fill(dataMSL55_94);
                  }
                           if(correctedCount > 95 && correctedCount <= 121) {
                    dataMSL95_121[kPt95_121]     = track->Pt();
                    dataMSL95_121[kEta95_121]     = track->Eta();
                    dataMSL95_121[kCharge95_121] = track->Charge()/3;
                    dataMSL95_121[kPercent95_121] = correctedCount;
                    dataMSL95_121[kVz95_121] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULTMSL95_121")) -> Fill(dataMSL95_121);   
                           }
                             if(correctedCount > 121 && correctedCount <= 350) {
                    dataMSL121_300[kPt121_300]     = track->Pt();
                    dataMSL121_300[kEta121_300]     = track->Eta();
                    dataMSL121_300[kCharge121_300] = track->Charge()/3;
                    dataMSL121_300[kPercent121_300] = correctedCount;
                    dataMSL121_300[kVz121_300] = vertex->GetZ();
                    
                    ((THnSparseF*)listPhysics-> FindObject("fHistSingleMuMULTMSL121_300")) -> Fill(dataMSL121_300); 
                             }
    }

 
 }
}   //end of PS
  PostData(1, listEvents);
  PostData(2, listSPDTracklets);
  PostData(3, listPhysics);

}

//====================================================================================================================================================================
void AliAnalysisTaskMuonVsMult::Terminate(Option_t * ) {


  listEvents = dynamic_cast < TList * > (GetOutputData(1));
  if (!listEvents) {
    AliError("Could not retrieve TList* listEvents");
    return;
  }

  listSPDTracklets = dynamic_cast < TList * > (GetOutputData(2));
  if (!listSPDTracklets) {
    AliError("Could not retrieve TList* listSPDTracklets");
    return;
  }

  listPhysics = dynamic_cast < TList * > (GetOutputData(3));
  if (!listPhysics) {
    AliError("Could not retrieve TList* listPhysics");
    return;
  }

}

//________________________________________________________________________
void AliAnalysisTaskMuonVsMult::SetHisto(TH1 * h0, TString titleXaxis, TString titleYaxis, TList * list, int idx) {

  h0 -> Sumw2();
  h0 -> SetStats(kTRUE);
  h0 -> GetXaxis() -> SetTitle(titleXaxis);
  h0 -> GetYaxis() -> SetTitle(titleYaxis);

  if (idx < 0) list -> AddLast(h0);
  else list -> AddAt(h0, idx);

}
//________________________________________________________________________
void AliAnalysisTaskMuonVsMult::SetHisto(TH2 * h0, TString titleXaxis, TString titleYaxis, TList * list, int idx) {

  h0 -> Sumw2();
  h0 -> SetStats(kTRUE);
  h0 -> GetXaxis() -> SetTitle(titleXaxis);
  h0 -> GetYaxis() -> SetTitle(titleYaxis);

  if (idx < 0) list -> AddLast(h0);
  else list -> AddAt(h0, idx);

}

//________________________________________________________________________
