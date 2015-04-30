// 
// compute_esat_pa.cpp
// Computes the alpha parameter for the satadjust.cpp function.
// 
// Calculates saturation water vapor pressure over water in Pascals
//
// Requires: T, Temperature in Kelvin
// Returns:  e_sat, saturation water vapor pressure 
//                  over water in Pascals
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

   double compute_esat_pa(double T){

// Break apart the equation and compute each part.
      double AA = 23.832241;
      double AB = 5.02808;
      double AC = log10(T);
      double AD = 1.3816e-7;

      double BA = 11.344;
      double BB = 0.0303998 * T;
      double B = pow(10,(BA-BB));

      double C = 8.1328e-3;

      double DA = 3.49149;
      double DB = 1302.8844 / T;
      double D = pow(10,(DA - DB));  

      double E = 2949.076/T;

// Put all the parts together    
      double EQN = 100 * pow(10, (AA-AB*AC-AD*B+C*D-E) );

      return EQN;

   } // All done!


