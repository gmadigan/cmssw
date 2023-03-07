#!/bin/sh

echo Analyzing for run: $1

# Date label
NOW=$(date +"%b_%d_%Y")
echo $NOW


##########################################################################
######      CSC Automated Calibration  -   Revision 11-24-2010      ######
######      Darin Baumgartel, Northeastern University               ######
##########################################################################

echo " "
echo "                  ***************************************************"
echo "                  ****     Step 0 of new Calibration Update      ****"
echo "                  ***************************************************"; echo " "


#######################################################################################
####        MERGE THE GAINS, PEDS, XTALK, MATRIX VALUES INTO SUMMARY FILES          ###
####        This part is needed if the summary files do not exist                   ###
#######################################################################################
#
### Replace the run numbes with your desired run numbers (things like "run_######_Calib_CFEB_[----].plots" directories)
#
#echo " ";echo "                  ****     Creating Summary Files:";echo " "
### CFEB02 - SCAPed is used for both noise-matrix (*_DB_NoiseMatrix.dat files) and pedestals (*_DB.dat files)
#matrixname="matrixSummary_$NOW.dat"
#for i in /data2/dqm/calibration/Test_CFEB02/run_$1_Calib_CFEB_SCAPed.plots/*/*_DB_NoiseMatrix.dat
#do
#cat $i >> $matrixname
#done
#echo "CFEB02: NoiseMatrix Summary File:      $matrixname    has been produced."; echo " "
#
#pedsname="pedSummary_$NOW.dat"
#for i in /data2/dqm/calibration/Test_CFEB02/run_$1_Calib_CFEB_SCAPed.plots/*/*_DB.dat
#do
#cat $i >> $pedsname
#done
#echo "CFEB02: Pedestals Summary File:        $pedsname       has been produced."; echo " "
#
### CFEB03 - Crosstalk is used for Crosstalk (*_DB_XTalk.dat files)
#xtalkname="xtalkSummary_$NOW.dat"
#for i in /data2/dqm/calibration/Test_CFEB03/run_$1_Calib_CFEB_CrossTalk.plots/*/*_DB_Xtalk.dat
#do
#cat $i >> $xtalkname
#done
#echo "CFEB03: Crosstalk Summary File:        $xtalkname     has been produced."; echo " "
#
### CFEB04 - Gains is used for Gains (*_DB.dat files)
#gainsname="gainSummary_$NOW.dat"
#for i in /data2/dqm/calibration/Test_CFEB04/run_$1_Calib_CFEB_Gains.plots/*/*.dat
#do
#cat $i >> $gainsname
#done
#echo "CFEB04: Gains Summary File:            $gainsname      has been produced."; echo " "


######################################################################################
###        HERE THE SUMMARY FILES EXIST ALREADY, SO WE JUST RENAME THEM            ###
######################################################################################
echo " ";echo "                  ****     Renaming Summary Files:";echo " "
matrixname="matrixSummary_$NOW.dat"
for i in run_xxx_dir/*_SCAPed_DB_NoiseMatrix.dat
do
cat $i >> $matrixname
echo "found:" $i
done
echo "CFEB02: NoiseMatrix Summary File:      $matrixname    has been produced."; echo " "

pedsname="pedSummary_$NOW.dat"
for i in run_xxx_dir/*_SCAPed_DB.dat
do
cat $i >> $pedsname
echo "found:" $i
done
echo "CFEB02: Pedestals Summary File:        $pedsname       has been produced."; echo " "

xtalkname="xtalkSummary_$NOW.dat"
for i in run_xxx_dir/*_CrossTalk_DB_Xtalk.dat
do
cat $i >> $xtalkname
echo "found:" $i
done
echo "CFEB03: Crosstalk Summary File:        $xtalkname     has been produced."; echo " "

gainsname="gainSummary_$NOW.dat"
for i in run_xxx_dir/*_Gains_DB.dat
do
cat $i >> $gainsname
echo "found:" $i
done
echo "CFEB04: Gains Summary File:            $gainsname      has been produced."; echo " "



echo " "
echo "                  ***************************************************"
echo "                  ****     Step 1 of new Calibration Update      ****"
echo "                  ***************************************************"; echo " "



#######################################################################################
###        Copy the read[----].cpp template files to date-labeled files and         ###
###        filenames (replacing the string "FileName" with the names above)         ###
#######################################################################################

echo " ";echo "         ****     The following \"read\" files have been produced from templates:";echo " "
cat readMatrix.cpp | sed -e 's/FileName/'$matrixname'/' > readMatrix_$NOW.cpp; echo "readMatrix_$NOW.cpp"
cat readPeds.cpp | sed -e 's/FileName/'$pedsname'/' > readPeds_$NOW.cpp; echo "readPeds_$NOW.cpp"
cat readXtalk.cpp | sed -e 's/FileName/'$xtalkname'/' > readXtalk_$NOW.cpp; echo "readXtalk_$NOW.cpp"
cat readGains.cpp | sed -e 's/FileName/'$gainsname'/' > readGains_$NOW.cpp; echo "readGains_$NOW.cpp"; echo " "


#######################################################################################
###        Run the read[----].cpp files                                              ###
#######################################################################################


g++ readMatrix_$NOW.cpp -o readMatrix_$NOW
g++ readPeds_$NOW.cpp -o readPeds_$NOW
g++ readXtalk_$NOW.cpp -o readXtalk_$NOW
g++ readGains_$NOW.cpp -o readGains_$NOW

echo " "
echo "                  ***************************************************"
echo "                  ****        Compile cc files completed         ****"
echo "                  ***************************************************"; echo " "



######################################################################################

echo " ";echo "                  ****     Running read____.cpp files. Succesful completetion:";echo " "
echo "  READ___.CPP FILE:       INPUT_FILE       -->     OUTPUT_FILE";echo " "

./readMatrix_$NOW
echo "readMatrix_$NOW.cpp:      $matrixname      -->     GoodVals_$matrixname";

./readPeds_$NOW
echo "readPeds_$NOW.cpp:        $pedsname        -->     GoodVals_$pedsname";

./readXtalk_$NOW
echo "readXtalk_$NOW.cpp:       $xtalkname       -->     GoodVals_$xtalkname";

./readGains_$NOW
echo "readGains_$NOW.cpp:       $gainsname       -->     GoodVals_$gainsname";

echo " "

mkdir -p Summary_Cali_Files;
mv *Summary_$NOW.dat Summary_Cali_Files/ ;

