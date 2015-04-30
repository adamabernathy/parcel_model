// 
// compute_alpha.cpp
// This function calculates the potential temperature which is known 
// as theta.
// 
// Requires: T, temperature in Kelvin
//           p, pressure in Pa
// 
// Returns:  theta, potential temperature in 
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
  
   double compute_theta(double T,double p){

   double theta,pi;

   double cp=1004.0;   // specific heat of dry air at constant pressure
   double rgas=287.0;  // gas constant for dry air
   double p0=100000.0; // pressure at sea level in Pa

   /*
   pi is called the nondimensional pressure or the Exner function. 
   This is derived from the hydrostatic reference.
   */

   pi = pow( ( (p)/p0 ),(rgas/cp) );
   theta = (T) / pi;
   
   return theta;

   } // All done!
  
