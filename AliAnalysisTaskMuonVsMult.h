#ifndef ANALYSISTASKMULTIPLICITY_H
#define ANALYSISTASKMULTIPLICITY_H

class TH1F;
class TH2F;
class TH3F;
class TProfile;
class TList;
class TObjArray;
class TArrayF;
class TRandom3;

class AliAnalysisManager;
class AliVEvent;
class AliCounterCollection;
class AliMuonTrackCuts;
class AliMuonEventCuts;
class AliAnalysisUtils;
class AliTriggerAnalysis;

#ifndef ALIANALYSISTASKSE_H
#include "AliAnalysisTaskSE.h"
#endif

class AliAnalysisTaskMuonVsMult : public AliAnalysisTaskSE {
public:
    AliAnalysisTaskMuonVsMult();
    AliAnalysisTaskMuonVsMult(const char *name);

    virtual ~AliAnalysisTaskMuonVsMult();
    virtual void     NotifyRun();
    virtual void     UserCreateOutputObjects();
    virtual void     UserExec(Option_t *option);
    virtual void     Terminate(Option_t *);

    void SetProfile( TProfile* tp ){ fSPDMeanTracklets = tp; }
    void SetHisto( TH1* h0, TString titleXaxis, TString titleYaxis, TList* list, int idx = -1);
    void SetHisto( TH2* h0, TString titleXaxis, TString titleYaxis, TList* list, int idx = -1);

    /// Get track cuts
    AliMuonTrackCuts* GetMuonTrackCuts() { return fMuonTrackCuts; }
    /// Get event cuts
    AliMuonTrackCuts *fMuonTrackCuts;  
    // set SPD pile up cut

private:

    AliAnalysisUtils *fUtils; //!
    Int_t fMinContrib;
    Double_t fMinEtaForTracklets;
    Double_t fMaxEtaForTracklets;
    TRandom3 *fRand;

    //declaration of the events histograms
    TH1I* hMBEventsCounter; //!
    TH1I* hEventsPerRun;
    //declaration of the physics histograms
    THnSparse *hSingleMu;
    TH1F *hAcceptedMuons;
    TH1F *hPtEta;
    TH1F *hPtThetaAbs;
    TH1F *hMatchTrigger;
    TH1F *hPdca;
    TH1F *hEtaAcceptedMuons;
    TH1F *hEta;
    TH1F *hEtaThetaAbs;
    TH1F *hEtaMatchTrigger;
    TH1F *hEtaPdca;

    // tracklets
    TH1F *hTrackletsPerEvent;		//!
    TH1F* hRawTrackletsPerEvent;	//!
    TH1F* hMBTrackletsPerEvent;		//!
    TH1F* hMBRawTrackletsPerEvent;	//!
    
//     TH1F* fHistZvtx         ;
//     TH1F* fHistZvtxWPS      ;
//     TH1F* fHistZvtxMSL      ;
//     TH1F* fHistZvtxNContMSL ;
//     TH1F* fHistGoodVtxMSL   ;
       // Vertex QA
    TProfile* hReferenceProfile;
    TProfile* hMeanTrackletsVsZVertex;	
    TProfile* hMBMeanTrackletsVsZVertex;	
    TProfile* hMeanRawTrackletsVsZVertex;	
    TProfile* hMBMeanRawTrackletsVsZVertex;
    TH2F* hTrackletsVsZVertex;		//!
    TH2F* hMBTrackletsVsZVertex;	//!
    TProfile* fSPDMeanTracklets; 
    TH2F* hRawTrackletsVsZVertex;		//!
    TH2F* hCorrectedVsRawTracklets;	//!
    TH2F* hMBRawTrackletsVsZVertex; //!
    TH2F* hMBCorrectedVsRawTracklets;	//!
  
enum{kPt,kEta,kVz,kMult,kCharge,kNvars};
enum{kPt0_100,kEta0_100,kVz0_100,kPercent0_100 ,kCharge0_100 };
enum{kPt0_10,kEta0_10,kVz0_10,kPercent0_10,kCharge0_10};
enum{kPt10_20,kEta10_20,kVz10_20,kPercent10_20,kCharge10_20};
enum{kPt20_30,kEta20_30,kVz20_30,kPercent20_30,kCharge20_30};
enum{kPt30_40,kEta30_40,kVz30_40,kPercent30_40,kCharge30_40};
enum{kPt40_50,kEta40_50,kVz40_50,kPercent40_50,kCharge40_50};
enum{kPt50_60,kEta50_60,kVz50_60,kPercent50_60,kCharge50_60};
enum{kPt60_70,kEta60_70,kVz60_70,kPercent60_70,kCharge60_70};
enum{kPt70_100,kEta70_100,kVz70_100,kPercent70_100,kCharge70_100};

enum{kPt0_300,kEta0_300,kVz0_300,kPercent0_300,kCharge0_300 };
enum{kPt1_37,kEta1_37,kVz1_37,kPercent1_37,kCharge1_37};
enum{kPt38_54,kEta38_54,kVz38_54,kPercent38_54,kCharge38_54 };
enum{kPt55_94,kEta55_94,kVz55_94,kPercent55_94,kCharge55_94};
enum{kPt95_121,kEta95_121,kVz95_121,kPercent95_121,kCharge95_121};
enum{kPt121_300,kEta121_300,kVz121_300,kPercent121_300,kCharge121_300};

  enum listList{ 
	    kDefaultContainer,
	    kListEvents, 
	    kListSPDTracklets,
	    kListPhysics,
    };

    TList* listPhysics;                
    TList* listEvents;              
    TList* listSPDTracklets;		

    ClassDef(AliAnalysisTaskMuonVsMult,1);
};

#endif
