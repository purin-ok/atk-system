set terminal postscript eps monochrome
# set output '../epsff/sinafpt.eps'
# set size nosquare 1,0.75
 set xrange [0:20]
#  set yrange [-1.1:255.1]
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
set term wxt
plot '../最終課題/100f100-s.csv' u 1:3 t "L" w l ls 1, '../最終課題/100f100-s.csv' u 1:2 t "R" w l ls 1 dt 3  
set output
reset