//
//  Compulations.c
//
//  Copyright © 2015 Mike Diehl. All rights reserved.
//
/*
 Copyright (c) 2014 Mike Diehl - ifixcompressors@gmail.com
 
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

#include "Compulations.h"
#include "UnitConversion.h"
#include "Math.h"

double motorPowerKW(double volts,
                    double amps,
                    double powerFactor)
{
    double kw = 0.0;

    if (volts > 0.0 && amps > 0.0 && powerFactor > 0.0)
    {
        kw = (volts * amps * powerFactor * 1.732) / 1000.0;
    }

    return kw;
}

double oilFloodedScrewOperatingTempF(double inletTempF,
                                     double dischargePressurePSI,
                                     double ambientPSIA)
{
    double opTempF = 0.0;

    double psiaLine = dischargePressurePSI + ambientPSIA;
    
    double ambientTemp = celsiusFromFahrenheit(inletTempF);
    
    if (dischargePressurePSI < 0)
    {
        opTempF = 6.1115 * exp((22.452 * ambientTemp) / (272.55 + ambientTemp));
    }
    else
    {
        opTempF = 6.1121 * exp((17.502 * ambientTemp) / (240.9 + ambientTemp));
    }
    
    opTempF = opTempF * (psiaLine / ambientPSIA);
    
    double pdpHi = log(opTempF / 6.1121) * 240.9 / (17.502 - log(opTempF / 6.1121));
    double pdpLo = log(opTempF / 6.1115) * 272.55 / (22.452 - log(opTempF / 6.115));
    
    if (pdpHi < 0)
    {
        opTempF = pdpLo;
    }
    else
    {
        opTempF = pdpHi;
    }

    return fahrenheitFromCelsius(opTempF);
}

double ambientPSIAForAltitudeInFeet(double altitude)
{
    double ambientPSIA = 0.0;
    
    ambientPSIA = (101325.0 * pow((1 - 0.0000225577 * metersFromFeet(altitude)), 5.25588)) / 6894.75729;
    
    return ambientPSIA;
}

double altitudeFeetFromPSIA(double psia)
{
    double altitude = 0.0;
    
    double mBar = kPaFromPSI(psia) * 10.0;
    
    double pstd = 1013.25;
    
    altitude =  (1 - pow((mBar/pstd), 0.190284)) * 145366.45;
    
    return altitude;

}

double pumpupTimeInSeconds(double tankSizeGallons,
                           double flowRateCFM,
                           double startPressurePSIG,
                           double endPressurePSIG,
                           double ambientAtmosphericPressurePSIA)
{
    double time = 0.0;

    double deltaP = endPressurePSIG - startPressurePSIG;

    if(tankSizeGallons > 0.0 && flowRateCFM > 0.0 && deltaP > 0.0)
    {
        double numerator = (cubicFeetFromGallons(tankSizeGallons) * deltaP);
        double denominator = (ambientAtmosphericPressurePSIA * flowRateCFM);
        time = ((numerator / denominator) * 60.0);
    }

    return time;
}

double leakRateCFM(double tankSizeGallons,
                   double startPSIG,
                   double endPSIG,
                   double ambientPSIA,
                   double decayTimeMins)
{
    double cfm = 0.0;
    
    if (tankSizeGallons > 0.0 && decayTimeMins > 0.0 && startPSIG > 0.0 && ambientPSIA > 0.0)
    {
        double tankSizeCF = cubicFeetFromGallons(tankSizeGallons);
        double deltaP = (startPSIG - endPSIG);
        double flowCorrection = 1.0;

        // Compressed Air Challenge says we need flow correction for wide pressure bands, specifically if low is 50% or less than high.
        if(endPSIG <= (startPSIG / 2.0))
        {
            flowCorrection = 1.25;
        }

        double numerator = tankSizeCF * deltaP * flowCorrection;
        double denominator = decayTimeMins * ambientPSIA;

        cfm = numerator / denominator;
    }
    return cfm;
}

double refillRateCFM(double storageCF,
                     double startPressurePSIG,
                     double endPressurePSIG,
                     double refillTimeMins,
                     double ambientPreesurePSIA)
{
    double cfm = 0.0;

    double deltaP = endPressurePSIG - startPressurePSIG;
    
    if (deltaP > 0.0 && storageCF > 0.0 && refillTimeMins > 0.0 && ambientPreesurePSIA > 0.0)
    {
        double numerator = storageCF * deltaP;
        double denominator = refillTimeMins * ambientPreesurePSIA;
        cfm = numerator / denominator;
    }
    
    return cfm;
}

double systemCapacityCF(double unloadedTimeSec,
                        double loadedTimeSec,
                        double unloadPressurePSIG,
                        double loadPressurePSIG,
                        double ratedFlowCFM,
                        double ambientPreesurePSIA)
{
    double volumeCF = 0.0;

    // Need these later, but we do it now to simplify > 0 for all vars.
    double totalTime = unloadedTimeSec + loadedTimeSec;
    double deltaP = unloadPressurePSIG - loadPressurePSIG;

    if (totalTime > 0.0 && deltaP > 0.0 && ratedFlowCFM > 0.0 && ambientPreesurePSIA > 0.0)
    {
        double volumeCF = 0.0;

        double numerator = loadedTimeSec * unloadedTimeSec * ratedFlowCFM * ambientPreesurePSIA;
        double denominator = totalTime * deltaP;

        volumeCF = numerator / denominator;
    }
    return volumeCF;
}

// Secondary storage
double eventStorageCF(double eventDurationMins,
                      double cfmRequiredForEvent,
                      double meteredCFMSupplied,
                      double ambientPSIA,
                      double initialPressurePSIG,
                      double minPressureForEventPSIG)
{
    double volumeCF = 0.0;
    
    double deltaP = initialPressurePSIG - minPressureForEventPSIG;
    double deltaF = cfmRequiredForEvent - meteredCFMSupplied;
    
    if (eventDurationMins > 0.0 && deltaF > 0.0 && deltaP > 0.0 && ambientPSIA > 0.0)
    {
        double numerator = eventDurationMins * deltaF * ambientPSIA;
        volumeCF = numerator / deltaP;
    }
    
    return volumeCF;
}

// Vapor pressure of water
double vaporPressureOfWaterInPsiForTemp(double degreesFahrenheit)
{
    // Return the vapor pressure of water using Antoine Equation
    // Good for temp range between 1-374 C
    double tempC = celsiusFromFahrenheit(degreesFahrenheit);
    
    double conA, conB, conC;
    
    if( tempC <= 100.0 )
    {
        conA = 8.07131;
        conB = 1730.63;
        conC = 233.426;
    }
    else
    {
        conA = 8.14019;
        conB = 1810.94;
        conC = 244.485;
        
    }
    
    double exponent = conA - (conB / (conC + tempC));
    double vapMMHG = pow(10, exponent);
    double vapPSIG = vapMMHG * 0.0193367747; //mmHG to PSI

    return vapPSIG;
}

// ACFM SCFM conversions
double scfmFromACFM(double acfm,
                    double standardAmbientPressurePSI,
                    double standardAmbientTempF,
                    double standardAmbientRH,
                    double siteAmbientPressurePSI,
                    double siteAmbientTempF,
                    double siteAmbientRH,
                    double inletPressurePSI)
{
    double scfm = 0.0;
    double rhNumerator = standardAmbientPressurePSI - (standardAmbientRH * vaporPressureOfWaterInPsiForTemp(standardAmbientTempF));
    double rhDenominator = siteAmbientPressurePSI - (siteAmbientRH * vaporPressureOfWaterInPsiForTemp(siteAmbientTempF));
    double rhMultiplier = rhNumerator / rhDenominator;
    double tempMultiplier = rankineFromFahrenheit(siteAmbientTempF) / rankineFromFahrenheit(standardAmbientTempF);
    double inletPressureMultiplier = siteAmbientPressurePSI / inletPressurePSI;
    scfm = (acfm / rhMultiplier) / tempMultiplier / inletPressureMultiplier;
    return scfm;
}

double acfmFromSCFM(double scfm,
                    double standardAmbientPressurePSI,
                    double standardAmbientTempF,
                    double standardAmbientRH,
                    double siteAmbientPressurePSI,
                    double siteAmbientTempF,
                    double siteAmbientRH,
                    double inletPressurePSI)
{
    double acfm = 0.0;
    double rhNumerator = standardAmbientPressurePSI - (standardAmbientRH * vaporPressureOfWaterInPsiForTemp(standardAmbientTempF));
    double rhDenominator = siteAmbientPressurePSI - (siteAmbientRH * vaporPressureOfWaterInPsiForTemp(siteAmbientTempF));
    double rhMultiplier = rhNumerator / rhDenominator;
    double tempMultiplier = rankineFromFahrenheit(siteAmbientTempF) / rankineFromFahrenheit(standardAmbientTempF);
    double inletPressureMultiplier = siteAmbientPressurePSI / inletPressurePSI;
    acfm = scfm * rhMultiplier * tempMultiplier * inletPressureMultiplier;
    return acfm;
}

// Determine pipe size in inches to obtain a specific velocity for site conditions.
double pipeDiamInForVelocity(double flowRateCFM,
                             double velocityFPS,
                             double linePressurePSI,
                             double ambientAtmosphericPressurePSI)
{
    double pipeDiameterIn = 0.0;
    
    if (flowRateCFM > 0.0 && velocityFPS > 0.0 && linePressurePSI > 0.0)
    {
        double numerator = (144.0 * flowRateCFM * ambientAtmosphericPressurePSI);
        double denominator = (velocityFPS * 60.0 * (linePressurePSI + ambientAtmosphericPressurePSI));
        double areaInSq = numerator / denominator;
        pipeDiameterIn = sqrt(areaInSq / M_PI) * 2.0;
    }

    return pipeDiameterIn;
}

// Mapped values
double mappedValue(double inputValue,
                   double inputMin,
                   double inputMax,
                   double outputMin,
                   double outputMax)
{
    double mapped = 0.0;

    double slope = 1.0 * (outputMax - outputMin) / (inputMax - inputMin);
    mapped = outputMin + slope * (inputValue - inputMin);

    return mapped;
}

// Gear speed
double gearSpeedFeetPerMinute(double gearDiameterInches,
                              double rpm)
{
    double speed = 0.0;
    speed = (M_PI / 12.0) * gearDiameterInches * rpm;
    return speed;
}
