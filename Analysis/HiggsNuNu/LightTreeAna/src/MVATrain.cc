#include "UserCode/ICHiggsTauTau/Analysis/HiggsNuNu/LightTreeAna/interface/MVATrain.h"
#include "UserCode/ICHiggsTauTau/Analysis/HiggsNuNu/LightTreeAna/interface/LightTreeFiles.h"
#include <iostream>
#include "TH1F.h"
#include "TCanvas.h"
#include <map>
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"


namespace ic{

  MVATrain::MVATrain(std::string name) : LTModule(name){
  };

  MVATrain::~MVATrain(){ ;};

  int MVATrain::Init(TFile* fs){
    fs_=fs;
    std::cout<<"Initialisation info for "<<module_name_<<":"<<std::endl;
    std::cout<<"Signal samples are: ";
    for(unsigned ivec=0;ivec<sigsets_.size();ivec++){
      std::cout<<sigsets_[ivec]<<", "<<std::endl;
    }
    std::cout<<"Background samples are: ";
    for(unsigned ivec=0;ivec<bkgsets_.size();ivec++){
      std::cout<<bkgsets_[ivec]<<", "<<std::endl;
    }
    std::cout<<"Variables used are: ";
    for(unsigned ivec=0;ivec<variables_.size();ivec++){
      std::cout<<variables_[ivec]<<", "<<std::endl;
    }
    return 0;
  };

  int MVATrain::Run(LTFiles* filemanager){
    std::cout<<module_name_<<":"<<std::endl;

    //MAKE TMVA FACTORY
    TFile *output_tmva=fs_;
    std::cout<<"Booking TMVA Factory..."<<std::endl;
    TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", output_tmva,
						"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    //ADD VARIABLES
    //!!DO SOMETHING ABOUT WHETHER IT'S A FLOAT OR AN INT
    for(unsigned iVar=0;iVar<variables_.size();iVar++){
      std::cout<<variables_[iVar].c_str()<<std::endl;
      factory->AddVariable(variables_[iVar].c_str(),variables_[iVar].c_str(), "", 'F');
      }
    //factory->AddVariable("jet2_eta","Jet 2 #eta", "", 'F');

    if(specvariables_.size()>0){
      for(unsigned iSpecVar=0;iSpecVar<specvariables_.size();iSpecVar++){
	factory->AddSpectator(variables_[iSpecVar],variables_[iSpecVar], "", 'F');
      }
    }
    //ADD THE SIGNAL AND BACKGROUND TREES AND WEIGHTS TO THE FACTORY !!MAKE WEIGHTS CONFIGURABLE
    for(unsigned iSig=0;iSig<sigsets_.size();iSig++){
      filemanager->OpenSet(sigsets_[iSig]);
      std::vector<LTFile> files=filemanager->GetFileSet(sigsets_[iSig]);
      double signalWeight=1.;
      for(unsigned iFile=0;iFile<files.size();iFile++){
	std::cout<<"ping 5"<<std::endl;
	factory->AddSignalTree(files[iFile].GetTree(),signalWeight);
        std::cout<<"ping 6"<<std::endl;
	factory->SetSignalWeightExpression("total_weight_lepveto");
        std::cout<<"ping 7"<<std::endl;
      }
    }
    for(unsigned iBkg=0;iBkg<bkgsets_.size();iBkg++){
      filemanager->OpenSet(bkgsets_[iBkg]);
      std::vector<LTFile> files=filemanager->GetFileSet(bkgsets_[iBkg]);
      double backgroundWeight=1.;
      for(unsigned iFile=0;iFile<files.size();iFile++){
	factory->AddBackgroundTree(files[iFile].GetTree(),backgroundWeight);
	factory->SetBackgroundWeightExpression("total_weight_lepveto");
      }
    }

    //PREPARE TRAINING AND TEST TREE
    TCut mycuts = (basesel_+sigcat_).c_str();//dijet_deta>3.8 && dijet_M > 1100 && met > 100 && met_significance>5";
    TCut mycutb = (basesel_+bkgcat_).c_str();//dijet_deta>3.8 && dijet_M > 1100 && met > 100 && met_significance>5";
    factory->PrepareTrainingAndTestTree( mycuts, mycutb,
					 "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

    //BOOK METHODS !!MAKE CONFIGURABLE
    factory->BookMethod( TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT",
			 "!H:!V:NTrees=1000:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.2:SeparationType=GiniIndex:nCuts=20" );

    //TRAIN, TEST AND EVALUATE ALL METHODS
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    //WRITE OUTPUT_TMVA
    output_tmva->Write();

    
    //!!DO ADD FRIEND MAYBE IN MVAEVALUATE

    //CLEANUP
    for(unsigned iSig=0;iSig<sigsets_.size();iSig++){
      filemanager->CloseSet(sigsets_[iSig]);
    }    
    for(unsigned iBkg=0;iBkg<bkgsets_.size();iBkg++){
      filemanager->CloseSet(bkgsets_[iBkg]);
    }
    delete factory;
    return 0;
  };

}