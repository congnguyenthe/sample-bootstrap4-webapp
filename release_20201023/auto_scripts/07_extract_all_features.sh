#!/bin/bash
data_folder=$(pwd)
if [ "$1" ]
then
    data_folder=$1
fi
current_folder=$(pwd)
cp final_data.template "$data_folder"/final_result.csv
cd "$data_folder"
for file in *.csv; do
	name=${file%%.*}
	if [ "$name" = "histogram" ]; then
		continue
	fi

	if [ "$name" = "final_result" ]; then
		continue
	fi
	echo "Working with file $name"
	SPD="${name}_SPD.txt"
	# Extract only SPD column from the csv file
	cat $file | cut -d"," -f2 > "${name}_SPD.txt"
	"$current_folder"/brushing_classification "${name}_SPD.txt"
	rm "${name}_SPD.txt"
done
cd -