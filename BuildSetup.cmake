#############################################################################
# cmake build setup for Marlin
#
# For building lcio with cmake type:
# (1) $ mkdir build
# (2) $ cd build
# (3) $ cmake -C ../BuildSetup.cmake ..
# (4) $ make install
#
# @author Jan Engels, DESY
#############################################################################


#############################################################################
# Setup path variables
#############################################################################

# ILC_HOME
SET( ILC_HOME "/afs/desy.de/group/it/ilcsoft/v01-01_beta"
    CACHE PATH "Path to ILC Software" FORCE )

# Path to LCIO
SET( LCIO_HOME "${ILC_HOME}/lcio/HEAD"
    CACHE PATH "Path to LCIO" FORCE )

# Path to LCCD
SET( LCCD_HOME "${ILC_HOME}/lccd/HEAD"
    CACHE PATH "Path to LCCD" FORCE )

# Path to GEAR
SET( GEAR_HOME "${ILC_HOME}/gear/HEAD"
    CACHE PATH "Path to GEAR" FORCE )

# Path to CLHEP
SET( CLHEP_HOME "${ILC_HOME}/CLHEP/2.0.2.2"
    CACHE PATH "Path to CLHEP" FORCE )

# Path to RAIDA
SET( RAIDA_HOME "${ILC_HOME}/RAIDA/HEAD"
    CACHE PATH "Path to RAIDA" FORCE )

# CMake Modules Path
SET( CMAKE_MODULE_PATH "${ILC_HOME}/CMakeModules/v01-00"
    CACHE PATH "Path to CMake Modules" FORCE )

###############################################
# Project options
###############################################

# optional packages
SET( BUILD_WITH "GEAR;LCCD;CLHEP;RAIDA"
    CACHE STRING "Build Marlin with these optional packages" FORCE )

#SET( BUILD_SHARED_LIBS OFF CACHE BOOL "Set to OFF to build static libraries" FORCE )
#SET( INSTALL_DOC OFF CACHE BOOL "Set to OFF to skip build/install Documentation" FORCE )
#SET( MARLIN_USE_DLL OFF CACHE BOOL "Set to OFF to build Marlin without DLL support" FORCE )
SET( MARLIN_GUI ON CACHE BOOL "Set to ON to build Marlin GUI" FORCE )

# set cmake build type, default value is: RelWithDebInfo
# possible options are: None Debug Release RelWithDebInfo MinSizeRel
#SET( CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE )

###############################################
# Advanced options
###############################################

# installation path for Marlin
#SET( CMAKE_INSTALL_PREFIX "/foo/bar" CACHE STRING "Where to install Marlin" FORCE )
