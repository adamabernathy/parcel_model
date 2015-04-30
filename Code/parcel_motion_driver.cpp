// 
// parcel_motion_driver.cpp
// Controls the vertical motion of the parcel
// 
// Requires:   pMB, pressure in [mb]
//             TC, temperature in [C]
//             qv, liquid water vapor mixing ratio
//             qc, liquid water mixing ratio
//             qvs, qv of environment
//             rh_i, initial relative humidity
//             dpMB, d/dt for pMB
//             ptopMB, max pMB
//             console_output, boolean int, write to screen?
//
// Returns:    struct packaged_computations
//
// ver. 1.2
// 
// -- Change log --
// April 23, 2015 - Initial Release
// April 27, 2015 - Removed support for directly calling the text
//                  output function, this is ISO build 4.
//
// -- Licence --
// Two Dimensinal Parcel Model with Variability by Adam C. Abernathy
// and Jeffery Fitzgerald is licensed under a Creative Commons 
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You can read the full licence and get the most recent code at
// https://github.com/whokilledkermit/parcel_model
//
// --------------------------------------------------------------------

   packaged_computations parcel_motion_driver(double pMB, double TC, 
      double qv, double qc, double qw, double qvs, double rh_i, 
      double dpMB, double ptopMB, int console_output){

   using namespace std;

// --------------------------------------------------------------------
// Due to the limited scope of this function, we will need to forward
// declare all the dependent functions. The same applies for the
// physical constants.
// --------------------------------------------------------------------

// Computation functions    
   extern double compute_theta(double T, double p);
   extern double compute_esat_pa(double T);
   extern double compute_des_dt_pa(double T);
   extern double compute_alpha(double pbar, double pibar, double tstar);
   
   extern adjusted_sat compute_satadjust(double theta,
      double qv,double qc,double p);

// Console output functions, found in 'terminal_lib.cpp'  
   extern void print_parcel(double p_mb, double theta_K, double T_K,
      double qv, double qc, double rh);
      
   extern void print_descend();
   extern void print_table_header(double TC, double qv, double qc);
   extern void print_table_line();

// Physical constants
   double pa_per_mb = 100.0;      // pa to mb conversion
   double temp_ice = 273.15;      // C to K conversion

// --------------------------------------------------------------------
// We now have our initialization parameters, so lets get going...
// --------------------------------------------------------------------


// Convert input parameters to SI units, and create new working
// variables. We don"t want to alter the orignial ones because we
// will use them later in our text print outs.
   double p = pMB * pa_per_mb;         // [Pa]
   double T = TC + temp_ice;           // [K]
   double dp = dpMB  * pa_per_mb;      // [Pa]
   double ptop = ptopMB * pa_per_mb;   // [Pa]
   double pibar = 0;                   // Unitless
   
// Define the initial "theta"
   double theta = compute_theta(T,p);

// 'n_cycles' & 'n_steps' are the number of loop iterations to drive
// the parcel in a given vertical direction. 'n_cycles' is a single
// direction and 'n_steps' is the full up & down iterations required.
   int n_cycles = ( (pMB-ptopMB)/dpMB );
   int n_steps = (2 * n_cycles) + 1;

// Set up 1D arrays for storing results
   double p_mb[n_steps],theta_K[n_steps],T_K[n_steps],qv_gkg[n_steps],
      qvs_gkg,qc_gkg[n_steps],qw_gkg[n_steps],rh[n_steps];
   
   
// Fill arrays with "1", this way we can diagnose any computational
// errors, by detecting null values.
   double null_val = -999;
   std::fill_n(p_mb,n_steps,null_val);
   std::fill_n(T_K,n_steps,null_val);
   std::fill_n(qv_gkg,n_steps,null_val);
   std::fill_n(qc_gkg,n_steps,null_val);
   std::fill_n(rh,n_steps,null_val);

// Store initial values (assuming no adjustment req'd)
   p_mb[0] = pMB;
   theta_K[0] = theta;
   T_K[0] = T;
   qv_gkg[0] = qv;
   qc_gkg[0] = qc;
   qw_gkg[0] = qw;
   rh[0] = rh_i;


// --------------------------------------------------------------------
// Initialization is complete. Starting to run the computations ...
// --------------------------------------------------------------------
// Ascend & Descend the parcel
//
// At this point we will 'push' the parcel up to the top of the
// atmosphere 'TOA' and then allow it to come back down.
// --------------------------------------------------------------------   
   
// Print the starting conditions.
   if ( console_output == 1){
      print_table_header(TC,qv,qc);
      print_parcel(p_mb[0],theta_K[0],T_K[0],qv_gkg[0],qc_gkg[0],rh[0]);
      printf("\n");
   } // End IF

// Loop thru the 'n_steps', this allows us to drive the parcel
// up and down in the atmosphere.

   int flag_1 = 0;   // ascend/descend flag   
   for ( int i = 1; i <= n_steps -1; i++ ){
   
// Check to see if we need to descent or not, if so print a message
   if ( i <= n_cycles ){
      p = p - dp;
      
   }else{
      if ( flag_1 == 0 && console_output == 1 ){print_descend();}
      
      flag_1 = 1;
      p = p + dp; // increase in pMB.
      
   } // end if/else, i <= cycles
   
// At this point we will drive the parcel up and down 
// through the atmosphere. We already have the pressure level
// incremented in the correct direction, as we just did that in the
// previous block.   
   
// Adjust the parcel. This is the real "meat & potatoes" ...   
// Assuming Dry Adiabatic ascent, theta, qv, qc don't change. This is
// an isobaric saturation adjustment.   
   adjusted_sat AA = compute_satadjust(theta,qv,qc,p);
  
// update the parcel's properties
   qv=AA.qv;
   qvs=AA.qvs;
   qc=AA.qc;
   pibar=AA.pibar;
   theta=AA.theta;  
  
// Record & store new variables, and set up the next cycle.
   p_mb[i] = p / pa_per_mb;
   theta_K[i] = theta;
   T_K[i] = theta * pibar;
   
   qv_gkg[i] = qv * 1.e3;
   qc_gkg[i] = qc  * 1.e3;
   
   rh[i]= qv_gkg[i] / (qvs*1.e3);

// Print data to user
   if ( console_output == 1){
      print_parcel(p_mb[i],theta_K[i],T_K[i],qv_gkg[i],qc_gkg[i],rh[i]);

// Break the lines up a bit for the user, this makes for easier reading
      int r = 5;
      if ( i%r == 0 ){printf("\n");}
   
   } // End IF, console output
   
   } // end for, [i], ascent & descent

   if ( console_output == 1){
      print_table_line();
   }



// Package up the computations and send them back to the main()
// controller.   
   packaged_computations AB;  // return structure
   
   for (int i=0;i <= n_steps-1; i++){
      AB.p_mb[i] = p_mb[i];
      AB.theta_K[i] = theta_K[i];
      AB.T_K[i] = T_K[i];
      AB.qv_gkg[i] = qv_gkg[i];
      AB.qc_gkg[i] = qc_gkg[i];
      AB.rh[i] = rh[i];
      AB.n_steps = n_steps;
   }

   
   return AB;
   
   
   } // All done!
