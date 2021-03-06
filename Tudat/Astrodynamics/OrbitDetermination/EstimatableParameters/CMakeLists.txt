 #    Copyright (c) 2010-2016, Delft University of Technology
 #    All rigths reserved
 #
 #    This file is part of the Tudat. Redistribution and use in source and
 #    binary forms, with or without modification, are permitted exclusively
 #    under the terms of the Modified BSD license. You should have received
 #    a copy of the license with this file. If not, please or visit:
 #    http://tudat.tudelft.nl/LICENSE.
 #
 #    Changelog
 #      YYMMDD    Author            Comment
 #      110820    S.M. Persson      File created.
 #      111025    K. Kumar          Adapted file to work with Revision 194.
 #      111026    K. Kumar          Adapted file so all headers show in project tree in Qt Creator.
 #

# Set the source files.
set(ESTIMATABLE_PARAMETERS_SOURCES
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/estimatableParameter.cpp"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/sphericalHarmonicSineCoefficients.cpp"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/sphericalHarmonicCosineCoefficients.cpp"
)

# Set the header files.
set(ESTIMATABLE_PARAMETERS_HEADERS
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/estimatableParameter.h"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/gravitationalParameter.h"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/initialTranslationalState.h"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/radiationPressureCoefficient.h"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/sphericalHarmonicSineCoefficients.h"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/sphericalHarmonicCosineCoefficients.h"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/constantRotationRate.h"
  "${SRCROOT}${ESTIMATABLEPARAMETERSDIR}/constantRotationalOrientation.h"
)

# Add static libraries.
add_library(tudat_estimatable_parameters STATIC ${ESTIMATABLE_PARAMETERS_SOURCES} ${ESTIMATABLE_PARAMETERS_HEADERS})
setup_tudat_library_target(tudat_estimatable_parameters "${SRCROOT}{ESTIMATABLEPARAMETERSDIR}")

