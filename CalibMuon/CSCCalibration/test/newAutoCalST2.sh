#!/bin/sh

echo Analyzing for run: $1

       ##########################################################################
       ######      CSC Automated Calibration  -   Revision 11-24-2010      ######
       ######      Darin Baumgartel, Northeastern University               ######
       ##########################################################################

echo " "
echo "                  ***************************************************"
echo "                  ****       Step 2 of Calibration Update        ****"
echo "                  ***************************************************"; echo " "

# Date label
NOW=$(date +"%b_%d_%Y")
echo $NOW

#echo " ";echo "                  ****   GoodVals_xxx_Summary Files Should be Present _$NOW.dat: : ****  ";echo " "

matrixname="matrixSummary_$NOW.dat"
pedsname="pedSummary_$NOW.dat"
xtalkname="xtalkSummary_$NOW.dat"
gainsname="gainSummary_$NOW.dat"


#######################################################################################
###    Read DataBase Values, designate them as "old_db[---].dat" for comparison     ###
#######################################################################################
rm dbxtalk.dat; rm dbmatrix.dat; rm dbgains.dat; rm dbpeds.dat;

echo " ";echo " ";
echo "          ---------------------------------------------------------"
echo "          -----    RETRIEVING DATABASE VALUES AND STORING     -----"
echo "          ---------------------------------------------------------"
echo " ";echo "         >>>>>>>>>>>>>> Retrieve Crosstalk from DataBase <<<<<<<<<<<<<<";echo " ";cmsRun readDBCrosstalk_cfg.py 
echo " ";echo "         >>>>>>>>>>>>>> Retrieve Matrix from DataBase <<<<<<<<<<<<<<";echo " ";cmsRun readDBNoiseMatrix_cfg.py
echo " ";echo "         >>>>>>>>>>>>>> Retrieve Gains from DataBase <<<<<<<<<<<<<<";echo " ";cmsRun readDBGains_cfg.py 
echo " ";echo "         >>>>>>>>>>>>>> Retrieve Pedestals from DataBase <<<<<<<<<<<<<<";echo " ";cmsRun readDBPedestals_cfg.py; echo " "
echo " ";echo " ";
echo "          ---------------------------------------------------------"
echo "          -----          DATABASE VALUES RETRIEVED            -----"
echo "          ---------------------------------------------------------"

echo " ";echo " ";echo "                  ****     Reading Database Values: ";echo " "
rm old_dbxtalk.dat;rm old_dbmatrix.dat;rm old_dbgains.dat;rm old_dbpeds.dat
mv dbxtalk.dat old_dbxtalk.dat;                      echo "Crosstalk     -- DataBase file:   old_dbxtalk.dat    has been produced.";
mv dbmatrix.dat old_dbmatrix.dat;                    echo "Noise Matrix  -- DataBase file:   old_dbmatrix.dat   has been produced.";
mv dbgains.dat old_dbgains.dat;                      echo "Gains         -- DataBase file:   old_dbgains.dat    has been produced.";
mv dbpeds.dat old_dbpeds.dat;                        echo "Pedestals     -- DataBase file:   old_dbpeds.dat     has been produced."; echo " "

# Here I remove unnecessary characters in the matrix file not suitable for comparison with the merged file...
mv old_dbmatrix.dat old_dbmatrix_orig.dat
cat old_dbmatrix_orig.dat | sed -e 's/E:[0-9][0-9]//;s/E:[0-9]//;s/S:[0-9][0-9]//;s/S:[0-9]//;s/R:[0-9][0-9]//;s/R:[0-9]//;s/C:[0-9][0-9]//;s/C:[0-9]//;s/L:[0-9][0-9]//;s/L:[0-9]//;s/chan [0-9][0-9]//;s/chan [0-9]//;s/          /  /' > old_dbmatrix.dat
rm old_dbmatrix_orig.dat


mkdir -p TempFileOldDB;
mv old_db*.dat TempFileOldDB/ ;



