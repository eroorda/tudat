/*! \file unitTestOrbitalElementConversions.cpp
 *    Source file of unit test for the orbitalElementConversion, from Cartesian
 *    to Keplerian and viceversa. The first part of the code tests the code for
 *    elliptical, parabolic, hyperbolic and circular orbits. SI units are used.
 *    The second part of the code tests the code from Cartesian to Keplerian
 *    with the example 3.4 pag. 63 of the book "Fondamenti di Meccanica del Volo
 *    Spaziale" (G. Mengali, A.A. Quarta). In this part of the code, canonical
 *    units are used.
 *
 *    Path              : /Astrodynamics/States/
 *    Version           : 11
 *    Check status      : Checked
 *
 *    Author            : E. Iorfida
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : elisabetta_iorfida@yahoo.it
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Checker           : J. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Date created      : 3 December, 2010
 *    Last modified     : 16 February, 2011
 *
 *    References
 *      http://www.astro.uu.nl/~strous/AA/en/reken/kepler.html,
 *          last accessed: 16th February, 2011.
 *      Vallado, D. A., McClain, W. D. Fundamentals of astrodynamics and
 *          applications, 2nd Edition, Kluwer Academic Publishers,
 *          The Netherlands, 2004.
 *      Fortescue, P. W., et al. Spacecraft systems engineering, Third Edition,
 *          Wiley, England, 2003.
 *
 *    Notes
 *      Test runs code and verifies result against expected value.
 *      If the tested code is erroneous, the test function returns a boolean
 *      true; if the code is correct, the function returns a boolean false.
 *
 *    Copyright (c) 2010 Delft University of Technology.
 *
 *    This software is protected by national and international copyright.
 *    Any unauthorized use, reproduction or modification is unlawful and
 *    will be prosecuted. Commercial and non-private application of the
 *    software in any form is strictly prohibited unless otherwise granted
 *    by the authors.
 *
 *    The code is provided without any warranty; without even the implied
 *    warranty of merchantibility or fitness for a particular purpose.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      101203    E. Iorfida        First creation of the code.
 *      101208    E. Iorfida        Fulfillment of the code with the elliptical
 *                                  case.
 *      101208    E. Iorfida        Modified punctuation.
 *      101215    E. Iorfida        Added tolerance, added parabolic, circular
 *                                  and hyperbolic cases.
 *      101217    E. Iorfida        Added computeAbsoluteValue( ) in the errors
 *                                  computation, modified punctuation.
 *      101219    J. Melman         Put gravitational parameters in one place,
 *                                  changed first right ascension to
 *                                  15.0 * pi / 8.0, thereby exposing a
 *                                  possible error.
 *      110107    E. Iorfida        orbitalConversionBookExampleUnitTest.test
 *                                  added to this file, to have a unique unit
 *                                  test file for the conversion code. Also some
 *                                  punctuation modifications have been made.
 *      110109    J. Melman         Included test for semi-latus rectum of
 *                                  circular case. Gave the orbital angles less
 *                                  trivial values, and not almost exclusively
 *                                  in the first quadrant.
 *      110111    E. Iorfida        Updated to the new format of unitTest file
 *                                  and added hyperbolic equatorial case.
 *      110204    K. Kumar          Removed "vector" from naming.
 *      110216    K. Kumar          Added unit tests for new orbital element
 *                                  conversion functions.
 */

// Include statements.
#include "unitTestOrbitalElementConversions.h"

// Using declarations.
using std::cerr;
using std::endl;
using mathematics::computeAbsoluteValue;
using mathematics::raiseToIntegerPower;
using mathematics::MACHINE_PRECISION_DOUBLES;
using orbital_element_conversions::convertCartesianToKeplerianElements;
using orbital_element_conversions::convertKeplerianToCartesianElements;
using orbital_element_conversions::ConvertMeanAnomalyToEccentricAnomaly;
using orbital_element_conversions::
        ConvertMeanAnomalyToHyperbolicEccentricAnomaly;
using predefined_planets::createPredefinedPlanet;

