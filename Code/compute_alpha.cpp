// 
// compute_alpha.cpp
// Computes the alpha parameter for the satadjust.cpp function.
// 
// Requires: pbar,pibar,tstar
// 
// Returns: alpha
//
// ver. 1.0
// 
// -- Change log --
// April 23, 2015 - Initial Release
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
   
   double compute_alpha(double pbar, double pibar, double tstar){

// Break into parts to solve   
      double A = compute_des_dt_pa(tstar);
      double B = 0.622;
      double C = pibar * pbar;
   
      double DA = pbar - compute_esat_pa(tstar);
      double D = DA * DA;
   
// Put the parts together
      double alpha = A * B * C / D;                    
     
      return alpha;
   
   } // All done!