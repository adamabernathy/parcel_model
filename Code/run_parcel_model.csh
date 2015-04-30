#!/bin/csh

echo 'Initializing Parcel Model'

# -------------------
# Initialization Parameters
# -------------------

set pMB = '1000.0'     # starting pressure in millibars
set TC = '20.0'        # starting temperature
set qv = '14.8e-3'     # water vapor mix ratio, using thermo const.
set qvs = '0.0'        # environmental water vapor mix ratio, using thermo const.
set qc = '0.0'         # liquid water mix ratio, assume dry atmosphere
set qw = ${qv}         # vapor saturation mixing ratio, same as 'qv'
set rh = '0.5'         # initial relative humidity value

set dp = '10.0'        # ascent/descent increment pMB value in millibars
set ptop = '500.0'     # maximum pressure ascent level in millibars

set do_output = '1'    # write output to text file? [1] Yes, [0] No
set do_console = '1'   # print to console? [1] Yes, [0] No

set pert = '0.01'      # perturbation scalar, 1 to -Inf
set ntrials = '10'     # no. of trials to run

# -------------------

# Execute
# Make sure you have the current build here!
./p_model_R4_build_2 ${do_output} ${do_console} ${pert} ${ntrials} ${pMB} ${dp} ${ptop} ${TC} ${qv} ${qc} ${qw} ${qvs} ${rh}

