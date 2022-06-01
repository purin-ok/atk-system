set terminal postscript eps monochrome
set output '../epsf/sin100f3_3point.eps'
set size nosquare 1,0.75
#  set xrange [0:pi*4]
#  set yrange [-1.1:255.1]
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../演習2/sin100f3.csv' u 1:2 t "no noise" w l ls 1 , '../演習3/smple_err.csv' u 1:2 t "noisy" w l ls 1 dt 3 
set output
reset