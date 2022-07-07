#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
  float elem33,elem34,elem44,elem35,elem45,elem55,elem46,elem56,elem66,elem57,elem67,elem77;
  int index,flag,flag1;
  int nrlines=0;

  std::vector<int>   index_id;
  std::vector<float> Elem33;
  std::vector<float> Elem34;
  std::vector<float> Elem44;
  std::vector<float> Elem35;
  std::vector<float> Elem45;
  std::vector<float> Elem55;
  std::vector<float> Elem46;
  std::vector<float> Elem56;
  std::vector<float> Elem66;
  std::vector<float> Elem57;
  std::vector<float> Elem67;
  std::vector<float> Elem77;

  std::ifstream dbdata;
  dbdata.open("FileName",std::ios::in);
  if(!dbdata)
  {
    std::cerr <<"Error: FileName -> no such file!"<< std::endl;
    exit(1);
  }

    float Selem33(0),Selem34(0),Selem44(0),Selem35(0),Selem45(0),Selem55(0),Selem46(0),Selem56(0),Selem66(0),Selem57(0),Selem67(0),Selem77(0);
    float Aelem33(0),Aelem34(0),Aelem44(0),Aelem35(0),Aelem45(0),Aelem55(0),Aelem46(0),Aelem56(0),Aelem66(0),Aelem57(0),Aelem67(0),Aelem77(0);
    int nIndexME11(0);
    
    float S42elem33(0),S42elem34(0),S42elem44(0),S42elem35(0),S42elem45(0),S42elem55(0),S42elem46(0),S42elem56(0),S42elem66(0),S42elem57(0),S42elem67(0),S42elem77(0);
    float A42elem33(0),A42elem34(0),A42elem44(0),A42elem35(0),A42elem45(0),A42elem55(0),A42elem46(0),A42elem56(0),A42elem66(0),A42elem57(0),A42elem67(0),A42elem77(0);
    int nIndexME42(0);
    
    
  while (!dbdata.eof() )
  {
    dbdata >> index >>elem33>>elem34>>elem44>>elem35>>elem45>>elem55>>elem46>>elem56>>elem66>>elem57>>elem67>>elem77 >>flag >>flag1;
    index_id.push_back(index);
    Elem33.push_back(elem33);
    Elem34.push_back(elem34);
    Elem44.push_back(elem44);
    Elem35.push_back(elem35);
    Elem45.push_back(elem45);
    Elem55.push_back(elem55);
    Elem46.push_back(elem46);
    Elem56.push_back(elem56);
    Elem66.push_back(elem66);
    Elem57.push_back(elem57);
    Elem67.push_back(elem67);
    Elem77.push_back(elem77);
    nrlines++;
      
      if (elem33<30.0 && elem33>0)
      {
          if (elem34>-5.0 && elem34<15.0)
          {
              if (elem44>0 && elem44<30.0)
              {
                  if (elem35<25. && elem35>-5.0)
                  {
                      if (elem45<30.&& elem45>-5.0)
                      {
                          if (elem55<30.&& elem55>0)
                          {
                              if (elem46>-5. && elem46<30.0)
                              {
                                  if(elem56<25.&& elem56>-5.0)
                                  {
                                      if (elem66<25.&& elem66>0)
                                      {
                                          if (elem57>-5. && elem57<30.0)
                                          {
                                              if (elem67<15.0 && elem67>-5.0)
                                              {
                                                  if (elem77<25. && elem77>0 )
                                                  {
                                                      //--- if ME11s use it for calculating average
                                                      if((index >= 252289 && index <= 273024) || (index >= 1 && index <= 17280)){
                                                          Selem33 += elem33;
                                                          Selem34 += elem34;
                                                          Selem44 += elem44;
                                                          Selem35 += elem35;
                                                          Selem45 += elem45;
                                                          Selem55 += elem55;
                                                          Selem46 += elem46;
                                                          Selem56 += elem56;
                                                          Selem66 += elem66;
                                                          Selem57 += elem57;
                                                          Selem67 += elem67;
                                                          Selem77 += elem77;
                                                          nIndexME11++;
                                                      }
                                                      //---
                                                      
                                                      if(elem34*elem34<elem33 && elem34*elem34<elem44)
                                                      {
                                                          if(elem35*elem35<elem33 && elem35*elem35<elem55)
                                                          {
                                                              if(elem45*elem45<elem44 && elem45*elem45<elem55)
                                                              {
                                                                  if(elem46*elem46<elem44 && elem46*elem46<elem66)
                                                                  {
                                                                      if(elem56*elem56<elem55 && elem56*elem56<elem66)
                                                                      {
                                                                          if(elem57*elem57<elem55 && elem57*elem57<elem77)
                                                                          {
                                                                              //--- if ME42s use it for calculating average
                                                                              if (index >= 217729 && index <= 252288){
                                                                                  S42elem33 += elem33;
                                                                                  S42elem34 += elem34;
                                                                                  S42elem44 += elem44;
                                                                                  S42elem35 += elem35;
                                                                                  S42elem45 += elem45;
                                                                                  S42elem55 += elem55;
                                                                                  S42elem46 += elem46;
                                                                                  S42elem56 += elem56;
                                                                                  S42elem66 += elem66;
                                                                                  S42elem57 += elem57;
                                                                                  S42elem67 += elem67;
                                                                                  S42elem77 += elem77;
                                                                                  nIndexME42++;
                                                                              }
                                                                              //---
                                                                          }
                                                                      }
                                                                  }
                                                              }
                                                          }
                                                      }
                                                  }
                                              }
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          }
      }
      
      
  }
    Aelem33 = Selem33/nIndexME11;
    Aelem34 = Selem34/nIndexME11;
    Aelem44 = Selem44/nIndexME11;
    Aelem35 = Selem35/nIndexME11;
    Aelem45 = Selem45/nIndexME11;
    Aelem55 = Selem55/nIndexME11;
    Aelem46 = Selem46/nIndexME11;
    Aelem56 = Selem56/nIndexME11;
    Aelem66 = Selem66/nIndexME11;
    Aelem57 = Selem57/nIndexME11;
    Aelem67 = Selem67/nIndexME11;
    Aelem77 = Selem77/nIndexME11;
    
    A42elem33 = S42elem33/nIndexME42;
    A42elem34 = S42elem34/nIndexME42;
    A42elem44 = S42elem44/nIndexME42;
    A42elem35 = S42elem35/nIndexME42;
    A42elem45 = S42elem45/nIndexME42;
    A42elem55 = S42elem55/nIndexME42;
    A42elem46 = S42elem46/nIndexME42;
    A42elem56 = S42elem56/nIndexME42;
    A42elem66 = S42elem66/nIndexME42;
    A42elem57 = S42elem57/nIndexME42;
    A42elem67 = S42elem67/nIndexME42;
    A42elem77 = S42elem77/nIndexME42;
    
    
  dbdata.close();
  std::ofstream myMatrixFile("GoodVals_FileName",std::ios::out);

  for(int i=0; i<nrlines-1;++i)
  {
    bool passMe11(false);
    bool pass(false);
      
    if (Elem33[i]<30.0 && Elem33[i]>0)
    {
      if (Elem34[i]>-5.0 && Elem34[i]<15.0)
      {
        if (Elem44[i]>0 && Elem44[i]<30.0)
        {
          if (Elem35[i]<25. && Elem35[i]>-5.0)
          {
            if (Elem45[i]<30.&& Elem45[i]>-5.0)
            {
              if (Elem55[i]<30.&& Elem55[i]>0)
              {
                if (Elem46[i]>-5. && Elem46[i]<30.0)
                {
                  if(Elem56[i]<25.&& Elem56[i]>-5.0)
                  {
                    if (Elem66[i]<25.&& Elem66[i]>0)
                    {
                      if (Elem57[i]>-5. && Elem57[i]<30.0)
                      {
                        if (Elem67[i]<15.0 && Elem67[i]>-5.0)
                        {
                          if (Elem77[i]<25. && Elem77[i]>0 )
                          {
                              passMe11 = true;
                              
                            if(Elem34[i]*Elem34[i]<Elem33[i] && Elem34[i]*Elem34[i]<Elem44[i])
                            {
                              if(Elem35[i]*Elem35[i]<Elem33[i] && Elem35[i]*Elem35[i]<Elem55[i])
                              {
                                if(Elem45[i]*Elem45[i]<Elem44[i] && Elem45[i]*Elem45[i]<Elem55[i])
                                {
                                  if(Elem46[i]*Elem46[i]<Elem44[i] && Elem46[i]*Elem46[i]<Elem66[i])
                                  {
                                    if(Elem56[i]*Elem56[i]<Elem55[i] && Elem56[i]*Elem56[i]<Elem66[i])
                                    {
                                      if(Elem57[i]*Elem57[i]<Elem55[i] && Elem57[i]*Elem57[i]<Elem77[i])
                                      {
                                        myMatrixFile<<index_id[i]<<"  "<<Elem33[i]<<"  "<<Elem34[i]<<"  "<<Elem44[i]<<"  "<<Elem35[i]<<"  "<<Elem45[i]<<"  "<<Elem55[i]<<"  "<<Elem46[i]<<"  "<<Elem56[i]<<"  "<<Elem66[i]<<"  "<<Elem57[i]<<"  "<<Elem67[i]<<"  "<<Elem77[i]<<std::endl;
                                        pass = true;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
      if (!pass && passMe11 && ((index_id[i] >= 252289 && index_id[i] <= 273024) || (index_id[i] >= 1 && index_id[i] <= 17280)) ){
          myMatrixFile<<index_id[i]<<"  "<<Elem33[i]<<"  "<<Elem34[i]<<"  "<<Elem44[i]<<"  "<<Elem35[i]<<"  "<<Elem45[i]<<"  "<<Elem55[i]<<"  "<<Elem46[i]<<"  "<<Elem56[i]<<"  "<<Elem66[i]<<"  "<<Elem57[i]<<"  "<<Elem67[i]<<"  "<<Elem77[i]<<std::endl;
      }
    
      if (!passMe11 && ((index_id[i] >= 252289 && index_id[i] <= 273024) || (index_id[i] >= 1 && index_id[i] <= 17280))){
          myMatrixFile<<index_id[i]<<"  "<<Aelem33<<"  "<<Aelem34<<"  "<<Aelem44<<"  "<<Aelem35<<"  "<<Aelem45<<"  "<<Aelem55<<"  "<<Aelem46<<"  "<<Aelem56<<"  "<<Aelem66<<"  "<<Aelem57<<"  "<<Aelem67<<"  "<<Aelem77<<std::endl;
      }
      
      if (!pass && (index_id[i] >= 217729 && index_id[i] <= 252288)){
          myMatrixFile<<index_id[i]<<"  "<<A42elem33<<"  "<<A42elem34<<"  "<<A42elem44<<"  "<<A42elem35<<"  "<<A42elem45<<"  "<<A42elem55<<"  "<<A42elem46<<"  "<<A42elem56<<"  "<<A42elem66<<"  "<<A42elem57<<"  "<<A42elem67<<"  "<<A42elem77<<std::endl;
      }
      
    if (flag==1 || flag1==1)
    {
      std::cout<<"Flag not 0: "<<index_id[i]<<" " <<flag<<"  "<<flag1<<std::endl;
    }
  }

  /*
    if(Elem34[i]*Elem34[i]<Elem33[i] && Elem34[i]*Elem34[i]<Elem44[i]){
    if(Elem35[i]*Elem35[i]<Elem33[i] && Elem35[i]*Elem35[i]<Elem55[i]){
    if(Elem45[i]*Elem45[i]<Elem44[i] && Elem45[i]*Elem45[i]<Elem55[i]){
    if(Elem46[i]*Elem46[i]<Elem44[i] && Elem46[i]*Elem46[i]<Elem66[i]){
      if(Elem56[i]*Elem56[i]<Elem55[i] && Elem56[i]*Elem56[i]<Elem66[i]){
      if(Elem57[i]*Elem57[i]<Elem55[i] && Elem57[i]*Elem57[i]<Elem77[i]){
      myMatrixFile<<index_id[i]<<"  "<<Elem33[i]<<"  "<<Elem34[i]<<"  "<<Elem44[i]<<"  "<<Elem35[i]<<"  "<<Elem45[i]<<"  "<<Elem55[i]<<"  "<<Elem46[i]<<"  "<<Elem56[i]<<"  "<<Elem66[i]<<"  "<<Elem57[i]<<"  "<<Elem67[i]<<"  "<<Elem77[i]<<std::endl;
      }
      }
    }
    }
    }
    }
  }
      */
}
