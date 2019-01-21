#ifndef KinematicPlots_ObjectHists_H
#define KinematicPlots_ObjectHists_H

#include "xAODAnaHelpers/HistogramManager.h"
#include "xAODAnaHelpers/HelperClasses.h"

#include <KinematicPlots/Objects.h>

class ObjectHists : public HistogramManager
{
  public:

    ObjectHists(std::string name, std::string detailStr, std::string prefix="", std::string title="");
    virtual ~ObjectHists() ;

    bool m_debug;
    virtual StatusCode initialize();
    StatusCode execute( const std::vector<gFEX::Jet>& jets, float eventWeight );
    StatusCode execute( const std::vector<gFEX::Tower>& towers, float eventWeight );
    StatusCode execute( const std::vector<gFEX::Block>& blocks, float eventWeight );
    StatusCode execute( const std::vector<gFEX::Object>& objects, float eventWeight );
    StatusCode execute( const gFEX::Object& object, float eventWeight );
    using HistogramManager::book; // make other overloaded version of book() to show up in subclass
    using HistogramManager::execute; // overload

  protected:

    // holds bools that control which histograms are filled
    HelperClasses::IParticleInfoSwitch* m_infoSwitch;

  private:
    std::string m_prefix;
    std::string m_title;

    //basic
    TH1F* m_Pt;                  //!
    TH1F* m_Pt_s;                //!
    TH1F* m_Eta;                 //!
    TH1F* m_Phi;                 //!
    TH1F* m_M;                   //!
    TH1F* m_E;                   //!
    TH1F* m_area;                //!
    TH1F* m_rho;                 //!

    // leading 2 objects' deltaPhi and dEt
    TH1F* m_deltaPhi;            //!
    TH2F* m_dPhi_v_dEt;          //!

    TH2F*  m_et_v_eta;           //!
    TH2F*  m_pT_v_eta;           //!
    TH2F*  m_pt_v_et;            //!
    TH2F*  m_area_v_eta;         //!
    TH2F*  m_rho_v_eta;          //!

    //NLeadingParticles
    std::vector< TH1F* > m_NPt;        //!
    std::vector< TH1F* > m_NPt_s;      //!
    std::vector< TH1F* > m_NEta;       //!
    std::vector< TH1F* > m_NPhi;       //!
    std::vector< TH1F* > m_NM;         //!
    std::vector< TH1F* > m_NE;         //!
    std::vector< TH1F* > m_NArea;      //!
    std::vector< TH1F* > m_Nrho;       //!

    std::vector< TH2F* > m_Net_v_eta;  //!
    std::vector< TH2F* > m_NpT_v_eta;  //!
    std::vector< TH2F* > m_Npt_v_et;   //!
    std::vector< TH2F* > m_Narea_v_eta;//!
    std::vector< TH2F* > m_Nrho_v_eta; //!

};

#endif
