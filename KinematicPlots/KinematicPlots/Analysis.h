#ifndef KinematicPlots_Analysis_H
#define KinematicPlots_Analysis_H

#include <math.h>

#include <EventLoop/Algorithm.h>
#include <KinematicPlots/Objects.h>
#include <KinematicPlots/ObjectHists.h>

#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include "TLorentzVector.h"


namespace gFEX {

  class Analysis : public EL::Algorithm {
    // put your configuration variables here as public variables.
    // that way they can be set directly from CINT and python.
  public:
    /// Maximum value for gTower Pt to be considered for pileup calculation [GeV]
    float m_rhoThreshold = 3.0;
    /// Minimum value for gTower Pt to be a seed [GeV]
    float m_seedThreshold = 15.0;
    /// Minimum value for gTower Pt to be considered for event [GeV]
    float m_noiseFilter = 0.0;
    /// Radius of gFEX Trigger Jet in eta-phi units
    float m_dR = 1.0;
    /// Use the seed as a center of a jet
    bool m_useSeedAsCenter = true;
    /// Apply MC Quality Cuts (see https://twiki.cern.ch/twiki/pub/AtlasProtected/JetStudies2012/JLacey_MC12_JZXW_weights_and_CleaningCuts.pdf)
    bool m_doMCQualityCut = true;
    /// Apply the Isolation Cut requiring offline large-R trimmed jets to be isolated by R=1.0
    bool m_doIsolationCut = false;
    /// Apply Isolation cuts for small-R jets, R=0.4.  The min radius to next jet is 1.0
    bool m_doIsolationCut4 = true;
    /// Add in extra debugging information
    bool m_debug = true;


    /// Apply SoftKiller to the gTowers before creating jets
    bool m_doSoftKiller = false;
    /// Apply SoftKiller (with fake median) to the gTowers before creating jets
    bool m_doFakeSoftKiller = false;
    /// Apply area subtraction (with fake median) to the gTowers before creating jets
    bool m_doAreaSub = false;
    /// Calculate and Apply SoftKiller to the absolute value of gTowers before creating jets
    bool m_doSoftKillerAbsVal = false;
    double gBlockJetRatio;
    double gTowerPtCut;
    double gTowerPtCounts;
    double DeltaRgBlockJet;
    double MetgBlocks;
    double MetXgBlocks;
    double MetYgBlocks;
   
    double MetgTowers;
    double MetXgTowers;
    double MetYgTowers;

    double MetAntiKt4;
    double MetXAntiKt4;
    double MetYAntiKt4;

    double gBlockMatchJetRatio;
    double jetMatchPt;

    int gBlockMinPtCut = -50;
    int gBlockMaxPtCut = 51;
    int gBlockPtCutStep = 5;

    unsigned int nBinsJetPt = 100;
    double maxBinJetPt = 100.;
    double minBinJetPt = 0.;

    double pi = 3.14159265359;

    unsigned int ptMaxBinDividedBy5 = 101;

    std::vector<double> offlinejetptAfterIso; //!

    std::vector<double> deltaRbetweenIsolatedJets; //!
    
    std::vector<int> tempVector; //!
    std::vector<double> dRgBlockMatchedOfflineJet; //!

    std::vector<double> OfflineJets_AntiKt4PtHist;  //!
    std::vector<double> gBlocksPtHist; //!

    std::vector<std::vector<double>> gBlocksPtMatchedJetWithPtCut; //!
    //std::vector<std::vector<double>> gBlocksPtMatchedJetRatioWithPtCut; //!
      

  
    std::vector<int> gTowerPtCount; //!
    std::vector<int> gTowerPtCountNumber; //!

    std::vector<double> gBlockJetRatioVector; //!
    std::vector<double> DeltaRgBlockJetVector; //!

    
    
    std::vector<double> gBlockJetMatchRatioVector; //!
    std::vector<double> gBlockJetMatchJetPtVector; //!
    std::vector<double> gBlockJetRatioJetPtVector; //!

    TLorentzVector jv1; //!
    TLorentzVector gv1; //!

    std::vector<TLorentzVector> jetVec; //!
    std::vector<TLorentzVector> gblockVec; //!
    std::vector<int> gblockIndices; //!

