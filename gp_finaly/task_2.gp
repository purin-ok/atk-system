set terminal postscript eps monochrome
set output '../epsff/task_2.eps'
# set size nosquare 1,0.75
#  set xrange [0:10]
#  set yrange [-1.1:255.1]
 set xlabel 'Time[ms]'
 set ylabel 'Amplitude'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../課題/CSV/task2_100.csv' u 1:2 t "M=1.0{/Symbol \26410^0" w l ls 1 ,'../課題/CSV/task2_101.csv' u 1:2 t "M=1.0{/Symbol \26410^1" w l ls 2,'../課題/CSV/task2_102.csv' u 1:2 t "M=1.0{/Symbol \26410^2" w l ls 3,'../課題/CSV/task2_104.csv' u 1:2 t "M=1.0{/Symbol \26410^4" w l ls 4
set output
reset