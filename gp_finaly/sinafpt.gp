set terminal postscript eps monochrome
set output '../epsff/sinafpt.eps'
# set size nosquare 1,0.75
 set xrange [0:600]
#  set yrange [-1.1:255.1]
 set xlabel 'Time[ms]'
 set ylabel 'Amplitude'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../演習2/sinafpt.csv' u 1:2 t "sinagpt" w l ls 1  
set output
reset