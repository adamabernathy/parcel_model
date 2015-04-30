// 
// compute_des_dt_pa.cpp
// Calculates change in saturation water vapor pressure over 
// water in Pascals
// 
// Requires: Temperature in Kelvin
// 
// Returns: desdT_Pa or the saturation water vapor pressure over 
// water in Pa
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

   double compute_des_dt_pa(double T){

// 'L' is the latent heat of vaporization at 0 degrees C in J/kg,
// and 'Rv' is the gas constant for water vapor in J/(kg*K)
      double L = 2.5e6;
      double Rv = 461.5;


      double AA; // this is a working variable for 'des/dT'
      double BB = compute_esat_pa(T);
   
      AA = (L/Rv) * ( BB / (T*T) );

      return AA;

   } // All Done!

		  


