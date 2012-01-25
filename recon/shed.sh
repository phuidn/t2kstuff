#!/bin/bash
#
# Searches the src directory for nd280 source files
#if your search is specific enough, will open the file
#if many search results, it lists them
#if no args then it tells you to do some args
#

if [ ! -n "$1" ] ; then
	ls /storage/epp2/t2k/software/ND280/v9r7p9/oaAnalysis/v4r37p5/src/
	echo "** Please add some arguements! **"
	exit 1
fi

if [ "$1" = "-f" ] && [ -n "$2" ]; then
	grep -li $2 /storage/epp2/t2k/software/ND280/v9r7p9/oaAnalysis/v4r37p5/src/* | grep .h
	grep -li $2 $OAEVENTROOT/src/* | grep .h
else
	numberofsearch=`ls /storage/epp2/t2k/software/ND280/v9r7p9/oaAnalysis/v4r37p5/src/ | grep -c $1`
	if [ $numberofsearch -eq 1 ] ; then
		vim -R /storage/epp2/t2k/software/ND280/v9r7p9/oaAnalysis/v4r37p5/src/`ls /storage/epp2/t2k/software/ND280/v9r7p9/oaAnalysis/v4r37p5/src/ | grep $1`
	else
		echo "---------------------------------------------------------------------------"
		ls /storage/epp2/t2k/software/ND280/v9r7p9/oaAnalysis/v4r37p5/src/ | grep $1
		echo "---------------------------------------------------------------------------"
		echo "There were "$numberofsearch" results. Please refine search."
	fi
fi
