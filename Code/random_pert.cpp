// 
// random_pert.cpp
// Generates a random perturbation for the variability support.
// 
// Requires: scalar, 0.0 to 1.0
// 
// Returns: random perturbation
//
// ver. 1.0
// 
// -- Change log --
// April 27, 2015 - Initial Release
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
   
   } // All done!
