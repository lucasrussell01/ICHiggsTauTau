#include "UserCode/ICHiggsTauTau/Analysis/HiggsTauTau/interface/RhoIDEmbedder.h"

 

namespace ic {

  RhoIDEmbedder::RhoIDEmbedder(std::string const& name) : ModuleBase(name), channel_(channel::tt) {
    fs_ = NULL;
    maketrees_ = false;
  }

  RhoIDEmbedder::~RhoIDEmbedder() {
    ;
  }

  double RhoIDEmbedder::read_mva_score(std::vector<double> vars) {
      var0=vars[0], var1=vars[1], var2=vars[2], var3=vars[3], var4=vars[4], var5=vars[5], var6=vars[6], var7=vars[7], var8=vars[8], var9=vars[9], var10=vars[10], var12=vars[12], var13=vars[13];
      double score = (reader_->EvaluateMVA( "BDT method" )+1)/2;
      return score;
  }


  int RhoIDEmbedder::PreAnalysis() {
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "RhoIDEmbedder" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    if(fs_&&maketrees_){  
      outtree_ = fs_->make<TTree>("train_ntuple","train_ntuple");
      outtree_->Branch("tauFlag1"       , &tauFlag1_ );     
      outtree_->Branch("tauFlag2"       , &tauFlag2_ );
      outtree_->Branch("gen_match_1"    , &gen_match_1_);
      outtree_->Branch("gen_match_2"    , &gen_match_2_);
      outtree_->Branch("wt"             , &wt_       );
      outtree_->Branch("Ngammas_1"      , &Ngammas_1_ );
      
      outtree_->Branch("Egamma1_1"      , &Egamma1_1_ );
      outtree_->Branch("Egamma2_1"      , &Egamma2_1_ );
      outtree_->Branch("Egamma3_1"      , &Egamma3_1_ );
      outtree_->Branch("Egamma4_1"      , &Egamma4_1_ );
      outtree_->Branch("Egamma5_1"      , &Egamma5_1_ );
      outtree_->Branch("Egamma6_1"      , &Egamma6_1_ );
      outtree_->Branch("Egamma7_1"      , &Egamma7_1_ );
      outtree_->Branch("Egamma8_1"      , &Egamma8_1_ );
      outtree_->Branch("Egamma9_1"      , &Egamma9_1_ );
      outtree_->Branch("Egamma10_1"     , &Egamma10_1_ );
      outtree_->Branch("Egamma11_1"     , &Egamma11_1_ );
      outtree_->Branch("Egamma12_1"     , &Egamma12_1_ );
      
      outtree_->Branch("Epi_1"          , &Epi_1_ );
      outtree_->Branch("Mpi0_1"         , &Mpi0_1_ );
      outtree_->Branch("Mrho_1"         , &Mrho_1_ );
      //outtree_->Branch("dphi_1"       , &dphi_1_ );
      //outtree_->Branch("dEta_1"       , &dEta_1_ );
      outtree_->Branch("gammas_dEta_1"  , &gammas_dEta_1_ );
      outtree_->Branch("gammas_dphi_1"  , &gammas_dphi_1_ );
      outtree_->Branch("pt_1"           , &pt_1_ );
      outtree_->Branch("eta_1"          , &eta_1_ );
      outtree_->Branch("phi_1"          , &phi_1_ );
      outtree_->Branch("E_1"            , &E_1_);
      outtree_->Branch("rho_dphi_1"     ,&rho_dphi_1_);
      outtree_->Branch("rho_dEta_1"     ,&rho_dEta_1_);
      outtree_->Branch("Epi0_1"         ,&Epi0_1_);
      outtree_->Branch("tau_decay_mode_1",&tau_decay_mode_1_);
      outtree_->Branch("Ngammas_2"      , &Ngammas_2_ );

      outtree_->Branch("Egamma1_2"      , &Egamma1_2_ );
      outtree_->Branch("Egamma2_2"      , &Egamma2_2_ );
      outtree_->Branch("Egamma3_2"      , &Egamma3_2_ );
      outtree_->Branch("Egamma4_2"      , &Egamma4_2_ );
      outtree_->Branch("Egamma5_2"      , &Egamma5_2_ );
      outtree_->Branch("Egamma6_2"      , &Egamma6_2_ );
      outtree_->Branch("Egamma7_2"      , &Egamma7_2_ );
      outtree_->Branch("Egamma8_2"      , &Egamma8_2_ );
      outtree_->Branch("Egamma9_2"      , &Egamma9_2_ );
      outtree_->Branch("Egamma10_2"     , &Egamma10_2_ );
      outtree_->Branch("Egamma11_2"     , &Egamma11_2_ );
      outtree_->Branch("Egamma12_2"     , &Egamma12_2_ );
      
      outtree_->Branch("Epi_2"          , &Epi_2_ );
      outtree_->Branch("Mpi0_2"         , &Mpi0_2_ );
      outtree_->Branch("Mrho_2"         , &Mrho_2_ );
      //outtree_->Branch("dphi_2"       , &dphi_2_ );
      //outtree_->Branch("dEta_2"       , &dEta_2_ );
      outtree_->Branch("gammas_dEta_2", &gammas_dEta_2_ );
      outtree_->Branch("gammas_dphi_2", &gammas_dphi_2_ );
      outtree_->Branch("pt_2"         , &pt_2_ );
      outtree_->Branch("eta_2"        , &eta_2_ );
      outtree_->Branch("phi_2"        , &phi_2_ );
      outtree_->Branch("E_2"          , &E_2_);
      outtree_->Branch("rho_dphi_2"   ,&rho_dphi_2_);
      outtree_->Branch("rho_dEta_2"   ,&rho_dEta_2_);
      outtree_->Branch("Epi0_2"       ,&Epi0_2_);
      outtree_->Branch("tau_decay_mode_2",&tau_decay_mode_2_);
      
//Added by Mohammad
      outtree_->Branch("ConeRadiusMax_2"     ,&ConeRadiusMax_2_);
      outtree_->Branch("ConeRadiusMedian_2"  ,&ConeRadiusMedian_2_);
      outtree_->Branch("ConeRadiusMean_2"    ,&ConeRadiusMean_2_);
      outtree_->Branch("ConeRadiusStdDev_2"  ,&ConeRadiusStdDev_2_);
      outtree_->Branch("ConeRadiusMax_1"     ,&ConeRadiusMax_1_);
      outtree_->Branch("ConeRadiusMedian_1"  ,&ConeRadiusMedian_1_);
      outtree_->Branch("ConeRadiusMean_1"    ,&ConeRadiusMean_1_);
      outtree_->Branch("ConeRadiusStdDev_1"  ,&ConeRadiusStdDev_1_);

 
      outtree_->Branch("ConeRadiusMaxWRTtau_2"     ,&ConeRadiusMaxWRTtau_2_);
      outtree_->Branch("ConeRadiusMedianWRTtau_2"  ,&ConeRadiusMedianWRTtau_2_);
      outtree_->Branch("ConeRadiusMeanWRTtau_2"    ,&ConeRadiusMeanWRTtau_2_);
      outtree_->Branch("ConeRadiusStdDevWRTtau_2"  ,&ConeRadiusStdDevWRTtau_2_);
      outtree_->Branch("ConeRadiusMaxWRTtau_1"     ,&ConeRadiusMaxWRTtau_1_);
      outtree_->Branch("ConeRadiusMedianWRTtau_1"  ,&ConeRadiusMedianWRTtau_1_);
      outtree_->Branch("ConeRadiusMeanWRTtau_1"    ,&ConeRadiusMeanWRTtau_1_);
      outtree_->Branch("ConeRadiusStdDevWRTtau_1"  ,&ConeRadiusStdDevWRTtau_1_);

      outtree_->Branch("ConeRadiusMaxWRTpi0_2"     ,&ConeRadiusMaxWRTpi0_2_);
      outtree_->Branch("ConeRadiusMedianWRTpi0_2"  ,&ConeRadiusMedianWRTpi0_2_);
      outtree_->Branch("ConeRadiusMeanWRTpi0_2"    ,&ConeRadiusMeanWRTpi0_2_);
      outtree_->Branch("ConeRadiusStdDevWRTpi0_2"  ,&ConeRadiusStdDevWRTpi0_2_);
      outtree_->Branch("ConeRadiusMaxWRTpi0_1"     ,&ConeRadiusMaxWRTpi0_1_);
      outtree_->Branch("ConeRadiusMedianWRTpi0_1"  ,&ConeRadiusMedianWRTpi0_1_);
      outtree_->Branch("ConeRadiusMeanWRTpi0_1"    ,&ConeRadiusMeanWRTpi0_1_);
      outtree_->Branch("ConeRadiusStdDevWRTpi0_1"  ,&ConeRadiusStdDevWRTpi0_1_);
  
      outtree_->Branch("NgammasModif_1"       , &NgammasModif_1_ );
      outtree_->Branch("NgammasModif_2"       , &NgammasModif_2_ );

      outtree_->Branch("DeltaR2WRTtau_1"      , &DeltaR2WRTtau_1_);
      outtree_->Branch("DeltaR2WRTtau_2"      , &DeltaR2WRTtau_2_);
      outtree_->Branch("DeltaR2WRTpi0_1"      , &DeltaR2WRTpi0_1_);
      outtree_->Branch("DeltaR2WRTpi0_2"      , &DeltaR2WRTpi0_2_);

      outtree_->Branch("Etagamma1_1"          , &Etagamma1_1_);
      outtree_->Branch("Etagamma2_1"          , &Etagamma2_1_);
      outtree_->Branch("Etagamma3_1"          , &Etagamma3_1_);
      outtree_->Branch("Etagamma4_1"          , &Etagamma4_1_);
      outtree_->Branch("Etagamma5_1"          , &Etagamma5_1_);
      outtree_->Branch("Etagamma6_1"          , &Etagamma6_1_);
      outtree_->Branch("Etagamma7_1"          , &Etagamma7_1_);
      outtree_->Branch("Etagamma8_1"          , &Etagamma8_1_);
      outtree_->Branch("Etagamma9_1"          , &Etagamma9_1_);
      outtree_->Branch("Etagamma10_1"         , &Etagamma10_1_);
      outtree_->Branch("Etagamma11_1"         , &Etagamma11_1_);
      outtree_->Branch("Etagamma12_1"         , &Etagamma12_1_);
      
      outtree_->Branch("Etagamma1_2"          , &Etagamma1_2_);
      outtree_->Branch("Etagamma2_2"          , &Etagamma2_2_);
      outtree_->Branch("Etagamma3_2"          , &Etagamma3_2_);
      outtree_->Branch("Etagamma4_2"          , &Etagamma4_2_);
      outtree_->Branch("Etagamma5_2"          , &Etagamma5_2_);
      outtree_->Branch("Etagamma6_2"          , &Etagamma6_2_);
      outtree_->Branch("Etagamma7_2"          , &Etagamma7_2_);
      outtree_->Branch("Etagamma8_2"          , &Etagamma8_2_);
      outtree_->Branch("Etagamma9_2"          , &Etagamma9_2_);
      outtree_->Branch("Etagamma10_2"         , &Etagamma10_2_);
      outtree_->Branch("Etagamma11_2"         , &Etagamma11_2_);
      outtree_->Branch("Etagamma12_2"         , &Etagamma12_2_);
      
      outtree_->Branch("Etapi_1"              , &Etapi_1_);
      outtree_->Branch("Etapi_2"              , &Etapi_2_);

      outtree_->Branch("Phigamma1_1"          , &Phigamma1_1_);
      outtree_->Branch("Phigamma2_1"          , &Phigamma2_1_);
      outtree_->Branch("Phigamma3_1"          , &Phigamma3_1_);
      outtree_->Branch("Phigamma4_1"          , &Phigamma4_1_);
      outtree_->Branch("Phigamma5_1"          , &Phigamma5_1_);
      outtree_->Branch("Phigamma6_1"          , &Phigamma6_1_);
      outtree_->Branch("Phigamma7_1"          , &Phigamma7_1_);
      outtree_->Branch("Phigamma8_1"          , &Phigamma8_1_);
      outtree_->Branch("Phigamma9_1"          , &Phigamma9_1_);
      outtree_->Branch("Phigamma10_1"         , &Phigamma10_1_);
      outtree_->Branch("Phigamma11_1"         , &Phigamma11_1_);
      outtree_->Branch("Phigamma12_1"         , &Phigamma12_1_);
      
      outtree_->Branch("Phigamma1_2"          , &Phigamma1_2_);
      outtree_->Branch("Phigamma2_2"          , &Phigamma2_2_);
      outtree_->Branch("Phigamma3_2"          , &Phigamma3_2_);
      outtree_->Branch("Phigamma4_2"          , &Phigamma4_2_);
      outtree_->Branch("Phigamma5_2"          , &Phigamma5_2_);
      outtree_->Branch("Phigamma6_2"          , &Phigamma6_2_);
      outtree_->Branch("Phigamma7_2"          , &Phigamma7_2_);
      outtree_->Branch("Phigamma8_2"          , &Phigamma8_2_);
      outtree_->Branch("Phigamma9_2"          , &Phigamma9_2_);
      outtree_->Branch("Phigamma10_2"         , &Phigamma10_2_);
      outtree_->Branch("Phigamma11_2"         , &Phigamma11_2_);
      outtree_->Branch("Phigamma12_2"         , &Phigamma12_2_);
   
      outtree_->Branch("Phipi_1"              , &Phipi_1_);
      outtree_->Branch("Phipi_2"              , &Phipi_2_);

      outtree_->Branch("FracPtDepos_dRLessThan0p008_2"              , &FracPtDepos_dRLessThan0p008_2_);
      outtree_->Branch("FracPtDepos_dRMoreThan0p008_2"              , &FracPtDepos_dRMoreThan0p008_2_);

      outtree_->Branch("FracPtDepos_dRLessThan0p008_1"              , &FracPtDepos_dRLessThan0p008_1_);
      outtree_->Branch("FracPtDepos_dRMoreThan0p008_1"              , &FracPtDepos_dRMoreThan0p008_1_);
      
      outtree_->Branch("Mpi0_TwoHighGammas_2"                       , &Mpi0_TwoHighGammas_2_); 
      outtree_->Branch("Mpi0_ThreeHighGammas_2"                     , &Mpi0_ThreeHighGammas_2_); 
      outtree_->Branch("Mpi0_FourHighGammas_2"                      , &Mpi0_FourHighGammas_2_); 
      
      outtree_->Branch("Mpi0_TwoHighGammas_1"                       , &Mpi0_TwoHighGammas_1_); 
      outtree_->Branch("Mpi0_ThreeHighGammas_1"                     , &Mpi0_ThreeHighGammas_1_); 
      outtree_->Branch("Mpi0_FourHighGammas_1"                      , &Mpi0_FourHighGammas_1_); 
      
      outtree_->Branch("Mrho_OneHighGammas_1"                       , &Mrho_OneHighGammas_1_);
      outtree_->Branch("Mrho_TwoHighGammas_1"                       , &Mrho_TwoHighGammas_1_);
      outtree_->Branch("Mrho_ThreeHighGammas_1"                     , &Mrho_ThreeHighGammas_1_);
      outtree_->Branch("Mrho_subleadingGamma_1"                     , &Mrho_subleadingGamma_1_);

      outtree_->Branch("Mrho_OneHighGammas_2"                       , &Mrho_OneHighGammas_2_);
      outtree_->Branch("Mrho_TwoHighGammas_2"                       , &Mrho_TwoHighGammas_2_);
      outtree_->Branch("Mrho_ThreeHighGammas_2"                     , &Mrho_ThreeHighGammas_2_);
      outtree_->Branch("Mrho_subleadingGamma_2"                     , &Mrho_subleadingGamma_2_);

      outtree_->Branch("wt_cp_sm", &wt_cp_sm_);
      outtree_->Branch("wt_cp_ps", &wt_cp_ps_);
      outtree_->Branch("wt_cp_mm", &wt_cp_mm_);
      outtree_->Branch("strip_pt_2", &strip_pt_2_);
      outtree_->Branch("strip_pt_1", &strip_pt_1_);
      outtree_->Branch("strip_pi_mass_1", &strip_pi_mass_1_);
      outtree_->Branch("strip_pi_mass_2", &strip_pi_mass_2_);

      outtree_->Branch("lead_gamma_pt_1", &lead_gamma_pt_1_);
      outtree_->Branch("lead_gamma_pt_2", &lead_gamma_pt_2_);
    
      outtree_->Branch("event", &event_);
    }



    if(ProductExists("MVAreader")){
        reader_ = GetProduct<TMVA::Reader*>("MVAreader");
        std::cout << "Getting MVAreader" << std::endl;
      } else { 
        reader_ = new TMVA::Reader();
        TString filename = (std::string)getenv("CMSSW_BASE")+"/src/UserCode/ICHiggsTauTau/Analysis/HiggsTauTau/input/MVA/TMVAClassification_BDT_rhoID.weights.xml";
      
        reader_->AddVariable( "Ngammas"    , &var11 );
        reader_->AddVariable( "Egamma1"    , &var0 );
        reader_->AddVariable( "Egamma2"    , &var1 );
        reader_->AddVariable( "Egamma3"    , &var2 );
        reader_->AddVariable( "Egamma4"    , &var3 );
        reader_->AddVariable( "Epi"        , &var4 );
        reader_->AddVariable( "Mpi0"       , &var5 );
        reader_->AddVariable( "Mrho"       , &var6 );
        reader_->AddVariable( "dphi"       , &var10 );
        reader_->AddVariable( "dEta"       , &var9 );
        reader_->AddVariable( "gammas_dEta", &var7 );
        reader_->AddVariable( "gammas_dphi", &var8 );
        reader_->AddVariable( "pt"         , &var13 );
        reader_->AddVariable( "eta"        , &var12 );
      
        reader_->BookMVA( "BDT method", filename );

        AddToProducts("MVAreader", reader_); 
        std::cout << "Adding MVAreader" << std::endl;
     }
    return 0;
  }

