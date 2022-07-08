#include "Riostream.h"

void FuncName(){

  gROOT->Reset();
  
  ifstream in;
  
  in.open("diff_Peds_FileName");
  
  Int_t index;
  Float_t diffPeds;
  int i=0;
  Int_t nlines = 0;
  TFile *f = new TFile("RootFile","RECREATE");
  
  TNtuple *ntuple = new TNtuple("DiffPeds","data from new ascii file","index:diffPeds");
  
  std::cout<<" looping diff_Peds ... "<<nlines<<std::endl;
  while (1) {
    i++;
    in >> index >> diffPeds ;
    if (!in.good()) break;
  
    DiffPeds->Fill(index,diffPeds);
    if (i % 10000 == 0) std::cout<< " Please Wait ... " << nlines <<std::endl;
    nlines++;
  }
  
  std::cout<<" found nr of lines: "<<nlines<<std::endl;
  
  in.close();
  f->Write();
}


