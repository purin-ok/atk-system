set terminal postscript eps monochrome
set output '../epsff/3-5.eps'
# set size nosquare 1,0.75
#  set xrange [0:10]
#  set yrange [-1.1:255.1]
 set xlabel 'Time[ms]'
 set ylabel 'Amplitude'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../演習3/mvave5-2.csv' u 1:3 t "mvave5-2" w l ls 1, '../演習3/smple_editing.csv' u 1:2 t "mvave3-2" w l ls 1 dt 3  
set output
reset