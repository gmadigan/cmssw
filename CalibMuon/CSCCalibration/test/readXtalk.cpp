#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>


using namespace std;

int main(){
  float leftslope,leftint,rightslope,rightint;
  int index,extra1,extra2;
  int nrlines1=0;

  std::vector<int> index_id;
  std::vector<float> leftSlope;
  std::vector<float> leftInt;
  std::vector<float> leftChi2;
  std::vector<float> rightSlope;
  std::vector<float> rightInt;

  std::ifstream newdata; 
  newdata.open("FileName",std::ios::in);
  if(!newdata) {
    std::cerr <<"FileName -> no such file!"<< std::endl;
    exit(1);
  }

    
    float sumLslopeME11(0), sumLIntcME11(0), sumRslopeME11(0), sumRIntcME11(0);
    float avgLslopeME11(0), avgLIntcME11(0), avgRslopeME11(0), avgRIntcME11(0);
    int nIndexME11(0);
    
    float sumLslopeME42(0), sumLIntcME42(0), sumRslopeME42(0), sumRIntcME42(0);
    float avgLslopeME42(0), avgLIntcME42(0), avgRslopeME42(0), avgRIntcME42(0);
    int nIndexME42(0);
    
    
  while (!newdata.eof() ) { 
    newdata >> index >> leftslope >> leftint >> rightslope >> rightint >> extra1 >> extra2; 
    index_id.push_back(index);
    leftSlope.push_back(leftslope);
    leftInt.push_back(leftint);
    rightSlope.push_back(rightslope);
    rightInt.push_back(rightint);
    nrlines1++;
      
      if ( ((index >= 252289 && index <= 273024) || (index >= 1 && index <= 17280)) && (rightslope!=-999 && leftslope!=-999 &&  leftint!=-999 && rightint!=-999 && extra1 !=1 && extra2 !=1) ){
          sumLslopeME11 += leftslope;
          sumLIntcME11  += leftint;
          sumRslopeME11 += rightslope;
          sumRIntcME11  += rightint;
          nIndexME11++;
      }
      
      if ( (index >= 217729 && index <= 252288) && (rightslope!=-999 && leftslope!=-999 &&  leftint!=-999 && rightint!=-999 && extra1 !=1 && extra2 !=1) ){
          sumLslopeME42 += leftslope;
          sumLIntcME42  += leftint;
          sumRslopeME42 += rightslope;
          sumRIntcME42  += rightint;
          nIndexME42++;
      }
      
  }
    
    avgLslopeME11 = sumLslopeME11/nIndexME11;
    avgLIntcME11  = sumLIntcME11/nIndexME11;
    avgRslopeME11 = sumRslopeME11/nIndexME11;
    avgRIntcME11  = sumRIntcME11/nIndexME11;
    
    avgLslopeME42 = sumLslopeME42/nIndexME42;
    avgLIntcME42  = sumLIntcME42/nIndexME42;
    avgRslopeME42 = sumRslopeME42/nIndexME42;
    avgRIntcME42  = sumRIntcME42/nIndexME42;
    
  newdata.close();

  std::ofstream myXtalkFile("GoodVals_FileName",std::ios::out);
    
  for(int i=0; i<nrlines1-1;++i){
    if (rightSlope[i]!=-999 && leftSlope[i]!=-999 &&  leftInt[i]!=-999 && rightInt[i]!=-999 && extra1 !=1){
      myXtalkFile<<index_id[i]<<"  "<<leftSlope[i]<<"  "<<leftInt[i]<<"  "<<rightSlope[i]<<"   "<<rightInt[i]<<std::endl;
    }
    else if ((index_id[i] >= 252289 && index_id[i] <= 273024) || (index_id[i] >= 1 && index_id[i] <= 17280)){
        myXtalkFile<<index_id[i]<<"  "<< avgLslopeME11 <<"  "<< avgLIntcME11 <<"  "<< avgRslopeME11 <<"   "<< avgRIntcME11 <<std::endl;
    }
    else if ( index_id[i] >= 217729 && index_id[i] <= 252288 ){
        myXtalkFile<<index_id[i]<<"  "<< avgLslopeME42 <<"  "<< avgLIntcME42 <<"  "<< avgRslopeME42 <<"   "<< avgRIntcME42 <<std::endl;
    }
      
    if (extra1==1 || extra2==1){
      std::cout<<"Flag not 0: "<<index_id[i]<<" " <<extra1<<"  "<<extra2<<std::endl;
    }
  }
}
