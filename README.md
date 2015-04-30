# Two Dimensional Lagrangian Parcel Model with Support for Variability


## LICENSE

   The above listed authors understand their project will be made 
available publicly through the class webpage. The include works have 
been open sourced under the Creative Commons CC-BY-NC-SA v4 license. 
For more information please see 

https://github.com/whokilledkermit/parcel_model/blob/master/LICENSE

## Documentation ...
   The documentation was compiled using PDFLaTeX.

## Installation ...
   You can obtain the most recent version of the code at:
      https://github.com/whokilledkermit/parcel_model/

## C++ Code Compiling ...
   Compiling of this code requires a C++ compiler with the C++11 
libraries installed. If you are running the most recent version of 
GCC (version 4.9.2) then you are more than likely all set to go.
   
   You can use the included Makefile or manually compile with 
   
    $ make
   
   or
   
    $ g++ parcel_model.cpp -o p_model_r4_build_2 -lm -std=c++11


## Running the model ...
	Running the model is pretty simple, you can run with the default
settings by simply running the compiled program, or you can ideally
use the initialization script "run_parcel_model.csh". In this file 
you will find a series of paramters and how to invoke them.
   
# GNU Plot Extension ...
   This version includes a GNUPlot script to view the temperature and
potential temperature in terms of pressure. To run this script simply
type 
	
    $ gnuplot 'p_model_plot.gp'
	
at the command line. Note: this script will export the plot as a PDF
to the current directory. 

Enjoy!
