#include <KinematicPlots/ObjectHists.h>
#include <sstream>

#include "xAODAnaHelpers/tools/ReturnCheck.h"
#include "TMath.h"

ObjectHists :: ObjectHists (std::string name, std::string detailStr, std::string prefix, std::string title) :
  HistogramManager(name, detailStr),
  m_infoSwitch(new HelperClasses::IParticleInfoSwitch(m_detailStr)),
  m_prefix(prefix),m_title(title)
{
  m_debug = false;
}

ObjectHists :: ~ObjectHists () {
  if(m_infoSwitch) delete m_infoSwitch;
}

StatusCode ObjectHists::initialize() {

  // These plots are always made
  m_Pt          = book(m_name, m_prefix+"Pt",       m_title+" p_{T} [GeV]", 128, -200., 3000.);
  m_Pt_s        = book(m_name, m_prefix+"Pt_s",     m_title+" p_{T} [GeV]", 300., -100., 200.);
  m_Eta         = book(m_name, m_prefix+"Eta",      m_title+" #eta",        99, -4.95, 4.95 );
  m_Phi         = book(m_name, m_prefix+"Phi",      m_title+" Phi",         64, -3.2, 3.2 );
  m_M           = book(m_name, m_prefix+"Mass",     m_title+" Mass [GeV]",  40, 0., 1000.);
  m_E           = book(m_name, m_prefix+"Energy",   m_title+" Energy [GeV]",128, -200., 3000.);
  m_area        = book(m_name, m_prefix+"Area",     m_title+" Area [radians]", 350, 0.0, 7.0);
  m_rho         = book(m_name, m_prefix+"Rho",      m_title+" Rho [GeV/radians]", 300, -300.0, 300.0);

  m_et_v_eta    = book(m_name, m_prefix+"et_v_eta",     m_title+" #eta", 99, -4.95, 4.95,           m_title+" E_{T} [GeV]", 100, 0.0, 1000.);
  m_pT_v_eta    = book(m_name, m_prefix+"pt_v_eta",     m_title+" #eta", 99, -4.95, 4.95,           m_title+" p_{T} [GeV]", 100, -1000., 1000.);
  m_pt_v_et     = book(m_name, m_prefix+"pt_v_et",      m_title+" E_{T} [GeV]", 1000., 0.0, 1000.,  m_title+" p_{T} [GeV]", 100., -1000., 1000.);
  m_area_v_eta  = book(m_name, m_prefix+"area_v_eta",   m_title+" #eta", 99, -4.95, 4.95,           m_title+" area [radians]", 350,0.0,7.0);
  m_rho_v_eta   = book(m_name, m_prefix+"rho_v_eta",    m_title+" #eta", 99, -4.95, 4.95,           m_title+" #rho [Gev/radians]", 300, -300, 300);

  m_deltaPhi    = book(m_name, m_prefix+"deltaPhi",     m_title+" #Delta#phi", 80, -4.0, 4.0);
  m_dPhi_v_dEt  = book(m_name, m_prefix+"dPhi_v_dEt",   m_title+" #Delta E_{T} [GeV]", 300, 0.0, 300.0,   m_title+" #Delta#phi", 80, -4.0, 4.0);

  if(m_debug) Info("ObjectHists::initialize()", m_name.c_str());

  // N leading jets
  if( m_infoSwitch->m_numLeading > 0 ){
    std::stringstream pNum;
    std::stringstream pTitle;
    for(int iObject=0; iObject < m_infoSwitch->m_numLeading; ++iObject){
      pNum << iObject;

      pTitle << iObject+1;
      switch(iObject)
	{
	case 0:
	  pTitle << "^{st}";
	  break;
	case 1:
	  pTitle << "^{nd}";
	  break;
	case 2:
	  pTitle << "^{rd}";
	  break;
	default:
	  pTitle << "^{th}";
	  break;
	}

      m_NPt.push_back(       book(m_name, (m_prefix+"Pt_"+pNum.str()),      pTitle.str()+" "+m_title+" p_{T} [GeV]" ,   128,   -200.,       3000.) );
      m_NPt_s.push_back(     book(m_name, (m_prefix+"Pt_s_"+pNum.str()),    pTitle.str()+" "+m_title+" p_{T} [GeV]" ,   300,   -100.,       200. ) );
      m_NEta.push_back(      book(m_name, (m_prefix+"Eta_"+pNum.str()),     pTitle.str()+" "+m_title+" #eta"        ,    99,   -4.95,       4.95 ) );
      m_NPhi.push_back(      book(m_name, (m_prefix+"Phi_"+pNum.str()),     pTitle.str()+" "+m_title+" Phi"         ,    64,   -3.20,        3.2 ) );
      m_NM.push_back(        book(m_name, (m_prefix+"Mass_"+pNum.str()),    pTitle.str()+" "+m_title+" Mass [GeV]"  ,    40,      0.,       1000.) );
      m_NE.push_back(        book(m_name, (m_prefix+"Energy_"+pNum.str()),  pTitle.str()+" "+m_title+" Energy [GeV]",   128,   -200.,       3000.) );
      m_NArea.push_back(     book(m_name, (m_prefix+"Area_"+pNum.str()),    pTitle.str()+" "+m_title+" Area [radians]", 350,     0.0,        7.0 ) );
      m_Nrho.push_back(      book(m_name, (m_prefix+"Rho"+pNum.str()),      pTitle.str()+" "+m_title+" Rho [GeV/radians]", 300, -300.0, 300.0) );

      m_Net_v_eta.push_back(    book(m_name, (m_prefix+"et_v_eta"+pNum.str()),     pTitle.str()+" "+m_title+" #eta", 99, -4.95, 4.95,               pTitle.str()+" "+m_title+" E_{T} [GeV]", 100, 0.0, 1000.) );
      m_NpT_v_eta.push_back(    book(m_name, (m_prefix+"pt_v_eta"+pNum.str()),     pTitle.str()+" "+m_title+" #eta", 99, -4.95, 4.95,               pTitle.str()+" "+m_title+" p_{T} [GeV]", 100, -1000., 1000.) );
      m_Npt_v_et.push_back(     book(m_name, (m_prefix+"pt_v_et"+pNum.str()),      pTitle.str()+" "+m_title+" E_{T} [GeV]", 1000., 0.0, 1000.,      pTitle.str()+" "+m_title+" p_{T} [GeV]", 100., -1000., 1000.) );
      m_Narea_v_eta.push_back(  book(m_name, (m_prefix+"area_v_eta"+pNum.str()),   pTitle.str()+" "+m_title+" #eta", 99, -4.95, 4.95,               pTitle.str()+" "+m_title+" area [radians]", 350,0.0,7.0) );
      m_Nrho_v_eta.push_back(   book(m_name, (m_prefix+"rho_v_eta"+pNum.str()),    pTitle.str()+" "+m_title+" #eta", 99, -4.95, 4.95,               pTitle.str()+" "+m_title+" #rho [Gev/radians]", 300, -300, 300) );

      pNum.str("");
      pTitle.str("");
    }//for iObject
  }

  return StatusCode::SUCCESS;
}

