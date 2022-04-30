#set terminal postscript eps monochrome
#set output 'sin1.eps'
set size nosquare 1,0.75
set xrange [0:pi*2]
set yrange [-1.1:1.1]
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
plot 'sin10af1.csv' u 1:2 t "sin10" w l ls 1 
#set output
reset