    double maxDistJetgBlock;
    double minDR;

    std::vector<double> offlineJetMatchgBlockPt; //!
    std::vector<int> gBlockPtCuts; //!
    std::vector<std::vector<double>> offlineJetMatchgBlockPtWithgBlockPtCuts; //!


    std::vector<std::vector<double>> RatiogBlockPtJetPtBinnedByJetPt; //!
    std::vector<std::vector<double>> RatiogBlockPtJetPtBinnedByJetPtEta; //!
    std::vector<std::vector<double>> RatiogBlockPtJetPtBinnedByJetPtPhi; //!
    std::vector<std::vector<double>> RatiogBlockPtJetPtBinnedByJetEta; //!

    
    std::vector<std::vector<double>> RatiogBlockPtJetPtBinnedByJetPtRatioBinEta; //!
    std::vector<std::vector<double>> RatiogBlockPtJetPtBinnedByJetPtRatioBinPhi; //!

    
    /**
        The first ~12 bunches have unusually high MET due to the bimodal LAr pulses.

        Skip events that are too close to the start of the bunch train.

        See Ben's slides here: https://indico.cern.ch/event/506258/contributions/2184428/attachments/1286943/1914771/L1CaloUpgradeSamples_JointMeeting_Carlson_June2016.pdf
      */
    int m_minDistanceFrontBunchTrain = 12;
    /// configuration for rho calculation
    std::string m_rhoCalculation = "median";
    /// configuration for pileup mitigation
    std::string m_pileupMitigation = "area-based";

    // Below are kinematic cuts for all offline jets (small-R and large-R)
    float m_minEta_offline = -2.5;
    float m_maxEta_offline = 2.5;

    // Below are configurations for the thresholds
    float m_singleTowerThreshold_start = 5.0;
    float m_singleTowerThreshold_stop = 100.0;
    float m_singleTowerThreshold_step = 5.0;

    float m_singleBlockThreshold_start = 5.0;
    float m_singleBlockThreshold_stop = 200.0;
    float m_singleBlockThreshold_step = 5.0;

    float m_singleJetThreshold_start = 100.0;
    float m_singleJetThreshold_stop = 450.0;
    float m_singleJetThreshold_step = 10.0;

  private:
    //    TH1F* m_RatioEtEtTruth; //!
    TH1F* m_offline_jet_pt = nullptr; //!
    TTree *m_mapTree = nullptr; //!
    TTree *m_tree = nullptr; //!
    std::string m_sampleName = ""; //!
	TTree *m_outTrees; //!

    std::string m_outputLabel; //!
    TFile* m_outputFile; //!
    
    // kinematic plots
    std::map<std::string, ObjectHists*> m_kinematicPlots;   //!

    // event-level plots
    std::map<std::string, TH1F*> m_eventPlots1D; //!
    std::map<std::string, TH2F*> m_eventPlots2D; //!


    
    // plots that contain information necessary for calculating the rates
    std::map<std::string, TH1F*> m_ratePlots; //!

    // various other plots
    std::map<std::string, TH1F*> m_triggerPlots;   //!
    std::map<std::string, TH2F*> m_2DtriggerPlots; //!
    std::map<std::string, TH3F*> m_3DPlots; //!

    TH2F* m_resolution; //!