  int RhoIDEmbedder::Execute(TreeEvent *event) {

    EventInfo const* eventInfo = event->GetPtr<EventInfo>("eventInfo");
    event_ = eventInfo->event() % 2 == 0; // if even then event_ = 1, odd = 0


    wt_cp_sm_=1; wt_cp_ps_=1; wt_cp_mm_=1;
    if(event->ExistsInTree("tauspinner")){
      EventInfo const* tauspinner = event->GetPtr<EventInfo>("tauspinner");
      wt_cp_sm_ = tauspinner->weight("wt_cp_0");
      wt_cp_ps_ = tauspinner->weight("wt_cp_0p5");
      wt_cp_mm_ = tauspinner->weight("wt_cp_0p25");
    }


    if (!(channel_ == channel::tt||channel_ == channel::mt||channel_ == channel::et)) return 0;
    
    wt_ = 1;
    wt_ = eventInfo->total_weight();

    std::vector<CompositeCandidate *> const& ditau_vec = event->GetPtrVec<CompositeCandidate>("ditau");
    CompositeCandidate const* ditau = ditau_vec.at(0);
    Candidate const* lep1 = ditau->GetCandidate("lepton1");
    Candidate const* lep2 = ditau->GetCandidate("lepton2");
    
    std::vector<ic::PFCandidate*> pfcands =  event->GetPtrVec<ic::PFCandidate>("pfCandidates");
    std::vector<ic::PFCandidate*> gammas1;
    std::vector<ic::PFCandidate*> gammas2;
    std::pair<ic::Candidate*, ic::Candidate*> rho_1; 
    std::pair<ic::Candidate*, ic::Candidate*> rho_2;

    if (event->Exists("tauFlag1")) tauFlag1_ = event->Get<int>("tauFlag1");
    if (event->Exists("tauFlag2")) tauFlag2_ = event->Get<int>("tauFlag2");

    if(event->Exists("gen_match_1")) gen_match_1_ = MCOrigin2UInt(event->Get<ic::mcorigin>("gen_match_1"));
    if(event->Exists("gen_match_2")) gen_match_2_ = MCOrigin2UInt(event->Get<ic::mcorigin>("gen_match_2"));

//-------------------------------------subleading tau--------------------

    if ((channel_ == channel::tt||channel_ == channel::mt||channel_ == channel::et) && event->ExistsInTree("pfCandidates")) {
      Tau const* tau2 = dynamic_cast<Tau const*>(lep2);
      tau_decay_mode_2_=tau2->decay_mode();
      gammas2 = GetTauGammas(tau2, pfcands);
      if(gammas2.size()>0) lead_gamma_pt_2_ = gammas2[0]->pt();
      else lead_gamma_pt_2_ = -1;
      //if(gammas2.size()>0 && tau_decay_mode_2_==1 && gammas2[0]->pt()<0.50) std::cout << gammas2[0]->pt() << std::endl;
      std::vector<ic::PFCandidate*> strips = HPS (gammas2, 0, 0, 0, 0.1349, 2);
      if(strips.size()>0) {
        strip_pt_2_ = strips[0]->pt();
        strip_pi_mass_2_ = (strips[0]->vector() + tau2->vector()).M();
      }
      else {
        strip_pi_mass_2_ = -1;
        strip_pt_2_ = -1;
      }

      if ( tau2->decay_mode()==1 || true) {

    //---initializing some of the variables-----------
    FracPtDepos_dRLessThan0p008_2_=-999; FracPtDepos_dRMoreThan0p008_2_=-999;
    //-----------------------------------------




        std::pair<ic::Candidate*, ic::Candidate*> rho_2 = GetRho(tau2, pfcands);

        Candidate *pi_2 = rho_2.first;
        Candidate *pi0_2 = rho_2.second;
        
        //-----------------
        Egamma1_2_=-1, Egamma2_2_=-1, Egamma3_2_=-1, Egamma4_2_=-1; Egamma5_2_=-1, Egamma6_2_=-1, Egamma7_2_=-1, Egamma8_2_=-1;
        Egamma9_2_=-1, Egamma10_2_=-1, Egamma11_2_=-1, Egamma12_2_=-1;

        if(gammas2.size()>=1) Egamma1_2_ = gammas2[0]->energy();
        if(gammas2.size()>=2) Egamma2_2_ = gammas2[1]->energy();
        if(gammas2.size()>=3) Egamma3_2_ = gammas2[2]->energy();
        if(gammas2.size()>=4) Egamma4_2_ = gammas2[3]->energy();
        if(gammas2.size()>=5) Egamma5_2_ = gammas2[4]->energy();
        if(gammas2.size()>=6) Egamma6_2_ = gammas2[5]->energy();
        if(gammas2.size()>=7) Egamma7_2_ = gammas2[6]->energy();
        if(gammas2.size()>=8) Egamma8_2_ = gammas2[7]->energy();
        if(gammas2.size()>=9) Egamma9_2_ = gammas2[8]->energy();
        if(gammas2.size()>=10) Egamma10_2_ = gammas2[9]->energy();
        if(gammas2.size()>=11) Egamma11_2_ = gammas2[10]->energy();
        if(gammas2.size()>=12) Egamma12_2_ = gammas2[11]->energy();
        //--------Mpi0---
        Mpi0_TwoHighGammas_2_=-1; Mpi0_ThreeHighGammas_2_=-1; Mpi0_FourHighGammas_2_=-1;
        if(gammas2.size()>=2) Mpi0_TwoHighGammas_2_ = (gammas2[0]->vector() + gammas2[1]->vector()).M();
        if(gammas2.size()>=3) Mpi0_ThreeHighGammas_2_ = (gammas2[0]->vector() + gammas2[1]->vector() + gammas2[2]->vector()).M();
        if(gammas2.size()>=4) Mpi0_FourHighGammas_2_ = (gammas2[0]->vector() + gammas2[1]->vector() + gammas2[2]->vector() + gammas2[3]->vector()).M();
        //--------Mrho------
        Mrho_OneHighGammas_2_=-1; Mrho_TwoHighGammas_2_=-1; Mrho_ThreeHighGammas_2_=-1; Mrho_subleadingGamma_2_=-1;
        if(gammas2.size()>=1) Mrho_OneHighGammas_2_=( pi_2->vector() + gammas2[0]->vector() ).M();
        if(gammas2.size()>=2) Mrho_TwoHighGammas_2_=( pi_2->vector() + gammas2[0]->vector() + gammas2[1]->vector()  ).M();
        if(gammas2.size()>=3) Mrho_ThreeHighGammas_2_=( pi_2->vector() + gammas2[0]->vector() + gammas2[1]->vector() + gammas2[2]->vector() ).M();
        if(gammas2.size()>=2) Mrho_subleadingGamma_2_= (pi_2->vector() + gammas2[1]->vector()).M();
        //------------
        
        E_2_=-1, Epi_2_=-1, Mpi0_2_=-1, Mrho_2_=-1, rho_dEta_2_=-1, rho_dphi_2_=-1, gammas_dphi_2_ = -1., gammas_dEta_2_ = -1.,  pt_2_=-1, eta_2_=-999;
        Ngammas_2_=-999; phi_2_=-999;

        if(gammas2.size()>1) {
          gammas_dphi_2_ =  std::fabs(ROOT::Math::VectorUtil::DeltaPhi(gammas2[0]->vector(),gammas2[1]->vector()));
          gammas_dEta_2_ =  std::fabs(gammas2[0]->eta()-gammas2[1]->eta());
        }

        E_2_ = tau2->energy();

        Epi_2_ = pi_2->energy();
        Epi0_2_ = pi0_2->energy();
        ROOT::Math::PtEtaPhiEVector gammas_vector_2;
        for (auto g : gammas2) gammas_vector_2+=g->vector();
        Mpi0_2_ = gammas_vector_2.M();
        Mrho_2_ = tau2->M();
        if(tau2->decay_mode()==0) Mrho_2_ = (pi_2->vector()+pi0_2->vector()).M();
        rho_dphi_2_ = std::fabs(ROOT::Math::VectorUtil::DeltaPhi(pi_2->vector(),pi0_2->vector()));
        rho_dEta_2_ = std::fabs(pi_2->eta()-pi0_2->eta());

        pt_2_ = tau2->pt();
        eta_2_ = tau2->eta();
        phi_2_= tau2->phi();
    //New variables by Mohammad
        //------charged prong eta & phi-----
        Etapi_2_=-999; Phipi_2_=-999;
        Etapi_2_=pi_2->eta(); Phipi_2_=pi_2->phi();
       
        //------------gammas/e---
        Etagamma1_2_=-999; Etagamma2_2_=-999; Etagamma3_2_=-999; Etagamma4_2_=-999; Etagamma5_2_=-999; Etagamma6_2_=-999; Etagamma7_2_=-999; Etagamma8_2_=-999;  
        Etagamma9_2_=-999; Etagamma10_2_=-999; Etagamma11_2_=-999; Etagamma12_2_=-999;

        Phigamma1_2_=-999; Phigamma2_2_=-999; Phigamma3_2_=-999; Phigamma4_2_=-999; Phigamma5_2_=-999; Phigamma6_2_=-999; Phigamma7_2_=-999; Phigamma8_2_=-999;
        Phigamma9_2_=-999; Phigamma10_2_=-999; Phigamma11_2_=-999; Phigamma12_2_=-999;
        
        if(gammas2.size()>=1) {Etagamma1_2_ = gammas2[0]->eta(); Phigamma1_2_= gammas2[0]->phi();}
        if(gammas2.size()>=2) {Etagamma2_2_ = gammas2[1]->eta(); Phigamma2_2_= gammas2[1]->phi();}
        if(gammas2.size()>=3) {Etagamma3_2_ = gammas2[2]->eta(); Phigamma3_2_= gammas2[2]->phi();}
        if(gammas2.size()>=4) {Etagamma4_2_ = gammas2[3]->eta(); Phigamma4_2_= gammas2[3]->phi();}
        if(gammas2.size()>=5) {Etagamma5_2_ = gammas2[4]->eta(); Phigamma5_2_= gammas2[4]->phi();}
        if(gammas2.size()>=6) {Etagamma6_2_ = gammas2[5]->eta(); Phigamma6_2_= gammas2[5]->phi();}
        if(gammas2.size()>=7) {Etagamma7_2_ = gammas2[6]->eta(); Phigamma7_2_= gammas2[6]->phi();}
        if(gammas2.size()>=8) {Etagamma8_2_ = gammas2[7]->eta(); Phigamma8_2_= gammas2[7]->phi();}
        if(gammas2.size()>=9) {Etagamma9_2_ = gammas2[8]->eta(); Phigamma9_2_= gammas2[8]->phi();}
        if(gammas2.size()>=10) {Etagamma10_2_ = gammas2[9]->eta(); Phigamma10_2_= gammas2[9]->phi();}
        if(gammas2.size()>=11) {Etagamma11_2_ = gammas2[10]->eta(); Phigamma11_2_= gammas2[10]->phi();}
        if(gammas2.size()>=12) {Etagamma12_2_ = gammas2[11]->eta(); Phigamma12_2_= gammas2[11]->phi();}

        //-----NgammasModif---
        NgammasModif_2_=0;
        for (auto g : gammas2) 
          if (g->energy()>1.0){
            if (g->energy()>10.0)
              NgammasModif_2_+=2;
            else
              NgammasModif_2_+=1;
          }
        //------------------
        CenterEta_2=-1;  CenterPhi_2=-1;//temp variables 
        ConeRadiusMax_2_=-1; ConeRadiusMedian_2_=-1; ConeRadiusMean_2_=-1; ConeRadiusStdDev_2_=-1;
        ConeRadiusMaxWRTtau_2_=-1; ConeRadiusMedianWRTtau_2_=-1; ConeRadiusMeanWRTtau_2_=-1; ConeRadiusStdDevWRTtau_2_=-1;
        ConeRadiusMaxWRTpi0_2_=-1; ConeRadiusMedianWRTpi0_2_=-1; ConeRadiusMeanWRTpi0_2_=-1; ConeRadiusStdDevWRTpi0_2_=-1;
        DeltaR2WRTtau_2_=-999; DeltaR2WRTpi0_2_=-999;
        if(gammas2.size()>=1){
          
          CenterEta_2=pi_2->eta();
          CenterPhi_2=pi_2->phi();
          for(auto g : gammas2) {
          CenterEta_2+=g->eta();
          CenterPhi_2+=g->phi();
          }
          CenterEta_2/=(1.0+double(gammas2.size()));
          CenterPhi_2/=(1.0+double(gammas2.size()));            
        
          std::vector<double> DistToCenter2; 
          DistToCenter2.push_back( sqrt( std::pow(CenterPhi_2-pi_2->phi(),2) + std::pow(CenterEta_2-pi_2->eta(),2) ) );
          for(auto g : gammas2) DistToCenter2.push_back( sqrt( std::pow(CenterPhi_2-g->phi(),2) + std::pow(CenterEta_2-g->eta(),2) ) );//FYI: DistToCenter2.size()=1+gammas.size()
          sort( DistToCenter2.begin() , DistToCenter2.end() );
          ConeRadiusMedian_2_= DistToCenter2[DistToCenter2.size()/2] * 0.5 + DistToCenter2[(DistToCenter2.size()+1)/2-1] * 0.5;
          ConeRadiusMax_2_=DistToCenter2[DistToCenter2.size()-1];
          ConeRadiusMean_2_= std::accumulate(DistToCenter2.begin(), DistToCenter2.end(), 0.0)/double(DistToCenter2.size());
          ConeRadiusStdDev_2_=(std::inner_product(DistToCenter2.begin(), DistToCenter2.end(), DistToCenter2.begin(), 0.0) - DistToCenter2.size()*pow(ConeRadiusMean_2_,2))/(-1+DistToCenter2.size());
          ConeRadiusStdDev_2_=sqrt(ConeRadiusStdDev_2_);//Variance to StdDeV                    
        

          //--------------Now calculate the same thing with tau->Eta and tau->phi, instead of unweighted average which are  CenterPhi and CenterEta------
          std::vector<double> DistTotau2;
          DistTotau2.push_back(std::fabs(ROOT::Math::VectorUtil::DeltaR(pi_2->vector(),tau2->vector())));
          for(auto g : gammas2) DistTotau2.push_back(std::fabs(ROOT::Math::VectorUtil::DeltaR(g->vector(),tau2->vector())));       
          sort( DistTotau2.begin() , DistTotau2.end() );
          ConeRadiusMedianWRTtau_2_= DistTotau2[DistTotau2.size()/2] * 0.5 + DistTotau2[(DistTotau2.size()+1)/2-1] * 0.5;
          ConeRadiusMaxWRTtau_2_=DistTotau2[DistTotau2.size()-1];
          ConeRadiusMeanWRTtau_2_= std::accumulate(DistTotau2.begin(), DistTotau2.end(), 0.0)/double(DistTotau2.size());
          ConeRadiusStdDevWRTtau_2_=(std::inner_product(DistTotau2.begin(), DistTotau2.end(), DistTotau2.begin(), 0.0) - DistTotau2.size()*pow(ConeRadiusMeanWRTtau_2_,2))
                              /(-1+DistTotau2.size());
          ConeRadiusStdDevWRTtau_2_=sqrt(ConeRadiusStdDevWRTtau_2_);//Variance to StdDeV                    
       

       //--------------Now calculate the same thing with pi0->Eta and pi0->phi------
          std::vector<double> DistTopi0_2;
          for(auto g: gammas2) DistTopi0_2.push_back(std::fabs(ROOT::Math::VectorUtil::DeltaR(pi0_2->vector(),g->vector())));
          sort(DistTopi0_2.begin(),DistTopi0_2.end());
          ConeRadiusMedianWRTpi0_2_=DistTopi0_2[DistTopi0_2.size()/2] * 0.5 + DistTopi0_2[(DistTopi0_2.size()+1)/2-1] * 0.5;
          ConeRadiusMaxWRTpi0_2_=DistTopi0_2[DistTopi0_2.size()-1];
          ConeRadiusMeanWRTpi0_2_=std::accumulate(DistTopi0_2.begin(), DistTopi0_2.end(), 0.0)/double(DistTopi0_2.size());
          ConeRadiusStdDevWRTpi0_2_=(std::inner_product(DistTopi0_2.begin(), DistTopi0_2.end(), DistTopi0_2.begin(), 0.0) - DistTopi0_2.size()*pow(ConeRadiusMeanWRTpi0_2_,2))
                                    /(-1+DistTopi0_2.size());
          ConeRadiusStdDevWRTpi0_2_=sqrt(ConeRadiusStdDevWRTpi0_2_);//Variance to StdDeV
          

          //--------------------------Shape based variables---------------
          //WRT tau
          DeltaR2WRTtau_2_=0;
          SumPt_2=0;
          DeltaR2WRTtau_2_=std::pow(ROOT::Math::VectorUtil::DeltaR(pi_2->vector(),tau2->vector()),2)*std::pow(pi_2->pt(),2);
          SumPt_2=std::pow(pi_2->pt(),2);
          for(auto g : gammas2){
            DeltaR2WRTtau_2_+=std::pow(ROOT::Math::VectorUtil::DeltaR(g->vector(),tau2->vector()),2)*std::pow(g->pt(),2);
            SumPt_2+=std::pow(g->pt(),2);
          }
          DeltaR2WRTtau_2_/=SumPt_2;
          

          //WRT pi0 (ignoring prong)
          DeltaR2WRTpi0_2_=0;          
          SumPt_2=0;
          for(auto g : gammas2){
            DeltaR2WRTpi0_2_+=std::pow(ROOT::Math::VectorUtil::DeltaR(g->vector(),pi0_2->vector()),2)*std::pow(g->pt(),2);
            SumPt_2+=std::pow(g->pt(),2);
          }
          DeltaR2WRTpi0_2_/=SumPt_2;

        } 


     //------------------EnergyFraction-------------------- 
        FracPtDepos_dRLessThan0p008_2_=0;  FracPtDepos_dRMoreThan0p008_2_=0;
        
        if( ROOT::Math::VectorUtil::DeltaR ( pi_2->vector() , tau2->vector() ) < 0.008 )
          FracPtDepos_dRLessThan0p008_2_+=pi_2->pt()/tau2->pt();
        
        if( ROOT::Math::VectorUtil::DeltaR ( pi_2->vector() , tau2->vector() ) >= 0.008 )
          FracPtDepos_dRMoreThan0p008_2_+=pi_2->pt()/tau2->pt();
        
                
        for (auto g: gammas2){
          if (ROOT::Math::VectorUtil::DeltaR ( g->vector() , tau2->vector() ) < 0.008)
            FracPtDepos_dRLessThan0p008_2_+=g->pt()/tau2->pt();

          if (ROOT::Math::VectorUtil::DeltaR ( g->vector() , tau2->vector() ) >= 0.008 )
            FracPtDepos_dRMoreThan0p008_2_+=g->pt()/tau2->pt();

        }
        
        
    
        std::vector<double> inputs2 = {Egamma1_2_/E_2_, Egamma2_2_/E_2_, Egamma3_2_/E_2_, Egamma4_2_/E_2_, Epi_2_/E_2_, Mpi0_2_, Mrho_2_, gammas_dEta_2_, gammas_dphi_2_, rho_dEta_2_, rho_dphi_2_,(double)gammas2.size(), eta_2_, pt_2_};


        // variables for subleading tau

        Ngammas_2_     = gammas2.size();
        Egamma1_2_     = Egamma1_2_;///Etau_2_;
        Egamma2_2_     = Egamma2_2_;///Etau_2_;
        Egamma3_2_     = Egamma3_2_;///Etau_2_;
        Egamma4_2_     = Egamma4_2_;///Etau_2_;
        Epi_2_         = Epi_2_;///Etau_2_;
        Mpi0_2_        = Mpi0_2_;
        Mrho_2_        = Mrho_2_;
        dphi_2_        = rho_dphi_2_;       
        dEta_2_        = rho_dEta_2_;       
        gammas_dEta_2_  = gammas_dEta_2_;
        gammas_dphi_2_ = gammas_dphi_2_;
        pt_2_          = pt_2_;
        eta_2_         = eta_2_;

        double score2 = read_mva_score(inputs2);

        event->Add("rho_id_2", score2);
      
      
      
      }
    }

//-------------------------------------leading tau--------------------
    if (channel_ == channel::tt && event->ExistsInTree("pfCandidates")) {
      Tau const* tau1 = dynamic_cast<Tau const*>(lep1);
      tau_decay_mode_1_=tau1->decay_mode();

      gammas1 = GetTauGammas(tau1, pfcands);
      if(gammas1.size()>0) lead_gamma_pt_1_ = gammas1[0]->pt();
      else lead_gamma_pt_1_ = -1;
      std::vector<ic::PFCandidate*> strips = HPS (gammas1, 0, 0, 0, 0.1349, 2);
      if(strips.size()>0) {
        strip_pt_1_ = strips[0]->pt();
        strip_pi_mass_1_ = (strips[0]->vector() + tau1->vector()).M();
      }
      else {
        strip_pi_mass_1_ = -1;
        strip_pt_1_ = -1;
      }

      
      if(tau1->decay_mode()==1 || true) {
        
    //---initializing some of the variables-----------        
    FracPtDepos_dRLessThan0p008_1_=-999; FracPtDepos_dRMoreThan0p008_1_=-999;
    //-------------------------    
        

        std::pair<ic::Candidate*, ic::Candidate*> rho_1 = GetRho(tau1, pfcands);

        Candidate *pi_1 = rho_1.first;
        Candidate *pi0_1 = rho_1.second;
       
        //------------------
        Egamma1_1_=-1, Egamma2_1_=-1, Egamma3_1_=-1, Egamma4_1_=-1; Egamma5_1_=-1, Egamma6_1_=-1, Egamma7_1_=-1, Egamma8_1_=-1;
        Egamma9_1_=-1, Egamma10_1_=-1, Egamma11_1_=-1, Egamma12_1_=-1;

        if(gammas1.size()>=1) Egamma1_1_ = gammas1[0]->energy();
        if(gammas1.size()>=2) Egamma2_1_ = gammas1[1]->energy();
        if(gammas1.size()>=3) Egamma3_1_ = gammas1[2]->energy();
        if(gammas1.size()>=4) Egamma4_1_ = gammas1[3]->energy();
        if(gammas1.size()>=5) Egamma5_1_ = gammas1[4]->energy();
        if(gammas1.size()>=6) Egamma6_1_ = gammas1[5]->energy();
        if(gammas1.size()>=7) Egamma7_1_ = gammas1[6]->energy();
        if(gammas1.size()>=8) Egamma8_1_ = gammas1[7]->energy();
        if(gammas1.size()>=9) Egamma9_1_ = gammas1[8]->energy();
        if(gammas1.size()>=10) Egamma10_1_ = gammas1[9]->energy();
        if(gammas1.size()>=11) Egamma11_1_ = gammas1[10]->energy();
        if(gammas1.size()>=12) Egamma12_1_ = gammas1[11]->energy();
        //--------------------
        Mpi0_TwoHighGammas_1_=-1; Mpi0_ThreeHighGammas_1_=-1; Mpi0_FourHighGammas_1_=-1;
        if(gammas1.size()>=2) Mpi0_TwoHighGammas_1_= (gammas1[0]->vector() + gammas1[1]->vector()).M();
        if(gammas1.size()>=3) Mpi0_ThreeHighGammas_1_ = (gammas1[0]->vector() + gammas1[1]->vector() + gammas1[2]->vector()).M();
        if(gammas1.size()>=4) Mpi0_FourHighGammas_1_ = (gammas1[0]->vector() + gammas1[1]->vector() + gammas1[2]->vector() + gammas1[3]->vector()).M();
        //-----------
        Mrho_OneHighGammas_1_=-1; Mrho_TwoHighGammas_1_=-1; Mrho_ThreeHighGammas_1_=-1; Mrho_subleadingGamma_1_=-1;
        if(gammas1.size()>=1) Mrho_OneHighGammas_1_=( pi_1->vector() + gammas1[0]->vector() ).M();
        if(gammas1.size()>=2) Mrho_TwoHighGammas_1_=( pi_1->vector() + gammas1[0]->vector() + gammas1[1]->vector()  ).M();
        if(gammas1.size()>=3) Mrho_ThreeHighGammas_1_=( pi_1->vector() + gammas1[0]->vector() + gammas1[1]->vector() + gammas1[2]->vector() ).M();
        if(gammas1.size()>=2) Mrho_subleadingGamma_1_= (pi_1->vector() + gammas1[1]->vector()).M();
        //------------
        E_1_=-1,  Epi_1_=-1, Mpi0_1_=-1, Mrho_1_=-1, rho_dEta_1_=-1, rho_dphi_1_=-1, pt_1_=-1, eta_1_=-999, gammas_dphi_1_ = -1., gammas_dEta_1_ = -1.; 
        Ngammas_1_=-999; phi_1_=-999;

        if(gammas1.size()>1) { 
          gammas_dphi_1_ =  std::fabs(ROOT::Math::VectorUtil::DeltaPhi(gammas1[0]->vector(),gammas1[1]->vector()));
          gammas_dEta_1_ =  std::fabs(gammas1[0]->eta()-gammas1[1]->eta());
        }

        
        E_1_ = tau1->energy();

        Epi_1_ = pi_1->energy();
        Epi0_1_ = pi0_1->energy();
        ROOT::Math::PtEtaPhiEVector gammas_vector_1;
        for (auto g : gammas1) gammas_vector_1+=g->vector();
        Mpi0_1_ = gammas_vector_1.M();
        Mrho_1_ = tau1->M();
        if(tau1->decay_mode()==0) Mrho_1_ = (pi_1->vector()+pi0_1->vector()).M();
        rho_dphi_1_ = std::fabs(ROOT::Math::VectorUtil::DeltaPhi(pi_1->vector(),pi0_1->vector()));
        rho_dEta_1_ = std::fabs(pi_1->eta()-pi0_1->eta());

        pt_1_ = tau1->pt();
        eta_1_ = tau1->eta();
        phi_1_ = tau1->phi();

    //New variables by Mohammad
        //------charged prong eta & phi-----
        Etapi_1_=-999; Phipi_1_=-999;
        Etapi_1_=pi_1->eta(); Phipi_1_=pi_1->phi();

        //------------gammas/e----
        Etagamma1_1_=-999; Etagamma2_1_=-999; Etagamma3_1_=-999; Etagamma4_1_=-999; Etagamma5_1_=-999; Etagamma6_1_=-999; Etagamma7_1_=-999; Etagamma8_1_=-999;
        Etagamma9_1_=-999; Etagamma10_1_=-999; Etagamma11_1_=-999; Etagamma12_1_=-999;
        
        Phigamma1_1_=-999; Phigamma2_1_=-999; Phigamma3_1_=-999; Phigamma4_1_=-999; Phigamma5_1_=-999; Phigamma6_1_=-999; Phigamma7_1_=-999; Phigamma8_1_=-999;
        Phigamma9_1_=-999; Phigamma10_1_=-999; Phigamma11_1_=-999; Phigamma12_1_=-999;
        
        if(gammas1.size()>=1) {Etagamma1_1_ = gammas1[0]->eta(); Phigamma1_1_= gammas1[0]->phi();}
        if(gammas1.size()>=2) {Etagamma2_1_ = gammas1[1]->eta(); Phigamma2_1_= gammas1[1]->phi();}
        if(gammas1.size()>=3) {Etagamma3_1_ = gammas1[2]->eta(); Phigamma3_1_= gammas1[2]->phi();}
        if(gammas1.size()>=4) {Etagamma4_1_ = gammas1[3]->eta(); Phigamma4_1_= gammas1[3]->phi();}
        if(gammas1.size()>=5) {Etagamma5_1_ = gammas1[4]->eta(); Phigamma5_1_= gammas1[4]->phi();}
        if(gammas1.size()>=6) {Etagamma6_1_ = gammas1[5]->eta(); Phigamma6_1_= gammas1[5]->phi();}
        if(gammas1.size()>=7) {Etagamma7_1_ = gammas1[6]->eta(); Phigamma7_1_= gammas1[6]->phi();}
        if(gammas1.size()>=8) {Etagamma8_1_ = gammas1[7]->eta(); Phigamma8_1_= gammas1[7]->phi();}
        if(gammas1.size()>=9) {Etagamma9_1_ = gammas1[8]->eta(); Phigamma9_1_= gammas1[8]->phi();}
        if(gammas1.size()>=10) {Etagamma10_1_ = gammas1[9]->eta(); Phigamma10_1_= gammas1[9]->phi();}
        if(gammas1.size()>=11) {Etagamma11_1_ = gammas1[10]->eta(); Phigamma11_1_= gammas1[10]->phi();}
        if(gammas1.size()>=12) {Etagamma12_1_ = gammas1[11]->eta(); Phigamma12_1_= gammas1[11]->phi();}
        
         //-----NgammasModif---
        NgammasModif_1_=0;
        for (auto g : gammas1) 
          if (g->energy()>1.0){
            if (g->energy()>10.0)
              NgammasModif_1_+=2;
            else
              NgammasModif_1_+=1;
          }
        //------------------
        CenterEta_1=-1;  CenterPhi_1=-1;//temp variables 
        ConeRadiusMax_1_=-1; ConeRadiusMedian_1_=-1; ConeRadiusMean_1_=-1; ConeRadiusStdDev_1_=-1;
        ConeRadiusMaxWRTtau_1_=-1; ConeRadiusMedianWRTtau_1_=-1; ConeRadiusMeanWRTtau_1_=-1; ConeRadiusStdDevWRTtau_1_=-1;
        ConeRadiusMaxWRTpi0_1_=-1; ConeRadiusMedianWRTpi0_1_=-1; ConeRadiusMeanWRTpi0_1_=-1; ConeRadiusStdDevWRTpi0_1_=-1;
        DeltaR2WRTtau_1_=-999; DeltaR2WRTpi0_1_=-999;
        if(gammas1.size()>=1){
          
          CenterEta_1=pi_1->eta();
          CenterPhi_1=pi_1->phi();
          for(auto g : gammas1) {
          CenterEta_1+=g->eta();
          CenterPhi_1+=g->phi();
          }
          CenterEta_1/=(1.0+double(gammas1.size()));
          CenterPhi_1/=(1.0+double(gammas1.size()));            
                 
          std::vector<double> DistToCenter1; 
          DistToCenter1.push_back( sqrt( std::pow(CenterPhi_1-pi_1->phi(),2) + std::pow(CenterEta_1-pi_1->eta(),2) ) );
          for(auto g : gammas1) DistToCenter1.push_back( sqrt( std::pow(CenterPhi_1-g->phi(),2) + std::pow(CenterEta_1-g->eta(),2) ) );//FYI: DistToCenter1.size()=1+gammas.size()
          sort( DistToCenter1.begin() , DistToCenter1.end() );
          ConeRadiusMedian_1_= DistToCenter1[DistToCenter1.size()/2] * 0.5 + DistToCenter1[(DistToCenter1.size()+1)/2-1] * 0.5;
          ConeRadiusMax_1_=DistToCenter1[DistToCenter1.size()-1];
          ConeRadiusMean_1_= std::accumulate(DistToCenter1.begin(), DistToCenter1.end(), 0.0)/double(DistToCenter1.size());
          
          ConeRadiusStdDev_1_=(std::inner_product(DistToCenter1.begin(), DistToCenter1.end(), DistToCenter1.begin(), 0.0) - DistToCenter1.size()*pow(ConeRadiusMean_1_,2))
                              /(-1+DistToCenter1.size());
          ConeRadiusStdDev_1_=sqrt(ConeRadiusStdDev_1_);//Variance to StdDeV                    
          //Problem: if Phi=3.1 and another Phi=-3.0 the delta=6.1???? 



          //--------------Now calculate the same thing with tau->Eta and tau->phi, instead of unweighted average which are  CenterPhi and CenterEta---------
        
          std::vector<double> DistTotau1;
          DistTotau1.push_back(std::fabs(ROOT::Math::VectorUtil::DeltaR(pi_1->vector(),tau1->vector())));
          for(auto g : gammas1) DistTotau1.push_back(std::fabs(ROOT::Math::VectorUtil::DeltaR(g->vector(),tau1->vector())));       
          sort( DistTotau1.begin() , DistTotau1.end() );
          ConeRadiusMedianWRTtau_1_= DistTotau1[DistTotau1.size()/2] * 0.5 + DistTotau1[(DistTotau1.size()+1)/2-1] * 0.5;
          ConeRadiusMaxWRTtau_1_=DistTotau1[DistTotau1.size()-1];
          ConeRadiusMeanWRTtau_1_= std::accumulate(DistTotau1.begin(), DistTotau1.end(), 0.0)/double(DistTotau1.size());
          
          ConeRadiusStdDevWRTtau_1_=(std::inner_product(DistTotau1.begin(), DistTotau1.end(), DistTotau1.begin(), 0.0) - DistTotau1.size()*pow(ConeRadiusMeanWRTtau_1_,2))
                              /(-1+DistTotau1.size());
          ConeRadiusStdDevWRTtau_1_=sqrt(ConeRadiusStdDevWRTtau_1_);//Variance to StdDeV                    
          

       //--------------Now calculate the same thing with pi0->Eta and pi0->phi------
          std::vector<double> DistTopi0_1;
          for(auto g: gammas1) DistTopi0_1.push_back(std::fabs(ROOT::Math::VectorUtil::DeltaR(pi0_1->vector(),g->vector())));
          sort(DistTopi0_1.begin(),DistTopi0_1.end());
          ConeRadiusMedianWRTpi0_1_=DistTopi0_1[DistTopi0_1.size()/2] * 0.5 + DistTopi0_1[(DistTopi0_1.size()+1)/2-1] * 0.5;
          ConeRadiusMaxWRTpi0_1_=DistTopi0_1[DistTopi0_1.size()-1];
          ConeRadiusMeanWRTpi0_1_=std::accumulate(DistTopi0_1.begin(), DistTopi0_1.end(), 0.0)/double(DistTopi0_1.size());
          ConeRadiusStdDevWRTpi0_1_=(std::inner_product(DistTopi0_1.begin(), DistTopi0_1.end(), DistTopi0_1.begin(), 0.0) - DistTopi0_1.size()*pow(ConeRadiusMeanWRTpi0_1_,2))
                                    /(-1+DistTopi0_1.size());
          ConeRadiusStdDevWRTpi0_1_=sqrt(ConeRadiusStdDevWRTpi0_1_);//Variance to StdDeV


          //--------------------------Shape based variables---------------
          //WRT tau
          DeltaR2WRTtau_1_=0;
          SumPt_1=0;
          DeltaR2WRTtau_1_=std::pow(ROOT::Math::VectorUtil::DeltaR(pi_1->vector(),tau1->vector()),2)*std::pow(pi_1->pt(),2);
          SumPt_1=std::pow(pi_1->pt(),2);
          for(auto g : gammas1){
            DeltaR2WRTtau_1_+=std::pow(ROOT::Math::VectorUtil::DeltaR(g->vector(),tau1->vector()),2)*std::pow(g->pt(),2);
            SumPt_1+=std::pow(g->pt(),2);
          }
          DeltaR2WRTtau_1_/=SumPt_1;
          

          //WRT pi0 (ignoring prong)
          DeltaR2WRTpi0_1_=0;          
          SumPt_1=0;
          for(auto g : gammas1){
            DeltaR2WRTpi0_1_+=std::pow(ROOT::Math::VectorUtil::DeltaR(g->vector(),pi0_1->vector()),2)*std::pow(g->pt(),2);
            SumPt_1+=std::pow(g->pt(),2);
          }
          DeltaR2WRTpi0_1_/=SumPt_1;

        }

     //------------------EnergyFraction-------------------- 
        FracPtDepos_dRLessThan0p008_1_=0; FracPtDepos_dRMoreThan0p008_1_=0;
        
        if( ROOT::Math::VectorUtil::DeltaR ( pi_1->vector() , tau1->vector() ) < 0.008 )
          FracPtDepos_dRLessThan0p008_1_+=pi_1->pt()/tau1->pt();
        
        if( ROOT::Math::VectorUtil::DeltaR ( pi_1->vector() , tau1->vector() ) >= 0.008 )
          FracPtDepos_dRMoreThan0p008_1_+=pi_1->pt()/tau1->pt();
        
                
        for (auto g: gammas1){
          if (ROOT::Math::VectorUtil::DeltaR ( g->vector() , tau1->vector() ) < 0.008)
            FracPtDepos_dRLessThan0p008_1_+=g->pt()/tau1->pt();

     //------------------EnergyFraction-------------------- 
        FracPtDepos_dRLessThan0p008_1_=0; FracPtDepos_dRMoreThan0p008_1_=0;
        
        if( ROOT::Math::VectorUtil::DeltaR ( pi_1->vector() , tau1->vector() ) < 0.008 )
          FracPtDepos_dRLessThan0p008_1_+=pi_1->pt()/tau1->pt();
        
        if( ROOT::Math::VectorUtil::DeltaR ( pi_1->vector() , tau1->vector() ) >= 0.008 )
          FracPtDepos_dRMoreThan0p008_1_+=pi_1->pt()/tau1->pt();
        
                
        for (auto g: gammas1){
          if (ROOT::Math::VectorUtil::DeltaR ( g->vector() , tau1->vector() ) < 0.008)
            FracPtDepos_dRLessThan0p008_1_+=g->pt()/tau1->pt();

          if (ROOT::Math::VectorUtil::DeltaR ( g->vector() , tau1->vector() ) >= 0.008 )
            FracPtDepos_dRMoreThan0p008_1_+=g->pt()/tau1->pt();

        }


        std::vector<double> inputs1 = {Egamma1_1_/E_1_, Egamma2_1_/E_1_, Egamma3_1_/E_1_, Egamma4_1_/E_1_, Epi_1_/E_1_, Mpi0_1_, Mrho_1_, gammas_dEta_1_, gammas_dphi_1_, rho_dEta_1_, rho_dphi_1_,(double)gammas1.size(), eta_1_, pt_1_};


        std::vector<double> inputs1 = {Egamma1_1_/E_1_, Egamma2_1_/E_1_, Egamma3_1_/E_1_, Egamma4_1_/E_1_, Epi_1_/E_1_, Mpi0_1_, Mrho_1_, gammas_dEta_1_, gammas_dphi_1_, rho_dEta_1_, rho_dphi_1_,(double)gammas1.size(), eta_1_, pt_1_};

        // variables for leading tau
      

        Ngammas_1_     = gammas1.size();       
        Egamma1_1_     = Egamma1_1_;///Etau_1_;  
        Egamma2_1_     = Egamma2_1_;///Etau_1_;  
        Egamma3_1_     = Egamma3_1_;///Etau_1_;   
        Egamma4_1_     = Egamma4_1_;///Etau_1_;   
        Epi_1_         = Epi_1_;///Etau_1_;
        Mpi0_1_        = Mpi0_1_;   
        Mrho_1_        = Mrho_1_; 
        dphi_1_        = rho_dphi_1_; 
        dEta_1_        = rho_dEta_1_; 
        gammas_dEta_1_  = gammas_dEta_1_;  
        gammas_dphi_1_ = gammas_dphi_1_;
        pt_1_          = pt_1_; 
        eta_1_         = eta_1_;

        double score1 = read_mva_score(inputs1);
        event->Add("rho_id_1", score1);
      } 
    }

    if(fs_&&maketrees_) outtree_->Fill();

    return 0;
  }
  int RhoIDEmbedder::PostAnalysis() {
    return 0;
  }

  void RhoIDEmbedder::PrintInfo() {
    ;
  }

}