StatusCode ObjectHists::execute( const std::vector<gFEX::Jet>& jets, float eventWeight) {
  std::vector<gFEX::Object> objects(jets.begin(), jets.end());
  return execute(objects, eventWeight);
}

StatusCode ObjectHists::execute( const std::vector<gFEX::Tower>& towers, float eventWeight) {
  std::vector<gFEX::Object> objects(towers.begin(), towers.end());
  return execute(objects, eventWeight);
}

StatusCode ObjectHists::execute( const std::vector<gFEX::Block>& blocks, float eventWeight) {
  std::vector<gFEX::Object> objects(blocks.begin(), blocks.end());
  return execute(objects, eventWeight);
}

StatusCode ObjectHists::execute( const std::vector<gFEX::Object>& objects, float eventWeight) {
  for( auto object : objects ) {
    RETURN_CHECK("ObjectHists::execute()", this->execute( object, eventWeight), "");
  }

  if(objects.size() > 1){
    double dPhi(objects.at(0).deltaPhi(objects.at(1)));
    m_deltaPhi->Fill(dPhi, eventWeight);
    m_dPhi_v_dEt->Fill((objects.at(0).pt() - objects.at(1).pt())/1.e3, dPhi, eventWeight);
  }

  if( m_infoSwitch->m_numLeading > 0){
    int numobjects = std::min( m_infoSwitch->m_numLeading, (int)objects.size() );
    for(int iObject=0; iObject < numobjects; ++iObject){
      m_NPt.at(iObject)->       Fill( objects.at(iObject).pt()/1.e3, eventWeight);
      m_NPt_s.at(iObject)->     Fill( objects.at(iObject).pt()/1.e3, eventWeight);
      m_NEta.at(iObject)->      Fill( objects.at(iObject).eta(),     eventWeight);
      m_NPhi.at(iObject)->      Fill( objects.at(iObject).phi(),     eventWeight);
      m_NM.at(iObject)->        Fill( objects.at(iObject).m()/1.e3,  eventWeight);
      m_NE.at(iObject)->        Fill( objects.at(iObject).e()/1.e3,  eventWeight);
      m_NArea.at(iObject)->     Fill( objects.at(iObject).area(),    eventWeight);
      m_Nrho.at(iObject)->      Fill( objects.at(iObject).rho()/1.e3,eventWeight);

      m_Net_v_eta.at(iObject)->  Fill( objects.at(iObject).eta(),     objects.at(iObject).et()/1.e3, eventWeight);
      m_NpT_v_eta.at(iObject)->  Fill( objects.at(iObject).eta(),     objects.at(iObject).pt()/1.e3, eventWeight);
      m_Npt_v_et.at(iObject)->   Fill( objects.at(iObject).et()/1.e3, objects.at(iObject).pt()/1.e3, eventWeight);
      m_Narea_v_eta.at(iObject)->Fill( objects.at(iObject).eta(),     objects.at(iObject).area(),    eventWeight);
      m_Nrho_v_eta.at(iObject)-> Fill( objects.at(iObject).eta(),     objects.at(iObject).rho()/1.e3,eventWeight);
    }
  }

  return StatusCode::SUCCESS;
}

