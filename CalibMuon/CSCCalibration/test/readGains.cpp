#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(){
  float gainSlope, gainIntercept,chi2;
  int index,flag,flag1;
  int nrlines=0;

  std::vector<int>   index_id;
  std::vector<float> Slope;
  std::vector<float> Intercept;
  std::vector<float> gainChi2;
  
  std::ifstream dbdata; 
  dbdata.open("FileName",std::ios::in);

  if(!dbdata) {
    std::cerr <<"Error: FileName -> no such file!"<< std::endl;
    exit(1);
  }

    float sumGslopeME11(0), sumGIntcME11(0), sumGchi2ME11(0);
    float avgGslopeME11(0), avgGIntcME11(0), avgGchi2ME11(0);
    int nIndexME11(0);
    
    float sumGslopeME42(0), sumGIntcME42(0), sumGchi2ME42(0);
    float avgGslopeME42(0), avgGIntcME42(0), avgGchi2ME42(0);
    int nIndexME42(0);
    
  while (!dbdata.eof() ) { 
    dbdata >> index >> gainSlope >> gainIntercept >>chi2 >>flag >>flag1; 
    index_id.push_back(index);
    Slope.push_back(gainSlope);
    Intercept.push_back(gainIntercept);
    gainChi2.push_back(chi2);
    nrlines++;
    
      if ( ((index >= 252289 && index <= 273024) || (index >= 1 && index <= 17280)) && (gainSlope>6.0 && gainSlope<11.0) ){
          sumGslopeME11 += gainSlope;
          sumGIntcME11  += gainIntercept;
          sumGchi2ME11  += chi2;
          nIndexME11++;
      }
      
      if ( (index >= 217729 && index <= 252288) && (gainSlope>6.0 && gainSlope<11.0) ){
          sumGslopeME42 += gainSlope;
          sumGIntcME42  += gainIntercept;
          sumGchi2ME42  += chi2;
          nIndexME42++;
      }
  }
    
    avgGslopeME11 = sumGslopeME11/nIndexME11;
    avgGIntcME11  = sumGIntcME11/nIndexME11;
    avgGchi2ME11  = sumGchi2ME11/nIndexME11;
    
    avgGslopeME42 = sumGslopeME42/nIndexME42;
    avgGIntcME42  = sumGIntcME42/nIndexME42;
    avgGchi2ME42  = sumGchi2ME42/nIndexME42;
    
  dbdata.close();
  std::ofstream myGainsFile("GoodVals_FileName",std::ios::out);
    
  for(int i=0; i<nrlines-1;++i){
    if (Slope[i]>6.0 && Slope[i]<11.0){
      myGainsFile<<index_id[i]<<"  "<<Slope[i]<<"  "<<Intercept[i]<<"  "<<gainChi2[i]<<std::endl;
      if (flag==1 || flag1==1){
  std::cout<<"Flag not 0: "<<index_id[i]<<" " <<flag<<"  "<<flag1<<std::endl;
          
      }
    }
    else if ((index_id[i] >= 252289 && index_id[i] <= 273024) || (index_id[i] >= 1 && index_id[i] <= 17280)){
        myGainsFile << index_id[i] <<"  "<< avgGslopeME11 <<"  "<< avgGIntcME11 <<"  "<< avgGchi2ME11 <<std::endl;
    }
    else if ( index_id[i] >= 217729 && index_id[i] <= 252288 ){
        myGainsFile << index_id[i] <<"  "<< avgGslopeME42 <<"  "<< avgGIntcME42 <<"  "<< avgGchi2ME42 <<std::endl;
    }
  }
    
}
