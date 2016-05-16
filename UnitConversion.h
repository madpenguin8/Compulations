//
//  UnitConversion.h
//
//
/*
 Copyright (c) 2014 Mike Diehl - ifixcompressors@gmail.com
 
 This file is part of Compulations.
 
 Compulations is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Compulations is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Compulations.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "math.h"

// Motor speed
static inline double frequencyFromSynchronousSpeedAndPoles(double speed, int poles){return (poles * speed) / 120.0;};
static inline int numberOfPolesFromSynchronousSpeedAndFrequency(double speed, double hz){return (int)(120 * hz) / speed;};
static inline double synchronousMotorSpeedForFrequencyAndPoles(double hz, int poles){return (120.0 * hz) / poles;};

// Temperature
static inline double celsiusFromFahrenheit(double f){return (f - 32.0) * (5.0f / 9.0);};
static inline double celsiusFromKelvin(double k){return k - 273.15;};
static inline double fahrenheitFromCelsius(double c){return  (c * 1.8) + 32.0;};
static inline double fahrenheitFromKelvin(double k){return (k - 273.15) * 1.8 + 32.0;};
static inline double fahrenheitFromRankine(double r){return r - 459.67;};
static inline double kelvinFromCelsius(double c){return c + 273.15;};
static inline double kelvinFromFahrenheit(double f){return ((f - 32.0) * (5.0f / 9.0)) + 273.15;};
static inline double rankineFromFahrenheit(double f){return f + 459.67;};

// Pressure
static inline double barFromPSI(double psi){return psi / 14.5037738;};
static inline double inH20FromkPa(double kPa){return kPa * 4.01474213311;};
static inline double inHgFromMmHg(double mmHg){return mmHg / 25.399999705;};
static inline double inHgFromkPa(double kPa){return kPa * 0.295299802;};
static inline double inHgFromPSI(double psi){return psi * 2.036025;};
static inline double kPaFromInH2O(double inH2O){return inH2O / 4.01474213311;};
static inline double kPaFromInHg(double inHg){return inHg / 0.295299802;};
static inline double kPaFromMmH2O(double mmH2O){return mmH2O / 101.971621298;};
static inline double kPaFromMmHg(double mmHg){return mmHg / 7.5006183;};
static inline double kPaFromPSI(double PSI){return PSI / 0.14503773773020923;};
static inline double mmH2OFromkPa(double kPa){return kPa * 101.971621298;};
static inline double mmHgFromInHg(double inHg){return inHg * 25.399999705;};
static inline double mmHgFromkPa(double kPa){return kPa * 7.5006183;};
static inline double psiFromBar(double bar){return bar * 14.5037738;};
static inline double psiFromInHg(double inHg){return inHg / 2.036025;};
static inline double psiFromkPa(double kPa){return kPa * 0.14503773773020923;};

// Length
static inline double inFromMillimeter(double mm){return mm / 25.4;};
static inline double feetFromMeters(double meters){return meters * 3.2808399;};
static inline double metersFromFeet(double feet){return feet / 3.2808399;};
static inline double mmFromInch(double inch){return inch * 25.4;};

// Volume
static inline double cubicFeetFromGallons(double gal){return gal / 7.48051948;};
static inline double cubicFeetFromCubicMeters(double m){return m * 35.3146667;};
static inline double cubicMetersFromCubicFeet(double ft){return ft / 35.3146667;};
static inline double gallonsFromCubicFeet(double ft){return ft * 7.48051948;};
static inline double gallonsFromLiters(double liters){return liters / 3.78541178;};
static inline double litersFromGallons(double gallons){return gallons * 3.78541178;};

// Power
static inline double hpFromKw(double kw){return kw / 0.745699872;};
static inline double kwFromHP(double hp){return hp * 0.745699872;};

// Voltage
static inline double voltsPeakFromVoltsRms(double vrms){return vrms * sqrt(2.0);};
static inline double voltsRmsFromVoltsPeak(double vp){return vp / sqrt(2.0);};

// Amps
static inline double ampsFLAFromWyeDelta(double wda){return wda * sqrt(3.0);};
static inline double ampsWyeDeltaFromFLA(double fla){return fla / sqrt(3.0);};

// Flow
static inline double cfmFromM3minute(double m3m){return m3m * 35.3146667;};
static inline double m3MinuteFromCFM(double cfm){return cfm / 35.3146667;};

// Force
static inline double newtonsFromPounds(double pounds){return pounds * 4.44822162825;};
static inline double poundsFromNewtons(double newtons){return newtons / 4.44822162825;};
