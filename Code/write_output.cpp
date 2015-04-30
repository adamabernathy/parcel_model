// 
// write_output.cpp
// Write the computational output to a CSV file, useful for plotting.
//
// REQUIRES THE C++11 LIBRARIES
// 
// Requires:   pMB, pressure in [mb]
//             theta_k, potential temperature in [K]
//             T_k, temperature in [K]
//             qv, liquid water vapor mixing ratio
//             qc, liquid water mixing ratio
//             rh_i, initial relative humidity
//             f, string, filename
// 
// Returns: void
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
   
   void write_output_csv(double p_mb[], double theta_K[], double T_K[],
                         double qv[], double qc[], double rh[],
                         int n_steps, int append_flag, 
                         const std::string& f){

   using namespace std;
   
   char delim = ',';
   
   ofstream results_file; // Define and open the text file for use.
   
// Decide if we need to open the file in append mode
   if ( append_flag == 1 ){
      results_file.open(f, ios::out | ios::app); // append mode

   }else{
// Since 'append_mode' is false, we will assume that the file is
// either new and we will also print the headers.
      results_file.open(f, ios::out);
   
      if (results_file.is_open()) {
         results_file << "# P_MB, T, TH, QV, QC" << endl;
      }else{
         cout << "File I/O Error! Check Output file.";
      } // End IF, file IO check
   
   } // End IF, append_flag
   
   
// We will check each time to ensure the text file is open before we
// attempt to write to it. This should help to catch errors, and is
// generally accepted as a best practice. Generally an error here is
// caused by the user not having writable access to the output path.
   
   
// Write the columns of data to the file
   for (int i=0; i <= n_steps -1; i++){

      if (results_file.is_open()) {
      
      results_file << p_mb[i] << delim
                   << T_K[i] << delim
                   << theta_K[i] << delim
                   << qv[i] << delim
                   << qc[i] << endl;
                   
      }else{
         cout << "File I/O Error! Check Output file.";
      }// End IF, file IO check
      
   
   } // End for, [i]


   results_file.close(); // Close the text file
      
   return;
   
   } // All done!