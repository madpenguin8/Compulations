//
//  Compulations.h
//
//
//
/*
 Copyright (c) 2016 Mike Diehl - ifixcompressors@gmail.com
 
 This file is part of Compulations.
 
 Compulations is free software: you can redistribute it and/or modify
 it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Compulations is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU LESSER GENERAL PUBLIC LICENSE
 along with Compulations.  If not, see <http://www.gnu.org/licenses/>.
 */

// Power
double motorPowerKW(double volts,
                    double amps,
                    double powerFactor);

// Temperatures
double oilFloodedScrewOperatingTempF(double inletTempF,
                                     double dischargePressurePSIG,
                                     double ambientPSIA);

// Pressure-Altitude relationship
double ambientPSIAForAltitudeInFeet(double altitude);
double altitudeFeetFromPSIA(double psia);

// Pumpup Time
double pumpupTimeInSeconds(double tankSizeGallons,
                           double flowRateCFM,
                           double startPressurePSIG,
                           double endPressurePSIG,
                           double ambientAtmosphericPressurePSIA);

// Leak Rate
double leakRateCFM(double tankSizeGallons,
                   double startPSIG,
                   double endPSIG,
                   double ambientPSIA,
                   double decayTimeMins);

// Refill Rate
double refillRateCFM(double storageCF,
                     double startPressurePSIG,
                     double endPressurePSIG,
                     double refillTimeMins,
                     double ambientPreesurePSIA);

// System Capacity Estimator
double systemCapacityCubicFeetByCycleTime(double unloadedTimeSec,
                                          double loadedTimeSec,
                                          double unloadPressurePSIG,
                                          double loadPressurePSIG,
                                          double ratedFlowCFM,
                                          double ambientPreesurePSIA);

// Secondary storage
double eventStorageCubicFeet(double eventDurationMins,
                             double cfmRequiredForEvent,
                             double meteredCFMSupplied,
                             double ambientPSIA,
                             double initialPressurePSIG,
                             double minPressureForEventPSIG);

// ACFM SCFM conversions
double vaporPressureOfWaterInPsiForTemp(double degreesFahrenheit);

double scfmFromACFM(double acfm,
                    double standardAmbientPressurePSI,
                    double standardAmbientTempF,
                    double standardAmbientRH,
                    double siteAmbientPressurePSI,
                    double siteAmbientTempF,
                    double siteAmbientRH,
                    double inletPressurePSI);

double acfmFromSCFM(double scfm,
                    double standardAmbientPressurePSI,
                    double standardAmbientTempF,
                    double standardAmbientRH,
                    double siteAmbientPressurePSI,
                    double siteAmbientTempF,
                    double siteAmbientRH,
                    double inletPressurePSI);

// Diameter in inches for flow and velocity
double pipeDiameterInchesForVelocity(double flowRateCFM,
                                     double velocityFPS,
                                     double linePressurePSIG,
                                     double ambientPreesurePSIA);

// Velocity of air for pipe diameter
double velocityInPipeFPS(double flowRateCFM,
                         double linePressurePSIG,
                         double ambientPreesurePSIA,
                         double pipeDiameterIn);

// Density of air lbs/ft^3
double airDensityPoundsPerCubicFoot(double linePressurePSIG,
                                    double ambientPreesurePSIA,
                                    double airTemperatureF);

// Mapping Function, useful for sensors
double mappedValue(double inputValue,
                   double inputMin,
                   double inputMax,
                   double outputMin,
                   double outputMax);

// Gear speed along pitch line in ft/min
double gearSpeedFeetPerMinute(double gearDiameterInches,
                              double rpm);

// Oil Carryover Volume
double oilCarryoverGallons(double flowRateCFM,
                           double concentrationPPM,
                           double operatingHours,
                           double oilSpecificGravity);

// Oil Carryover Concentration
double oilCarryoverConcentrationPPM(double flowRateCFM,
                                    double oilLossGallons,
                                    double operatingHours,
                                    double oilSpecificGravity);
