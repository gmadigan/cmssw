#include "Riostream.h"

void FuncName(){
  
  gROOT->Reset();

  ifstream in;

  in.open("diff_Gains_FileName");

  Int_t index;
  Float_t diffGains;
  int i=0;
  Int_t nlines = 0;
  TFile *f = new TFile("RootFile","RECREATE");

  TNtuple *DiffGains = new TNtuple("DiffGains","data from new ascii file","index:diffGains");

  while (1) {
    i++;
    in >> index >> diffGains ;
    if (!in.good()) break;

    DiffGains->Fill(index,diffGains);
    if (i % 10000 == 0) std::cout<< " Please Wait ... " << nlines <<std::endl;
    nlines++;
  }

  std::cout<<" found nr of lines: "<<nlines<<std::endl;

  in.close();
  f->Write();
}



