# To run this script start gnuplot and then execute load 'plot.p'
# To exit gnuplot, type q.

# Since we are using a CSV file ...
set datafile separator ','

set size ratio 1
set pointsize 1

# Set the title of the figure
set title 'Temperature & Potential Temperature'

# Label of the horizontal axis
set xlabel 'Temperature [K]'

# Label of the vertical axis
set ylabel 'Pressure [mb]'

# Range of the figure in the horizontal direction
set xrange [270:325]   

# Range of the figure in the vertical direction
set yrange [500:1000] reverse

plot 'results.txt' using 2:1 with points pt 1 linecolor rgb 'red' title 'Temperature', \
	'' using 3:1 with points pt 1 linecolor rgb 'blue' title 'Theta'



# The figure is going to be replotted into a pdf file
set term pdf

# Set the name of the file
set output 'pmodel_results.pdf'

# replot the graphs
replot

# Returns to normal display
unset term
   
