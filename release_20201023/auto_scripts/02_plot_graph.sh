#!/bin/bash
data_folder=$(pwd)
if [ "$1" ]
  then
    data_folder=$1
fi
current_folder=$(pwd)
cd "$data_folder"
for file in *.csv; do
	name=${file%%.*}
	# echo "Working with file $name"
	gnuplot -e "image_file='$name.png';data_file='$name.csv'" "$current_folder"/plot.gp
done
cd -