// define a quick way to add cutflows
#define REG_CUTFLOW(name)                                                                                                 \
  do {                                                                                                                    \
    if (std::find(m_cutflow_names.begin(), m_cutflow_names.end(), name) == m_cutflow_names.end()){                        \
      m_cutflow_names.push_back(name);                                                                                    \
      m_cutflows[name].first = 0;                                                                                         \
      m_cutflows[name].second = 0;                                                                                        \
    }                                                                                                                     \
  } while(0)

#define ADD_CUTFLOW(name)                                                                                                 \
  do {                                                                                                    \
    if (std::find(m_cutflow_names.begin(), m_cutflow_names.end(), name) == m_cutflow_names.end()){                        \
      Error("ADD_CUTFLOW", ("You need to call REG_CUTFLOW(\""+std::string(name)+"\") first in histInitialize.").c_str()); \
      return EL::StatusCode::FAILURE;                                                                                     \
    }                                                                                                                     \
    m_cutflows[name].first += 1;                                                                                          \
    m_cutflows[name].second += eventWeight;                                                                               \
  } while(0)

#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <KinematicPlots/Analysis.h>
#include <KinematicPlots/Algorithms.h>

#include "xAODAnaHelpers/tools/ReturnCheck.h"

#include "TLorentzVector.h"




// this is needed to distribute the algorithm to the workers
ClassImp(gFEX::Analysis)

gFEX::Analysis :: Analysis () {}

EL::StatusCode gFEX::Analysis :: setupJob (EL::Job& /*job*/) { return EL::StatusCode::SUCCESS; }
EL::StatusCode gFEX::Analysis :: histInitialize ()
{


  std::string detailStr = "NLeading4";

  // register the cutflows
  REG_CUTFLOW("total");
  REG_CUTFLOW("dist_from_bunch_train");
  REG_CUTFLOW("one_truth_jet");
  REG_CUTFLOW("two_reco_jets");
  REG_CUTFLOW("mc_quality_cut");
  REG_CUTFLOW("isolation_cut");
  REG_CUTFLOW("final");

  // plots for various selections
  std::vector<std::string> selections = {"presel","postsel"};
  for(const auto& selection: selections){
    std::string path;

    // standard kinematic plots
    path = selection+"/OfflineJets_AntiKt10";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/OfflineJets_AntiKt10Trimmed";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/OfflineJets_AntiKt4";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/OfflineJets_CamKt12";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/TruthJets_AntiKt10";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/TruthJets_AntiKt4";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/TruthJets_CamKt12";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/Run2_L1Jets";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/Run2_L1Jets_central";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/gTowers";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "tower");
    path = selection+"/gTowers_central";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "tower");
    path = selection+"/gBlocks_central";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "tower");
    path = selection+"/gJets";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/gJets_central";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");
    path = selection+"/gJets_corrected";
    m_kinematicPlots[path] = new ObjectHists(path.c_str(), detailStr, "", "jet");

    // event level plots
    path = selection+"/event/rho_median";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "median #rho", 100, -100., 300.);
    path = selection+"/event/rho_median_central";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "median #rho (|#eta^{gTower}| < 2.5)", 100, -100., 300.);
    path = selection+"/event/rho_offline";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "offline #rho", 100, -100., 300.);
    path = selection+"/event/rho_positive_median";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "median #rho (E_{T}^{gTower} > 0)", 100, -100.0, 300.0);
    path = selection+"/event/rho_positive_median_central";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "median #rho (E_{T}^{gTower} > 0, |#eta^{gTower}| < 2.5)", 100, -100.0, 300.0);
    path = selection+"/event/rho_median_versus_rho_median_central";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "gjet Rho v Rho Cut", 100, -100, 300, 100, -100, 300);
    path = selection+"/event/minDeltaR_offlineJets";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "offlineJets", 100., 0., 10.0);
    path = selection+"/event/minDeltaR4_offlineJets";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "offlineJets,R=.4", 100., 0., 10.0);
    m_eventPlots1D[path]->GetXaxis()->SetTitle("(#Delta R)^{oJet}");
    m_eventPlots1D[path]->GetYaxis()->SetTitle("number of events");
    path = selection+"/event/distFrontBunchTrain";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "distFrontBunchTrain", 73, -0.5, 72.5);
    path = selection+"/event/rho_median_versus_distFrontBunchTrain";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "rho versus dist(BCID)", 73, -0.5, 72.5, 100, -100., 300.);
    path = selection+"/event/rho_median_central_versus_distFrontBunchTrain";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "rho central versus dist(BCID)", 73, -0.5, 72.5, 100, -100., 300.);
    path = selection+"/event/rho_offline_versus_distFrontBunchTrain";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "rho versus dist(BCID)", 73, -0.5, 72.5, 100, -100., 300.);
    path = selection+"/event/rho_median_versus_rho_offline";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "offline #rho versus median #rho", 100, -100., 300., 100., -100., 300.);
    path = selection+"/event/rho_median_central_versus_rho_offline";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "offline #rho versus median #rho (|#eta| < 2.5)", 100, -100., 300., 100, -100., 300.);
    path = selection+"/event/rho_positive_median_versus_rho_offline";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "offline #rho versus median #rho (E_{T}^{gTower} > 0)", 100, -100., 300., 100., -100., 300.);
    path = selection+"/event/rho_positive_median_central_versus_rho_offline";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "offline #rho versus median #rho (E_{T}^{gTower} > 0, |#eta^{gTower}| < 2.5)", 100, -100., 300., 100, -100., 300.);
    path = selection+"/event/RatiogBlockJetPt";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "Ratio of gBlock pt to (uncalibrated) AntiKt4 Jets", 100, 0., 10.);
    path = selection+"/event/METgBlocks";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "MET, gBlocks", 100, 0., 1000.);
    path = selection+"/event/METXgBlocks";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "METX, gBlocks", 200, -1000., 1000.);
    path = selection+"/event/METYgBlocks";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "METY, gBlocks", 200, -1000., 1000.);
    
    path = selection+"/event/METgTowers";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "MET, gTowers", 100, 0., 1000.);
    path = selection+"/event/METXgTowers";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "METX, gTowers", 200, -1000., 1000.);
    path = selection+"/event/METYgTowers";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "METY, gTowers", 200, -1000., 1000.);
    
    path = selection+"/event/METOfflineAntiKt4";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "MET, OfflineAntiKt4", 100, 0., 1000.);
    path = selection+"/event/METXOfflineAntiKt4";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "METX, OfflineAntiKt4", 200, -1000., 1000.);
    path = selection+"/event/METYOfflineAntiKt4";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "METY, OfflineAntiKt4", 200, -1000., 1000.);
  
    path = selection+"/event/number_towers_after_cut";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "Number of gTowers after pT cuts", 20, 1, 20, 100, 0., 100.);
    path = selection+"/event/RatiogBlockJetPtDeltaR";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "Ratio of gBlock pt to Jet Pt vs Delta R", 10, 0., 5., 20, 0., 10.);
    // path = selection+"/event/RatiogBlockJetPt";
    //m_eventPlots1D[path] = new TH1F(path.c_str(), "Ratio of gBlock pT to jet pT", 100, 0., 10.);
    path = selection+"/event/gBlockJetMatchvsJetPt";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "Fraction of gBlocks match to OfflineAntiKt4 Jets as function of Jet Pt", 50, 0., 50., 10, 0., 2.);

    //path = selection+"/event/offlineJetMatchgBlockPtgBlockPtCut-50";
    //m_eventPlots1D[path] = new TH1F(path.c_str(), "OfflineJet_AntiKt4 that match gBlock Pt with gBlock Pt Cut of ", 1000, 0., 1000.);

    double ratioRange=-1.;
    //int k=0;
    while(ratioRange<=1.5){
      //std::cout << "This one Make" << ratioRange << std::endl;
      std::string path = selection+"/event/RatiogBlockJetPt_"+std::to_string(ratioRange)+"_"+std::to_string(ratioRange+.1);
      //std::cout << "Defined path: " << path << std::endl;
      std::string pathname = "Ratio of Matching gBlock to Jet Pt, Ratio "+std::to_string(ratioRange)+" to "+std::to_string(ratioRange+.1);
      m_eventPlots2D[path] = new TH2F(path.c_str(), pathname.c_str(), 60, -3., 3., 64, -3.2, 3.2);
      ratioRange+=0.1;
      //std::cout << "Finished Make" << std::endl;
      //k+=1;
    }
    

    path = selection+"/event/RatiogBlockJetPt_0.8_0.9_JetPt_25_30";
    m_eventPlots2D[path] = new TH2F(path.c_str(), "Ratio of Matching gBlock to Jet Pt 0.8-0.9, Jet Pt 25-30 GeV", 60, -3., 3., 64, -3.2, 3.2);
    
    for(unsigned int i=0; i<ptMaxBinDividedBy5 ; i++){//RatiogBlockPtJetPtBinnedByJetPt.size() ; i++){
      path = selection+"/event/RatiogBlockPtJetPtBinnedByJetPt"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      m_eventPlots1D[path] = new TH1F(path.c_str(), ("Matching gBlockPt/offlineJetPt for Jet Pt "+std::to_string(5*i)+" to "+std::to_string(5+5*i)).c_str() , 400, -10., 10.);
      path = selection+"/event/RatiogBlockPtJetPtBinnedByJetPtEta"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      m_eventPlots1D[path] = new TH1F(path.c_str(), ("Eta of matching gBlockPt/offlineJetPt for Jet Pt "+std::to_string(5*i)+" to "+std::to_string(5+5*i)).c_str() , 60, -3., 3.);
      path = selection+"/event/RatiogBlockPtJetPtBinnedByJetPtPhi"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      m_eventPlots1D[path] = new TH1F(path.c_str(), ("Phi of matching gBlockPt/offlineJetPt for Jet Pt "+std::to_string(5*i)+" to "+std::to_string(5+5*i)).c_str() , 64, -3.2, 3.2);
      
      path = selection+"/event/RatioVsEtagBlockPtJetPtBinnedByJetPt"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      m_eventPlots2D[path] = new TH2F(path.c_str(), ("Ratio Vs Eta of matching gBlockPt/offlineJetPt for Jet Pt "+std::to_string(5*i)+" to "+std::to_string(5+5*i)).c_str() , 130, -3., 10., 64, -3.2, 3.2);
      path = selection+"/event/RatioVsPhigBlockPtJetPtBinnedByJetPt"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      m_eventPlots2D[path] = new TH2F(path.c_str(), ("Ratio Vs Phi of matching gBlockPt/offlineJetPt for Jet Pt "+std::to_string(5*i)+" to "+std::to_string(5+5*i)).c_str() , 130, -3., 10., 64, -3.2, 3.2);
    }

    for(unsigned int i=0; i<51 ; i=i+5){//RatiogBlockPtJetPtBinnedByJetPt.size() ; i++){
      double etaLow = (i/10.)-2.5;
      path = selection+"/event/RatiogBlockPtJetPtBinnedByJetEta"+std::to_string(etaLow)+"_"+std::to_string(.5+etaLow);
      m_eventPlots1D[path] = new TH1F(path.c_str(), ("Matching gBlockPt/offlineJetPt for Jet Eta "+std::to_string(etaLow)+" to "+std::to_string(.5+etaLow)).c_str() , 100, -10., 10.);      
    }

    
    
    for(int i=gBlockMinPtCut ; i<gBlockMaxPtCut ; i+=gBlockPtCutStep){
      path = selection+"/event/offlineJetMatchgBlockPtgBlockPtCut"+std::to_string(i);
      m_eventPlots1D[path] = new TH1F(path.c_str(), ("OfflineJet_AntiKt4 that match gBlock Pt with gBlock Pt Cut of "+std::to_string(i)).c_str() , nBinsJetPt, minBinJetPt, maxBinJetPt);
      path = selection+"/event/offlineJetMatchgBlockPtRatioWithCut"+std::to_string(i);
      m_eventPlots1D[path] = new TH1F(path.c_str(), ("Ratio of offline AntiKt4 jets to OAK4 Jets with gBlock Pt Cut of "+std::to_string(i)).c_str() , nBinsJetPt, minBinJetPt, maxBinJetPt);
      path = selection+"/event/gBlocksPtMatchedJetWithPtCut"+std::to_string(i);
      m_eventPlots1D[path] = new TH1F(path.c_str(), ("gBlocks Pt with gBlock Pt Cut of "+std::to_string(i)).c_str() , nBinsJetPt, minBinJetPt, maxBinJetPt);
      path = selection+"/event/gBlocksPtMatchedJetRatioWithPtCut"+std::to_string(i);
      m_eventPlots1D[path] = new TH1F(path.c_str(), ("Ratio of gBlocks Pt to gBlock Pt with gBlock Pt Cut of "+std::to_string(i)).c_str() , nBinsJetPt, minBinJetPt, maxBinJetPt);
    }
    
    path = selection+"/event/OfflineJet_AntiKt4Pt";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "Offine AntiKt4 Jet Pt", nBinsJetPt, minBinJetPt, maxBinJetPt);

    path = selection+"/event/gBlocksPtHist";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "gBlocks Jet Pt", nBinsJetPt, minBinJetPt, maxBinJetPt);

    path = selection+"/event/deltaRbetweenIsolatedJets";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "Delta R between Isolated Jets", 50, 0., 10.);

    path = selection+"/event/dRgBlockMatchedOfflineJet";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "Delta R between Isolated Jets and Nearest gBlock", 500, 0., 5.);

    //path = selection+"/event/deltaRbetweenIsolatedJets";
    //m_eventPlots1D[path] = new TH1F(path.c_str(), "Delta R between Isolated Jets", 50, 0., 10.);

    path = selection+"/event/eventWeight";
    m_eventPlots1D[path] = new TH1F(path.c_str(), "Event Weight", 50, 0., 10.);

    
    //std::string path1 = selection+"/event/offlineJetMatchgBlockPtgBlockPtCut-50";//+std::to_string(-50);//gBcut;//+std::to_string(gBlockPtCuts[i]);
    //m_eventPlots1D[path1] =  new TH1F(path.c_str(), "test" , 1000, 0., 1000.);
      
    //"OfflineJet_AntiKt4 that match gBlock Pt with gBlock Pt Cut of "+std::to_string(gBlockPtCuts[i])
  }
  // various resolution plots
  m_2DtriggerPlots["resolution"]               = new TH2F("resolution/leading_gJet_versus_oJet", "resolution", 100, 0., 1500., 100, -2., 2.);
  m_2DtriggerPlots["resolution_corrected"]     = new TH2F("resolution/leading_gJet_corrected_versus_oJet", "resolution with gJet corrected pT", 100, 0., 1500., 100, -2., 2.);
  m_resolution = new TH2F("resolution/truthJets_versus_oJets", "resolution", 100., 0., 1000., 100.,-5.0,5.0);
  m_resolution->GetXaxis()->SetTitle("p_T^{truthJet} [GeV]");
  m_resolution->GetYaxis()->SetTitle("resolution (offline-truth)/truth");

  // the nbins is needed only for histograms which is why the user provides start, stop, and step
  //    - user provides start, stop, and step; we still need to calculate nbins for the rate histograms
  float rate_tower_nbins = std::ceil( (m_singleTowerThreshold_stop - m_singleTowerThreshold_start)/m_singleTowerThreshold_step )-1;
  float rate_block_nbins = std::ceil( (m_singleBlockThreshold_stop - m_singleBlockThreshold_start)/m_singleBlockThreshold_step )-1;
  float rate_jet_nbins = std::ceil( (m_singleJetThreshold_stop - m_singleJetThreshold_start)/m_singleJetThreshold_step )-1;

  // rate plots
  //    - underflow bin is the total number of events
  //    - each bin corresponds to a specific threshold
  for(int i=1; i<=6; ++i){
    m_ratePlots[std::string(std::to_string(i)+"tower_central")] = new TH1F(std::string("rates/"+std::to_string(i)+"tower_central").c_str(), std::string(std::to_string(i)+" central gTower rates").c_str(), rate_tower_nbins, m_singleTowerThreshold_start, m_singleTowerThreshold_start + m_singleTowerThreshold_step * rate_tower_nbins);
    m_ratePlots[std::string(std::to_string(i)+"block_central")] = new TH1F(std::string("rates/"+std::to_string(i)+"block_central").c_str(), std::string(std::to_string(i)+" central gBlock rates").c_str(), rate_block_nbins, m_singleBlockThreshold_start, m_singleBlockThreshold_start + m_singleBlockThreshold_step * rate_block_nbins);
    m_ratePlots[std::string(std::to_string(i)+"jet_central")]   = new TH1F(std::string("rates/"+std::to_string(i)+"jet_central").c_str(), std::string(std::to_string(i)+" central gJet rates").c_str(), rate_jet_nbins, m_singleJetThreshold_start, m_singleJetThreshold_start + m_singleJetThreshold_step * rate_jet_nbins);
  
    //m_ratePlots["stochastic/singleTower_central"] = new TH1F("rates/stochastic/singleTower_central", "single central gTower stochastic rates", rate_tower_nbins, m_singleTowerThreshold_start, m_singleTowerThreshold_start + m_singleTowerThreshold_step * rate_tower_nbins);
    //m_ratePlots["stochastic/singleBlock_central"] = new TH1F("rates/stochastic/singleBlock_central", "single central gBlock stochastic rates", rate_block_nbins, m_singleBlockThreshold_start, m_singleBlockThreshold_start + m_singleBlockThreshold_step * rate_block_nbins);
  }
  

  // all of our turn-on curves are built in amazing for-loops
  // gTower Turn-On Curves and Rates
  {
    std::string path("turnon/tower/all");
    m_triggerPlots[path+"/denominator"] = new TH1F((path+"/denominator").c_str(), "offline_smallR_jet_pt", 80.0, 0.0, 800.0);
    for(int threshold = m_singleTowerThreshold_start; threshold < m_singleTowerThreshold_stop; threshold+=m_singleTowerThreshold_step){
      std::string trigger_path(path+"/L1_GFEX_T"+std::to_string(threshold)+"/numerator");
      m_triggerPlots[trigger_path] = new TH1F(trigger_path.c_str(),"offline_smallR_jet_pt", 80.0, 0.0, 800.0);
    }
  }
  // gBlock Turn-On Curves and Rates
  {
    std::string path("turnon/block/all");
    m_triggerPlots[path+"/denominator"] = new TH1F((path+"/denominator").c_str(), "offline_smallR_jet_pt", 80.0, 0.0, 800.0);
    // gBlock Turn-On Curves
    for(int threshold = m_singleBlockThreshold_start; threshold < m_singleBlockThreshold_stop; threshold+=m_singleBlockThreshold_step){
      std::string trigger_path(path+"/L1_GFEX_B"+std::to_string(threshold)+"/numerator");
      m_triggerPlots[trigger_path] = new TH1F(trigger_path.c_str(),"offline_smallR_jet_pt", 80.0, 0.0, 800.0);
    }
  }

  // gJet Turn-On Curves
  {
     
    for(int num_subjets=0; num_subjets<4; ++num_subjets){
      std::string path("turnon/jet");
      // when num_subjets == 0, use this as "inclusive"
      //  and when num_subjets == 3, it means >= 3
      if(num_subjets!=0) path+= "/"+std::to_string(num_subjets)+"subjet";
      else path+= "/all"; // inclusive

      // denominators for various offline selections
      m_triggerPlots[path+"/denominator"]             = new TH1F((path+"/denominator").c_str(), "offline_largeR_jet_pt", 80.0, 0.0, 800.0);

      // L1 Turn-On Curves
      std::string l1_path(path+"/L1_J100/numerator");
      m_triggerPlots[l1_path]                         = new TH1F(l1_path.c_str(), "offline_largeR_jet_pt", 80.0, 0.0, 800.0);

      // gJet Turn-On Curves
      for(int threshold = m_singleJetThreshold_start; threshold < m_singleJetThreshold_stop; threshold+=m_singleJetThreshold_step){
        std::string gfex_path(path+"/L1_GFEX_J"+std::to_string(threshold)+"/numerator");
        // use uncorrected gFEX jets
        m_triggerPlots[gfex_path]                     = new TH1F(gfex_path.c_str(),"offline_largeR_jet_pt", 80.0, 0.0, 800.0);
        // use corrected gFEX jets
        m_triggerPlots[gfex_path+"_pileupCorrection"]           = new TH1F((gfex_path+"_pileupCorrection").c_str(),"offline_largeR_jet_pt_wPileupCorrection", 80.0, 0.0, 800.0);
      }
    }
  }

  // initialize everything and record to worker
  for(const auto& plot: m_kinematicPlots){
    RETURN_CHECK("histInitialize()", (plot.second)->initialize(), ("Could not initialize ObjectHists for "+plot.first).c_str());
    (plot.second)->record( wk() );
  }

  for(const auto& plot: m_eventPlots1D)     wk()->addOutput(plot.second);
  for(const auto& plot: m_eventPlots2D)     wk()->addOutput(plot.second);

  for(const auto& plot: m_ratePlots)        wk()->addOutput(plot.second);

  for(const auto& plot: m_triggerPlots)     wk()->addOutput(plot.second);
  for(const auto& plot: m_2DtriggerPlots)   wk()->addOutput(plot.second);

  wk()->addOutput(m_resolution);

  
  return EL::StatusCode::SUCCESS;
  }