//! Namespace for all unit tests.
namespace unit_tests
{

//! Test of orbitalElementConversion code.
bool testOrbitalElementConversions( )
{
    // Test of orbital element conversion methods imeplemented in Tudat.
    // Test 1: Test of Cartesian-to-Keplerian elements conversion and
    //         Keplerian-to-Cartesian elements conversion.
    // Test 2: Test of true anomaly to eccentric anomaly conversion.
    // Test 3: Test of eccentric anomaly to true anomaly conversion.
    // Test 4: Test of true anomaly to hyperbolic eccentric anomaly conversion.
    // Test 5: Test of hyperbolic eccentric anomaly to true anomaly conversion.
    // Test 6: Test of eccentric anomaly to mean anomaly conversion.
    // Test 7: Test of mean anomaly to eccentric anomaly conversion.
    // Test 8: Test of hyperbolic eccentric anomaly to mean anomaly conversion.
    // Test 9: Test of mean anomaly to hyperbolic eccentric anomaly conversion.
    // Test 10: Test of elapsed time to mean anomaly for elliptical orbits.
    // Test 11: Test of mean anomaly to elapsed time for elliptical orbits.
    // Test 12: Test of elapsed time to mean anomaly for hyperbolic orbits.
    // Test 13: Test of mean anomaly to elapsed time for hyperbolic orbits.

    // Test 1: Test of Cartesian-to-Keplerian elements conversion and
    //         Keplerian-to-Cartesian elements conversion.

    // Test result initialised to false.
    bool isOrbitalElementConversionErroneous = false;

    // Define tolerance.
    double errorTolerance_ = 1.0e2 * MACHINE_PRECISION_DOUBLES;

    // Create predefind Earth.
    CelestialBody* pointerToPredefinedEarth_ = new CelestialBody;
    pointerToPredefinedEarth_ = createPredefinedPlanet(
            predefined_planets::earth );

    // Create predefined Mars.
    CelestialBody* pointerToPredefinedMars_ = new CelestialBody;
    pointerToPredefinedMars_ = createPredefinedPlanet(
            predefined_planets::mars );

    // Create custom-defined Sun with central gravity field.
    CelestialBody* pointerToCustomDefinedSun_ = new CelestialBody;
    SphericalHarmonicsGravityField* pointerToSunCentralGravity_
            = new SphericalHarmonicsGravityField;
    pointerToSunCentralGravity_->setGravitationalParameter( 132712440018e8 );
    pointerToSunCentralGravity_->setDegreeOfExpansion( 0 );
    pointerToSunCentralGravity_->setOrderOfExpansion( 0 );
    pointerToCustomDefinedSun_
            ->setGravityFieldModel( pointerToSunCentralGravity_ );

    // Create custom-defined central body.
    CelestialBody* pointerToCustomDefinedBody_ = new CelestialBody;
    SphericalHarmonicsGravityField* pointerToCustomBodyCentralGravity_
            = new SphericalHarmonicsGravityField;
    pointerToCustomBodyCentralGravity_
            ->setGravitationalParameter( 1.0 );
    pointerToCustomBodyCentralGravity_->setDegreeOfExpansion( 0 );
    pointerToCustomBodyCentralGravity_->setOrderOfExpansion( 0 );
    pointerToCustomDefinedBody_
            ->setGravityFieldModel( pointerToCustomBodyCentralGravity_ );

    // *************************************************************************
    // Elliptical orbit case around the Earth.
    // *************************************************************************

    // From Keplerian to Cartesian.
    KeplerianElements* pointerToKeplerianEllipticalElements1_
            = new KeplerianElements;

    // Define Keplerian elements.
    pointerToKeplerianEllipticalElements1_->setSemiMajorAxis(
            unit_conversions::convertAstronomicalUnitsToMeters( 0.3 ) );
    pointerToKeplerianEllipticalElements1_->setEccentricity( 0.2 );
    pointerToKeplerianEllipticalElements1_->setInclination( M_PI / 4.0  );
    pointerToKeplerianEllipticalElements1_
            ->setArgumentOfPeriapsis( 4.0 * M_PI / 3.0 );
    pointerToKeplerianEllipticalElements1_
            ->setRightAscensionOfAscendingNode( M_PI / 8.0 );
    pointerToKeplerianEllipticalElements1_->setTrueAnomaly( M_PI / 3.0 );
    pointerToKeplerianEllipticalElements1_->setSemiLatusRectum(
            pointerToKeplerianEllipticalElements1_->getSemiMajorAxis( )
            * ( 1.0 - raiseToIntegerPower(
                    pointerToKeplerianEllipticalElements1_
                    ->getEccentricity( ), 2 ) ) );

    // Compute Cartesian elements.
    CartesianElements* pointerToCartesianEllipticalElements_
            = new CartesianElements;

    pointerToCartesianEllipticalElements_ =
            convertKeplerianToCartesianElements(
            pointerToKeplerianEllipticalElements1_,
            pointerToPredefinedEarth_ );

    // From Cartesian to Keplerian.
    // Compute Keplerian elements.
    KeplerianElements* pointerToKeplerianEllipticalElements2_
            = new KeplerianElements;

    pointerToKeplerianEllipticalElements2_ =
            convertCartesianToKeplerianElements(
                    pointerToCartesianEllipticalElements_,
                    pointerToPredefinedEarth_ );

    // Set test result to false if the output Keplerian elements of the
    // conversion from Cartesian to Keplerian are equal to the input Keplerian
    // elements of the conversion from Keplerian to Cartesian, within a
    // tolerance limit.
    if ( computeAbsoluteValue( ( pointerToKeplerianEllipticalElements2_
                                 ->getSemiMajorAxis( ) -
                 pointerToKeplerianEllipticalElements1_->getSemiMajorAxis( ) ) /
               pointerToKeplerianEllipticalElements1_->getSemiMajorAxis( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianEllipticalElements2_
                               ->getEccentricity( ) -
               pointerToKeplerianEllipticalElements1_->getEccentricity( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianEllipticalElements2_
                               ->getInclination( ) -
               pointerToKeplerianEllipticalElements1_->getInclination( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianEllipticalElements2_
                               ->getArgumentOfPeriapsis( ) -
               pointerToKeplerianEllipticalElements1_
               ->getArgumentOfPeriapsis( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianEllipticalElements2_->
               getRightAscensionOfAscendingNode( ) -
               pointerToKeplerianEllipticalElements1_->
               getRightAscensionOfAscendingNode( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianEllipticalElements2_
                               ->getTrueAnomaly( ) -
               pointerToKeplerianEllipticalElements1_->getTrueAnomaly( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( ( pointerToKeplerianEllipticalElements2_
                                 ->getSemiLatusRectum( ) -
                 pointerToKeplerianEllipticalElements1_
                 ->getSemiLatusRectum( ) ) /
               pointerToKeplerianEllipticalElements1_
               ->getSemiLatusRectum( ) ) >=
         errorTolerance_ )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The orbital element conversion for an elliptical orbit is "
             << "erroneous." << endl;
    }

    // *************************************************************************
    // Parabolic orbit case around Mars.
    // *************************************************************************

    // From Keplerian to Cartesian.
    KeplerianElements* pointerToKeplerianParabolicElements1_
            = new KeplerianElements;

    // Define Keplerian elements.
    pointerToKeplerianParabolicElements1_->setSemiLatusRectum(
            unit_conversions::convertAstronomicalUnitsToMeters( 4.0 ) );
    pointerToKeplerianParabolicElements1_->setEccentricity( 1.0 );
    pointerToKeplerianParabolicElements1_->setInclination( M_PI / 6.0 );
    pointerToKeplerianParabolicElements1_->setArgumentOfPeriapsis( M_PI / 8.0 );
    pointerToKeplerianParabolicElements1_->setRightAscensionOfAscendingNode(
            8.0 * M_PI / 7.0 );
    pointerToKeplerianParabolicElements1_->setTrueAnomaly( 7.0 * M_PI / 4.0 );

    // Compute Cartesian elements.
    CartesianElements* pointerToCartesianParabolicElements_
            = new CartesianElements;

    pointerToCartesianParabolicElements_ =
            convertKeplerianToCartesianElements(
            pointerToKeplerianParabolicElements1_, pointerToPredefinedMars_ );

    // From Cartesian to Keplerian.
    // Compute Keplerian elements.
    KeplerianElements* pointerToKeplerianParabolicElements2_
            = new KeplerianElements;

    pointerToKeplerianParabolicElements2_ =
            convertCartesianToKeplerianElements(
            pointerToCartesianParabolicElements_, pointerToPredefinedMars_ );

    // Set test result to false if the output Keplerian elements of the
    // conversion from Cartesian to Keplerian are equal to the input Keplerian
    // elements of the conversion from Keplerian to Cartesian, within a
    // tolerance limit.
    if ( computeAbsoluteValue( ( pointerToKeplerianParabolicElements2_
                                 ->getSemiLatusRectum( ) -
                 pointerToKeplerianParabolicElements1_->getSemiLatusRectum( ) ) /
               pointerToKeplerianParabolicElements1_->getSemiLatusRectum( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianParabolicElements2_
                               ->getEccentricity( ) -
               pointerToKeplerianParabolicElements1_->getEccentricity( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianParabolicElements2_
                               ->getInclination( ) -
               pointerToKeplerianParabolicElements1_->getInclination( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianParabolicElements2_
                               ->getArgumentOfPeriapsis( ) -
               pointerToKeplerianParabolicElements1_->getArgumentOfPeriapsis( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianParabolicElements2_
                               ->getRightAscensionOfAscendingNode( ) -
               pointerToKeplerianParabolicElements1_
               ->getRightAscensionOfAscendingNode( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianParabolicElements2_
                               ->getTrueAnomaly( ) -
               pointerToKeplerianParabolicElements1_->getTrueAnomaly( ) ) >=
         errorTolerance_ )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The orbital element conversion for a parabolic orbit is "
             << "erroneous." << endl;
    }

    // *************************************************************************
    // Circular equatorial orbit case around the Earth.
    // *************************************************************************

    // From Keplerian to Cartesian.
    KeplerianElements* pointerToKeplerianCircularElements1_
            = new KeplerianElements;

    // Define Keplerian elements.
    pointerToKeplerianCircularElements1_->setSemiMajorAxis(
            unit_conversions::convertAstronomicalUnitsToMeters( 0.1 ) );
    pointerToKeplerianCircularElements1_->setEccentricity( 0.0 );
    pointerToKeplerianCircularElements1_->setInclination( 0.0 );
    pointerToKeplerianCircularElements1_->setArgumentOfPeriapsis( 0.0 );
    pointerToKeplerianCircularElements1_
            ->setRightAscensionOfAscendingNode( 0.0 );
    pointerToKeplerianCircularElements1_->setTrueAnomaly( M_PI / 4.0 );

    // Compute Cartesian elements.
    CartesianElements* pointerToCartesianCircularElements_
            = new CartesianElements;

    pointerToCartesianCircularElements_ =
            convertKeplerianToCartesianElements(
            pointerToKeplerianCircularElements1_, pointerToPredefinedEarth_ );

    // From Cartesian to Keplerian.
    // Compute Keplerian elements.
    KeplerianElements* pointerToKeplerianCircularElements2_
            = new KeplerianElements;

    pointerToKeplerianCircularElements2_ =
            convertCartesianToKeplerianElements(
            pointerToCartesianCircularElements_, pointerToPredefinedEarth_ );

    // Set test result to false if the output Keplerian elements of the
    // conversion from Cartesian to Keplerian are equal to the input Keplerian
    // elements of the conversion from Keplerian to Cartesian, within a
    // tolerance limit.
    if ( computeAbsoluteValue( ( pointerToKeplerianCircularElements2_
                                 ->getSemiMajorAxis( ) -
                 pointerToKeplerianCircularElements1_->getSemiMajorAxis( ) ) /
               pointerToKeplerianCircularElements1_->getSemiMajorAxis( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianCircularElements2_
                               ->getEccentricity( ) -
               pointerToKeplerianCircularElements1_->getEccentricity( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianCircularElements2_
                               ->getInclination( ) -
               pointerToKeplerianCircularElements1_->getInclination( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianCircularElements2_
                               ->getArgumentOfPeriapsis( ) -
               pointerToKeplerianCircularElements1_->getArgumentOfPeriapsis( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianCircularElements2_
                               ->getRightAscensionOfAscendingNode( ) -
               pointerToKeplerianCircularElements1_->getRightAscensionOfAscendingNode( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianCircularElements2_
                               ->getTrueAnomaly( ) -
               pointerToKeplerianCircularElements1_->getTrueAnomaly( ) ) >=
         errorTolerance_ )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The orbital element conversion for a circular orbit is "
             << "erroneous." << endl;
    }

    // *************************************************************************
    // Hyperbolic equatorial orbit case around the Sun.
    // *************************************************************************

    // From Keplerian to Cartesian.
    KeplerianElements* pointerToKeplerianHyperbolicElements1_
            = new KeplerianElements;

    // Define Keplerian elements.
    pointerToKeplerianHyperbolicElements1_->setSemiMajorAxis(
            unit_conversions::convertAstronomicalUnitsToMeters( -3.0 ) );
    pointerToKeplerianHyperbolicElements1_->setEccentricity( 2.0 );
    pointerToKeplerianHyperbolicElements1_->setInclination( 0.0 );
    pointerToKeplerianHyperbolicElements1_->setArgumentOfPeriapsis(
            11.0 * M_PI / 8.0 );
    pointerToKeplerianHyperbolicElements1_->setRightAscensionOfAscendingNode(
            0.0 );
    pointerToKeplerianHyperbolicElements1_->setTrueAnomaly( 9.0 * M_PI / 16.0 );

    // Compute Cartesian elements.
    CartesianElements* pointerToCartesianHyperbolicElements_
            = new CartesianElements;

    pointerToCartesianHyperbolicElements_ =
            convertKeplerianToCartesianElements(
            pointerToKeplerianHyperbolicElements1_,
            pointerToCustomDefinedSun_ );

    // From Cartesian to Keplerian.
    // Compute Keplerian elements.
    KeplerianElements* pointerToKeplerianHyperbolicElements2_
            = new KeplerianElements;

    pointerToKeplerianHyperbolicElements2_ =
            convertCartesianToKeplerianElements(
            pointerToCartesianHyperbolicElements_,
            pointerToCustomDefinedSun_ );

    // Set test result to false if the output Keplerian elements of the
    // conversion from Cartesian to Keplerian are equal to the input Keplerian
    // elements of the conversion from Keplerian to Cartesian, within a
    // tolerance limit.
    if ( computeAbsoluteValue( ( pointerToKeplerianHyperbolicElements2_
                                 ->getSemiMajorAxis( ) -
                 pointerToKeplerianHyperbolicElements1_->getSemiMajorAxis( ) ) /
               pointerToKeplerianHyperbolicElements1_->getSemiMajorAxis( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianHyperbolicElements2_
                               ->getEccentricity( ) -
               pointerToKeplerianHyperbolicElements1_->getEccentricity( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianHyperbolicElements2_
                               ->getInclination( ) -
               pointerToKeplerianHyperbolicElements1_->getInclination( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianHyperbolicElements2_
                               ->getArgumentOfPeriapsis( ) -
               pointerToKeplerianHyperbolicElements1_->getArgumentOfPeriapsis( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianHyperbolicElements2_
                               ->getRightAscensionOfAscendingNode( ) -
               pointerToKeplerianHyperbolicElements1_
               ->getRightAscensionOfAscendingNode( ) ) >=
         errorTolerance_ ||
         computeAbsoluteValue( pointerToKeplerianHyperbolicElements2_
                               ->getTrueAnomaly( ) -
               pointerToKeplerianHyperbolicElements1_->getTrueAnomaly( ) ) >=
         errorTolerance_ )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The orbital element conversion for a hyperbolic orbit is "
             << "erroneous." << endl;
    }

    // *************************************************************************
    // Book example.
    // *************************************************************************

    // Define tolerance, related to the precision of the values in the book.
    double errorToleranceBookExample_ = 1.0e-04;

    // From Cartesian to Keplerian.
    CartesianElements* pointerToCartesianElements_ = new CartesianElements;

    // Define Cartesian elements.
    // Position expressed in canonical units.
    pointerToCartesianElements_->setCartesianElementX( 1.0 );
    pointerToCartesianElements_->setCartesianElementY( 2.0 );
    pointerToCartesianElements_->setCartesianElementZ( 1.0 );

    // Velocity expressed in canonical units.
    pointerToCartesianElements_->setCartesianElementXDot( -0.25 );
    pointerToCartesianElements_->setCartesianElementYDot( -0.25 );
    pointerToCartesianElements_->setCartesianElementZDot( 0.5 );

    // Define Keplerian elements.
    KeplerianElements* pointerToKeplerianElements_ = new KeplerianElements;

    // Convert Cartesian to Keplerian elements.
    // Gravitational parameter is equal to 1 in the applied units.
    pointerToKeplerianElements_ =
            convertCartesianToKeplerianElements(
                    pointerToCartesianElements_, pointerToCustomDefinedBody_ );

    // Set test result to false if the output Keplerian elements of the
    // conversion from Cartesian to Keplerian are equal to the output Keplerian
    // elements of the exercise, within a tolerance limit.
    if ( computeAbsoluteValue( pointerToKeplerianElements_
                               ->getSemiMajorAxis( ) - 2.265 ) >=
         errorToleranceBookExample_ ||
         computeAbsoluteValue( pointerToKeplerianElements_
                               ->getEccentricity( ) - 0.185 ) >=
         errorToleranceBookExample_ ||
         computeAbsoluteValue( pointerToKeplerianElements_
                               ->getInclination( ) - 1.401 ) >=
         errorToleranceBookExample_ ||
         computeAbsoluteValue( pointerToKeplerianElements_
                               ->getArgumentOfPeriapsis( ) - 2.6143 ) >=
         errorToleranceBookExample_ ||
         computeAbsoluteValue( pointerToKeplerianElements_
                               ->getRightAscensionOfAscendingNode( ) -
               1.0304 ) >= errorToleranceBookExample_ ||
         computeAbsoluteValue( pointerToKeplerianElements_
                               ->getTrueAnomaly( ) - 4.0959 ) >=
         errorToleranceBookExample_ )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The orbital element conversion for the book example is "
             << "erroneous." << endl;
    }

    // Test 2: Test of true anomaly to eccentric anomaly conversion.
    // Source: http://www.astro.uu.nl/~strous/AA/en/reken/kepler.html.

    // Set tolerance for conversion.
    double toleranceOrbitalElementConversion = 1e-8;

    // Set eccentricity.
    double eccentricity = 0.01671;

    // Set true anomaly.
    double trueAnomaly = unit_conversions::
                         convertDegreesToRadians( 61.6755418 );

    // Compute eccentric anomaly.
    double eccentricAnomaly = orbital_element_conversions::
                              convertTrueAnomalyToEccentricAnomaly(
                                      trueAnomaly, eccentricity );

    // Check if computed eccentric anomaly is equal to reference value.
    if ( computeAbsoluteValue( eccentricAnomaly - 1.061789204 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of true anomaly to eccentric anomaly is "
             << "erroneous as the computed eccentric anomaly after applying "
             << "the conversion ( "
             << unit_conversions::convertRadiansToDegrees( eccentricAnomaly )
             << " ) does not match the expected value of the eccentric "
             << "anomaly ( "
             << unit_conversions::convertRadiansToDegrees( 1.061789204 )
             << " ) " << endl;
    }

    // Test 3: Test of eccentric anomaly to true anomaly conversion.
    // Source: http://www.astro.uu.nl/~strous/AA/en/reken/kepler.html.

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-8;

    // Set eccentricity.
    eccentricity = 0.01671;

    // Set eccentric anomaly.
    eccentricAnomaly = 1.061789204;

    // Compute true anomaly.
    trueAnomaly = orbital_element_conversions::
                  convertEccentricAnomalyToTrueAnomaly(
                          eccentricAnomaly, eccentricity );

    // Check if computed true anomaly is equal to reference value.
    if ( computeAbsoluteValue( trueAnomaly - unit_conversions::
                               convertDegreesToRadians( 61.6755418 ) )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of eccentric anomaly to true anomaly is "
             << "erroneous as the computed true anomaly after applying "
             << "the conversion ( "
             << unit_conversions::convertRadiansToDegrees( trueAnomaly )
             << " ) does not match the expected value of the true anomaly "
             << "( " << 61.6755418 << " ) " << endl;
    }

    // Test 4: Test of true anomaly to hyperbolic eccentric anomaly conversion.
    // Source: ( Fortescue, 2003 ).

    // Set tolerance for orbital element conversion.
    toleranceOrbitalElementConversion = 1e-4;

    // Set eccentricity.
    eccentricity = 3.0;

    // Set true anomaly.
    trueAnomaly = 0.5291;

    // Compute hyperbolic eccentric anomaly.
    double hyperbolicEccentricAnomaly
            = orbital_element_conversions::
              convertTrueAnomalyToHyperbolicEccentricAnomaly(
                      trueAnomaly, eccentricity );

    // Check if computed hyperbolic eccentric anomaly is equal to reference
    // value.
    if ( computeAbsoluteValue( hyperbolicEccentricAnomaly - 0.3879 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of true anomaly to hyperbolic eccentric "
             << "anomaly is erroneous as the computed hyperbolic eccentric "
             << "anomaly after applying the conversion ( "
             << unit_conversions::convertRadiansToDegrees(
                     hyperbolicEccentricAnomaly )
             << " ) does not match the expected value of the hyperbolic "
             << "eccentric anomaly ( "
             << unit_conversions::convertRadiansToDegrees( 0.3879 )
             << " ) " << endl;
    }

    // Test 5: Test of hyperbolic eccentric anomaly to true anomaly conversion.
    // Source: ( Fortescue, 2003 ).

    // Set tolerance for orbital element conversion.
    toleranceOrbitalElementConversion = 1e-4;

    // Set eccentricity.
    eccentricity = 3.0;

    // Set hyperbolic eccentric anomaly.
    hyperbolicEccentricAnomaly = 0.3879;

    // Compute true anomaly.
    trueAnomaly = orbital_element_conversions::
                  convertHyperbolicEccentricAnomalyToTrueAnomaly(
                          hyperbolicEccentricAnomaly, eccentricity );

    // Check if computed true anomaly is equal to reference value.
    if ( computeAbsoluteValue( trueAnomaly - 0.5291 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of hyperbolic eccentric anomaly to true "
             << "anomaly is erroneous as the computed true anomaly after "
             << "applying the conversion ( "
             << unit_conversions::convertRadiansToDegrees(
                    trueAnomaly )
             << " ) does not match the expected value of the true anomaly "
             << "( "
             << unit_conversions::convertRadiansToDegrees( 0.5291 )
             << " ) " << endl;
    }

    // Test 6: Test of eccentric anomaly to mean anomaly conversion.
    // Source: ( Vallado, 2004 ).

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-8;

    // Set eccentricity.
    eccentricity = 0.01671;

    // Set eccentric anomaly.
    eccentricAnomaly = 1.061789204;

    // Compute mean anomaly.
    double meanAnomaly = orbital_element_conversions::
                         convertEccentricAnomalyToMeanAnomaly(
                                 eccentricAnomaly, eccentricity );

    // Check if computed mean anomaly is equal to reference value.
    if ( computeAbsoluteValue( meanAnomaly - unit_conversions::
                               convertDegreesToRadians( 60.0 ) )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of eccentric anomaly to mean anomaly is "
             << "erroneous as the computed mean anomaly after applying "
             << "the conversion ( "
             << unit_conversions::convertRadiansToDegrees( meanAnomaly )
             << " ) does not match the expected value of the mean anomaly "
             << "( " << 60.0 << " ) " << endl;
    }

    // Test 7: Test of mean anomaly to eccentric anomaly conversion.
    // Source: ( Vallado, 2004 ).

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-8;

    // Set eccentricity.
    eccentricity = 0.01671;

    // Set mean anomaly.
    meanAnomaly = unit_conversions::convertDegreesToRadians( 60.0 );

    // Create object for mean anomaly to eccentric anomaly conversion.
    orbital_element_conversions::ConvertMeanAnomalyToEccentricAnomaly
            convertMeanAnomalyToEccentricAnomaly;

    // Create pointer to Newton-Raphson object.
    NewtonRaphson* pointerToNewtonRaphson = new NewtonRaphson;

    // Set eccentricity.
    convertMeanAnomalyToEccentricAnomaly.setEccentricity( 0.01671 );

    // Set mean anomaly.
    convertMeanAnomalyToEccentricAnomaly.setMeanAnomaly( meanAnomaly );

    // Set Newton-Raphson method.
    convertMeanAnomalyToEccentricAnomaly
            .setNewtonRaphson( pointerToNewtonRaphson );

    // Compute eccentric anomaly.
    eccentricAnomaly = convertMeanAnomalyToEccentricAnomaly.convert( );

    // Check if computed eccentric anomaly is equal to reference value.
    if ( computeAbsoluteValue( eccentricAnomaly - 1.061789204 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of mean anomaly to eccentric anomaly is "
             << "erroneous as the computed eccentric anomaly after applying "
             << "the conversion ( "
             << unit_conversions::convertRadiansToDegrees( eccentricAnomaly )
             << " ) does not match the expected value of the eccentric anomaly "
             << "( "
             << unit_conversions::convertRadiansToDegrees( 1.061789204 )
             << " ) " << endl;
    }

    // Test 8: Test of hyperbolic eccentric anomaly to mean anomaly conversion.
    // Source: ( Vallado, 2004 ).

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-8;

    // Set eccentricity.
    eccentricity = 2.4;

    // Set hyperbolic eccentric anomaly.
    hyperbolicEccentricAnomaly = 1.6013761449;

    // Compute mean anomaly.
    meanAnomaly = orbital_element_conversions::
                  convertHyperbolicEccentricAnomalyToMeanAnomaly(
                          hyperbolicEccentricAnomaly, eccentricity );

    // Check if computed mean anomaly is equal to reference value.
    if ( computeAbsoluteValue( meanAnomaly - unit_conversions::
                               convertDegreesToRadians( 235.4  ) )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of hyperbolic eccentric anomaly to mean "
             << "anomaly is erroneous as the computed mean anomaly after "
             << "applying the conversion ( "
             << unit_conversions::
                    convertRadiansToDegrees( hyperbolicEccentricAnomaly )
             << " ) does not match the expected value of the mean anomaly "
             << "( " << 235.4 << " ) " << endl;
    }

    // Test 9: Test of mean anomaly to hyperbolic eccentric anomaly conversion.
    // Source: ( Vallado, 2004 ).

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-8;

    // Set eccentricity.
    eccentricity = 2.4;

    // Set mean anomaly.
    meanAnomaly = unit_conversions::convertDegreesToRadians( 235.4 );

    // Create object for mean anomaly to hyperbolic eccentric anomaly
    // conversion.
    orbital_element_conversions::ConvertMeanAnomalyToHyperbolicEccentricAnomaly
            convertMeanAnomalyToHyperbolicEccentricAnomaly;

    // Set eccentricity.
    convertMeanAnomalyToHyperbolicEccentricAnomaly.setEccentricity( 2.4 );

    // Set mean anomaly.
    convertMeanAnomalyToHyperbolicEccentricAnomaly
            .setMeanAnomaly( meanAnomaly );

    // Set Newton-Raphson method.
    convertMeanAnomalyToHyperbolicEccentricAnomaly
            .setNewtonRaphson( pointerToNewtonRaphson );

    // Compute hyperbolic eccentric anomaly.
    hyperbolicEccentricAnomaly = convertMeanAnomalyToHyperbolicEccentricAnomaly
                                 .convert( );

    // Check if computed hyperbolic eccentric anomaly is equal to reference
    // value.
    if ( computeAbsoluteValue( hyperbolicEccentricAnomaly - 1.6013761449 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of mean anomaly to hyperbolic eccentric "
             << "anomaly is erroneous as the computed hyperbolic eccentric "
             << "anomaly after applying the conversion ( "
             << unit_conversions::
                    convertRadiansToDegrees( hyperbolicEccentricAnomaly )
             << " ) does not match the expected value of the hyperbolic "
             << "eccentric anomaly ( "
             << unit_conversions::convertRadiansToDegrees( 1.6013761449 )
             << " ) " << endl;
    }

    // Test 10: Test of elapsed time to mean anomaly for elliptical orbits.

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-11;

    // Set elapsed time.
    double elapsedTime = 4000.0;

    // Create pre-defined Earth.
    CelestialBody* pointerToEarth
            = predefined_planets::createPredefinedPlanet(
                    predefined_planets::earth );

    // Set semi-major axis.
    double semiMajorAxis = unit_conversions::
                           convertKilometersToMeters( 2500.0 );

    // Compute mean anomaly.
    meanAnomaly = orbital_element_conversions::
                  convertElapsedTimeToMeanAnomalyForEllipticalOrbits(
                          elapsedTime, pointerToEarth, semiMajorAxis );

    // Check if computed mean anomaly is equal to reference value.
    if ( computeAbsoluteValue( meanAnomaly - 20.203139659369779 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of elapsed time to mean anomaly is erroneous "
             << "as the computed mean anomaly after applying the conversion ( "
             << unit_conversions::
                    convertRadiansToDegrees( meanAnomaly )
             << " ) does not match the expected value of the mean anomaly ( "
             << unit_conversions::convertRadiansToDegrees( 20.203139659369779 )
             << " ) " << endl;
    }

    // Test 11: Test of mean anomaly to elapsed time for elliptical orbits.

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-11;

    // Set mean anomaly.
    meanAnomaly = 20.203139659369779;

    // Set pre-defined Earth.
    pointerToEarth = predefined_planets::createPredefinedPlanet(
            predefined_planets::earth );

    // Set semi-major axis.
    semiMajorAxis = unit_conversions::convertKilometersToMeters( 2500.0 );

    // Compute elapsed time.
    elapsedTime = orbital_element_conversions::
                  convertMeanAnomalyToElapsedTimeForEllipticalOrbits(
                          meanAnomaly, pointerToEarth, semiMajorAxis );

    // Check if computed elapsed time is equal to reference value.
    if ( computeAbsoluteValue( elapsedTime - 4000.0 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of mean anomaly to elapsed time is erroneous "
             << "as the computed elapsed time after applying the conversion ( "
             << elapsedTime
             << " ) does not match the expected value of the elapsed time ( "
             << 4000.0 << " ) " << endl;
    }

    // Test 12: Test of elapsed time to mean anomaly for hyperbolic orbits.

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-11;

    // Set elapsed time.
    elapsedTime = 1000.0;

    // Create pre-defined Earth.
    pointerToEarth = predefined_planets::createPredefinedPlanet(
            predefined_planets::earth );

    // Set semi-major axis.
    semiMajorAxis = unit_conversions::convertKilometersToMeters( -40000.0 );

    // Compute mean anomaly.
    meanAnomaly = orbital_element_conversions::
                  convertElapsedTimeToMeanAnomalyForHyperbolicOrbits(
                          elapsedTime, pointerToEarth, semiMajorAxis );

    // Check if computed mean anomaly is equal to reference value.
    if ( computeAbsoluteValue( meanAnomaly - 0.078918514294413 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of elapsed time to mean anomaly is erroneous "
             << "as the computed mean anomaly after applying the conversion ( "
             << unit_conversions::
                    convertRadiansToDegrees( meanAnomaly )
             << " ) does not match the expected value of the mean anomaly ( "
             << unit_conversions::convertRadiansToDegrees( 0.078918514294413 )
             << " ) " << endl;
    }

    // Test 13: Test of mean anomaly to elapsed time for hyperbolic orbits.

    // Set tolerance for conversion.
    toleranceOrbitalElementConversion = 1e-11;

    // Set mean anomaly.
    meanAnomaly = 0.078918514294413;

    // Set pre-defined Earth.
    pointerToEarth = predefined_planets::createPredefinedPlanet(
            predefined_planets::earth );

    // Set semi-major axis.
    semiMajorAxis = unit_conversions::convertKilometersToMeters( -40000.0 );

    // Compute elapsed time.
    elapsedTime = orbital_element_conversions::
                  convertMeanAnomalyToElapsedTimeForHyperbolicOrbits(
                          meanAnomaly, pointerToEarth, semiMajorAxis );

    // Check if computed elapsed time is equal to reference value.
    if ( computeAbsoluteValue( elapsedTime - 1000.0 )
        > toleranceOrbitalElementConversion )
    {
        isOrbitalElementConversionErroneous = true;

        cerr << "The conversion of mean anomaly to elapsed time is erroneous "
             << "as the computed elapsed time after applying the conversion ( "
             << elapsedTime
             << " ) does not match the expected value of the elapsed time ( "
             << 1000.0 << " ) " << endl;
    }

    return isOrbitalElementConversionErroneous;
}

}

// End of file.