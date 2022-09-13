set terminal postscript eps monochrome
set output '../epsff/chimes_int.eps'
# set size nosquare 1,0.75
#  set xrange [0:pi*4]
#  set yrange [-1.1:255.1]
 set xlabel 'Time[ms]'
 set ylabel 'Amplitude'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../演習5/chimes_int.csv' u 1:2 t "chimesL" w l ls 1 , '../演習5/chimes_int.csv' u 1:3 t "chimesR" w l ls 1 dt 3 
set output
reset