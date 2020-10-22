#!/bin/bash
data_folder=$(pwd)
# Cut each data file into CUTTING_LINE samples
CUTTING_LINE=512
OUTLINER=65535
OUTLINER2=1

if [ "$1" ]
  then
    data_folder=$1
fi

if [ "$2" ]
  then
    CUTTING_LINE=$2
fi

cd "$data_folder"
for file in *.csv; do
	name=${file%%.*}

	# remove lines which does not start with a number to remove title lines on top
	sed -n '/^[0-9]/p' $name.csv > "${name}_removeTitleLine.csv"

	lineNo=$(cat "${name}_removeTitleLine.csv" | wc -l)
	index=1
	for (( i=1; i<$lineNo-$CUTTING_LINE/2; i+=$CUTTING_LINE/2))
	do  
   		startLine=$i
		endLine=$(( CUTTING_LINE + i - 1 ))
		if [[ ${#index} -lt 2 ]]
		then
				indexFile="0${index}"
		else 
			indexFile=$index
		fi	
		sed -n -e $startLine,$endLine"p" "${name}_removeTitleLine.csv" > ${name}_$indexFile.csv
		((index++))
	done
	# split --numeric-suffixes=1 --additional-suffix=.csv -l$CUTTING_LINE "${name}_removeTitleLine.csv" "${name}_"
	rm "${name}_removeTitleLine.csv"
done

for file_cut in *_??.csv; do
	move_next_file=0
	# Remove file if number of samples is less than CUTTING_LINE
	file_len_str=$(cat $file_cut | wc -l | bc)
	if (( $file_len_str < $CUTTING_LINE ))
	then
		echo "Remove ${file_cut} because length is less than ${CUTTING_LINE}"
		rm $file_cut
		move_next_file=1
	fi

	if (( $move_next_file == 1 ))
	then
		move_next_file=0
		continue
	fi

	# # Remove file after cut into CUTTING_LINE lines per file if SPD is 65536
	if grep --quiet $OUTLINER $file_cut;
	then
		echo "Remove ${file_cut} because it contains ${OUTLINER}"
		rm $file_cut
	elif grep --quiet ",${OUTLINER2}," $file_cut;
	then
		echo "Remove ${file_cut} because it contains ${OUTLINER2}"
		rm $file_cut
	fi
done

processed_data="processed_data_"

if [ -d "$processed_data" ]
then
    rm -r "$processed_data"
    mkdir "$processed_data"
else
    mkdir "$processed_data"
fi
mv *_*_*.csv "$processed_data"

cd -
