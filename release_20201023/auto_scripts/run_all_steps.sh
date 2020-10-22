#!/bin/bash
sampleLength=("519")

# 1. Install dependency
sudo apt-get install build-essential gnuplot

# 2. Compile source code
gcc -std=c99 -Wall ../spd_classification/*.c -o brushing_classification

# 3. Processing
for i in ${!sampleLength[@]}
do
  #3.1 Data processing
  ./06_splitting_data.sh ../raw_data_JP/Normal/ ${sampleLength[$i]}
  mv ../raw_data_JP/Normal/processed_data_/ ../processed_data_JP_normal_${sampleLength[$i]}/

  # 3.2 Evaluate all files
  ./07_extract_all_features.sh ../processed_data_JP_normal_${sampleLength[$i]}/
  mv ../processed_data_JP_normal_${sampleLength[$i]}/final_result.csv final_result_JP_normal_${sampleLength[$i]}.csv
done

# 4. Visualize data using GNUPLOT
./02_plot_graph.sh ../raw_data_JP/Normal/