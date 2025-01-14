#include "HiggsNuNu/interface/HiggsNuNuAnalysisTools.h"
#include <iostream>
#include <vector>
#include <map>
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/format.hpp"
#include "boost/range/algorithm_ext.hpp"
#include "boost/filesystem.hpp"
#include "Utilities/interface/SimpleParamParser.h"
#include "Utilities/interface/FnRootTools.h"
#include "TEfficiency.h"
#include "TH3F.h"
#include "TPad.h"
#include "TLatex.h"

namespace ic{

  void DrawCMSLogoTest(TPad* pad, TString cmsText, TString extraText, int iPosX,float relPosX, float relPosY, float relExtraDY) {
    TVirtualPad *pad_backup = gPad;
    pad->cd();
    float cmsTextFont = 61;  // default is helvetic-bold

    bool writeExtraText = extraText.Length() > 0;
    float extraTextFont = 52;  // default is helvetica-italics

    // text sizes and text offsets with respect to the top frame
    // in unit of the top margin size
    TString lumiText;
    float lumiTextOffset = 0.2;
    float cmsTextSize = 0.8;
    float lumiTextSize = 0.6;
    // float cmsTextOffset    = 0.1;  // only used in outOfFrame version

    // ratio of "CMS" and extra text size
    float extraOverCmsTextSize = 0.76;

    //!!MAKE CHOICE CONFIGURABLE
    TString lumi_13TeV_2016_ICHEP = "12.9 fb^{-1}";
    TString lumi_13TeV_2016_full  = "27.7 fb^{-1}";
    TString lumi_13TeV_2015 = "2.3 fb^{-1}";
    TString lumi_8TeV = "19.2 fb^{-1}";
    TString lumi_7TeV = "5.1 fb^{-1}";

    lumiText +=lumi_13TeV_2016_ICHEP;//lumi_13TeV;//lumi_8TeV;
    lumiText +=" (13 TeV - ICHEP)";
    //lumiText +=lumi_13TeV_2016_full;//lumi_13TeV;//lumi_8TeV;
    //lumiText +=" (13 TeV)";


    bool outOfFrame = false;
    if (iPosX / 10 == 0) {
      outOfFrame = true;
    }
    int alignY_ = 3;
    int alignX_ = 2;
    if (iPosX / 10 == 0) alignX_ = 1;
    if (iPosX == 0) alignX_ = 1;
    if (iPosX == 0) alignY_ = 1;
    if (iPosX / 10 == 1) alignX_ = 1;
    if (iPosX / 10 == 2) alignX_ = 2;
    if (iPosX / 10 == 3) alignX_ = 3;
    if (iPosX == 0) relPosX = 0.14;
    int align_ = 10 * alignX_ + alignY_;

    float l = pad->GetLeftMargin();
    float t = pad->GetTopMargin();
    float r = pad->GetRightMargin();
    float b = pad->GetBottomMargin();

    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);

    float extraTextSize = extraOverCmsTextSize * cmsTextSize;
    float pad_ratio = (static_cast<float>(pad->GetWh()) * pad->GetAbsHNDC()) /
      (static_cast<float>(pad->GetWw()) * pad->GetAbsWNDC());
    if (pad_ratio < 1.) pad_ratio = 1.;

    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(lumiTextSize*t*pad_ratio);    
    latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

