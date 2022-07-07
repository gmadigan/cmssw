#!/bin/sh
# This file is used for making all constants in a single SQLite file. That file is for use with the CSC Validation package to test new constants.  

NOW=$(date +"%b_%d_%Y")
echo $NOW

matrixname="matrixSummary_$NOW.dat"
pedsname="pedSummary_$NOW.dat"
xtalkname="xtalkSummary_$NOW.dat"
gainsname="gainSummary_$NOW.dat"

mv Calibration_$NOW/Summary_Cali_Files/GoodVals_*_$NOW.dat ./;
mv Calibration_$NOW/TempFileOldDB/old_db*.dat ./;
mv GoodVals_$gainsname gains.dat; mv GoodVals_$matrixname matrix.dat; mv GoodVals_$xtalkname xtalk.dat; mv GoodVals_$pedsname peds.dat;


cmsRun CSCDBCrosstalkPopCon_cfg.py
mv DBCrossTalk.db DBNoiseMatrix.db

cmsRun CSCDBNoiseMatrixPopCon_cfg.py
mv DBNoiseMatrix.db DBPedestals.db

cmsRun CSCDBPedestalsPopCon_cfg.py
mv DBPedestals.db DBGains.db

cmsRun CSCDBGainsPopCon_cfg.py
mv DBGains.db NewConstantsTest.db 



mv gains.dat GoodVals_$gainsname; mv matrix.dat GoodVals_$matrixname; mv xtalk.dat GoodVals_$xtalkname; mv peds.dat GoodVals_$pedsname;

rm *log.db

mv GoodVals_*_$NOW.dat Calibration_$NOW/Summary_Cali_Files/.
mv old_db*dat Calibration_$NOW/TempFileOldDB/.
mv *$NOW* Calibration_$NOW
mv NewConstantsTest.db Calibration_$NOW