    //--------------------
    // Branch Variables
    //--------------------
    // --- supercell and tower maps Tree (maps) ---
    std::vector<float>*         scells_eta = nullptr; //!
    std::vector<float>*         scells_phi = nullptr; //!
    std::vector<float>*         scells_etaMin = nullptr; //!
    std::vector<float>*         scells_etaMax = nullptr; //!
    std::vector<float>*         scells_phiMin = nullptr; //!
    std::vector<float>*         scells_phiMax = nullptr; //!
    std::vector<float>*         scells_etaGranularity = nullptr; //!
    std::vector<float>*         scells_phiGranularity = nullptr; //!
    std::vector<float>*         scells_sinTh = nullptr; //!
    std::vector<float>*         scells_cosTh = nullptr; //!
    std::vector<float>*         scells_sinPhi = nullptr; //!
    std::vector<float>*         scells_cosPhi = nullptr; //!
    std::vector<float>*         scells_cotTh = nullptr; //!
    std::vector<float>*         scells_x = nullptr; //!
    std::vector<float>*         scells_y = nullptr; //!
    std::vector<float>*         scells_z = nullptr; //!
    std::vector<bool> *         scells_badcell = nullptr; //!
    std::vector<unsigned int>*  scells_ID = nullptr; //!
    std::vector<std::string>*   scells_detName = nullptr; //!
    std::vector<int>*           SCgTowerIndex = nullptr; //!
    int                         gTowerN = 0; //!
    std::vector<float>*         gTowerPhi = nullptr; //!
    std::vector<float>*         gTowerPhiGeometric = nullptr; //!
    std::vector<float>*         gTowerEta = nullptr; //!
    std::vector<float>*         gTowerEtaGeometric = nullptr; //!
    std::vector<float>*         gTowerEtaBins = nullptr; //!
    std::vector<float>*         gTowerEtaMin = nullptr; //!
    std::vector<float>*         gTowerEtaMax = nullptr; //!
    std::vector<float>*         gTowerPhiBins = nullptr; //!
    std::vector<float>*         gTowerPhiBinsFCAL = nullptr; //!
    std::vector<float>*         gTowerPhiMin = nullptr; //!
    std::vector<float>*         gTowerPhiMax = nullptr; //!
    //int                         jTowerN = 0; //!
    //std::vector<float>*         jTowerPhi = nullptr; //!
    //std::vector<float>*         jTowerEta = nullptr; //!
    //std::vector<float>*         jTowerEtaMin = nullptr; //!
    //std::vector<float>*         jTowerEtaMax = nullptr; //!
    //std::vector<float>*         jTowerPhiMin = nullptr; //!
    //std::vector<float>*         jTowerPhiMax = nullptr; //!

