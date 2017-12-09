#! /bin/bash


export TIME="%e"
function puztime
{
	puzdone=0
	puzattempted=0
	tot=0
	for puz in `cat "$1"`
	do
		(( puzattempted++ ))
		#time outputs its results to stderr so this gets messy
		val=$( { /usr/bin/time ../a.exe $puz > /dev/null; } 2>&1 )
		if [ "$?" -eq "9" ]
		then
			echo "Can't sovle puzzle: "
			echo "    $puz"
			continue
		fi
		val=`echo $val | sed s/[.]//g`
		(( tot=$tot+$val ))
		(( puzdone++ ))	
	done
	echo "For file $1" 
	echo "It took $tot hundreths of a second to solve $puzdone/$puzattempted puzzles"
	echo "Average = $(( $tot/$puzdone )) hundreths of a second"
	echo
}
puztime "./easy"
puztime "./medium"
puztime "./hard"
puztime "./evil"
