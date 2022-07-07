#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(){
  float peds,chi2;
  int index,flag,flag1;
  int nrlines=0;

  std::vector<int>   index_id;
  std::vector<float> Ped;
  std::vector<float> pedChi2;
  
  std::ifstream dbdata; 
  dbdata.open("FileName",std::ios::in);
  if(!dbdata) {
    std::cerr <<"Error: FileName -> no such file!"<< std::endl;
    exit(1);
  }

    float sumPedsME11(0), sumPchi2ME11(0);
    float avgPedsME11(0), avgPchi2ME11(0);
    int nIndexME11(0);
    
    float sumPedsME42(0), sumPchi2ME42(0);
    float avgPedsME42(0), avgPchi2ME42(0);
    int nIndexME42(0);

  while (!dbdata.eof() ) {
    dbdata >> index >> peds >>chi2 >>flag >>flag1; 
    index_id.push_back(index);
    Ped.push_back(peds);
    pedChi2.push_back(chi2);
    nrlines++;
      
      if ( ((index >= 252289 && index <= 273024) || (index >= 1 && index <= 17280)) && (peds>1000.0 && peds<1300.0) ){
          sumPedsME11 += peds;
          sumPchi2ME11  += chi2;
          nIndexME11++;
      }
      
      if ( (index >= 217729 && index <= 252288) && (peds>400.0 && peds<1000.0) ){
          sumPedsME42 += peds;
          sumPchi2ME42  += chi2;
          nIndexME42++;
      }
  }
    
    avgPedsME11 = sumPedsME11/nIndexME11;
    avgPchi2ME11  = sumPchi2ME11/nIndexME11;
    
    avgPedsME42 = sumPedsME42/nIndexME42;
    avgPchi2ME42  = sumPchi2ME42/nIndexME42;
    
  dbdata.close();
  std::ofstream myPedsFile("GoodVals_FileName",std::ios::out);
 
  for(int i=0; i<nrlines-1;++i){
      
    if ( (index_id[i] >= 252289 && index_id[i] <= 273024) || (index_id[i] >= 1 && index_id[i] <= 17280) ){
        if (Ped[i]>1000.0 && Ped[i]<1300.0){
            myPedsFile<<index_id[i]<<"  "<<Ped[i]<<"  "<<pedChi2[i]<<std::endl;
        }
        else{
            myPedsFile<<index_id[i]<<"  "<< avgPedsME11 <<"  "<< avgPchi2ME11 <<std::endl;
        }
    }
    else if (Ped[i]>400.0 && Ped[i]<1000.0){
      myPedsFile<<index_id[i]<<"  "<<Ped[i]<<"  "<<pedChi2[i]<<std::endl;
      if (flag==1 || flag1==1){
  std::cout<<"Flag not 0: "<<index_id[i]<<" " <<flag<<"  "<<flag1<<std::endl;
      }
    }
    else if ( index_id[i] >= 217729 && index_id[i] <= 252288 ){
        myPedsFile<<index_id[i]<<"  "<< avgPedsME42 <<"  "<< avgPchi2ME42 <<std::endl;
    }
      
  }
}
