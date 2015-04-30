// 
// satadjust.cpp
//
// Please ensure you have the entire *.cpp collection from:
//    https://github.com/whokilledkermit/parcel_model
// before using this function.
//
// This function performs an isobaric moist adiabatic adjustment.
// The final state is either subsaturated with no liquied water 
// present or exactly saturated with liquid water present.
// 
// Units: SI(MKS)
// 
// Requires:
// TH: potential temperature, theta (K)
// QV: mixing ratio of water vapor, q_v (kg/kg)
// QC: mixing ratio of liquid water, q_c (kg/kg)
// 
// Returns: struct adjusted_sat
// theta: adjusted potential temperature, theta^{n+1} (K)
// qv: adjusted mixing ratio of water vapor, q_v^{n+1} (kg/kg)
// qc: adjusted mixing ratio of liquid water, q_c^{n+1} (kg/kg)
// qvs: saturation mixing ration, q_vs^{n+1} (kg/kg) for TH1, PBAR
// pibar: Exner function, pi (non-dimensional pressure)
//
// ver. 2.0
// 
// -- Change log --
// March 17, 2015 - Build 2 Release. Build 1 entirely depreciated.
//
// -- Licence --
// Two Dimensinal Parcel Model with Variability by Adam C. Abernathy
// and Jeffery Fitzgerald is licensed under a Creative Commons 
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You can read the full licence and get the most recent code at
// https://github.com/whokilledkermit/parcel_model
//
// The idea for this algorithm was developed by 
// Steven Krueger, steven.krueger@utah.edu and later extended by the
// current authors of this program. 
//
// --------------------------------------------------------------------


   adjusted_sat compute_satadjust(double theta,double qv,
                                  double qc,double pbar){
   
   extern void print_table_line(); 
   
   //using namespace std;  // for diagnostics
     
// Variables we will use later
   double tstar,es1,alpha,theta_e,theta_fac,theta_1,qv_sat,
          qv1,qc1,qvs1,dT;   

// physical constants
   double hlf = 2.5e6;      // latent heat
   double cp = 1004.0;      // specific heat of dry air
   double rgas = 287.0;     // gas constant for dry air
   double pzero = 100000.0; // pressure of atmosphere at sea level, [Pa]

// iteration parameters, stop iterating once T adjustment 
// is less than dT_crit
   int do_it = 1;
   int itt = 1;
   
   double ittmax = 10; // max number of iterations allowed, failsafe
   double dT_crit = 0.001; // numerical resolution

// --------------------------------------------------------------------
// Computations
// --------------------------------------------------------------------

// 'pbar' is a (hydrostatic) reference pressure field, we will use this
// in the Exner function to compute 'pibar'. 'pi' at environmental
// temperature. 
   double pibar = pow( (pbar / pzero),( rgas/cp ) );

   double gamma = hlf / ( cp*pibar );

   double theta_star = theta;
   double qv_star = qv;
   double qw = qv + qc;


// Start the computation loop. We will stay in here until the 'dT_crit'
// is met at the requested resolution.
   while (do_it == 1){

      tstar = theta_star * pibar; // temp star
      es1 = compute_esat_pa( tstar );

      alpha = compute_alpha(pbar,pibar,tstar);
      theta_fac = gamma / ( 1 + gamma*alpha );
      qv_sat = 0.622 / ( pbar-es1 ) * es1;

      theta_1 = theta_star + theta_fac * ( qv_star - qv_sat );

      qv1 = qv_sat + alpha * ( theta_1-theta_star );
      qc1 = qw - qv1;
      
      //qvs1 = qv1; // fix this so RH works!
      qvs1 = qv_sat + alpha * ( theta_1-theta_star );

      if( qc1 < 0 ){
         qc1 = 0;
         qv1 = qw;
         theta_1 = theta_star + gamma * ( qv_star-qv1 );
         qvs1 = qv_sat + alpha * ( theta_1-theta_star );
      } // end if

// T adjustment for this iteration
      dT = (theta_1 - theta_star) * pibar;
      
      if( fabs(dT) < dT_crit || itt == ittmax ){
         do_it = 0; // get out of the loop, all criteria is met.
      } // end if

// Lets find out if the failsafe of 'ittmax' was hit, Need to tell the
// user, since the computation has lost integrity at this point.
      if ( itt == ittmax ){
         print_table_line();
         printf("             FAILSAFE REACHED!");
         print_table_line();
      } // End IF, ittmax


// Reset for the next round of the adjustment, since at this point
// 'dT_crit' was not met.
      theta_star = theta_1;
      qv_star = qv1;

      itt++;

   } // End while loop


// Package up the variables and send them back
   adjusted_sat rtn;
   
   rtn.theta = theta_1;
   rtn.qv = qv1;
   rtn.qc = qc1;
   rtn.qvs = qvs1;
   rtn.pibar = pibar;
    
   return rtn;

   } // end function
