#!/bin/sh

echo Analyzing for run: $1

       ##########################################################################
       ######      CSC Automated Calibration  -   Revision 11-24-2010      ######
       ######      Darin Baumgartel, Northeastern University               ######
       ##########################################################################

echo " "
echo "                  ***************************************************"
echo "                  ****      Step 3 of Calibration Update         ****"
echo "                  ***************************************************"; echo " "

# Date label
NOW=$(date +"%b_%d_%Y")
echo $NOW


matrixname="matrixSummary_$NOW.dat"
pedsname="pedSummary_$NOW.dat"
xtalkname="xtalkSummary_$NOW.dat"
gainsname="gainSummary_$NOW.dat"


        #######################################################################################
        ###      Save values into SQLite File                                               ###
        #######################################################################################

echo " ";echo " ";
echo "          ---------------------------------------------------------"
echo "          -----             Creating SQLite Files             -----"
echo "          ---------------------------------------------------------"


mv TempFileOldDB/old_db*.dat ./;
mv Summary_Cali_Files/*.dat ./;

mv GoodVals_$gainsname gains.dat; mv GoodVals_$matrixname matrix.dat; mv GoodVals_$xtalkname xtalk.dat; mv GoodVals_$pedsname peds.dat;

cmsRun CSCDBGainsPopCon_cfg.py; cmsRun CSCDBNoiseMatrixPopCon_cfg.py; cmsRun CSCDBCrosstalkPopCon_cfg.py; cmsRun CSCDBPedestalsPopCon_cfg.py

mv gains.dat GoodVals_$gainsname; mv matrix.dat GoodVals_$matrixname; mv xtalk.dat GoodVals_$xtalkname; mv peds.dat GoodVals_$pedsname;

mv DBGains.db DBGains_$NOW.db; mv DBNoiseMatrix.db DBNoiseMatrix_$NOW.db; mv DBCrossTalk.db DBCrossTalk_$NOW.db; mv DBPedestals.db DBPedestals_$NOW.db;


##mv *$NOW.db TempFile/ ; mv *$NOW.dat TempFile/ ; mv *log.db TempFile/ ; mv old_db*.dat TempFile/ ;
##mv TempFile/old_dbpeds.dat ./;
##mv peds.dat GoodVals_$pedsname; mv DBPedestals.db DBPedestals_$NOW.db; mv *$NOW.db TempFile/ ; mv *$NOW.dat TempFile/ ; mv TempFile/*.* ./; rm -r TempFile;

echo " "; echo " "; echo " SQLite File Creation Complete"

#######################################################################################
###       Create and Run Python Comparison Module                                   ###
#######################################################################################
echo " ";echo " ";
echo "          ---------------------------------------------------------"
echo "          -----    Running Comparison With Python Modules     -----"
echo "          ---------------------------------------------------------"

rm stubs/Compare.cc;
cat Compare_template.txt | sed -e 's/Matrix_FileName/'GoodVals_$matrixname'/;s/Peds_FileName/'GoodVals_$pedsname'/;s/Gains_FileName/'GoodVals_$gainsname'/;s/Xtalk_FileName/'GoodVals_$xtalkname'/' > stubs/Compare.cc;
cd ../../../
scramv1 b -j 4
cd -
echo "              "
echo "                    stubs/Compare.C File Created"; echo " "
 echo        "THIS MAY TAKE SEVERAL MINUTES, GO HAVE A CUP OF COFFEE"
echo " "; echo "                    Running Comparisons... ";

cmsRun compare_cfg.py
