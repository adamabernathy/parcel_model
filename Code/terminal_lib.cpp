// 
// terminal_lib.cpp
// Collection of user print messages.
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



// Need to foreward declare these, since some of these internal
// functions are dependent on them.

   void print_parcel(double p_mb, double theta_K, double T_K,
      double qv, double qc, double rh);
      
   void print_descend();
   void print_table_header(double TC, double qv, double qc);
   void print_table_line();

// --------------------------------------------------------------------

   void print_parcel(double p_mb, double theta_K, double T_K,
      double qv, double qc, double rh){

      printf("%4.0f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",
         p_mb,theta_K,T_K,qv,qc);

      return;
      
   } // End print_line
   
   
// Prints the 'Descending' marker
   void print_descend(){
      
      printf("------------------------------------------\n");
      printf("                DECENDING                 \n");
      printf("------------------------------------------\n");
      
      return;
   
   } // End print_descend
   
   
// Print parcel table header
   void print_table_header(double TC, double qv, double qc){  
   
      printf("\n\nParameters & Units\n\n");
      printf("Var\tDescription\t\tUnit\n");
      print_table_line();
      
      printf("P\tPressure\t\t[mb]\n");
      printf("TH\tTheta\t\t\t[K]\n");
      printf("T_{C}\tTemperature\t\t[C]\n");
      printf("Q_{v}\tWater Vap Mix Rat.\t[g*kg^-1]\n");
      printf("Q_{c}\tLiq Water Mix Rat.\t[g*kg^-1]\n");
      print_table_line();

      printf("\nINITIAL CONDITIONS...\n");
      printf("T_{C}: %3.2f\n",TC);
      printf("Q_{v}: %3.2f\n",qv);
      printf("Q_{c}: %3.2f\n",qc);

      printf("\nCOMPUTATIONS...\n\n");
      printf("P\tTH\tT\tqv\tqc");
      print_table_line();
   
      return;
   
   } // End print_table_header
   
   
// Print table divider line
   void print_table_line(){
      printf("\n------------------------------------------\n");
      
      return;
   }