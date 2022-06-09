set terminal postscript eps monochrome
# set output '../epsff/sinafpt.eps'
# set size nosquare 1,0.75
#  set xrange [0:10]
#  set yrange [-1.1:255.1]
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
set term wxt
plot '../課題/CSV/task_2.csv' u 1:2 t "task_2" w l ls 1  
set output
reset