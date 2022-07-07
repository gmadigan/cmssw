{
gROOT->Reset();
#include "Riostream.h"

ifstream in;

in.open("diff_Matrix_FileName");

Int_t index;
Float_t diffElem33,diffElem34,diffElem44,diffElem35,diffElem45,diffElem55,diffElem46,diffElem56,diffElem66,diffElem57,diffElem67,diffElem77;
int i=0;
Int_t nlines = 0;
TFile *f = new TFile("RootFile","RECREATE");

TNtuple *ntuple = new TNtuple("DiffMatrix","data from new ascii file","index:diffElem33:diffElem34:diffElem44:diffElem35:diffElem45:diffElem55:diffElem46:diffElem56:diffElem66:diffElem57:diffElem67:diffElem77");

std::cout<<" looping diff_Matrix ... "<<nlines<<std::endl;
while (1) {
  i++;
  in >> index >> diffElem33 >> diffElem34 >> diffElem44 >> diffElem35 >> diffElem45 >> diffElem55 >> diffElem46 >> diffElem56 >> diffElem66 >> diffElem57 >> diffElem67 >> diffElem77 ;
  if (!in.good()) break;

  DiffMatrix->Fill(index,diffElem33,diffElem34,diffElem44,diffElem35,diffElem45,diffElem55,diffElem46,diffElem56,diffElem66,diffElem57,diffElem67,diffElem77);
  if (i % 10000 == 0) std::cout<< " Please Wait ... " << nlines <<std::endl;
  nlines++;
}

std::cout<<" found nr of lines: "<<nlines<<std::endl;

in.close();
f->Write();
}