    if (outOfFrame) {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11);
      latex.SetTextSize(cmsTextSize * t * pad_ratio);
      latex.DrawLatex(l, 1 - t + lumiTextOffset * t, cmsText);
    }


    float posX_ = 0;
    if (iPosX % 10 <= 1) {
      posX_ = l + relPosX * (1 - l - r);
    } else if (iPosX % 10 == 2) {
      posX_ = l + 0.5 * (1 - l - r);
    } else if (iPosX % 10 == 3) {
      posX_ = 1 - r - relPosX * (1 - l - r);
    }
    float posY_ = 1 - t - relPosY * (1 - t - b);
    if (!outOfFrame) {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextSize(cmsTextSize * t * pad_ratio);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, cmsText);
      if (writeExtraText) {
        latex.SetTextFont(extraTextFont);
        latex.SetTextAlign(align_);
        latex.SetTextSize(extraTextSize * t * pad_ratio);
        latex.DrawLatex(posX_, posY_ - relExtraDY * cmsTextSize * t, extraText);
      }
    }
    else if (writeExtraText) {
      if (iPosX == 0) {
        posX_ = l + relPosX * (1 - l - r);
        posY_ = 1 - t + lumiTextOffset * t;
      }
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize * t * pad_ratio);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, extraText);
    }
    pad_backup->cd();
  }

  void DrawCMSLogoTest(TPad* pad, TString cmsText, TString extraText, int iPosX) {
    DrawCMSLogoTest(pad, cmsText, extraText, iPosX, 0.045, 0.035, 1.2);
  }



  double Integral(TH1F const* hist) {
    if (hist) {
      double ltmp =hist->Integral(0, hist->GetNbinsX() + 1);
      if (ltmp<0 || ltmp != ltmp) {
        std::cout << " -- Warning: integral is " << ltmp << ". Removing overflows. " << std::endl;
        ltmp = hist->Integral(1, hist->GetNbinsX());
        if (ltmp<0 || ltmp != ltmp) {
          std::cout << " -- Warning: integral is " << ltmp << ". Removing bins with nans." << std::endl;
          ltmp=0;

          for (int iB(0); iB<hist->GetNbinsX() + 2; ++iB){
            if (hist->GetBinContent(iB)!=hist->GetBinContent(iB)) continue;
            ltmp += hist->GetBinContent(iB);
            //std::cout << " bin " << iB << " content " << hist->GetBinContent(iB) << std::endl;
          }

          if (ltmp<0 || ltmp != ltmp) {
            std::cout << " -- Warning: integral is " << ltmp << ". Setting to 0." << std::endl;
            ltmp=0;
          }
        }
      }
      return ltmp;
    }
    else return 0;
  }

  double Error(TH1F const* hist) {
    double err = 0.0;
    if (hist) {
      //hist->Sumw2();
      hist->IntegralAndError(0, hist->GetNbinsX()+1, err);
      if (err<0 || err != err) {
        std::cout << " -- Warning: error on integral is " << err << ". Removing overflows." << std::endl;
        hist->IntegralAndError(1, hist->GetNbinsX(), err);
        if (err<0 || err != err) {
          std::cout << " -- Warning: error on integral is " << err << ". Setting to 0." << std::endl;
          err=0;
        }
      }
    }
    return err;
  }

  double Integral(TH2F const* hist) {
    if (hist) {
      double ltmp =hist->Integral(0, hist->GetNbinsX() + 1, 0, hist->GetNbinsY() + 1);
      if (ltmp<0 || ltmp != ltmp) {
        std::cout << " -- Warning: integral is " << ltmp << ". Removing overflows. " << std::endl;
        ltmp = hist->Integral(1, hist->GetNbinsX(),1,hist->GetNbinsY());
        if (ltmp<0 || ltmp != ltmp) {
          std::cout << " -- Warning: integral is " << ltmp << ". Setting to 0." << std::endl;
          ltmp=0;
        }
      }
      return ltmp;
    }
  else return 0;
  }

  double Error(TH2F const* hist) {
    double err = 0.0;
    if (hist) {
      //hist->Sumw2();
      hist->IntegralAndError(0, hist->GetNbinsX()+1,0, hist->GetNbinsY() + 1, err);
      if (err<0 || err != err) {
        std::cout << " -- Warning: error on integral is " << err << ". Removing overflows." << std::endl;
        hist->IntegralAndError(1, hist->GetNbinsX(),1,hist->GetNbinsY(), err);
        if (err<0 || err != err) {
          std::cout << " -- Warning: error on integral is " << err << ". Setting to 0." << std::endl;
          err=0;
        }
      }
    }
    return err;
  }

  double IntegralWithError(TH1F const* hist, int binmin, int binmax, double &err){
    if (hist) {
      //hist->Sumw2();
      double ltmp =hist->IntegralAndError(binmin, binmax, err);
      if (ltmp<0 || ltmp != ltmp) {
        std::cout << " -- Warning: integral is " << ltmp << ". Setting to 0." << std::endl;
        ltmp=0;
      }
      return ltmp;
    }
    else return 0;
  }

  double IntegralWithError(TH1F const* hist, double err){
    if (hist) {
      //hist->Sumw2();
      double ltmp =hist->IntegralAndError(0, hist->GetNbinsX()+1, err);
      if (ltmp<0 || ltmp != ltmp) {
        std::cout << " -- Warning: integral is " << ltmp << ". Remove overflows." << std::endl;
        ltmp=hist->IntegralAndError(1, hist->GetNbinsX(), err);
        if (ltmp<0 || ltmp != ltmp) {
          std::cout << " -- Warning: integral is " << ltmp << ". Setting to 0." << std::endl;
          ltmp=0;
        }
      }
      return ltmp;
    }
    else return 0;
  }

  double Integral(TH1F const* hist, int binmin, int binmax){
    if (hist) {
      double ltmp =hist->Integral(binmin, binmax);
      if (ltmp<0 || ltmp != ltmp) {
        std::cout << " -- Warning: integral is " << ltmp << ". Setting to 0." << std::endl;
        ltmp=0;
      }
      return ltmp;
    }
    else return 0;
  }

  double Integral(TH2F const* hist, int xbinmin, int xbinmax, int ybinmin, int ybinmax){
    if (hist) {
      double ltmp =hist->Integral(xbinmin, xbinmax,ybinmin, ybinmax);
      if (ltmp<0 || ltmp != ltmp) {
        std::cout << " -- Warning: integral is " << ltmp << ". Setting to 0." << std::endl;
        ltmp=0;
      }
      return ltmp;
    }
    else return 0;
  }

  double Integral(TH3F const* hist, int xbinmin, int xbinmax, int ybinmin, int ybinmax, int zbinmin, int zbinmax){
    if (hist) {
      double ltmp =hist->Integral(xbinmin, xbinmax,ybinmin, ybinmax,zbinmin, zbinmax);
      if (ltmp<0 || ltmp != ltmp) {
        std::cout << " -- Warning: integral is " << ltmp << ". Setting to 0." << std::endl;
        ltmp=0;
      }
      return ltmp;
    }
    else return 0;
  }

  double Error(TH1F const* hist,int binmin,int binmax) {
    double err = 0.0;
    if (hist) {
      //hist->Sumw2();
      hist->IntegralAndError(binmin, binmax, err);
      if (err<0 || err != err) {
        std::cout << " -- Warning: error on integral is " << err << ". Setting to 0." << std::endl;
        err=0;
      }
    }
    return err;
  }

  double Error(TH2F const* hist,int xbinmin, int xbinmax, int ybinmin, int ybinmax) {
    double err = 0.0;
    if (hist) {
      //hist->Sumw2();
      hist->IntegralAndError(xbinmin, xbinmax,ybinmin, ybinmax, err);
      if (err<0 || err != err) {
        std::cout << " -- Warning: error on integral is " << err << ". Setting to 0." << std::endl;
        err=0;
      }
    }
    return err;
  }

  double Error(TH3F const* hist,int xbinmin, int xbinmax, int ybinmin, int ybinmax, int zbinmin, int zbinmax) {
    double err = 0.0;
    if (hist) {
      //hist->Sumw2();
      hist->IntegralAndError(xbinmin, xbinmax,ybinmin, ybinmax,zbinmin, zbinmax, err);
      if (err<0 || err != err) {
        std::cout << " -- Warning: error on integral is " << err << ". Setting to 0." << std::endl;
        err=0;
      }
    }
    return err;
  }

  std::string BuildCutString(std::string const& selection,std::string const& category,std::string const& weight) {
    std::string full_selection;
    if (weight != "" && (selection != "" || category != "")) full_selection += "( ";

    if (selection != "")                    full_selection += ("(" + selection + ")");
    if (selection != "" && category != "")  full_selection += " && ";
    if (category != "")                     full_selection += ("(" + category + ")");
    if (weight != "" && (selection != "" || category != "")) full_selection += " ) * ";
    if (weight != "") full_selection += ("("+weight+")");
    return full_selection;
  }

  std::string BuildVarString(std::string const& variable) {
    std::string full_variable = variable;
    if (full_variable.find_last_of("(") != full_variable.npos
        && full_variable.find("[") == full_variable.npos
        && full_variable.find("]") == full_variable.npos) {
      full_variable.insert(full_variable.find_last_of("("),">>htemp");
    }
    return full_variable;
  }

  TH1F GetShape(std::string const& variable, std::string const& selection, std::string const& category, std::string const& weight, TTree* ttree){
    TH1F temp;
    GetShape(temp,variable,selection,category,weight,ttree,false);
    return temp;
  }

  bool GetShape(TH1F & shape, std::string const& variable, std::string const& selection, std::string const& category, std::string const& weight, TTree* ttree, const bool toadd){
    std::string full_variable= BuildVarString(variable);
    std::string full_selection = BuildCutString(selection, category, weight);
    TH1::AddDirectory(true);
    int success = ttree->Draw(full_variable.c_str(), full_selection.c_str(), "goff");
    if (success <0) {
      std::cout << " -- Problem with TTree->Draw... return code is " << success << std::endl;
      return false;
    }
    TH1F* myhtemp = (TH1F*)gDirectory->Get("htemp");
    if (!myhtemp) {
      std::cout << " ERROR! Histogram " << full_variable.c_str() << " not found for selection " << full_selection.c_str() << std::endl;
      //std::cout<<"Returning empty histogram!"<<std::endl;
      //TH1F hshape;
      //shape.SetName("EMPTY");
      return false;
    }
    //std::cout << variable << " nEvtsPerFile = " << myhtemp->GetEntries() << " " << myhtemp->Integral() << std::endl;
    if (!toadd) {
      myhtemp->SetDirectory(0); 
      //TH1::AddDirectory(false);
      shape= (*myhtemp);
      shape.SetName("myshape");
      shape.Sumw2();
    }
    else {
      if (!shape.Add(myhtemp)) {
        std::cout << " Failed adding shape." << std::endl;
        return false;
      }
      gDirectory->Delete("htemp;*");
    }
    std::cout << variable << " nEvtsIntegrated = " << shape.GetEntries() << " " << shape.Integral() << std::endl;

    //gDirectory->Delete("htemp;*");
    return true;
  }

  TH2F GetShape2D(std::string const& variable, std::string const& selection, std::string const& category, std::string const& weight, TTree* ttree){

    TH2F temp;
    GetShape2D(temp,variable,selection,category,weight,ttree,false);
    return temp;
  }

  bool GetShape2D(TH2F & shape, std::string const& variable, std::string const& selection, std::string const& category, std::string const& weight, TTree* ttree, const bool toadd){
    std::string full_variable= BuildVarString(variable);
    std::string full_selection = BuildCutString(selection, category, weight);
    TH1::AddDirectory(true);
    bool success = ttree->Draw(full_variable.c_str(), full_selection.c_str(), "goff");
    if (success <0) {
      std::cout << " -- Problem with TTree->Draw... return code is " << success << std::endl;
      return false;
    }
    //TH1::AddDirectory(false);
    TH2F* myhtemp = (TH2F*)gDirectory->Get("htemp");
    if (!myhtemp) {
      std::cout << " ERROR! Histogram " << full_variable.c_str() << " not found for selection " << full_selection.c_str() << std::endl;
      //std::cout<<"Returning empty histogram!"<<std::endl;
      //TH2F hshape;
      //hshape.SetName("EMPTY");
      return false;
    }


    std::cout << variable << " nEvtsPerFile = " << myhtemp->GetEntries() << " " << myhtemp->Integral() << std::endl;

    if (!toadd) {
      myhtemp->SetDirectory(0);
      //TH1::AddDirectory(false);
      shape = (*myhtemp);
      shape.SetName("myshape");
      shape.Sumw2();
    }
    else {
      if (!shape.Add(myhtemp)) {
        std::cout << " Failed adding shape." << std::endl;
        return false;
      }
      gDirectory->Delete("htemp;*");
    }
    std::cout << variable << " nEvtsIntegrated = " << shape.GetEntries() << " " << shape.Integral() << std::endl;

    //gDirectory->Delete("myhtemp;*");
    return true;
  }

  TH3F GetShape3D(std::string const& variable, std::string const& selection, std::string const& category, std::string const& weight, TTree* ttree){
    std::string full_variable= BuildVarString(variable);
    std::string full_selection = BuildCutString(selection, category, weight);
    TH3::AddDirectory(true);
    ttree->Draw(full_variable.c_str(), full_selection.c_str(), "goff");
    TH3::AddDirectory(false);
    TH3F* myhtemp = (TH3F*)gDirectory->Get("htemp");
    if (!myhtemp) {
      std::cout << " ERROR! Histogram " << full_variable.c_str() << " not found for selection " << full_selection.c_str() << std::endl;
      std::cout<<"Returning empty histogram!"<<std::endl;
      TH3F hshape;
      hshape.SetName("EMPTY");
      return hshape;
    }
    TH3F hshape= (*myhtemp);
    gDirectory->Delete("myhtemp;*");
    return hshape;
  }

}
