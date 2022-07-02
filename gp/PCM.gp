set terminal postscript eps monochrome
set output '../epsf/PCM.eps'
set size nosquare 1,0.75
#  set xrange [0:pi*4]
#  set yrange [-1.1:255.1]
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../演習5/100f10dt3.csv' u 1:2 t "DT=3" w l ls 1 , '../演習2/100f10dt97.csv' u 1:2 t "DT=97" w l ls 1 dt 3 
set output
reset