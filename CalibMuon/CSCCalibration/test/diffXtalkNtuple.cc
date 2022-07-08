#include "Riostream.h"

void FuncName(){

  gROOT->Reset();
  
  ifstream in;
  
  in.open("diff_Xtalk_FileName");
  
  Int_t index;
  Float_t diffXtalkR;
  Float_t diffXtalkL;
  Float_t diffIntL;
  Float_t diffIntR;
  int i=0;
  Int_t nlines = 0;
  TFile *f = new TFile("RootFile","RECREATE");
  
  TNtuple *ntuple = new TNtuple("DiffXtalk","data from new ascii file","index:diffXtalkR:diffIntR:diffXtalkL:diffIntL");
  
  std::cout<<" looping diff__Xtalk ... "<<nlines<<std::endl;
  while (1) {
    i++;
    in >> index >> diffXtalkR >> diffIntR >> diffXtalkL >> diffIntL ;
    if (!in.good()) break;
  
    DiffXtalk->Fill(index,diffXtalkR,diffIntR,diffXtalkL,diffIntL);
    if (i % 10000 == 0) std::cout<< " Please Wait ... " << nlines <<std::endl;
    nlines++;
  }
  
  std::cout<<" found nr of lines: "<<nlines<<std::endl;
  
  in.close();
  f->Write();
}
