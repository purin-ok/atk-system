set terminal postscript eps monochrome
set output '../epsff/tri.eps'
set size nosquare 1,0.75
 set xrange [-2*pi:2*pi]
 set yrange [-1.1:1.1]
 set xlabel 'Angle[rad]'
 set ylabel 'Amplitude'
 set xtics pi
 set format x "%.0P{/Symbol p}"
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../演習1/CSV/tri.csv' u 1:2 t "triangle" w l ls 1  
set output
reset