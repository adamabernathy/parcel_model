//
// parcel_model_r4.cpp
//    
// To compile:
// $ g++ parcel_model_r4.cpp -o parcel_model_R4_build_2 -lm -std=c++11
//
// Adam Abernathy, adam.abernathy@utah.edu
// Jeff Fitzgerald, j.fitzgerald@utah.edu
//
 
// --------------------------------------------------------------------
//    Headers & Compiler options
// --------------------------------------------------------------------

   #include <fstream>
   #include <iostream>
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #include <math.h>
   #include <time.h>
   #include <array>
   
   #define cmax 1000     // 'cmax' is the max size of the 
                         // packaged_computation's arrays.

   struct adjusted_sat {
      double theta; // adj. potential temperature, theta^{n+1} (K)
      double qv;    // adj. mixing water vapor rat., q_v^{n+1} (kg/kg)
      double qc;    // adj. mixing liquid water rat., q_c^{n+1} (kg/kg)
      double qvs;   // sat mixing rat., q_vs^{n+1} (kg/kg),TH1, PBAR
      double pibar; // Exner function, pi (non-dimensional pressure)
   }; 
                     
   struct packaged_computations {
      double p_mb[cmax];
      double theta_K[cmax];
      double T_K[cmax];
      double qv_gkg[cmax];
      double qc_gkg[cmax];
      double rh[cmax];
      int n_steps;
   };

   #include "terminal_lib.cpp"
   #include "compute_theta.cpp"
   #include "compute_esat_pa.cpp"
   #include "compute_des_dt_pa.cpp"
   #include "compute_alpha.cpp"
   #include "satadjust.cpp"
   #include "write_output.cpp"
   #include "parcel_motion_driver.cpp"
      
   using namespace std;

// Function declaration   

// Computation functions    
   double compute_theta(double T, double p);
   double compute_esat_pa(double T);
   double compute_des_dt_pa(double T);
   double compute_alpha(double pbar, double pibar, double tstar);
   
   adjusted_sat compute_satadjust(double theta,
      double qv,double qc,double p);
      
   double random_pertubate(double scalar);


// Console output functions, found in 'terminal_lib.cpp'  
   void print_parcel(double p_mb, double theta_K, double T_K,
      double qv, double qc, double rh);
      
   void print_descend();
   void print_table_header(double TC, double qv, double qc);
   void print_table_line();
   
// CSV functions
   void write_output_csv(double p_mb[], double theta_K[], double T_K[],
                         double qv[], double qc[], double rh[],
                         int n_steps, int append_flag, 
                         const std::string& f);
                         
// Parcel motion driver                       
   packaged_computations parcel_motion_driver(double pMB, double TC, 
      double qv, double qc, double qw, double qvs, double rh_i, 
      double dpMB, double ptopMB, int console_output);

   
// --------------------------------------------------------------------
//    MAIN()
// --------------------------------------------------------------------

   int main(int nbargs, char* args[]) {
   
   printf("\n\n2D Parcel Model\n");

// --------------------------------------------------------------------
// Initialization Parameters
// --------------------------------------------------------------------

// We will need to add support for all sorts of input but for starters
// lets just define them all here.

   int do_write_output,do_console_output,n_trials;
   double pMB,TC,qv,qvs,qc,qw,rh_i,dpMB,ptopMB,pert_scalar;

// Deal with command line arguments
   if(nbargs!=14) { 
   
      printf("Using default parameters ...\n");
      printf("Usage: <do_output> <do_console> <pert> <ntrials> \n");
      printf("<pMB> <dp> <ptop> <TC> <qv> <qc> <qw> <qvs> <rh>\n");
      
      printf("\nSee 'readme' for more information\n");      

// Default kick-off parameters
      do_write_output = 1;    // If the user wants to save the output
      do_console_output = 1;  // Print to console?
      
      pert_scalar = 1.0;      // Perturbation scaler
      n_trials = 1;           // no. of trials to run

// Initial parcel properties
      pMB = 1000.;            // pressure (mb)
      TC = 20.0;              // temperature (deg C)
   
      qv = 14.8e-3;           // water vapor mixing ratio 
      qc = 0.0;               // liquid water mixing ratio
      qw = 14.8e-3;
      qvs = 0.0;
   
      rh_i = 0.5;             // initial RH value

// Accent parameters  
      dpMB = 10.0;            // pressure interval (mb)
      ptopMB = 500.0;         // ending pressure (mb)
      
      
// --------------------------------------------------------------------
// If the user DOES pass initialization parameters
   }else{
// --------------------------------------------------------------------
// Get the params from the input.
// Default kick-off parameters
      do_write_output = atoi(args[1]);   // save output?
      do_console_output = atoi(args[2]); // Print to console?
      
      pert_scalar = atof(args[3]);       // Perturbation scaler
      n_trials = atoi(args[4]);          // no. of trials to run

// Initial parcel properties
      TC = atof(args[8]);        // temperature (deg C)

      qv = atof(args[9]);        // water vapor mixing ratio 
      qc = atof(args[10]);       // liquid water mixing ratio
      qw = atof(args[11]);
      qvs = atof(args[12]);

      rh_i = atof(args[13]);     // initial RH value

// Accent parameters  
      pMB = atof(args[5]);       // pressure (mb)
      dpMB = atof(args[6]);      // pressure interval (mb)
      ptopMB = atof(args[7]);    // ending pressure (mb)  

   } // end IF/ELSE initialization parameters, nbargs !=11
   

// --------------------------------------------------------------------
// We now have our initialization parameters, so lets get going...
// --------------------------------------------------------------------

   int append_flag = 0;  // Append to text file?
   

// Initialize simulation loop
   for (int i=0; i < n_trials; i++){   
   
   if ( n_trials == 1 || i == 0 ){
      append_flag = 0; // no
   }else{
      append_flag = 1; // yes
   } 

// Invoke the parcel motion driver. This routine is responsible for
// 'pushing' the parcel up and down vertically in the atmosphere.
// At this point, the parcel motion driver is responsible for sending
// the data arrays to be printing to a CSV file. The majority of the 
// working and output variables are declared internally to the 
// parcel motion driver in order to keep their scope limited, thus
// limiting the potential for SEGFAULTS.
   packaged_computations AB;
   AB = parcel_motion_driver(pMB, TC + random_pertubate(pert_scalar),
                             qv,qc,qw,qvs,rh_i,dpMB,ptopMB,
                             do_console_output);

// Unpack the return structure and save to CSV.  
  if ( do_write_output == 1 ){
      //printf("> Saving output ... \n");
      
      string ff = "results.txt";
            
      write_output_csv(AB.p_mb, AB.theta_K, AB.T_K, AB.qv_gkg,
                       AB.qc_gkg, AB.rh, AB.n_steps, append_flag, ff);
        
   } // End IF, do_write_output

   } // End FOR, [i], simulation loop
   
// Tell the user we are done!
   printf("> Complete.\n\n");
   
   return 0;
   
   }  //  End main()
 

// --------------------------------------------------------------------

   double random_pertubate(double scalar) {

// Generate a radom variable between 0 and RAND_MAX using random(), then
// Normalize this number such that it falls between 0 and 1 by dividing
// by RAND_MAX. Return the number
      int rand_max = 10;
      
      double sign = 1.; // plus/minus sign for the random number
      double pm = random() * (1.0/RAND_MAX); // random number
      
      
      if ( pm > 0.5 ){ sign = -1.; } // change signs?
      
      double rtn = random() * (scalar/RAND_MAX) * sign;
      
      return rtn;
   
   } // end rndm()  

// All done!

