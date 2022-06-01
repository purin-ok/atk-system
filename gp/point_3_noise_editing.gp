set terminal postscript eps monochrome
set output '../epsf/point_3_noise_deleat.eps'
set size nosquare 1,0.75
#  set xrange [0:pi*4]
#  set yrange [-1.1:255.1]
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../演習3/smple_editing.csv' u 1:2 t "editing" w l ls 1 , '../演習3/smple_err.csv' u 1:2 t "noisy" w l ls 1 dt 3 
set output
reset