EL::StatusCode gFEX::Analysis :: fileExecute () {
  //std::cout << "fileexecute!!!" << std::endl;
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode gFEX::Analysis :: changeInput (bool /*firstFile*/)
{
  //std::cout << "Chaginig input now" << std::endl;
    Info("changeInput", "Changing input");
	// There are two trees to acknowledge here
	//  - Maps
    //std::cout << "Changed INPUT" << std::endl;
	m_mapTree = dynamic_cast<TTree*> (wk()->inputFile()->Get("maps"));
	//  - Physics
    //std::cout << "Map tree" << std::endl;
	m_tree = wk()->tree();
    //std::cout << "wk" << std::endl;
	InitializeBranches();
    //std::cout << "Initizized branches" << std::endl;

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode gFEX::Analysis :: initialize ()
{
  m_sampleName = wk()->metaData()->castString("sample_name");
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode gFEX::Analysis :: execute ()
{
  // Get the Event Entry from both trees
  //std::cout << "Execute here" << std::endl;
  wk()->tree()->GetEntry (wk()->treeEntry());

  m_mapTree->GetEntry(0);
  int evtNum = wk()->tree()->GetEntryNumber (wk()->treeEntry());

  // Set the Event's weight
  double eventWeight = 1.;//mcEventWeight->at(0);		// "weight" is a shortcut to this

  if(m_debug) std::cout << "Event #" << evtNum << " with weight " << eventWeight << std::endl;

  ADD_CUTFLOW("total");

  // get all of our objects set up
  gFEX::GetJets(OfflineJets_AntiKt10, AntiKt10LCTopoJets_n, *AntiKt10LCTopoJets_pt, *AntiKt10LCTopoJets_eta, *AntiKt10LCTopoJets_phi, *AntiKt10LCTopoJets_m);
  if(m_debug) std::cout <<"Offline Jets" << std::endl;

  gFEX::GetJets(OfflineJets_AntiKt10Trimmed, AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_n, *AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_pt, *AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_eta, *AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_phi, *AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_m, *AntiKt10LCTopoTrimmedSmallR20PtFrac5Jets_nsj);
  if(m_debug) std::cout <<"Offline Trimmed" << std::endl;

  gFEX::GetJets(OfflineJets_AntiKt4, AntiKt4LCTopoJets_n, *AntiKt4LCTopoJets_pt, *AntiKt4LCTopoJets_eta, *AntiKt4LCTopoJets_phi, *AntiKt4LCTopoJets_m);
  if(m_debug) std::cout <<"AntiKt4" << std::endl;

  gFEX::GetJets(OfflineJets_CamKt12, CamKt12LCTopoJets_n, *CamKt12LCTopoJets_pt, *CamKt12LCTopoJets_eta, *CamKt12LCTopoJets_phi, *CamKt12LCTopoJets_m);
  if(m_debug) std::cout <<"Camt12" << std::endl;

  gFEX::GetJets(TruthJets_AntiKt10, AntiKt10TruthJets_n, *AntiKt10TruthJets_pt, *AntiKt10TruthJets_eta, *AntiKt10TruthJets_phi, *AntiKt10TruthJets_m);
  if(m_debug) std::cout <<"Truth Jets 10" << std::endl;

  gFEX::GetJets(TruthJets_AntiKt4, AntiKt4TruthJets_n, *AntiKt4TruthJets_pt, *AntiKt4TruthJets_eta, *AntiKt4TruthJets_phi, *AntiKt4TruthJets_m);
  if(m_debug) std::cout <<"Truth Jets 4" << std::endl;

  gFEX::GetJets(TruthJets_CamKt12, CamKt12TruthJets_n, *CamKt12TruthJets_pt, *CamKt12TruthJets_eta, *CamKt12TruthJets_phi, *CamKt12TruthJets_m);
  if(m_debug) std::cout <<"Truth Jets 12" << std::endl;

  gFEX::GetTowers(gTowers, gTowerEt->size(), *gTowerEt, *gTowerEtaGeometric, *gTowerPhiGeometric, *gTowerEtaMin, *gTowerEtaMax, *gTowerPhiMin, *gTowerPhiMax, *gTowerEtaWeighted, *gTowerPhiWeighted);
  //gFEX::GetTowers(jTowers, jTowerEt->size(), *jTowerEt, *jTowerEtaGeometric, *jTowerPhiGeometric, *jTowerEtaMin, *jTowerEtaMax, *jTowerPhiMin, *jTowerPhiMax);
  if(m_debug) std::cout <<"gTowers" << std::endl;

  // get list of gTowers in central region
  std::vector<gFEX::Tower> gTowers_central(gTowers.size());
  // hide the scope of "it"
  {
    auto it = std::copy_if(gTowers.begin(), gTowers.end(), gTowers_central.begin(), [](gFEX::Tower tower){return std::fabs(tower.eta()) <= 2.4;});
    gTowers_central.resize(std::distance(gTowers_central.begin(), it));
  }
  if(m_debug) std::cout << "gTowers central" << std::endl;

  std::vector<gFEX::Tower> gTowers_positive(gTowers.size());
  // hide the scope of "it"
  {
    auto it = std::copy_if(gTowers.begin(), gTowers.end(), gTowers_positive.begin(), [](gFEX::Tower tower){return tower.pt() >= 0.0;});
    gTowers_positive.resize(std::distance(gTowers_positive.begin(), it));
  }
  if(m_debug) std::cout << "gTowers positive" << std::endl;

  std::vector<gFEX::Tower> gTowers_positive_central(gTowers_central.size());
  // hide the scope of "it"
  {
    auto it = std::copy_if(gTowers_central.begin(), gTowers_central.end(), gTowers_positive_central.begin(), [](gFEX::Tower tower){return tower.pt() >= 0.0;});
    gTowers_positive_central.resize(std::distance(gTowers_positive_central.begin(), it));
  }
  if(m_debug) std::cout << "gTowers positive central" << std::endl;

  // need to write a function to build gBlocks, copy gTowers for now
  std::vector<gFEX::Block> gBlocks_central(gTowers_central.size());
  gFEX::BuildBlocksFromTowers(gBlocks_central, gTowers_central, 3, 3);

  std::vector<gFEX::Tower> gTowers_corrected(gTowers_central.size());
  double SKCut = 0;
  if(m_doAreaSub) gFEX::ApplyAreaSub(gTowers_corrected, gTowers_central);
  if(m_doSoftKiller) SKCut = gFEX::ApplySoftKiller(gTowers_central, gTowers_central, 0.6, 2.5, false, false);
  if(m_doSoftKillerAbsVal) SKCut = gFEX::ApplySoftKiller(gTowers_central, gTowers_central, 0.6, 2.5, true, false, true);
  if(m_doFakeSoftKiller) SKCut = gFEX::ApplyFakeSK(gTowers_central, 0.6, 2.5, 500, 7000, false);
  if(m_debug) std::cout << "softkiller stuff" << std::endl;

  //gFEX::GetJets(gJets, ConeGJet10_Et->size(), *ConeGJet10_Et, *ConeGJet10_eta, *ConeGJet10_phi, std::vector<float>(ConeGJet10_Et->size(), 0.0), *ConeGJet10_seedIndex);
  gFEX::BuildJetsFromTowers(gJets, gTowers, m_seedThreshold, m_dR, m_useSeedAsCenter);
  gFEX::BuildJetsFromTowers(gJets_central, gTowers_central, m_seedThreshold, m_dR, m_useSeedAsCenter);
  if(m_debug) std::cout <<"gJets" << std::endl;

  // correct gJets using area-based subtraction with rho calculated via the median approach for gTowers in the central FPGAs only
  gFEX::PileupCorrection(gJets_corrected, gJets_central, gTowers_central, m_pileupMitigation, m_rhoCalculation);
  if(m_debug) std::cout << "gJets corrected" << std::endl;

  gFEX::GetJets(Run2_L1Jets, Run2_L1Jet_Et->size(), *Run2_L1Jet_Et, *Run2_L1Jet_eta, *Run2_L1Jet_phi, std::vector<float>(Run2_L1Jet_Et->size(), 0.0));
  std::vector<gFEX::Jet> Run2_L1Jets_central(Run2_L1Jets.size());
  // hide the scope of "it"
  {
    auto it = std::copy_if(Run2_L1Jets.begin(), Run2_L1Jets.end(), Run2_L1Jets_central.begin(), [](gFEX::Jet jet){return std::fabs(jet.eta()) <= 3.2;});
    Run2_L1Jets_central.resize(std::distance(Run2_L1Jets_central.begin(), it));
  }

  if(m_debug) std::cout << "Run2" << std::endl;

  // pileup calculations
  double rho         = gFEX::GetRho(gTowers, m_rhoCalculation);
  double rho_median_central = gFEX::GetRho(gTowers_central, m_rhoCalculation);
  double rho_offline = Kt4EMTopoEventShape_Density;
  double rho_positive_median = gFEX::GetRho(gTowers_positive, "median");
  double rho_positive_median_central = gFEX::GetRho(gTowers_positive_central, "median");

  // calculate the minimum deltaR of all trimmed large-R jets
  double minimumDeltaR = gFEX::GetMinimumDeltaR(OfflineJets_AntiKt10Trimmed);
  double minimumDeltaR4 = gFEX::GetMinimumDeltaR(OfflineJets_AntiKt4);
  /** ================================================== **/
  /**            NO MORE OBJECT DEFINITIONS              **/
  /** ================================================== **/

  /** ================================================== **/
  /**          KINEMATIC PLOTS PRE SELECTION             **/
  /** ================================================== **/
  
  m_kinematicPlots["presel/OfflineJets_AntiKt10"]->execute(OfflineJets_AntiKt10, eventWeight);
  m_kinematicPlots["presel/OfflineJets_AntiKt10Trimmed"]->execute(OfflineJets_AntiKt10Trimmed, eventWeight);
  m_kinematicPlots["presel/OfflineJets_AntiKt4"]->execute(OfflineJets_AntiKt4, eventWeight);
  m_kinematicPlots["presel/OfflineJets_CamKt12"]->execute(OfflineJets_CamKt12, eventWeight);
  m_kinematicPlots["presel/TruthJets_AntiKt10"] ->execute(TruthJets_AntiKt10, eventWeight);
  m_kinematicPlots["presel/TruthJets_AntiKt4"]->execute(TruthJets_AntiKt4, eventWeight);
  m_kinematicPlots["presel/TruthJets_CamKt12"]->execute(TruthJets_CamKt12, eventWeight);
  m_kinematicPlots["presel/Run2_L1Jets"]->execute(Run2_L1Jets, eventWeight);
  m_kinematicPlots["presel/Run2_L1Jets_central"]->execute(Run2_L1Jets_central, eventWeight);
  m_kinematicPlots["presel/gTowers"]->execute(gTowers, eventWeight);
  m_kinematicPlots["presel/gTowers_central"]->execute(gTowers_central, eventWeight);
  m_kinematicPlots["presel/gBlocks_central"]->execute(gBlocks_central, eventWeight);
  m_kinematicPlots["presel/gJets"]->execute(gJets, eventWeight);
  m_kinematicPlots["presel/gJets_central"]->execute(gJets_central, eventWeight);
  m_kinematicPlots["presel/gJets_corrected"]->execute(gJets_corrected, eventWeight);
  
  //m_kinematicPlots["presel/gBlocks_central/RatiogBlockJetPt"]->execute(gBlockJetRatio, eventWeight);


  m_eventPlots1D["presel/event/rho_median"]->Fill(rho/1.e3, eventWeight);
  m_eventPlots1D["presel/event/rho_median_central"]->Fill(rho_median_central/1.e3, eventWeight);
  m_eventPlots1D["presel/event/rho_offline"]->Fill(rho_offline/1.e3, eventWeight);
  m_eventPlots1D["presel/event/rho_positive_median"]->Fill(rho_positive_median/1.e3, eventWeight);
  m_eventPlots1D["presel/event/rho_positive_median_central"]->Fill(rho_positive_median_central/1.e3, eventWeight);
  m_eventPlots2D["presel/event/rho_median_versus_rho_median_central"]->Fill(rho_median_central/1.e3, rho/1.e3, eventWeight);
  m_eventPlots1D["presel/event/minDeltaR_offlineJets"]->Fill(minimumDeltaR, eventWeight);
  m_eventPlots1D["presel/event/minDeltaR4_offlineJets"]->Fill(minimumDeltaR4, eventWeight);
  m_eventPlots1D["presel/event/distFrontBunchTrain"]->Fill(distFrontBunchTrain, eventWeight);
  for(unsigned int i=0 ; i<gBlockJetRatioVector.size() ; i++){
    m_eventPlots1D["presel/event/RatiogBlockJetPt"]->Fill(gBlockJetRatio, eventWeight);
  }

  m_eventPlots1D["presel/event/METgBlocks"]->Fill(MetgBlocks, eventWeight);
  m_eventPlots1D["presel/event/METXgBlocks"]->Fill(MetXgBlocks, eventWeight);
  m_eventPlots1D["presel/event/METYgBlocks"]->Fill(MetYgBlocks, eventWeight);
  
  m_eventPlots1D["presel/event/METgTowers"]->Fill(MetgTowers, eventWeight);
  m_eventPlots1D["presel/event/METXgTowers"]->Fill(MetXgTowers, eventWeight);
  m_eventPlots1D["presel/event/METYgTowers"]->Fill(MetYgTowers, eventWeight);
  
  m_eventPlots1D["presel/event/METOfflineAntiKt4"]->Fill(MetAntiKt4, eventWeight);
  m_eventPlots1D["presel/event/METXOfflineAntiKt4"]->Fill(MetXAntiKt4, eventWeight);
  m_eventPlots1D["presel/event/METYOfflineAntiKt4"]->Fill(MetYAntiKt4, eventWeight);

  
  m_eventPlots2D["presel/event/rho_median_versus_distFrontBunchTrain"]->Fill(distFrontBunchTrain, rho/1.e3, eventWeight);
  m_eventPlots2D["presel/event/rho_median_central_versus_distFrontBunchTrain"]->Fill(distFrontBunchTrain, rho_median_central/1.e3, eventWeight);
  m_eventPlots2D["presel/event/rho_offline_versus_distFrontBunchTrain"]->Fill(distFrontBunchTrain, rho_offline/1.e3, eventWeight);
  m_eventPlots2D["presel/event/rho_median_versus_rho_offline"]->Fill(rho/1.e3, rho_offline/1.e3, eventWeight);
  m_eventPlots2D["presel/event/rho_median_central_versus_rho_offline"]->Fill(rho_median_central/1.e3, rho_offline/1.e3, eventWeight);
  m_eventPlots2D["presel/event/rho_positive_median_versus_rho_offline"]->Fill(rho_positive_median/1.e3, rho_offline/1.e3, eventWeight);
  m_eventPlots2D["presel/event/rho_positive_median_central_versus_rho_offline"]->Fill(rho_positive_median_central/1.e3, rho_offline/1.e3, eventWeight);

  //Ratio of gBlock pT to jet pT and 2-d of the ratio vs delta R between jet and gblock
  for(unsigned int i=0 ; i<gBlockJetRatioVector.size() ; i++){
    m_eventPlots1D["presel/event/RatiogBlockJetPt"]->Fill(gBlockJetRatioVector[i], eventWeight);
    m_eventPlots2D["presel/event/RatiogBlockJetPtDeltaR"]->Fill(DeltaRgBlockJetVector[i], gBlockJetRatioVector[i], eventWeight);
  }
  //number of gTowers that pass some pT cut as function of pt
  for(unsigned int i=0; i<gTowerPtCount.size(); i++){
    m_eventPlots2D["presel/event/number_towers_after_cut"]->Fill(gTowerPtCountNumber[i], gTowerPtCount[i], eventWeight);
  }
  //  //Ratio of number of gBlocks matched to offline jet as function of offline jet pT
  
  for (unsigned int i=0 ; i<gBlockJetMatchJetPtVector.size() ; i++){
    m_eventPlots2D["presel/event/gBlockJetMatchvsJetPt"]->Fill(gBlockJetMatchJetPtVector[i], gBlockJetMatchRatioVector[i], eventWeight);
  }

  // for(unsigned int i=0 ; i<gBlockPtCuts.size() ; i++){
  //     path = selection+"/event/offlineJetMatchgBlockPtgBlockPtCut"+std::to_string(gBlockPtCuts[i]);
  //     m_eventPlots1D[path] = new TH1F(path.c_str(), ("OfflineJet_AntiKt4 that match gBlock Pt with gBlock Pt Cut of "+std::to_string(gBlockPtCuts[i])).c_str(), 1000, 0., 1000.);
  //   }
  
  // for(unsigned int i=0 ; i<offlineJetMatchgBlockPt.size(); i++){
  //   m_eventPlots1D["presel/event/offlineJetMatchgBlockPt"]->Fill(offlineJetMatchgBlockPt[i], eventWeight);
  // }

  // for(unsigned int i=0 ; i<gBlockPtCuts.size() ; i++){
  //   for (unsigned int j=0 ; j<offlineJetMatchgBlockPtWithgBlockPtCuts[i].size() ; j++){
  //     m_eventPlots1D["presel/event/offlineJetMatchgBlockPtgBlockPtCut"+std::to_string((int)gBlockPtCuts[i])]->Fill(offlineJetMatchgBlockPtWithgBlockPtCuts[i][j], eventWeight);
  //   }
  // }

  /** ================================================== **/
  /**   START EVENT SELECTIONS AND OFFLINE SELECTIONS    **/
  /** ================================================== **/

  if(distFrontBunchTrain < m_minDistanceFrontBunchTrain){
    wk()->skipEvent();
    return EL::StatusCode::SUCCESS;
  }
  ADD_CUTFLOW("dist_from_bunch_train");


  /** ================================================== **/
  /**       RATE PLOTS HAVE NO OFFLINE SELECTIONS        **/
  /** ================================================== **/
  for(unsigned int i=1; i<=6; ++i){
    m_ratePlots[std::string(std::to_string(i)+"tower_central")]->Fill(-1, eventWeight);
    //m_ratePlots["stochastic/singleTower_central"]->Fill(-1, eventWeight);
    if(gTowers_central.size() >= i){
      m_ratePlots[std::string(std::to_string(i)+"tower_central")]->Fill(gTowers_central.at(i-1).pt()/1.e3, eventWeight);
      //m_ratePlots["stochastic/singleTower_central"]->Fill(std::fabs(gTowers_central.back().pt())/1.e3, eventWeight);
    }

    m_ratePlots[std::string(std::to_string(i)+"block_central")]->Fill(-1, eventWeight);
    //m_ratePlots["stochastic/singleBlock_central"]->Fill(-1, eventWeight);
    if(gBlocks_central.size() >= i){
      m_ratePlots[std::string(std::to_string(i)+"block_central")]->Fill(gBlocks_central.at(i-1).pt()/1.e3, eventWeight);
      //m_ratePlots["stochastic/singleBlock_central"]->Fill(std::fabs(gBlocks_central.back().pt())/1.e3, eventWeight);
    }

    m_ratePlots[std::string(std::to_string(i)+"jet_central")]->Fill(-1, eventWeight);
    if(gJets_central.size() >= i){
      m_ratePlots[std::string(std::to_string(i)+"jet_central")]->Fill(gJets_central.at(i-1).pt()/1.e3, eventWeight);
    }
  }

  // Kinematic/ Monte Carlo Quality Cut
  if(m_doMCQualityCut){
    // if we do not have enough information in the event to make this cut, reject the event
    if(TruthJets_AntiKt4.size() < 1){
      wk()->skipEvent();
      return EL::StatusCode::SUCCESS;
    }

    ADD_CUTFLOW("one_truth_jet");
    if(OfflineJets_AntiKt4.size() < 2){
      wk()->skipEvent();
      return EL::StatusCode::SUCCESS;
    }
    ADD_CUTFLOW("two_reco_jets");

    // only accept events that pass: 0.6 < pTavg/leading truth pT < 1.4
    float average_pT = (OfflineJets_AntiKt4.at(0).pt() + OfflineJets_AntiKt4.at(1).pt())/2.;
    float ratio = average_pT / TruthJets_AntiKt4.at(0).pt();
    if(0.6 >= ratio || ratio >= 1.4){
      wk()->skipEvent();
      return EL::StatusCode::SUCCESS;
    }
    ADD_CUTFLOW("mc_quality_cut");
  }
  if(m_debug) std::cout << "Pass MC Quality Cut" << std::endl;

  // std::vector<int> testdrvector;
  // testdrvector.clear();
  // for(unsigned int i=0 ; i<101 ; i++){
  //   testdrvector.push_back(i);
  // }
  // //  testdrvector.erase(testdrvector.begin()+2);
  // // testdrvector.erase(testdrvector.begin()+3);

  // std::vector<int> tester;
  // tester.clear();
  // tester.push_back(10);
  // tester.push_back(5);
  // tester.push_back(12);

  // std::sort (tester.begin(), tester.end());
  // for(unsigned int i=0; i<tester.size() ; i++){
  //   std::cout << "tester: " << tester[i] << std::endl;
  // }

  // std::vector<int> indexToRemove;
  // indexToRemove.clear();
  // indexToRemove.push_back(4);
  // indexToRemove.push_back(2);
  // std::sort(indexToRemove.begin(), indexToRemove.end());
  
  // for(unsigned int i=0; i<indexToRemove.size() ; i++){
  //   testdrvector.erase(testdrvector.begin()+indexToRemove[i]-i);
  // }
    
  // // for(unsigned int i=0 ; i<testdrvector.size(); i++){
  // //   if(testdrvector[i]==2){
  // //     testdrvector.erase(testdrvector.begin()+i);
  // //   }
    
  // // }
  // for(unsigned int i=0 ; i<testdrvector.size(); i++){
  //   std::cout << "Some element: " << testdrvector[i] << std::endl;
  // }
        
    

  std::vector<double> deltaRbetweenJets;
  // for(unsigned int i=0; i<OfflineJets_AntiKt4.size() ; i++ ){
  //   double smallestDeltaR = 99.;
  //   TLorentzVector oj1(0., 0., 0., 0.);
  //   oj1.SetPtEtaPhiM(OfflineJets_AntiKt4[i].pt(), OfflineJets_AntiKt4[i].eta(), OfflineJets_AntiKt4[i].phi(), OfflineJets_AntiKt4[i].m());
  //   //std::cout << "OJ1 Kinematics:   " << oj1.Pt() << "  " << oj1.Eta() << "  " << oj1.Phi() << "  " << oj1.M() << std::endl;
  //   for (unsigned int j=0; j<OfflineJets_AntiKt4.size() ; j++ ){
  //     if(i!=j){
  //       TLorentzVector oj2(0., 0., 0., 0.);
  //        oj2.SetPtEtaPhiM(OfflineJets_AntiKt4[j].pt(), OfflineJets_AntiKt4[j].eta(), OfflineJets_AntiKt4[j].phi(), OfflineJets_AntiKt4[j].m());
  //        //std::cout << "OJ2 Kinematics:   " << oj2.Pt() << "  " << oj2.Eta() << "  " << oj2.Phi() << "  " << oj2.M() << std::endl;
  //       double newsmallDeltaR;
  //       newsmallDeltaR = oj1.DeltaR(oj2);
  //       if(newsmallDeltaR<1.0){
  //         OfflineJets_AntiKt4.erase(OfflineJets_AntiKt4.begin()+i);
  //         OfflineJets_AntiKt4.erase(OfflineJets_AntiKt4.begin()+j);
  //       }
  //       //std::cout << "Jets:  " << i << ", " << j << "  delta R: " << newsmallDeltaR << std::endl;
  //       if(newsmallDeltaR<smallestDeltaR){
  //         smallestDeltaR = newsmallDeltaR;
  //       }
  //     }
  //     deltaRbetweenJets.push_back(smallestDeltaR);    
  //   }
  // }

  std::vector<int> JetsToErase;
  JetsToErase.clear();
  
  for(unsigned int i=0; i<OfflineJets_AntiKt4.size() ; i++ ){
    for (unsigned int j=0; j<OfflineJets_AntiKt4.size() ; j++ ){
      if(i!=j){
      double dphiJet=0.;
      double detaJet=0.;
      double dRJet=0.;
      dphiJet = std::fabs(std::fabs(std::fabs(OfflineJets_AntiKt4[i].phi()-OfflineJets_AntiKt4[j].phi())-pi)-pi);
      detaJet = OfflineJets_AntiKt4[i].eta()-OfflineJets_AntiKt4[j].eta();
      dRJet = std::sqrt((detaJet*detaJet)+(dphiJet*dphiJet));
      if(dRJet<1.){
        JetsToErase.push_back(i);
        JetsToErase.push_back(j);
      }
      }
    }
  }
  
  std::sort(JetsToErase.begin(), JetsToErase.end());
  JetsToErase.erase(unique(JetsToErase.begin(), JetsToErase.end()), JetsToErase.end());
  
  for(unsigned int i=0 ; i<JetsToErase.size() ; i++){
    OfflineJets_AntiKt4.erase(OfflineJets_AntiKt4.begin()+JetsToErase[i]-i);
  }

  deltaRbetweenIsolatedJets.clear();
  for(unsigned int i=0; i<OfflineJets_AntiKt4.size() ; i++ ){
    for (unsigned int j=0; j<OfflineJets_AntiKt4.size() ; j++ ){
      if(i!=j){
      double dphiJet=0.;
      double detaJet=0.;
      double dRJet=0.;
      dphiJet = std::fabs(std::fabs(std::fabs(OfflineJets_AntiKt4[i].phi()-OfflineJets_AntiKt4[j].phi())-pi)-pi);
      detaJet = OfflineJets_AntiKt4[i].eta()-OfflineJets_AntiKt4[j].eta();
      dRJet = std::sqrt((detaJet*detaJet)+(dphiJet*dphiJet));
      deltaRbetweenIsolatedJets.push_back(dRJet);

      TLorentzVector test1;
      TLorentzVector test2;
      test1.SetPtEtaPhiM(0., 0., 0., 0.);
      test2.SetPtEtaPhiM(0., 0., 0., 0.);

      test1.SetPtEtaPhiM(OfflineJets_AntiKt4[i].pt()/1.e3, OfflineJets_AntiKt4[i].eta(), OfflineJets_AntiKt4[i].phi(), OfflineJets_AntiKt4[i].m()/1.e3);
      test2.SetPtEtaPhiM(OfflineJets_AntiKt4[j].pt()/1.e3, OfflineJets_AntiKt4[j].eta(), OfflineJets_AntiKt4[j].phi(), OfflineJets_AntiKt4[j].m()/1.e3);

      double testDR = 0.;
      testDR = test1.DeltaR(test2);
      if(testDR<1.){
        std::cout << "There is a problem with delta R:  " << testDR << "  alternate way:   "  << dRJet << std::endl;
      }
      
      }
    }
  }


  // //std::cout << "Number of jets before isolation: " << OfflineJets_AntiKt4.size() << std::endl;
  // for(unsigned int i=0; i<OfflineJets_AntiKt4.size() ; i++ ){  
  //   if(m_doIsolationCut4){
  //     //std::cout << "Delta R between jets: " << deltaRbetweenJets[i] << std::endl;
  //     if(deltaRbetweenJets[i] < 1.0){
  //       OfflineJets_AntiKt4.erase(OfflineJets_AntiKt4.begin()+i);
  //     }
  //   }
  // }

  //std::cout << "Number of jets AFTER isolation: " << OfflineJets_AntiKt4.size() << std::endl;
  double minimumDeltaR4Isolated = gFEX::GetMinimumDeltaR(OfflineJets_AntiKt4);

  
  // filter out our large-R trimmed offline jets
  {// for small-R offline jets  EDIT HERE
    auto newEnd = std::remove_if(OfflineJets_AntiKt4.begin(), OfflineJets_AntiKt4.end(),
        [this](gFEX::Jet ojet) -> bool { return (ojet.eta() < m_minEta_offline ||
                                                 ojet.eta() > m_maxEta_offline);});
    OfflineJets_AntiKt4.erase( newEnd, OfflineJets_AntiKt4.end() );
    
  }
  {// for large-R offline jets
    auto newEnd = std::remove_if(OfflineJets_AntiKt10Trimmed.begin(), OfflineJets_AntiKt10Trimmed.end(),
        [this](gFEX::Jet ojet) -> bool { return (ojet.eta() < m_minEta_offline ||
                                            ojet.eta() > m_maxEta_offline);});
    OfflineJets_AntiKt10Trimmed.erase( newEnd, OfflineJets_AntiKt10Trimmed.end() );
  }

  if(m_doIsolationCut){
    // require the offline jets to be isolated
    if(minimumDeltaR < 2.0){
      wk()->skipEvent();
      return EL::StatusCode::SUCCESS;
    }
    ADD_CUTFLOW("isolation_cut");
  }

  
  // if(m_doIsolationCut4){
  //   if(minimumDeltaR4 < 1.0){
  //     //wk()->skipEvent();
  //     return EL::StatusCode::SUCCESS;
  //   }
  //   //ADD_CUTFLOW("isolation_cut4"); //This could be added later to the cutflow
  // }
    
  if(m_debug) std::cout << "Pass Isolation Cut" << std::endl;
  //m_outTrees.clear();

  //m_outTrees = new TTree("PostSelKinematics", "PostSelKinematics");
  
  /** ================================================== **/
  /**          KINEMATIC PLOTS POST SELECTION            **/
  /** ================================================== **/
  m_kinematicPlots["postsel/OfflineJets_AntiKt10"]->execute(OfflineJets_AntiKt10, eventWeight);
  m_kinematicPlots["postsel/OfflineJets_AntiKt10Trimmed"]->execute(OfflineJets_AntiKt10Trimmed, eventWeight);
  m_kinematicPlots["postsel/OfflineJets_AntiKt4"]->execute(OfflineJets_AntiKt4, eventWeight);
  m_kinematicPlots["postsel/OfflineJets_CamKt12"]->execute(OfflineJets_CamKt12, eventWeight);
  m_kinematicPlots["postsel/TruthJets_AntiKt10"] ->execute(TruthJets_AntiKt10, eventWeight);
  m_kinematicPlots["postsel/TruthJets_AntiKt4"]->execute(TruthJets_AntiKt4, eventWeight);
  m_kinematicPlots["postsel/TruthJets_CamKt12"]->execute(TruthJets_CamKt12, eventWeight);
  m_kinematicPlots["postsel/Run2_L1Jets"]->execute(Run2_L1Jets, eventWeight);
  m_kinematicPlots["postsel/Run2_L1Jets_central"]->execute(Run2_L1Jets_central, eventWeight);
  m_kinematicPlots["postsel/gTowers"]->execute(gTowers, eventWeight);
  m_kinematicPlots["postsel/gTowers_central"]->execute(gTowers_central, eventWeight);
  m_kinematicPlots["postsel/gBlocks_central"]->execute(gBlocks_central, eventWeight);
  m_kinematicPlots["postsel/gJets"]->execute(gJets, eventWeight);
  m_kinematicPlots["postsel/gJets_central"]->execute(gJets_central, eventWeight);
  m_kinematicPlots["postsel/gJets_corrected"]->execute(gJets_corrected, eventWeight);

  m_eventPlots1D["postsel/event/rho_median"]->Fill(rho/1.e3, eventWeight);
  m_eventPlots1D["postsel/event/rho_median_central"]->Fill(rho_median_central/1.e3, eventWeight);
  m_eventPlots1D["postsel/event/rho_offline"]->Fill(rho_offline/1.e3, eventWeight);
  m_eventPlots1D["postsel/event/rho_positive_median"]->Fill(rho_positive_median/1.e3, eventWeight);
  m_eventPlots1D["postsel/event/rho_positive_median_central"]->Fill(rho_positive_median_central/1.e3, eventWeight);
  m_eventPlots2D["postsel/event/rho_median_versus_rho_median_central"]->Fill(rho_median_central/1.e3, rho/1.e3, eventWeight);
  m_eventPlots1D["postsel/event/minDeltaR_offlineJets"]->Fill(minimumDeltaR, eventWeight);
  m_eventPlots1D["postsel/event/minDeltaR4_offlineJets"]->Fill(minimumDeltaR4Isolated, eventWeight);
  m_eventPlots1D["postsel/event/distFrontBunchTrain"]->Fill(distFrontBunchTrain, eventWeight);
  //Ratio of gBlock pT to jet pT and 2-d of the ratio vs delta R between jet and gblock
  if(gBlockJetRatioVector.size()>0){
  for(unsigned int i=0 ; i<gBlockJetRatioVector.size() ; i++){
    m_eventPlots1D["postsel/event/RatiogBlockJetPt"]->Fill(gBlockJetRatioVector[i], eventWeight);
    m_eventPlots2D["postsel/event/RatiogBlockJetPtDeltaR"]->Fill(DeltaRgBlockJetVector[i], gBlockJetRatioVector[i], eventWeight);
  }
  }

  //m_outTrees->Branch("EventWeight", &eventWeight);

  //number of gTowers that pass some pT cut as function of pt
  //for(unsigned int i=0; i<gTowerPtCount.size(); i++){
  //  m_eventPlots2D["postsel/event/number_towers_after_cut"]->Fill(gTowerPtCountNumber[i], gTowerPtCount[i], eventWeight);
  //}
  //Ratio of number of gBlocks matched to offline jet as function of offline jet pT
  //std::cout << "Test size : " << RatiogBlockPtJetPtBinnedByJetPt.size() << std::endl;
  for(unsigned int i=0; i<RatiogBlockPtJetPtBinnedByJetPt.size() ; i++){
    for(unsigned int j=0; j<RatiogBlockPtJetPtBinnedByJetPt[i].size() ; j++){
      std::string path;
      path = "postsel/event/RatiogBlockPtJetPtBinnedByJetPt"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      //std::cout << path << std::endl;
      m_eventPlots1D[path.c_str()]->Sumw2();
      m_eventPlots1D[path.c_str()]->Fill(RatiogBlockPtJetPtBinnedByJetPt[i][j], eventWeight);
      path = "postsel/event/RatiogBlockPtJetPtBinnedByJetPtEta"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      //std::cout << path << std::endl;
      m_eventPlots1D[path.c_str()]->Sumw2();
      m_eventPlots1D[path.c_str()]->Fill(RatiogBlockPtJetPtBinnedByJetPtEta[i][j], eventWeight);
      path = "postsel/event/RatiogBlockPtJetPtBinnedByJetPtPhi"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      //std::cout << path << std::endl;
      m_eventPlots1D[path.c_str()]->Sumw2();
      m_eventPlots1D[path.c_str()]->Fill(RatiogBlockPtJetPtBinnedByJetPtPhi[i][j], eventWeight);
      path = "postsel/event/RatioVsPhigBlockPtJetPtBinnedByJetPt"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      //std::cout << path << std::endl;
      m_eventPlots2D[path.c_str()]->Sumw2();
      m_eventPlots2D[path.c_str()]->Fill(RatiogBlockPtJetPtBinnedByJetPt[i][j], RatiogBlockPtJetPtBinnedByJetPtPhi[i][j], eventWeight);
      path = "postsel/event/RatioVsEtagBlockPtJetPtBinnedByJetPt"+std::to_string(5*i)+"_"+std::to_string(5+5*i);
      //std::cout << path << std::endl;
      m_eventPlots2D[path.c_str()]->Sumw2();
      m_eventPlots2D[path.c_str()]->Fill(RatiogBlockPtJetPtBinnedByJetPt[i][j], RatiogBlockPtJetPtBinnedByJetPtEta[i][j], eventWeight);
    }
  }
  //std::cout << "HERE" << std::endl;
  //std::cout << "Size:  " << RatiogBlockPtJetPtBinnedByJetEta.size() << std::endl;
  for(unsigned int i=0; i<RatiogBlockPtJetPtBinnedByJetEta.size() ; i++){//50 ; i++){
    double etaLow=((i*5)/10.)-2.5;
    //std::cout << "eta low: " << etaLow << std::endl;
    //std::cout << "Inner size: " << RatiogBlockPtJetPtBinnedByJetEta[i].size() << std::endl;
   for(unsigned int j=0 ; j<RatiogBlockPtJetPtBinnedByJetEta[i].size() ; j++){
     //std::cout << "Filling histo " << i << "  " << j << std::endl;
     std::string path;
     path = "postsel/event/RatiogBlockPtJetPtBinnedByJetEta"+std::to_string(etaLow)+"_"+std::to_string(.5+etaLow);
     //std::cout << path << std::endl;
     m_eventPlots1D[path.c_str()]->Sumw2();
     m_eventPlots1D[path.c_str()]->Fill(RatiogBlockPtJetPtBinnedByJetEta[i][j], eventWeight);
   }
 }
  //std::cout << "There" << std::endl;

  // double ratioRange=-1.;
  // int k=0;
  // while(ratioRange<=1.5){
  //   std::string path;
  //   std::cout << "This one Fill " << ratioRange  << "  " << k << std::endl;
  //   std::cout << "Big Size: " << RatiogBlockPtJetPtBinnedByJetPtRatioBinEta.size() << std::endl;
  //   if(RatiogBlockPtJetPtBinnedByJetPtRatioBinEta.size()>0){
  //   std::cout << "Size: " << RatiogBlockPtJetPtBinnedByJetPtRatioBinEta[k].size() << "  " << RatiogBlockPtJetPtBinnedByJetPtRatioBinPhi[k].size() << std::endl;
  //   path = "postsel/event/RatiogBlockJetPt_"+std::to_string(ratioRange)+"_"+std::to_string(ratioRange+.1);
  //   ////for(unsigned int k=0 ; k<RatiogBlockPtJetPtBinnedByJetPtRatioBinEta.size() ; k++){
  //   for(unsigned int i=0 ; i<RatiogBlockPtJetPtBinnedByJetPtRatioBinEta[k].size() ; i++){
  //     m_eventPlots2D[path.c_str()]->Fill(RatiogBlockPtJetPtBinnedByJetPtRatioBinEta[k][i], RatiogBlockPtJetPtBinnedByJetPtRatioBinPhi[k][i], eventWeight);
  //   ////}
  //     std::cout << "hi" << std::endl;
  //     }
  //   }
  //     //std::cout << "Finished Fill" << std::endl;
  //   k+=1;
  //   ratioRange+=0.1;
  // }

  // //std::cout << "Finished all fill" << std::endl;
  
  // std::string path;
  // path = "postsel/event/RatiogBlockJetPt_0.8_0.9_JetPt_25_30";
  // for(unsigned int i=0 ; i<RatiogBlockPtJetPtBinnedByJetPtRatioBinEta.size() ; i++){
  //   m_eventPlots2D[path.c_str()]->Fill(RatiogBlockPtJetPtBinnedByJetPtRatioBinEta[i], RatiogBlockPtJetPtBinnedByJetPtRatioBinPhi[i], eventWeight);
  //     }
  
  if(gBlockJetMatchJetPtVector.size()>0){
  for (unsigned int i=0 ; i<gBlockJetMatchJetPtVector.size() ; i++){
    m_eventPlots2D["postsel/event/gBlockJetMatchvsJetPt"]->Fill(gBlockJetMatchJetPtVector[i], gBlockJetMatchRatioVector[i], eventWeight);
  }
  }
  
  if(m_debug) std::cout << "Postsel" << std::endl;
  m_eventPlots1D["postsel/event/METgBlocks"]->Fill(MetgBlocks, eventWeight);
  m_eventPlots1D["postsel/event/METXgBlocks"]->Fill(MetXgBlocks, eventWeight);
  m_eventPlots1D["postsel/event/METYgBlocks"]->Fill(MetYgBlocks, eventWeight);
  
  m_eventPlots1D["postsel/event/METgTowers"]->Fill(MetgTowers, eventWeight);
  m_eventPlots1D["postsel/event/METXgTowers"]->Fill(MetXgTowers, eventWeight);
  m_eventPlots1D["postsel/event/METYgTowers"]->Fill(MetYgTowers, eventWeight);
  
  m_eventPlots1D["postsel/event/METOfflineAntiKt4"]->Fill(MetAntiKt4, eventWeight);
  m_eventPlots1D["postsel/event/METXOfflineAntiKt4"]->Fill(MetXAntiKt4, eventWeight);
  m_eventPlots1D["postsel/event/METYOfflineAntiKt4"]->Fill(MetYAntiKt4, eventWeight);

  m_eventPlots1D["postsel/event/eventWeight"]->Fill(eventWeight);

  // std::vector<double> m_OfflineJets_AntiKt4Pt;
  // std::vector<double> m_OfflineJets_AntiKt4Eta;
  // std::vector<double> m_OfflineJets_AntiKt4Phi;
  // std::vector<double> m_OfflineJets_AntiKt4M;

  // m_OfflineJets_AntiKt4Pt.clear();
  // m_OfflineJets_AntiKt4Eta.clear();
  // m_OfflineJets_AntiKt4Phi.clear();
  // m_OfflineJets_AntiKt4M.clear();

  // for(unsigned int i=0 ; i<OfflineJets_AntiKt4.size() ; i++){
  //   m_OfflineJets_AntiKt4Pt.push_back(OfflineJets_AntiKt4[i].pt()/1.e3);
  //   m_OfflineJets_AntiKt4Eta.push_back(OfflineJets_AntiKt4[i].eta());
  //   m_OfflineJets_AntiKt4Phi.push_back(OfflineJets_AntiKt4[i].phi());
  //   m_OfflineJets_AntiKt4M.push_back(OfflineJets_AntiKt4[i].m()/1.e3);
  // }
  
  // m_outTrees->Branch("OfflineJets_AntiKt4Pt", &m_OfflineJets_AntiKt4Pt);
  // m_outTrees->Branch("OfflineJets_AntiKt4Eta", &m_OfflineJets_AntiKt4Eta);
  // m_outTrees->Branch("OfflineJets_AntiKt4Phi", &m_OfflineJets_AntiKt4Phi);
  // m_outTrees->Branch("OfflineJets_AntiKt4M", &m_OfflineJets_AntiKt4M);

  // std::vector<double> m_gTowerPt;
  // std::vector<double> m_gTowerEta;
  // std::vector<double> m_gTowerPhi;
  // std::vector<double> m_gTowerM;

  // m_gTowerPt.clear();
  // m_gTowerEta.clear();
  // m_gTowerPhi.clear();
  // m_gTowerM.clear();

  // for(unsigned int i=0 ; i<gTowers_central.size() ; i++){
  //   m_gTowerPt.push_back(gTowers_central[i].pt()/1.e3);
  //   m_gTowerEta.push_back(gTowers_central[i].eta());
  //   m_gTowerPhi.push_back(gTowers_central[i].phi());
  //   m_gTowerM.push_back(gTowers_central[i].m()/1.e3);
  // }
  
  // m_outTrees->Branch("gTowerPt", &m_gTowerPt);
  // m_outTrees->Branch("gTowerEta", &m_gTowerEta);
  // m_outTrees->Branch("gTowerPhi", &m_gTowerPhi);
  // m_outTrees->Branch("gTowerM", &m_gTowerM);


  // std::vector<double> m_gBlockPt;
  // std::vector<double> m_gBlockEta;
  // std::vector<double> m_gBlockPhi;
  // std::vector<double> m_gBlockM;

  // m_gBlockPt.clear();
  // m_gBlockEta.clear();
  // m_gBlockPhi.clear();
  // m_gBlockM.clear();

  // for(unsigned int i=0 ; i<gBlocks_central.size() ; i++){
  //   m_gBlockPt.push_back(gBlocks_central[i].pt()/1.e3);
  //   m_gBlockEta.push_back(gBlocks_central[i].eta());
  //   m_gBlockPhi.push_back(gBlocks_central[i].phi());
  //   m_gBlockM.push_back(gBlocks_central[i].m()/1.e3);
  // }
  
  // m_outTrees->Branch("gBlockPt", &m_gBlockPt);
  // m_outTrees->Branch("gBlockEta", &m_gBlockEta);
  // m_outTrees->Branch("gBlockPhi", &m_gBlockPhi);
  // m_outTrees->Branch("gBlockM", &m_gBlockM);
  

  
  m_eventPlots2D["postsel/event/rho_median_versus_distFrontBunchTrain"]->Fill(distFrontBunchTrain, rho/1.e3, eventWeight);
  m_eventPlots2D["postsel/event/rho_median_central_versus_distFrontBunchTrain"]->Fill(distFrontBunchTrain, rho_median_central/1.e3, eventWeight);
  m_eventPlots2D["postsel/event/rho_offline_versus_distFrontBunchTrain"]->Fill(distFrontBunchTrain, rho_offline/1.e3, eventWeight);
  m_eventPlots2D["postsel/event/rho_median_versus_rho_offline"]->Fill(rho/1.e3, rho_offline/1.e3, eventWeight);
  m_eventPlots2D["postsel/event/rho_median_central_versus_rho_offline"]->Fill(rho_median_central/1.e3, rho_offline/1.e3, eventWeight);
  m_eventPlots2D["postsel/event/rho_positive_median_versus_rho_offline"]->Fill(rho_positive_median/1.e3, rho_offline/1.e3, eventWeight);
  m_eventPlots2D["postsel/event/rho_positive_median_central_versus_rho_offline"]->Fill(rho_positive_median_central/1.e3, rho_offline/1.e3, eventWeight);
  if(m_debug) std::cout << "Postsel2" << std::endl;

  if(gTowerPtCount.size()>0){
  for(unsigned int i=0; i<gTowerPtCount.size(); i++){
    m_eventPlots2D["postsel/event/number_towers_after_cut"]->Fill(gTowerPtCountNumber[i], gTowerPtCount[i], eventWeight);
  }
  }
  if(m_debug) std::cout << "Postsel3" << std::endl;
  //if(offlineJetMatchgBlockPt.size()>0){
  //for(unsigned int i=0 ; i<offlineJetMatchgBlockPt.size(); i++){
  //  m_eventPlots1D["postsel/event/offlineJetMatchgBlockPt"]->Fill(offlineJetMatchgBlockPt[i], eventWeight);
  //}
  //}
  if(m_debug) std::cout << "Postsel4" << std::endl;
  tempVector.clear();
  for(int i=gBlockMinPtCut ; i<gBlockMaxPtCut ; i+=gBlockPtCutStep){
    tempVector.push_back(i);
  }
  for(unsigned int i=0 ; i<offlineJetMatchgBlockPtWithgBlockPtCuts.size() ; i++){
    std::string path1 = "postsel/event/offlineJetMatchgBlockPtgBlockPtCut"+std::to_string(tempVector[i]);
    for (unsigned int j=0 ; j<offlineJetMatchgBlockPtWithgBlockPtCuts[i].size() ; j++){
      m_eventPlots1D[path1]->Fill(offlineJetMatchgBlockPtWithgBlockPtCuts[i][j], eventWeight);
    }
  }

  

  
  for(unsigned int i=0 ; i<gBlocksPtMatchedJetWithPtCut.size() ; i++){
    std::string path1 = "postsel/event/gBlocksPtMatchedJetWithPtCut"+std::to_string(tempVector[i]);
    for (unsigned int j=0 ; j<gBlocksPtMatchedJetWithPtCut[i].size() ; j++){
      m_eventPlots1D[path1]->Fill(gBlocksPtMatchedJetWithPtCut[i][j], eventWeight);
    }
  }
  
  for(unsigned int i=0 ; i<OfflineJets_AntiKt4PtHist.size() ; i++){
    m_eventPlots1D["postsel/event/OfflineJet_AntiKt4Pt"]->Fill(OfflineJets_AntiKt4PtHist[i], eventWeight);
  }

  for(unsigned int i=0 ; i<gBlocksPtHist.size() ; i++){
    m_eventPlots1D["postsel/event/gBlocksPtHist"]->Fill(gBlocksPtHist[i], eventWeight);
  }

  for(unsigned int i=0 ; i<deltaRbetweenIsolatedJets.size() ; i++){
    m_eventPlots1D["postsel/event/deltaRbetweenIsolatedJets"]->Fill(deltaRbetweenIsolatedJets[i], eventWeight);
  }
  
  for(unsigned int i=0 ; i<dRgBlockMatchedOfflineJet.size() ; i++){
    m_eventPlots1D["postsel/event/dRgBlockMatchedOfflineJet"]->Fill(dRgBlockMatchedOfflineJet[i], eventWeight);
  }

  //take a minute to calculate ratio of gblock pt cuts to original jet pt
  //std::vector<int> tempVector;
  tempVector.clear();
  for(int i=gBlockMinPtCut ; i<gBlockMaxPtCut ; i+=gBlockPtCutStep){
    tempVector.push_back(i);
  }
  for(unsigned int j=0; j<tempVector.size(); j++){
    std::string path1 = "postsel/event/offlineJetMatchgBlockPtgBlockPtCut"+std::to_string(tempVector[j]);
    std::string path2 = "postsel/event/offlineJetMatchgBlockPtRatioWithCut"+std::to_string(tempVector[j]);
    for(unsigned int i=0; i<nBinsJetPt+1 ; i++){
      double binContCut = m_eventPlots1D[path1]->GetBinContent(i);
      double binContJet = m_eventPlots1D["postsel/event/OfflineJet_AntiKt4Pt"]->GetBinContent(i);
      double JetRatio = 0.;
      if(binContJet>0.)  JetRatio = binContCut/binContJet;
      else JetRatio = 0.;
      m_eventPlots1D[path2]->SetBinContent(i, JetRatio);
    }
  }
  
 for(unsigned int j=0; j<tempVector.size(); j++){
    std::string path1 = "postsel/event/gBlocksPtMatchedJetWithPtCut"+std::to_string(tempVector[j]);
    std::string path2 = "postsel/event/gBlocksPtMatchedJetRatioWithPtCut"+std::to_string(tempVector[j]);
    for(unsigned int i=0; i<nBinsJetPt+1 ; i++){
      double binContCut = m_eventPlots1D[path1]->GetBinContent(i);
      double binContJet = m_eventPlots1D["postsel/event/gBlocksPtHist"]->GetBinContent(i);
      double JetRatio = 0.;
      if(binContJet>0.)  JetRatio = binContCut/binContJet;
      else JetRatio = 0.;
      m_eventPlots1D[path2]->SetBinContent(i, JetRatio);
    }
  }      

 //m_outTrees->Fill();
 //m_outTrees->Write();
 //delete m_outTrees;



  //






  
  if(m_debug) std::cout << "Event-Level plots" << std::endl;

  if(gJets_central.size() > 0 && gJets_corrected.size() > 0 && OfflineJets_AntiKt10Trimmed.size() > 0) {
      m_2DtriggerPlots["resolution"]->Fill(OfflineJets_AntiKt10Trimmed[0].pt()/1.e3, (gJets_central[0].pt() - OfflineJets_AntiKt10Trimmed[0].pt())/OfflineJets_AntiKt10Trimmed[0].pt(), eventWeight);
      m_2DtriggerPlots["resolution_corrected"]->Fill(OfflineJets_AntiKt10Trimmed[0].pt()/1.e3, (gJets_corrected[0].pt() - OfflineJets_AntiKt10Trimmed[0].pt())/OfflineJets_AntiKt10Trimmed[0].pt(), eventWeight);
  }

  // build all turnon curves
  if(OfflineJets_AntiKt4.size() > 0){
    // only use leading
    const auto& jet = OfflineJets_AntiKt4.at(0);
  
    m_triggerPlots["turnon/tower/all/denominator"]->Fill(jet.pt()/1.e3, eventWeight);

    if(gTowers_central.size() > 0){
      for(int threshold = m_singleTowerThreshold_start; threshold < m_singleTowerThreshold_stop; threshold+=m_singleTowerThreshold_step){
        std::string path = "turnon/tower/all/L1_GFEX_T"+std::to_string(threshold)+"/numerator";
        if(gTowers_central[0].pt()/1.e3 >= threshold){
          m_triggerPlots[path]->Fill(jet.pt()/1.e3, eventWeight);
        }
      }
    }
  
    m_triggerPlots["turnon/block/all/denominator"]->Fill(jet.pt()/1.e3, eventWeight);

    if(gBlocks_central.size() > 0){      
      for(int threshold = m_singleBlockThreshold_start; threshold < m_singleBlockThreshold_stop; threshold+=m_singleBlockThreshold_step){
        if(gBlocks_central[0].pt()/1.e3 >= threshold){
          m_triggerPlots["turnon/block/all/L1_GFEX_B"+std::to_string(threshold)+"/numerator"]->Fill(jet.pt()/1.e3, eventWeight);
        }
      }
    }
  }
  
  if(m_debug) std::cout << "blocks and towers turn-ons" << std::endl;




    //Create vectors to use for ratio calculation

    //std::vector<int> gTowerPtCount;
    //std::vector<int> gTowerPtCountNumber;
    if(gTowers_central.size()>0){
      for(unsigned int gTpT=0; gTpT<20; gTpT++){
        gTowerPtCountNumber.push_back(gTpT);
        gTowerPtCut = gTpT;
        int numTowers=0;
        for(unsigned int gTind=0; gTind<gTowers_central.size(); gTind++){
          if(gTowers_central[gTind].pt()/1.e3 >= double(gTpT)){
            numTowers++;
          }
        }
        gTowerPtCounts=double(numTowers);
        gTowerPtCount.push_back(numTowers);
      }
    }


    // std::vector<TLorentzVector> allJets;
    // std::vector<TLorentzVector> jetVec;

    // for(int i; i<OfflineJets_AntiKt4.size(); i++){
    //   TLorentzVector jv1(0., 0., 0., 0.);
    //   jv1.SetPtEtaPhiM(OfflineJets_AntiKt4[i].pt()/1.e3, OfflineJets_AntiKt4[i].eta(), OfflineJets_AntiKt4[i].phi(), OfflineJets_AntiKt4[i].m()/1.e3);
    //     //std::cout << "Jet pt " << i << "    " << OfflineJets_AntiKt4[i].pt()/1.e3 << std::endl;
    //   jetVec.push_back(jv1);
        
    // }

    

    
    //for(unsigned int i=0; i<gTowerPtCount.size(); i++){
      //std::cout << "gTower Pt:  " << gTowers_central[i].pt()/1.e3 << ", gTower Pt Cut:  " << gTowerPtCountNumber[i] << ", gTower Number:  " << gTowerPtCount[i] << std::endl;
    //}

    
    //public: double gBlockJetRatio

    gTowerPtCount.clear();
    gTowerPtCountNumber.clear();
    gBlockJetMatchRatioVector.clear();
    gBlockJetMatchJetPtVector.clear();
    gBlockJetRatioJetPtVector.clear();
      

    gBlockJetRatioVector.clear();
    DeltaRgBlockJetVector.clear();
    gBlockJetRatioJetPtVector.clear();
    jetVec.clear();
    gblockVec.clear();
    gblockIndices.clear();
    gblockIndices.push_back(-1.); //give a dummy index for something to scan over at first
    
    for(unsigned int i=0; i<OfflineJets_AntiKt4.size(); i++){
        jv1.SetPtEtaPhiM(0., 0., 0., 0.);
        jv1.SetPtEtaPhiM(OfflineJets_AntiKt4[i].pt()/1.e3, OfflineJets_AntiKt4[i].eta(), OfflineJets_AntiKt4[i].phi(), OfflineJets_AntiKt4[i].m()/1.e3);
        //std::cout << "Jet pt " << i << "    " << OfflineJets_AntiKt4[i].pt()/1.e3 << std::endl;
        jetVec.push_back(jv1);
      }

      double matchJetgBlock=0.;
      double mismatchJetgBlock=0.;
      for(unsigned int i=0; i<gBlocks_central.size(); i++){
        gv1.SetPtEtaPhiM(0., 0., 0., 0.);
        gv1.SetPtEtaPhiM(gBlocks_central[i].pt()/1.e3, gBlocks_central[i].eta(), gBlocks_central[i].phi(), gBlocks_central[i].m()/1.e3);
        //std::cout << "gBlock number: " << i << "      " << gBlocks_central[i].pt()/1.e3 << std::endl;
        gblockVec.push_back(gv1);
      }

      //std::cout << "Delta R test: " << gblockVec[0].DeltaR(jetVec[0]) << std::endl;
      double newDeltaR=0.0;
      //loop over all jets and gblocks to match jets to gBlocks (central)
      for(unsigned int j=0; j<OfflineJets_AntiKt4.size(); j++){
        double minDeltaR = 0.0;
        int gblockInd = 0;
        if(OfflineJets_AntiKt4[j].pt()>20 && std::fabs(OfflineJets_AntiKt4[j].eta())<2.5){ //Set Jet Pt here
          minDeltaR = jetVec[j].DeltaR(gblockVec[0]);
          for(unsigned int i=1; i<2*OfflineJets_AntiKt4.size(); i++){ //loop over twice as many gBlocks as jets so you don't have to go over all 768 gBlocks - gBlocks are pT ordered so should be ok
            newDeltaR = 0.0;
            newDeltaR=jetVec[j].DeltaR(gblockVec[i]);
            if(newDeltaR<minDeltaR){ minDeltaR=newDeltaR;}
            
            //if((std::find(gblockIndices.begin(), gblockIndices.end(), i) == gblockIndices.end()) && newDeltaR<minDeltaR){
            //minDeltaR=newDeltaR; //replace the old min with new one
            //gblockInd=i; //keep track of the index of the gBlock
            //}
          }
        }
          //else std::cout << "Not less than" <<std::endl;
        
      
        //after looping over all gBlocks, add index of closest to list so it can't be used again and calculaate ratio
        //std::cout << "Jet number: " << j << " of total number: " << OfflineJets_AntiKt4.size() << std::endl;
        gblockIndices.push_back(gblockInd);
        DeltaRgBlockJet = newDeltaR;
        gBlockJetRatio=0.0;
        gBlockJetRatio = gBlocks_central[gblockInd].pt()/OfflineJets_AntiKt4[j].pt();

        gBlockJetRatioVector.push_back(gBlockJetRatio);
        DeltaRgBlockJetVector.push_back(DeltaRgBlockJet);
        gBlockJetRatioJetPtVector.push_back(OfflineJets_AntiKt4[j].pt());  //This is a vector of jet pts
      }

      dRgBlockMatchedOfflineJet.clear();
      offlineJetMatchgBlockPt.clear();
      maxDistJetgBlock=0.1*std::sqrt(2);
      std::vector<int> gBlockIndices;
      std::vector<double> gBlocksPtWithOneCut;
      gBlocksPtWithOneCut.clear();
      gBlockIndices.clear();
      offlineJetMatchgBlockPtWithgBlockPtCuts.clear();
      gBlockPtCuts.clear();
      gBlocksPtMatchedJetWithPtCut.clear();
      gBlocksPtHist.clear();
      //std::vector<int> gBlockPtCutsTest;
      //gBlockPtCutsTest.clear();

      for(int gblockptcut=gBlockMinPtCut ; gblockptcut<gBlockMaxPtCut ; gblockptcut+=gBlockPtCutStep){//gBlockMinPtCut ; gblockptcut<gBlockMaxPtCut; gblockptcut+=gBlockPtCutStep){
        gBlockPtCuts.push_back(gblockptcut);
        
        offlineJetMatchgBlockPt.clear();
        if(gBlocks_central.size()>0){  
          for(unsigned int i=0; i<OfflineJets_AntiKt4.size(); i++){
            double ratioOfflineJetPtToMatchingJetPt=0.;
            minDR=99.;
            double offlineJetPtMatching=0.;
            int gBlockIndex=-99;
       
            if(std::fabs(OfflineJets_AntiKt4[i].eta())<2.5){
              for(unsigned int j=0; j<gBlocks_central.size(); j++){
                if(std::find(gblockIndices.begin(), gblockIndices.end(), j) == gblockIndices.end() && (gBlocks_central[j].pt()/1.e3)>gblockptcut){

                  

                  double dphi=0.;
                  double deta=0.;
                  double dR=0.;
                  dphi = std::fabs(std::fabs(std::fabs(OfflineJets_AntiKt4[i].phi()-gBlocks_central[j].phi())-pi)-pi);
                  deta = OfflineJets_AntiKt4[i].eta()-gBlocks_central[j].eta();
                  dR = std::sqrt((deta*deta)+(dphi*dphi));
                  //std::cout << "DR between gBlocks and jets:  " << dR << std::endl;
                  if(dR<minDR && dphi<.1 && deta<.1){
                    minDR=dR;
                    gBlockIndex=j;
                  }
                  }
              }
              // if(minDR==99.){
              //   std::cout << "No Match:  jet pt: "  << OfflineJets_AntiKt4[i].pt() << "  Eta:  " << OfflineJets_AntiKt4[i].eta() << "  Phi:  " << OfflineJets_AntiKt4[i].phi()  << std::endl;
              // }
              if(minDR<maxDistJetgBlock){//minDR<10.){ //Just has to be less than 99.
                //std::cout << "PASSED cut on pt: " << OfflineJets_AntiKt4[i].pt()/1.e3 << std::endl;
                gBlockIndices.push_back(gBlockIndex);
                offlineJetMatchgBlockPt.push_back(OfflineJets_AntiKt4[i].pt()/1.e3);
                dRgBlockMatchedOfflineJet.push_back(minDR);
                gBlocksPtWithOneCut.push_back(gBlocks_central[i].pt()/1.e3);
              }
              }
            }
          }
        //std::cout << offlineJetMatchgBlockPt.size() << std::endl;
        //for(unsigned int k=0 ; k<offlineJetMatchgBlockPt.size() << k++){
        //std::cout << "vector from cut " << gblockptcut << "  "  << offlineJetMatchgBlockPt[k] << std::endl;
        //}
        offlineJetMatchgBlockPtWithgBlockPtCuts.push_back(offlineJetMatchgBlockPt);
        gBlocksPtMatchedJetWithPtCut.push_back(gBlocksPtWithOneCut);
      }

      OfflineJets_AntiKt4PtHist.clear();
      for(unsigned int i=0; i<OfflineJets_AntiKt4.size() ; i++){
        OfflineJets_AntiKt4PtHist.push_back(OfflineJets_AntiKt4[i].pt()/1.e3);
      }
      
      for(unsigned int i=0 ; i<gBlocks_central.size() ; i++){
        gBlocksPtHist.push_back(gBlocks_central[i].pt()/1.e3);
      }
          

      // for(unsigned int i=0 ; i<offlineJetMatchgBlockPtWithgBlockPtCuts.size() ; i++){
      //   for(unsigned int j=0 ; j<offlineJetMatchgBlockPtWithgBlockPtCuts[i].size() ; j++){
      //     std::cout << "Items in vector:  " << i << "  " << j << "  " << offlineJetMatchgBlockPtWithgBlockPtCuts[i][j] << std::endl;
      //   }
      // }
      //gBlockPtCutsTest.clear();
      //std::string path = "/event/offlineJetMatchgBlockPtgBlockPtCut"+std::to_string((int)gBlockPtCuts[0]);
      //std::cout << "Number of Jets:  " << OfflineJets_AntiKt4.size() << "  and number of delta Rs:  " << DeltaRgBlockJetVector.size() << " jetvec: " << jetVec.size() << "  gvec  " << gblockVec.size() << std::endl;
      
    
        // if(DeltaRgBlockJet<=1.) {
        //   gBlockJetMatchRatioVector.push_back(gBlockJetRatio);
        //   gBlockJetMatchJetPtVector.push_back(OfflineJets_AntiKt4[j].pt());
        //   gBlockMatchJetRatio = gBlockJetRatio; // matchJetgBlock += 1.;
        //   jetMatchPt = OfflineJets_AntiKt4[j].pt();
        // }
        
        //else mismatchJetgBlock+=1.;
        //std::cout << "INDEX:    " << gblockInd << ",   DeltaR:  " << minDeltaR  << "   Ratio:  " << gBlockJetRatio << std::endl;
    
      //gBlockJetRatio = matchJetgBlock/(matchJetgBlock+mismatchJetgBlock);
   
      for(unsigned int i=0; i<100 ; i++){
        double numberMatched=0.;
        double numberMisMatched=0.;
        for(unsigned int j=0; j<DeltaRgBlockJetVector.size(); j++){
         
          if(DeltaRgBlockJetVector[j]<1. && (gBlockJetRatioJetPtVector[j]/1.e3)>i && (gBlockJetRatioJetPtVector[j]/1.e3)<(i+1)){
            numberMatched+=1;
            //std::cout << "Jet Pt and delta R:  " << gBlockJetRatioJetPtVector[j]/1.e3 << "  " << DeltaRgBlockJetVector[j] << std::endl;
            //std::cout << "Jet Pt:  " << gBlockJetRatioJetPtVector[j]/1.e3 << std::endl;
            //std::cout << "Delta R: " << DeltaRgBlockJetVector[j] << std::endl;
          }
          if(DeltaRgBlockJetVector[j]>1. && (gBlockJetRatioJetPtVector[j]/1.e3)>i && (gBlockJetRatioJetPtVector[j]/1.e3)<(i+1)){
            numberMisMatched+=1;
            //std::cout << "Jet Pt and delta R:  " << gBlockJetRatioJetPtVector[j]/1.e3 << "  " << DeltaRgBlockJetVector[j] << std::endl;

          }
        }
        
        if(numberMatched+numberMisMatched!=0){
          
          //std::cout << "counts: " << numberMatched << "  " << numberMisMatched <<std::endl;
          //std::cout << "Jet Pt and ratio:  " << i << "  " << (numberMatched/(numberMatched+numberMisMatched)) << std::endl;
          double MatchingRatio=0.;
          MatchingRatio=numberMatched/(numberMatched+numberMisMatched);
          if(MatchingRatio>1.){std::cout << "Ratio greater than 1:  " << MatchingRatio << std::endl;}            
          gBlockJetMatchJetPtVector.push_back(i);
          gBlockJetMatchRatioVector.push_back(MatchingRatio);
        }
      }

      
      MetgBlocks=0.;
      MetXgBlocks=0.;
      MetYgBlocks=0.;
      double gBlockPt=0.;
      double gBlockPx=0.;
      double gBlockPy=0.;
      for(unsigned int i=0 ; i<gBlocks_central.size() ; i++){

        //std::cout << "gBlock Pt:  " << gBlocks_central[i].pt() << std::endl;
        
        gBlockPt+=gBlocks_central[i].pt();
        gBlockPx+=gBlocks_central[i].pt()*std::cos(gBlocks_central[i].phi());
        gBlockPy+=gBlocks_central[i].pt()*std::sin(gBlocks_central[i].phi());
      } 
      //MetgBlocks = gBlockPt/(9*1.e3);
      MetXgBlocks = gBlockPx/(9*1.e3); //9 gTowers per block so divide by 9
      MetYgBlocks = gBlockPy/(9*1.e3);
      MetgBlocks = std::sqrt(MetXgBlocks*MetXgBlocks + MetYgBlocks*MetYgBlocks);

      MetgTowers=0.;
      MetXgTowers=0.;
      MetYgTowers=0.;
      double gTowersPt=0.;
      double gTowersPx=0.;
      double gTowersPy=0.;
      for(unsigned int i=0 ; i<gTowers_central.size() ; i++){
        gTowersPt+=gTowers_central[i].pt();
        gTowersPx+=gTowers_central[i].pt()*std::cos(gTowers_central[i].phi());
        gTowersPy+=gTowers_central[i].pt()*std::sin(gTowers_central[i].phi());
      }
      MetgTowers = gTowersPt/1.e3;
      MetXgTowers = gTowersPx/1.e3;
      MetYgTowers = gTowersPy/1.e3;

      MetAntiKt4=0.;
      MetXAntiKt4=0.;
      MetYAntiKt4=0.;
      double AntiKt4Pt=0.;
      double AntiKt4Px=0.;
      double AntiKt4Py=0.;
      for(unsigned int i=0 ; i<OfflineJets_AntiKt4.size() ; i++){
        if(std::fabs(OfflineJets_AntiKt4[i].eta())<2.5){
          AntiKt4Pt+=OfflineJets_AntiKt4[i].pt();
          AntiKt4Px+=OfflineJets_AntiKt4[i].pt()*std::cos(OfflineJets_AntiKt4[i].Phi());
          AntiKt4Py+=OfflineJets_AntiKt4[i].pt()*std::sin(OfflineJets_AntiKt4[i].Phi());
        
        }
      }
      MetAntiKt4 = AntiKt4Pt/1.e3;
      MetXAntiKt4 = AntiKt4Px/1.e3;
      MetYAntiKt4 = AntiKt4Py/1.e3;
      //std::cout << "gBlockMet: " << MetgBlocks << "  gTowerMet: " << MetgTowers << "  JetMet: " << MetAntiKt4 << std::endl;

      std::vector<double> tempRatioEtaVector;
      std::vector<double> tempRatioPhiVector;
      tempRatioEtaVector.clear();
      tempRatioPhiVector.clear();


      // Now to make the Ratio of gblock pt/offline jet pt binned by offline jet pt

      //Make vectors of vectors for bins
      RatiogBlockPtJetPtBinnedByJetPt.clear();
      RatiogBlockPtJetPtBinnedByJetPtEta.clear();
      RatiogBlockPtJetPtBinnedByJetPtPhi.clear();
      RatiogBlockPtJetPtBinnedByJetPtRatioBinEta.clear();
      RatiogBlockPtJetPtBinnedByJetPtRatioBinPhi.clear();
      RatiogBlockPtJetPtBinnedByJetEta.clear();

      for(unsigned int l=0 ; l<ptMaxBinDividedBy5 ; l++){
        std::vector<double> ratioVector;
        std::vector<double> ratioVectorEta;
        std::vector<double> ratioVectorPhi;        
        ratioVector.clear();
        ratioVectorEta.clear();
        ratioVectorPhi.clear();
        RatiogBlockPtJetPtBinnedByJetPt.push_back(ratioVector);
        RatiogBlockPtJetPtBinnedByJetPtEta.push_back(ratioVectorEta);
        RatiogBlockPtJetPtBinnedByJetPtPhi.push_back(ratioVectorPhi);        
      }

      //std::cout << "Size before: " << RatiogBlockPtJetPtBinnedByJetEta.size() << std::endl;
      for(unsigned int l=0 ; l<51 ; l=l+5){
        std::vector<double> ratioVectorBinnedEta;
        ratioVectorBinnedEta.clear();
        RatiogBlockPtJetPtBinnedByJetEta.push_back(ratioVectorBinnedEta);
      }
      //std::cout << "Size after: " << RatiogBlockPtJetPtBinnedByJetEta.size() << std::endl;
      
      std::vector<double> tempVectorK;
      std::vector<double> tempVectorL;
      if(OfflineJets_AntiKt4.size() > 0 && gBlocks_central.size()>0){
      double ratioRange=-1.;
      //int k=0;
      while(ratioRange<=1.5){  
        tempVectorK.clear();
        tempVectorL.clear();
        RatiogBlockPtJetPtBinnedByJetPtRatioBinEta.push_back(tempVectorK);
        RatiogBlockPtJetPtBinnedByJetPtRatioBinPhi.push_back(tempVectorL);
        ratioRange+=0.1;
      }
      }

      

      //COMMENT: first do matching between gblock and offline jet:
      if(OfflineJets_AntiKt4.size() > 0 && gBlocks_central.size()>0){
        for(unsigned int i=0; i<OfflineJets_AntiKt4.size(); i++){
            minDR=99.;
            int gBlockIndex=-99;
            if(std::fabs(OfflineJets_AntiKt4[i].eta())<2.5){
              for(unsigned int j=0; j<gBlocks_central.size(); j++){
                if(std::find(gblockIndices.begin(), gblockIndices.end(), j) == gblockIndices.end()){
                  double dphi=0.;
                  double deta=0.;
                  double dR=0.;
                  dphi = std::fabs(std::fabs(std::fabs(OfflineJets_AntiKt4[i].phi()-gBlocks_central[j].phi())-pi)-pi);
                  deta = OfflineJets_AntiKt4[i].eta()-gBlocks_central[j].eta();
                  dR = std::sqrt((deta*deta)+(dphi*dphi));
                  //std::cout << "DR between gBlocks and jets:  " << dR << std::endl;
                  if(dR<minDR && dphi<.1 && deta<.1){
                    minDR=dR;
                    gBlockIndex=j;
                  }
                }
              }
              //COMMENT: Now calculate gblock/jet pt ratio in bins of 5 gev
              double ptRangeLow = 0.;
              if(gBlockIndex>=0 && minDR<99.){
              for(unsigned int l=0 ; l<ptMaxBinDividedBy5 ; l++){
                //std::cout << "3" << std::endl;
                ptRangeLow = 0.; //This just resets ptRangeLow just in case
                ptRangeLow = 5*l; //This is the actual ptRangeLow
                if(OfflineJets_AntiKt4[i].pt()/1.e3 > ptRangeLow && OfflineJets_AntiKt4[i].pt()/1.e3 < (ptRangeLow+5)){
                double ratiogBlockPtJetPt = -99.;
                double ratiogBlockPtJetPtEta = -99.;
                double ratiogBlockPtJetPtPhi = -99.;
                double ptRangeLow = 0.;
                if(OfflineJets_AntiKt4[i].pt() != 0.){ //COMMENT: Just to protect from n/0
                  ratiogBlockPtJetPt =  gBlocks_central[gBlockIndex].pt()/OfflineJets_AntiKt4[i].pt();
                  ratiogBlockPtJetPtEta = OfflineJets_AntiKt4[i].eta();
                  ratiogBlockPtJetPtPhi = OfflineJets_AntiKt4[i].phi();
                }
                else ratiogBlockPtJetPt = -99.;
               

                //COMMENT:  Here loop over the bins and fill the 2d eta vs phi in the correct ratio bin
                  double ratioRange=-1.;  //This won't work, need to fill individual vectors
                  int k=0;
                  while(ratioRange<=1.5){
                    //std::cout << "This one " << ratioRange << std::endl;
                      if(ratiogBlockPtJetPt>ratioRange && ratiogBlockPtJetPt<ratioRange+.1){
                        std::string path;
                        path = "postsel/event/RatiogBlockJetPt_"+std::to_string(ratioRange)+"_"+std::to_string(ratioRange+.1);
                        m_eventPlots2D[path.c_str()]->Fill(OfflineJets_AntiKt4[i].eta(), OfflineJets_AntiKt4[i].phi(), eventWeight);
                       RatiogBlockPtJetPtBinnedByJetPtRatioBinEta[k].push_back(OfflineJets_AntiKt4[i].eta());
                       RatiogBlockPtJetPtBinnedByJetPtRatioBinPhi[k].push_back(OfflineJets_AntiKt4[i].phi());
                      }
                     ratioRange+=0.1;
                     k+=1;
                     
                  }


                  
                  //COMMENT: push back values into vectors
                RatiogBlockPtJetPtBinnedByJetPt[l].push_back(ratiogBlockPtJetPt);
                RatiogBlockPtJetPtBinnedByJetPtEta[l].push_back(ratiogBlockPtJetPtEta);
                RatiogBlockPtJetPtBinnedByJetPtPhi[l].push_back(ratiogBlockPtJetPtPhi);
                ratiogBlockPtJetPt=-99.;
                ratiogBlockPtJetPtEta=-99.;
                ratiogBlockPtJetPtPhi=-99.;

                }
              }

              //Now bin by jet eta instead of pt
              double etaRangeLow=-99.; //resets etarangelow

              for(unsigned int l=0 ; l<51 ; l=l+5){
                etaRangeLow = (l/10)-2.5; // make it run from -2.5-2.4
                //std::cout << l << std::endl;
                if(OfflineJets_AntiKt4[i].eta() > etaRangeLow && OfflineJets_AntiKt4[i].eta() < (etaRangeLow+0.5)){
                  double ratiogBlockPtJetEta = -99.;
                  if(OfflineJets_AntiKt4[i].pt() != 0.){ //COMMENT: Just to protect from n/0
                    ratiogBlockPtJetEta =  gBlocks_central[gBlockIndex].pt()/OfflineJets_AntiKt4[i].pt();
                  }
                  else ratiogBlockPtJetEta = -99.;
                

                  
                  //COMMENT: push back values into vectors
                  //std::cout << ratiogBlockPtJetEta << "  " << l/5 << std::endl;
                RatiogBlockPtJetPtBinnedByJetEta[l/5].push_back(ratiogBlockPtJetEta);
                ratiogBlockPtJetEta=-99.;
                //std::cout << "Filled vector " << l << std::endl;
                }
                
              }
              
              }
              
            }
            
        }

      }


      // for(unsigned int i=0 ; i<gBlocks_central.size() ; i++){
      //   if(std::fabs(gBlocks_central[i].eta()-gBlocks_central[642].eta())<=0.2 && std::fabs(std::fabs(std::fabs(gBlocks_central[i].phi()-gBlocks_central[642].phi())-pi)-pi)<=0.2){
      //       if(evtNum>120 && evtNum<141){
      //         std::cout << "Event Number: " << evtNum << "  gBlock(" << i << ") Pt: " << gBlocks_central[i].pt()/1.e3 << std::endl;
      //       }
      //   }
      // }
  if(OfflineJets_AntiKt10Trimmed.size() > 0){
    // only use leading
    const auto& jet = OfflineJets_AntiKt10Trimmed.at(0);
    int num_subjets(jet.numSubjets());
    // for right now, if it has no subjets, it now has one.
    if(num_subjets == 0) num_subjets = 1;

    // hold a string for the subjet path we fill in
    std::string subjet_path("turnon/jet");
    if(num_subjets>=3)      subjet_path+= "/3subjet"; // inclusive offline subjet selection (>=3)
    else if(num_subjets>0 && num_subjets<3) subjet_path+= "/"+std::to_string(num_subjets)+"subjet"; // exclusive offline subjet selection

    // inclusive denominators
    m_triggerPlots["turnon/jet/all/denominator"]->Fill(jet.pt()/1.e3, eventWeight);
    m_triggerPlots[subjet_path+"/denominator"]->Fill(jet.pt()/1.e3, eventWeight);

    // fill in Run2 trigger
    if(Run2_L1Jets_central.size() > 0){
      if(Run2_L1Jets_central[0].pt()/1.e3 >= 100.0){
        m_triggerPlots["turnon/jet/all/L1_J100/numerator"]->Fill(jet.pt()/1.e3, eventWeight);
        m_triggerPlots[subjet_path+"/L1_J100/numerator"]->Fill(jet.pt()/1.e3, eventWeight);
      }
    }
  
    if(gJets_central.size() > 0){
      for(int threshold = m_singleJetThreshold_start; threshold < m_singleJetThreshold_stop; threshold+=m_singleJetThreshold_step){
        if(gJets_central[0].pt()/1.e3 >= threshold){
          m_triggerPlots["turnon/jet/all/L1_GFEX_J"+std::to_string(threshold)+"/numerator"]->Fill(jet.pt()/1.e3, eventWeight);
          m_triggerPlots[subjet_path+"/L1_GFEX_J"+std::to_string(threshold)+"/numerator"]->Fill(jet.pt()/1.e3, eventWeight);
        }
      }
    }

    if(gJets_corrected.size() > 0){
      for(int threshold = m_singleJetThreshold_start; threshold < m_singleJetThreshold_stop; threshold+=m_singleJetThreshold_step){
        if(gJets_corrected[0].pt()/1.e3 >= threshold){
          m_triggerPlots["turnon/jet/all/L1_GFEX_J"+std::to_string(threshold)+"/numerator_pileupCorrection"]->Fill(jet.pt()/1.e3, eventWeight);
          m_triggerPlots[subjet_path+"/L1_GFEX_J"+std::to_string(threshold)+"/numerator_pileupCorrection"]->Fill(jet.pt()/1.e3, eventWeight);
        }
      }
    }
  }

  // dR match everything to figure out resolution
  for(const auto& truthJet: TruthJets_AntiKt4){
    gFEX::Jet closestJet;
    float closestApproach = 999.0;
    for(const auto& offlineJet: OfflineJets_AntiKt4){
      if(truthJet.deltaR(offlineJet) < closestApproach){
        closestApproach = truthJet.deltaR(offlineJet);
        closestJet = offlineJet;
      }
    }
    m_resolution->Fill(truthJet.pt()/1.e3, (closestJet.pt() - truthJet.pt())/truthJet.pt(), eventWeight);
  }

  ADD_CUTFLOW("final");

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode gFEX::Analysis :: postExecute () { return EL::StatusCode::SUCCESS; }
EL::StatusCode gFEX::Analysis :: finalize () {

  Info("finalize()", "Recording the cutflow");
  for(const auto &cutflow_name: m_cutflow_names){
    TH1F* hist = new TH1F(("cutflow/"+cutflow_name).c_str(), cutflow_name.c_str(), 2, 1, 3);
    auto cutflow = m_cutflows.at(cutflow_name);
    hist->SetBinContent(1, cutflow.first);
    hist->SetBinContent(2, cutflow.second);
    wk()->addOutput(hist);
    Info("finalize()", "\t%20s\t(%10.2f, %10.2f)", cutflow_name.c_str(), cutflow.first, cutflow.second);
  }

  // clear it all
  m_cutflows.clear();
  m_cutflow_names.clear();

  //m_outTrees->Fill();
  //m_outTrees->Write();
  //delete m_outTrees;
  
  return EL::StatusCode::SUCCESS;
}
EL::StatusCode gFEX::Analysis :: histFinalize () { return EL::StatusCode::SUCCESS;}
