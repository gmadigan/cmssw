#!/bin/sh

echo Analyzing for run: $1

       ##########################################################################
       ######      CSC Automated Calibration  -   Revision 11-24-2010      ######
       ######      Darin Baumgartel, Northeastern University               ######
       ##########################################################################

echo " "
echo "                  ***************************************************"
echo "                  ****     Final Step of Calibration Update      ****"
echo "                  ***************************************************"; echo " "

# Date label
NOW=$(date +"%b_%d_%Y")
echo $NOW


matrixname="matrixSummary_$NOW.dat"
pedsname="pedSummary_$NOW.dat"
xtalkname="xtalkSummary_$NOW.dat"
gainsname="gainSummary_$NOW.dat"


#######################################################################################
###      Load Results into Root NTuple                                              ###
#######################################################################################

echo " ";echo " ";
echo "          ---------------------------------------------------------"
echo "          -----      Creating/Running Root-NTuple Scripts     -----"
echo "          ---------------------------------------------------------"


cat diffGainsNtuple.cc | sed -e 's/Gains_FileName/'GoodVals_$gainsname'/;s/RootFile/'diffGains_$NOW.root'/;s/FuncName/'diffGainsNtuple_$NOW'/' >  "diffGainsNtuple_$NOW.cc"
cat diffPedsNtuple.cc | sed -e 's/Peds_FileName/'GoodVals_$pedsname'/;s/RootFile/'diffPeds_$NOW.root'/;s/FuncName/'diffPedsNtuple_$NOW'/  ' >  "diffPedsNtuple_$NOW.cc"
cat diffMatrixNtuple.cc | sed -e 's/Matrix_FileName/'GoodVals_$matrixname'/;s/RootFile/'diffMatrix_$NOW.root'/;s/FuncName/'diffMatrixNtuple_$NOW'/' >  "diffMatrixNtuple_$NOW.cc"
cat diffXtalkNtuple.cc | sed -e 's/Xtalk_FileName/'GoodVals_$xtalkname'/;s/RootFile/'diffXtalk_$NOW.root'/;s/FuncName/'diffXtalkNtuple_$NOW'/' >  "diffXtalkNtuple_$NOW.cc"

echo "               Scripts Produced:"; echo " "
echo "diffGainsNtuple_$NOW.cc"; echo "diffPedsNtuple_$NOW.cc";echo "diffMatrixNtuple_$NOW.cc";echo "diffXtalkNtuple_$NOW.cc"; echo " ";echo " "
echo "               Running Scripts:"; echo " "
 
rm RootProcesses
echo "{gROOT->ProcessLine(\"gROOT->Reset()\"); gROOT->ProcessLine(\".L diffGainsNtuple_$NOW.cc\"); gROOT->ProcessLine(\"diffGainsNtuple_$NOW()\");gROOT->ProcessLine(\"gROOT->Reset()\"); gROOT->ProcessLine(\".L diffPedsNtuple_$NOW.cc\");gROOT->ProcessLine(\"diffPedsNtuple_$NOW()\");gROOT->ProcessLine(\"gROOT->Reset()\"); gROOT->ProcessLine(\".L diffMatrixNtuple_$NOW.cc\");gROOT->ProcessLine(\"diffMatrixNtuple_$NOW()\");gROOT->ProcessLine(\"gROOT->Reset()\"); gROOT->ProcessLine(\".L diffXtalkNtuple_$NOW.cc\"); gROOT->ProcessLine(\"diffXtalkNtuple_$NOW()\");gROOT->ProcessLine(\".q\");}" >RootProcesses
root -l RootProcesses



echo " "; echo " ";echo "Root N-tuple production complete. "


#######################################################################################
###      Store Results                                                              ###
#######################################################################################

echo " ";echo " ";
echo "          ---------------------------------------------------------"
echo "          -----      Transferring Results to Dated Folder     -----"
echo "          ---------------------------------------------------------"

mv old_db*.dat TempFileOldDB/ ;
mv *Summary_$NOW.dat Summary_Cali_Files/ ;

mkdir "Calibration_$NOW"
mv *$NOW* Calibration_$NOW
mv *log.db Calibration_$NOW
mv TempFileOldDB Calibration_$NOW/;
mv Summary_Cali_Files Calibration_$NOW/;

echo "          Results/Files stored in folder Calibration_$NOW"

echo " "
echo "                  ***************************************************"
echo "                  ****        Calibration Run is Complete        ****"
echo "                  ***************************************************"; echo " "
