#!/bin/bash
# This script done for Continous Building ...

#script to recursively travel a dir of n levels


makeAndRun()
{
	rm -rf html
	rm *.gcda
	rm ../*.gcda
	rm *.o
	rm *.gcno

	cp ../LpsInit.c ../LpsProcess.c ../LpsUpdate.c  ../LpsUtility.c ../LpsZeroing.c ../LpsWeighLlw.c ../LpsWeighRangeWeigh.c ../LpsWeighBestBktWt.c ../LpsWeighLiveWeigh.c ../LpsWeighDigDetect.c ../LpsWeighDumpState.c ../LpsWeighDumpWtChange.c ../../../../lps_common/src/LpsCommonLookUpTblUtility.c .
	
	make cleanGtest
	sleep 1
	
	make -j 10 CPU=$CPU
#	make CPU=$CPU
	sleep 1
	
	run
}

run()
{
	# path to current dir, and to GTest for other libraries
	export LD_LIBRARY_PATH="../../../../x86_LIBs:../../../../GTest"

	mkdir html
	./gcovTest --gtest_output=xml:coverage.xml
#	cp -f $(find ../ -name '*.cc' -or -name '*.gcda' -or -name '*.gcno' -or -name '*.h') ./html
	sleep 1
#	cd html
#	../../../../../GTest/gcovr -r . --html --html-details -o GcovTestResult.html
	python ../../../../GTest/gcovr -r . --html --html-details -o GcovTestResult.html
	cp -f $(find ../ -name '*.html') ./html
	rm *.html
	
	#read -p "View Code Coverage? (y/n) " -n 1 -r
	#if [[ $REPLY =~ ^[Yy]$ ]]
	#then
	#       	exo-open --launch WebBrowser file:./GcovTestResult.html
	#fi
}

CPU=`getconf LONG_BIT`

case "$1" in
  run)
        run
        ;;
  *)
        makeAndRun
esac

exit 1