StatusCode ObjectHists::execute( const gFEX::Object& object, float eventWeight) {

  if(m_debug) std::cout << "ObjectHists: in execute " <<std::endl;

  //basic
  m_Pt   ->     Fill( object.pt()/1e3,  eventWeight );
  m_Pt_s ->     Fill( object.pt()/1e3,  eventWeight );
  m_Eta  ->     Fill( object.eta(),     eventWeight );
  m_Phi  ->     Fill( object.phi(),     eventWeight );
  m_M    ->     Fill( object.m()/1e3,   eventWeight );
  m_E    ->     Fill( object.e()/1e3,   eventWeight );
  m_area ->     Fill( object.area(),    eventWeight );
  m_rho  ->     Fill( object.rho()/1.e3,eventWeight );

  m_et_v_eta->  Fill( object.eta(),     object.et()/1.e3, eventWeight);
  m_pT_v_eta->  Fill( object.eta(),     object.pt()/1.e3, eventWeight);
  m_pt_v_et->   Fill( object.et()/1.e3, object.pt()/1.e3, eventWeight);
  m_area_v_eta->Fill( object.eta(),     object.area(),    eventWeight);
  m_rho_v_eta-> Fill( object.eta(),     object.rho()/1.e3,    eventWeight);

  return StatusCode::SUCCESS;
}

