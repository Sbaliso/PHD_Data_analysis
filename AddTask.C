#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TString.h"

#include "AliAnalysisManager.h"
#include "AliAnalysisDataContainer.h"

#include "AliMuonTrackCuts.h"
#include "AliMuonEventCuts.h"
#include "AliAnalysisTaskMuonVsMult.h"
#endif 
 
AliAnalysisTaskMuonVsMult *AddTask(TString name = "name" ){
  
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    ::Error("AddtaskSingleMu", "No analysis manager to connect to.");
    return NULL;
  } 
   //  my task
  //-------------------------
//   TString naming = "";
//   naming.ReplaceAll("-","_");
//   Bool_t IsMC = kFALSE;
//   Bool_t ApplyPUCuts;
//   Double_t MeanTrRef;
  AliAnalysisTaskMuonVsMult *task = new AliAnalysisTaskMuonVsMult("AliAnalysisTaskMuonVsMult");
    
  task->GetMuonTrackCuts()->SetFilterMask (/* AliMuonTrackCuts::kMuEta |AliMuonTrackCuts::kMuThetaAbs |*/ AliMuonTrackCuts::kMuPdca /*| AliMuonTrackCuts::kMuMatchLpt*/);
// //   task->GetMuonTrackCuts()->SetIsMC(useMC);
  task->GetMuonTrackCuts()->Print("mask");
  task->GetMuonTrackCuts()->SetPassName("muon_calo_pass2");
  task->GetMuonTrackCuts()->SetAllowDefaultParams(kTRUE);
//   task->GetMuonTrackCuts()->ApplySharpPtCutInMatching(kTRUE);
  
   mgr->AddTask(task);
   
   TFile* fileEstimator=TFile::Open("16rprofile.root");
   TProfile* fSPDMeanTracklets = (TProfile*)fileEstimator->Get("hMBMeanRawTrackletsVsZVertex");
   task->SetProfile(fSPDMeanTracklets);
   
  TString file = "MuonVsMultData.root";
  
AliAnalysisDataContainer *coutput2 = mgr->CreateContainer("ListEvents",TList::Class(),AliAnalysisManager::kOutputContainer,file.Data()); 
AliAnalysisDataContainer *coutput3 = mgr->CreateContainer("ListSPDtracklets",TList::Class(),AliAnalysisManager::kOutputContainer,file.Data());
AliAnalysisDataContainer *coutput4 = mgr->CreateContainer("ListPhysics",TList::Class(),AliAnalysisManager::kOutputContainer,file.Data());

  
mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
mgr->ConnectOutput(task,1,coutput2);
mgr->ConnectOutput(task,2,coutput3);
mgr->ConnectOutput(task,3,coutput4);
   return task;
}