    // --- physics Tree (mytree) ---
    std::vector<float>*         scells_Et = nullptr; //!
    std::vector<float>*         scells_time = nullptr; //!
    std::vector<unsigned int>*  scells_provenance = nullptr; //!
    std::vector<unsigned int>*  scells_quality = nullptr; //!
    std::vector<float>*         gTowerEt = nullptr; //!
    std::vector<float>*         gTowerPhiWeighted = nullptr; //!
    std::vector<float>*         gTowerEtaWeighted = nullptr; //!
    std::vector<int>*           gTowerNCells = nullptr; //!
    std::vector<float>*         gTowerEt_EM = nullptr; //!
    std::vector<float>*         gTowerPhi_EM = nullptr; //!
    std::vector<float>*         gTowerEta_EM = nullptr; //!
    std::vector<float>*         gTowerPhiWeighted_EM = nullptr; //!
    std::vector<float>*         gTowerEtaWeighted_EM = nullptr; //!
    std::vector<int>*           gTowerNCells_EM = nullptr; //!
    std::vector<float>*         gTowerEt_Had = nullptr; //!
    std::vector<float>*         gTowerPhi_Had = nullptr; //!
    std::vector<float>*         gTowerEta_Had = nullptr; //!
    std::vector<float>*         gTowerPhiWeighted_Had = nullptr; //!
    std::vector<float>*         gTowerEtaWeighted_Had = nullptr; //!
    std::vector<int>*           gTowerNCells_Had = nullptr; //!
    //std::vector<float>*         jTowerEt = nullptr; //!
    //std::vector<int>*           jTowerNCells = nullptr; //!
    //std::vector<float>*         jTowerEt_EM = nullptr; //!
    //std::vector<int>*           jTowerNCells_EM = nullptr; //!
    //std::vector<float>*         jTowerEt_Had = nullptr; //!
    //std::vector<int>*           jTowerNCells_Had = nullptr; //!
    std::vector<float>*         Run2_TT_eta = nullptr; //!
    std::vector<float>*         Run2_TT_phi = nullptr; //!
    std::vector<float>*         Run2_TT_JEP_Et = nullptr; //!
    std::vector<float>*         Run2_TT_CP_Et = nullptr; //!
    std::vector<float>*         Run2_L1Jet_Et = nullptr; //!
    std::vector<float>*         Run2_L1Jet_eta = nullptr; //!
    std::vector<float>*         Run2_L1Jet_phi = nullptr; //!
    std::vector<float>*         Run2_AntiKt4TT_Et = nullptr; //!
    std::vector<float>*         Run2_AntiKt4TT_eta = nullptr; //!
    std::vector<float>*         Run2_AntiKt4TT_phi = nullptr; //!
    std::vector<float>*         ConeGJet10_Et = nullptr; //!
    std::vector<float>*         ConeGJet10_eta = nullptr; //!
    std::vector<float>*         ConeGJet10_phi = nullptr; //!
    std::vector<int>*         ConeGJet10_seedIndex = nullptr; //!
    //std::vector<float>*         JFexJet_Et = nullptr; //!
    //std::vector<float>*         JFexJet_eta = nullptr; //!
    //std::vector<float>*         JFexJet_phi = nullptr; //!
    std::vector<float>*         AntiKt10gT_Et = nullptr; //!
    std::vector<float>*         AntiKt10gT_eta = nullptr; //!
    std::vector<float>*         AntiKt10gT_phi = nullptr; //!
    std::vector<float>*         AntiKt4jT_Et = nullptr; //!
    std::vector<float>*         AntiKt4jT_eta = nullptr; //!
    std::vector<float>*         AntiKt4jT_phi = nullptr; //!
    int                         AntiKt10LCTopoJets_n = 0; //!
    std::vector<float>*         AntiKt10LCTopoJets_pt = nullptr; //!
    std::vector<float>*         AntiKt10LCTopoJets_eta = nullptr; //!
    std::vector<float>*         AntiKt10LCTopoJets_phi = nullptr; //!
    std::vector<float>*         AntiKt10LCTopoJets_m = nullptr; //!
    int                         AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_n = 0; //!
    std::vector<float>*         AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_pt = nullptr; //!
    std::vector<float>*         AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_eta = nullptr; //!
    std::vector<float>*         AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_phi = nullptr; //!
    std::vector<float>*         AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_m = nullptr; //!
    std::vector<int>*           AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_nsj = nullptr; //!
    int                         AntiKt4LCTopoJets_n = 0; //!
    std::vector<float>*         AntiKt4LCTopoJets_pt = nullptr; //!
    std::vector<float>*         AntiKt4LCTopoJets_eta = nullptr; //!
    std::vector<float>*         AntiKt4LCTopoJets_phi = nullptr; //!
    std::vector<float>*         AntiKt4LCTopoJets_m = nullptr; //!
    int                         CamKt12LCTopoJets_n = 0; //!
    std::vector<float>*         CamKt12LCTopoJets_pt = nullptr; //!
    std::vector<float>*         CamKt12LCTopoJets_eta = nullptr; //!
    std::vector<float>*         CamKt12LCTopoJets_phi = nullptr; //!
    std::vector<float>*         CamKt12LCTopoJets_m = nullptr; //!
    int                         AntiKt10TruthJets_n = 0; //!
    std::vector<float>*         AntiKt10TruthJets_pt = nullptr; //!
    std::vector<float>*         AntiKt10TruthJets_eta = nullptr; //!
    std::vector<float>*         AntiKt10TruthJets_phi = nullptr; //!
    std::vector<float>*         AntiKt10TruthJets_m = nullptr; //!
    int                         AntiKt4TruthJets_n = 0; //!
    std::vector<float>*         AntiKt4TruthJets_pt = nullptr; //!
    std::vector<float>*         AntiKt4TruthJets_eta = nullptr; //!
    std::vector<float>*         AntiKt4TruthJets_phi = nullptr; //!
    std::vector<float>*         AntiKt4TruthJets_m = nullptr; //!
    int                         CamKt12TruthJets_n = 0; //!
    std::vector<float>*         CamKt12TruthJets_pt = nullptr; //!
    std::vector<float>*         CamKt12TruthJets_eta = nullptr; //!
    std::vector<float>*         CamKt12TruthJets_phi = nullptr; //!
    std::vector<float>*         CamKt12TruthJets_m = nullptr; //!
    float                       MET_Truth_NonInt_mpx = 0; //!
    float                       MET_Truth_NonInt_mpy = 0; //!
    float                       MET_Truth_NonInt_sumet = 0; //!
    float                       MET_Truth_Int_mpx = 0; //!
    float                       MET_Truth_Int_mpy = 0; //!
    float                       MET_Truth_Int_sumet = 0; //!
    float                       MET_Truth_IntOut_mpx = 0; //!
    float                       MET_Truth_IntOut_mpy = 0; //!
    float                       MET_Truth_IntOut_sumet = 0; //!
    float                       MET_Truth_IntMuons_mpx = 0; //!
    float                       MET_Truth_IntMuons_mpy = 0; //!
    float                       MET_Truth_IntMuons_sumet = 0; //!
    float                       MET_Truth_IntCentral_mpx = 0; //!
    float                       MET_Truth_IntEndCap_mpx = 0; //!
    float                       MET_Truth_IntForward_mpx = 0; //!
    float                       MET_Truth_IntCentral_mpy = 0; //!
    float                       MET_Truth_IntEndCap_mpy = 0; //!
    float                       MET_Truth_IntForward_mpy = 0; //!
    float                       MET_Truth_IntCentral_sumet = 0; //!
    float                       MET_Truth_IntEndCap_sumet = 0; //!
    float                       MET_Truth_IntForward_sumet = 0; //!
    int                         eventNumber = 0; //!
    float                       weight = 0; //!
    std::vector<float>*         mcEventWeight = nullptr; //!
    float                       actualIntPerCross; //!
    float                       averageIntPerCross; //!
    int                         PileUp_inTime_MinBias; //!
    int                         distFrontBunchTrain;
    float                       Kt4LCTopoEventShape_Density; //!
    float                       Kt4LCTopoEventShape_DensityArea; //!
    float                       Kt4LCTopoEventShape_DensitySigma; //!
    float                       Kt4EMTopoEventShape_Density; //!
    float                       Kt4EMTopoEventShape_DensityArea; //!
    float                       Kt4EMTopoEventShape_DensitySigma; //!
    float                       Kt4EMPFlowEventShape_Density; //!
    float                       Kt4EMPFlowEventShape_DensityArea; //!
    float                       Kt4EMPFlowEventShape_DensitySigma; //!

