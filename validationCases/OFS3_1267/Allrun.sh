#!/bin/sh
cd ${0%/*} || exit 1    # Run from this directory
. $WM_PROJECT_DIR/bin/tools/RunFunctions
rm log*
rm -r ./processor*
rm -rf ./0.0*
restore0Dir

# Set application name
application=$(getApplication)
runApplication blockMesh
runApplication setFields
runApplication setExprFields
runApplication decomposePar
mpirun -np 4 $application -parallel > log.$application &

# runApplication $application &
# tail -f log.cmiFoam_dev | grep --line-buffered Time -w

#------------------------------------------------------------------------------
