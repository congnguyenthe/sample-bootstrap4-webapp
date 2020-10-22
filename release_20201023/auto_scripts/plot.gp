if (!exists("image_file")) image_file='xyz.png'
if (!exists("data_file")) data_file='1_1.csv'
set terminal png size 800,600; set output image_file;
set datafile separator comma
#set key bottom right
#set key autotitle columnhead
set yrange [0:250]
set title "Data"
set xlabel word("Time", 1)
set ylabel word("Value", 1)
plot data_file using 0:2 with lines title "SPD", '' using 0:3 with lines title "DUTY"
#plot data_file using 0:2 with lines title "SPD"