    // find this in Root/TTreeHelper.cxx
    void InitializeBranches();

  public:
    // this is a standard constructor
    Analysis ();

    // these are the functions inherited from Algorithm
    virtual EL::StatusCode setupJob (EL::Job& job);
    virtual EL::StatusCode fileExecute ();
    virtual EL::StatusCode histInitialize ();
    virtual EL::StatusCode changeInput (bool firstFile);
    virtual EL::StatusCode initialize ();
    virtual EL::StatusCode execute ();
    virtual EL::StatusCode postExecute ();
    virtual EL::StatusCode finalize ();
    virtual EL::StatusCode histFinalize ();

    // this is needed to distribute the algorithm to the workers
    ClassDef(Analysis, 1);

  private:
    // a map holding (cutflow, (unweighted, weighted))
    std::map<std::string, std::pair<float, float>> m_cutflows; //!
    // a vector holding the order of the names of the cutflow
    std::vector<std::string> m_cutflow_names; //!

    std::vector<Tower> gTowers;                     //!
    std::vector<Jet>   gJets;                       //!
    std::vector<Jet>   gJets_central;               //!
    std::vector<Jet>   gJets_corrected;             //!

    std::vector<Jet> OfflineJets_AntiKt10;          //!
    std::vector<Jet> OfflineJets_AntiKt10Trimmed;   //!
    std::vector<Jet> OfflineJets_AntiKt4;           //!
    std::vector<Jet> OfflineJets_CamKt12;           //!
    std::vector<Jet> TruthJets_AntiKt10;            //!
    std::vector<Jet> TruthJets_AntiKt4;             //!
    std::vector<Jet> TruthJets_CamKt12;             //!
    std::vector<Jet> Run2_L1Jets;                   //!
  };
}

#endif
