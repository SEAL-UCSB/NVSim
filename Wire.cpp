/*******************************************************************************
* Copyright (c) 2012-2013, The Microsystems Design Labratory (MDL)
* Department of Computer Science and Engineering, The Pennsylvania State University
* Exascale Computing Lab, Hewlett-Packard Company
* All rights reserved.
* 
* This source code is part of NVSim - An area, timing and power model for both 
* volatile (e.g., SRAM, DRAM) and non-volatile memory (e.g., PCRAM, STT-RAM, ReRAM, 
* SLC NAND Flash). The source code is free and you can redistribute and/or modify it
* by providing that the following conditions are met:
* 
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
* 
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
* Author list: 
*   Cong Xu	    ( Email: czx102 at psu dot edu 
*                     Website: http://www.cse.psu.edu/~czx102/ )
*   Xiangyu Dong    ( Email: xydong at cse dot psu dot edu
*                     Website: http://www.cse.psu.edu/~xydong/ )
*******************************************************************************/


#include "Wire.h"
#include "global.h"
#include "formula.h"
#include "constant.h"
#include <math.h>

Wire::Wire() {
	// TODO Auto-generated constructor stub
	initialized = false;
	senseAmp = NULL;
}

Wire::~Wire() {
	// TODO Auto-generated destructor stub
	if (senseAmp)
		delete senseAmp;
}

void Wire::Initialize(int _featureSizeInNano, WireType _wireType, WireRepeaterType _wireRepeaterType,
		int _temperature, bool _isLowSwing) {
	if (initialized) {
		/* reload the new input, clear the previous setting */
		initialized = false;
		if (senseAmp)
			delete senseAmp;
		senseAmp = NULL;
	}

	featureSizeInNano = _featureSizeInNano;
	featureSize = _featureSizeInNano * 1e-9;
	wireType = _wireType;
	wireRepeaterType = _wireRepeaterType;
	temperature = _temperature;
	isLowSwing = _isLowSwing;

	if (wireRepeaterType != repeated_none && isLowSwing) {
		cout << "[Wire] Error: Low Swing is not supported for repeated wires!" << endl;
		exit(-1);
	}

	double copper_resistivity = COPPER_RESISTIVITY;
	/* Initialize copper resistivity */

	if (_featureSizeInNano <= 22) {
		featureSize = 22e-9;
		switch (wireType) {
		case local_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.55;
			wirePitch = 2 * featureSize;
			aspectRatio = 1.9;
			ildThickness = aspectRatio * featureSize;
			copper_resistivity =  6.0e-8;
			break;
		case local_conservative:
			barrierThickness = 0.0021e-6;
			horizontalDielectric = 3;
			wirePitch = 2 * featureSize;
			aspectRatio = 1.9;
			ildThickness = aspectRatio * featureSize;
			copper_resistivity =  6.0e-8;
			break;
		case semi_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.55;
			wirePitch = 4 * featureSize;
			aspectRatio = 1.9;
			ildThickness = 2 * aspectRatio * featureSize;
			copper_resistivity =  6.0e-8;
			break;
		case semi_conservative:
			barrierThickness = 0.0021e-6;
			horizontalDielectric = 3;
			wirePitch = 4 * featureSize;
			aspectRatio = 1.9;
			ildThickness = 2 * aspectRatio * featureSize;
			copper_resistivity =  6.0e-8;
			break;
		case global_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.55;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.34;
			ildThickness = 0.42e-6 * 22 / 32;
			copper_resistivity =  3.0e-8; /* TO-DO confusing data in ITRS */
			break;
		case global_conservative:
			barrierThickness = 0.0063e-6; /* TO-DO No data in ITRS */
			horizontalDielectric = 3;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.34;
			ildThickness = 0.385e-6 * 22 / 32;
			copper_resistivity =  3.0e-8; /* TO-DO confusing data in ITRS */
			break;
		default:	/* dram_wordline */
			/* TO-DO CACTI does not have a detailed model for it */
			barrierThickness = 0e-6;
			horizontalDielectric = 0;
			wirePitch = 2 * featureSize;
			aspectRatio = 0;
			ildThickness = 0e-6;
		}
	} else if (_featureSizeInNano <= 32) {
		featureSize = 32e-9;
		switch (wireType) {
		case local_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.82;
			wirePitch = 2 * featureSize;
			aspectRatio = 1.8;
			ildThickness = aspectRatio * featureSize;
			copper_resistivity =  5.0e-8;
			break;
		case local_conservative:
			barrierThickness = 0.0026e-6;
			horizontalDielectric = 3.16;
			wirePitch = 2 * featureSize;
			aspectRatio = 1.8;
			ildThickness = aspectRatio * featureSize;
			copper_resistivity =  5.0e-8;
			break;
		case semi_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.82;
			wirePitch = 4 * featureSize;
			aspectRatio = 1.9;
			ildThickness = 2 * aspectRatio * featureSize;
			copper_resistivity =  5.0e-8;
			break;
		case semi_conservative:
			barrierThickness = 0.0026e-6;
			horizontalDielectric = 3.16;
			wirePitch = 4 * featureSize;
			aspectRatio = 1.9;
			ildThickness = 2 * aspectRatio * featureSize;
			copper_resistivity =  5.0e-8;
			break;
		case global_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.82;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.34;
			ildThickness = 0.42e-6;
			copper_resistivity =  2.5e-8; /* TO-DO confusing data in ITRS */
			break;
		case global_conservative:
			barrierThickness = 0.0078e-6; /* TO-DO No data in ITRS */
			horizontalDielectric = 3.16;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.34;
			ildThickness = 0.385e-6;
			copper_resistivity =  2.5e-8; /* TO-DO confusing data in ITRS */
			break;
		default:	/* dram_wordline */
			/* TO-DO CACTI does not have a detailed model for it */
			barrierThickness = 0e-6;
			horizontalDielectric = 0;
			wirePitch = 2 * featureSize;
			aspectRatio = 0;
			ildThickness = 0e-6;
		}
	} else if (_featureSizeInNano <= 45) {
		featureSize = 45e-9;
		switch (wireType) {
		case local_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.6;
			wirePitch = 0.102e-6;
			aspectRatio = 1.8;
			ildThickness = 0.0918e-6;
			copper_resistivity =  4.08e-8;
			break;
		case local_conservative:
			barrierThickness = 0.0033e-6;
			horizontalDielectric = 2.9;
			wirePitch = 0.102e-6;
			aspectRatio = 1.8;
			ildThickness = 0.0918e-6;
			copper_resistivity =  4.08e-8;
			break;
		case semi_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.6;
			wirePitch = 4 * featureSize;
			aspectRatio = 1.8;
			ildThickness = 2 * aspectRatio * featureSize;
			copper_resistivity =  4.08e-8;
			break;
		case semi_conservative:
			barrierThickness = 0.0033e-6;
			horizontalDielectric = 2.9;
			wirePitch = 4 * featureSize;
			aspectRatio = 1.8;
			ildThickness = 2 * aspectRatio * featureSize;
			copper_resistivity =  4.08e-8;
			break;
		case global_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.6;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.34;
			ildThickness = 0.63e-6;
			copper_resistivity =  2.06e-8;
			break;
		case global_conservative:
			barrierThickness = 0.01e-6;
			horizontalDielectric = 2.9;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.34;
			ildThickness = 0.55e-6;
			copper_resistivity =  2.06e-8;
			break;
		default:	/* dram_wordline */
			/* TO-DO CACTI does not have a detailed model for it */
			barrierThickness = 0e-6;
			horizontalDielectric = 0;
			wirePitch = 2 * featureSize;
			aspectRatio = 0;
			ildThickness = 0e-6;
		}
	} else if (_featureSizeInNano <= 65) {
		featureSize = 65e-9;
		switch (wireType) {
		case local_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.303;
			wirePitch = 2.5* featureSize;
			aspectRatio = 2.7;
			ildThickness = 0.405e-6;
			break;
		case local_conservative:
			barrierThickness = 0.006e-6;
			horizontalDielectric = 2.734;
			wirePitch = 2.5* featureSize;
			aspectRatio = 2.0;
			ildThickness = 0.405e-6;
			break;
		case semi_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.303;
			wirePitch = 4 * featureSize;
			aspectRatio = 2.7;
			ildThickness = 0.405e-6;
			break;
		case semi_conservative:
			barrierThickness = 0.006e-6;
			horizontalDielectric = 2.734;
			wirePitch = 4 * featureSize;
			aspectRatio = 2.0;
			ildThickness = 0.405e-6;
			break;
		case global_aggressive:
			barrierThickness = 0.00e-6;
			horizontalDielectric = 2.303;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.8;
			ildThickness = 0.81e-6;
			break;
		case global_conservative:
			barrierThickness = 0.006e-6;
			horizontalDielectric = 2.734;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.2;
			ildThickness = 0.77e-6;
			break;
		default:	/* dram_wordline */
			/* TO-DO CACTI does not have a detailed model for it */
			barrierThickness = 0e-6;
			horizontalDielectric = 0;
			wirePitch = 2 * featureSize;
			aspectRatio = 0;
			ildThickness = 0e-6;
		}
	} else if (_featureSizeInNano <= 90) {
		featureSize = 90e-9;
		switch (wireType) {
		case local_aggressive:
			barrierThickness = 0.01e-6;
			horizontalDielectric = 2.709;
			wirePitch = 2.5* featureSize;
			aspectRatio = 2.4;
			ildThickness = 0.48e-6;
			break;
		case local_conservative:
			barrierThickness = 0.008e-6;
			horizontalDielectric = 3.038;
			wirePitch = 2.5* featureSize;
			aspectRatio = 2.0;
			ildThickness = 0.48e-6;
			break;
		case semi_aggressive:
			barrierThickness = 0.01e-6;
			horizontalDielectric = 2.709;
			wirePitch = 4 * featureSize;
			aspectRatio = 2.4;
			ildThickness = 0.48e-6;
			break;
		case semi_conservative:
			barrierThickness = 0.008e-6;
			horizontalDielectric = 3.038;
			wirePitch = 4 * featureSize;
			aspectRatio = 2.0;
			ildThickness = 0.48e-6;
			break;
		case global_aggressive:
			barrierThickness = 0.01e-6;
			horizontalDielectric = 2.709;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.7;
			ildThickness = 0.96e-6;
			break;
		case global_conservative:
			barrierThickness = 0.008e-6;
			horizontalDielectric = 3.038;
			wirePitch = 8 * featureSize;
			aspectRatio = 2.2;
			ildThickness = 1.1e-6;
			break;
  		default:	/* dram_wordline */
			/* TO-DO CACTI does not have a detailed model for it */
			barrierThickness = 0e-6;
			horizontalDielectric = 0;
			wirePitch = 2 * featureSize;
			aspectRatio = 0;
			ildThickness = 0e-6;
		}
	} else if (_featureSizeInNano <= 120) {
		featureSize = 120e-9;
		switch (wireType) {
		case local_aggressive:
			barrierThickness = 0.012e-6;
			horizontalDielectric = 3.3;
			wirePitch = 240e-9;
			aspectRatio = 1.6;
			ildThickness = 0.48e-6;
			break;
		case local_conservative:
			barrierThickness = 0.01e-6;
			horizontalDielectric = 3.6;
			wirePitch = 240e-9;
			aspectRatio = 1.4;
			ildThickness = 0.48e-6;
			break;
		case semi_aggressive:
			barrierThickness = 0.012e-6;
			horizontalDielectric = 3.3;
			wirePitch = 320e-9;
			aspectRatio = 1.7;
			ildThickness = 0.48e-6;
			break;
		case semi_conservative:
			barrierThickness = 0.01e-6;
			horizontalDielectric = 3.6;
			wirePitch = 320e-9;
			aspectRatio = 1.5;
			ildThickness = 0.48e-6;
			break;
		case global_aggressive:
			barrierThickness = 0.012e-6;
			horizontalDielectric = 3.3;
			wirePitch = 475e-9;
			aspectRatio = 2.1;
			ildThickness = 0.96e-6;
			break;
		case global_conservative:
			barrierThickness = 0.01e-6;
			horizontalDielectric = 3.6;
			wirePitch = 475e-9;
			aspectRatio = 1.9;
			ildThickness = 1.1e-6;
			break;
  		default:	/* dram_wordline */
			/* TO-DO CACTI does not have a detailed model for it */
			barrierThickness = 0e-6;
			horizontalDielectric = 0;
			wirePitch = 2 * featureSize;
			aspectRatio = 0;
			ildThickness = 0e-6;
		}
	} else if (_featureSizeInNano <= 200) {
		featureSize = 200e-9;
		switch (wireType) {
		case local_aggressive:
			barrierThickness = 0.016e-6;
			horizontalDielectric = 3.75;
			wirePitch = 0.45e-6;
			aspectRatio = 2.4;
			ildThickness = 1e-6; /* TO-DO: for test */
			break;
		case local_conservative:
			barrierThickness = 0.016e-6 * 0.8;
			horizontalDielectric = 3.75 * 3.038 / 2.709;
			wirePitch = 0.45e-6;
			aspectRatio = 1.2;
			ildThickness = 1e-6; /* TO-DO: for test */
			break;
		case semi_aggressive:
			barrierThickness = 0.016e-6;
			horizontalDielectric = 3.75;
			wirePitch = 0.575e-6;
			aspectRatio = 2.1;
			ildThickness = 1e-6; /* TO-DO: for test */
			break;
		case semi_conservative:
			barrierThickness = 0.016e-6 * 0.8;
			horizontalDielectric = 3.75 * 3.038 / 2.709;
			wirePitch = 0.575e-6;
			aspectRatio = 2.1 * 2.0 / 2.4;
			ildThickness = 1e-6; /* TO-DO: for test */
			break;
		case global_aggressive:
			barrierThickness = 0.016e-6;
			horizontalDielectric = 3.75;
			wirePitch = 0.945e-6;
			aspectRatio = 2.1;
			ildThickness = 2e-6; /* TO-DO: for test */
			break;
		case global_conservative:
			barrierThickness = 0.016e-6 * 0.8;
			horizontalDielectric = 3.75 * 3.038 / 2.709;
			wirePitch = 0.945e-6;
			aspectRatio = 2.1 * 2.2 / 2.7;
			ildThickness = 2.2e-6; /* TO-DO: for test */
			break;
  		default:	/* dram_wordline */
			/* TO-DO CACTI does not have a detailed model for it */
			barrierThickness = 0e-6;
			horizontalDielectric = 0;
			wirePitch = 2 * featureSize;
			aspectRatio = 0;
			ildThickness = 0e-6;
		}
	}

	wireWidth = wirePitch / 2;
	wireThickness = aspectRatio * wireWidth;
	wireSpacing = wirePitch - wireWidth;

	/* TO-DO: here we only support copper wire, aluminum is to be added */
	copper_resistivity = copper_resistivity
			* (1 + COPPER_RESISTIVITY_TEMPERATURE_COEFFICIENT * (temperature - 293));
	resWirePerUnit = CalculateWireResistance(copper_resistivity, wireWidth, wireThickness, barrierThickness,
			0 /* Dishing Thickness */, 1 /* Alpha Scatter */);
	capWirePerUnit = CalculateWireCapacitance(PERMITTIVITY, wireWidth, wireThickness, wireSpacing,
		ildThickness, 1.5 /* miller value */, horizontalDielectric, 3.9 /* Vertical Dielectric */,
		1.15e-10 /* Fringe Capacitance (Unit: F/m), TO-DO: CACTI assumes a fixed number here */);

	if (wireRepeaterType != repeated_none) {
		/* If the repeaters are inserted in the wire */
		findOptimalRepeater();
		if (wireRepeaterType != repeated_opt) {
			/* The repeated wire is not fully latency optimized */
			double penalty;
			switch (wireRepeaterType) {
			case repeated_5:
				penalty = 0.05;
				break;
			case repeated_10:
				penalty = 0.10;
				break;
			case repeated_20:
				penalty = 0.20;
				break;
			case repeated_30:
				penalty = 0.30;
				break;
			case repeated_40:
				penalty = 0.40;
				break;
			default:	/* repeated_50 ? */
				penalty = 0.50;
			}
			findPenalizedRepeater(penalty);
		}
		/* calculate repeated wire pitch */
		CalculateGateArea(INV, 1, repeaterSize * MIN_NMOS_SIZE * tech->featureSize,
				repeaterSize * MIN_NMOS_SIZE * tech->featureSize * tech->pnSizeRatio, 1e41, *tech,
				&repeaterHeight, &repeaterWidth);
		if (repeaterWidth < repeaterHeight) {
			double temp = repeaterWidth;
			repeaterWidth = repeaterHeight;
			repeaterHeight = temp;
		}
		repeatedWirePitch = wirePitch + repeaterWidth;
	}

	initialized =true;
}


void Wire::CalculateLatencyAndPower(double _wireLength, double *delay, double *dynamicEnergy, double *leakagePower) {
	if (!initialized) {
		cout << "[Wire] Error: Require initialization first!" << endl;
	} else {
		if (isLowSwing) {
			/* When it is low-swing */
			if (wireRepeaterType == repeated_none) {
				double widthNmos = MIN_NMOS_SIZE * tech->featureSize;
				double widthPmos = widthNmos * tech->pnSizeRatio;
				double capInput, capOutput;
				double tr;
				double gm;
				double beta;
				double resPullUp;
				double resPullDown;
				double capLoad;
				double temp;
				double riseTime, fallTime;
				double rampInput;

				/* Calculate rampInput */
				CalculateGateCapacitance(INV, 1, widthNmos, widthPmos, tech->featureSize * MAX_TRANSISTOR_HEIGHT, *tech, &capInput, &capOutput);
				capLoad = capInput + capOutput;
				resPullUp = CalculateOnResistance(widthNmos, NMOS, inputParameter->temperature, *tech);
				resPullUp = CalculateOnResistance(widthPmos, PMOS, inputParameter->temperature, *tech);
				tr = resPullUp * capLoad;
				gm = CalculateTransconductance(widthPmos, PMOS, *tech);
				beta = 1 / (resPullUp * gm);
				horowitz(tr, beta, 1e20, &riseTime);
				resPullDown = CalculateOnResistance(widthNmos, NMOS, inputParameter->temperature, *tech);
				tr = resPullDown * capLoad;
				gm = CalculateTransconductance(widthNmos, NMOS, *tech);
				beta = 1 / (resPullDown * gm);
				horowitz(tr, beta, riseTime, &fallTime);
				rampInput = fallTime;

				/* Calculate FO4 delay */
				double delayFO4;
				capLoad = capOutput + 4 * capInput;
				tr = resPullDown * capLoad;
				delayFO4 = horowitz(tr, beta, 1e20, &temp);

				/* Caluculate the size of driver */
				double wireLength = _wireLength;
				double capGateDriver;
				double capWire = capWirePerUnit * wireLength;
				double resWire = resWirePerUnit * wireLength;
				double resDriver = ((-8) * delayFO4 / ( log(0.5) * capWire)) / RES_ADJ;
				double widthNmosDriver = resPullDown * widthNmos / resDriver;
				widthNmosDriver = MIN(widthNmosDriver, MAX_NMOS_SIZE * tech->featureSize);
				widthNmosDriver = MAX(widthNmosDriver, MIN_NMOS_SIZE * tech->featureSize);

				if(resWire * capWire > 8 * delayFO4)
				{
					widthNmosDriver = inputParameter->maxNmosSize * tech->featureSize;
				}

				// size the inverter appropriately to minimize the transmitter delay
				// Note - In order to minimize leakage, we are not adding a set of inverters to
				// bring down delay. Instead, we are sizing the single gate
				// based on the logical effort.
				CalculateGateCapacitance(INV, 1, widthNmosDriver, 0, tech->featureSize*40, *tech, &capGateDriver, &temp);
				CalculateGateCapacitance(INV, 1, 2 * widthNmos, 2 * widthPmos, tech->featureSize*40, *tech, &capInput, &capOutput);
				double stageEffort   = sqrt(((2 + tech->pnSizeRatio) / (1 + tech->pnSizeRatio)) * capGateDriver / capInput);
				double reqCin  = (((2 + tech->pnSizeRatio) / (1 + tech->pnSizeRatio)) * capGateDriver) / stageEffort;
				CalculateGateCapacitance(INV, 1, widthNmos, widthPmos, tech->featureSize*40, *tech, &capInput, &capOutput);
				double sizeInverter = reqCin / capInput;
				sizeInverter = MAX(sizeInverter, 1);

				/* nand gate delay */
				resPullDown *= 2;
				beta = 1 / (resPullDown * gm);
				double capNandInput, capNandOutput;
				CalculateGateCapacitance(NAND, 2, 2 * widthNmos, widthPmos, tech->featureSize*40, *tech, &capNandInput, &capNandOutput);
				CalculateGateCapacitance(INV, 1, sizeInverter * widthNmos, sizeInverter * widthPmos, tech->featureSize*40, *tech, &capInput, &capOutput);
				capLoad = capNandOutput + capInput;
				tr = resPullDown * capLoad;
				*(delay) = horowitz(tr, beta, rampInput, &temp);
				*(dynamicEnergy) = capLoad * tech->vdd * tech->vdd;
				rampInput = temp; /* for the next stage */

				/* Inverter *(delay):
				 *    * The load capacitance of this inv depends on
				 *    * the gate capacitance of the final stage nmos
				 *    * transistor which in turn depends on nsize
				 *    */
				resPullDown = CalculateOnResistance(sizeInverter * widthNmos, NMOS, inputParameter->temperature, *tech);
				gm = CalculateTransconductance(widthNmos, NMOS, *tech);
				beta = 1 / (resPullDown * gm);
				capLoad = capOutput + capGateDriver;
				tr = resPullDown * capLoad;
				*(delay) += horowitz(tr, beta, rampInput, &temp);
				*(dynamicEnergy) += capLoad * tech->vdd * tech->vdd;
				rampInput = temp; /* for the next stage */

				*(leakagePower) = 2 * tech->vdd * CalculateGateLeakage(INV, 1, sizeInverter * widthNmos, sizeInverter * widthPmos, inputParameter->temperature, *tech);
				*(leakagePower) += 2 * tech->vdd * CalculateGateLeakage(NAND, 2, 2 * widthNmos, widthPmos, inputParameter->temperature, *tech);
				*(leakagePower) *= 2;

				senseAmp = new SenseAmp;
				senseAmp->Initialize(1, false, cell->minSenseVoltage, 1 /* for test */);
				senseAmp->CalculateRC();

				/* nmos *(delay) + wire *(delay) */
				/*
				 * 			   * NOTE: nmos is used as both pull up and pull down transistor
				 * 			   * in the transmitter. This is because for low voltage swing, drive
				 *			   * resistance of nmos is less than pmos
				 *			   * (for a detailed graph ref: On-Chip Wires: Scaling and Efficiency)
			   */
				double drainCapDriver = CalculateDrainCap(widthNmosDriver, NMOS, tech->featureSize*40, *tech);
				capLoad = capWire + drainCapDriver * 2 + senseAmp->capLoad;
				resPullDown = CalculateOnResistance(widthNmosDriver, NMOS, inputParameter->temperature, *tech);
				gm = CalculateTransconductance(widthNmosDriver, NMOS, *tech);
				beta = 1 / (resPullDown * gm);
				tr = resPullDown * RES_ADJ *(capWire + drainCapDriver * 2) + capWire * resWire / 2 + (resPullDown + resWire) * senseAmp->capLoad;
				if (delay)
					*(delay) += horowitz(tr, beta, rampInput, &temp); //TO-DO: inconsistent with Cacti 6.5
				if (dynamicEnergy) {
					*(dynamicEnergy) += capLoad * VOL_SWING * 0.4; /* .4v is the over drive voltage */
					*(dynamicEnergy) *=2;
				}
				if (leakagePower)
					*(leakagePower) += 4 * tech->vdd * CalculateGateLeakage(INV, 1, widthNmosDriver, 0, inputParameter->temperature, *tech);

				/* SA *(delay) and power */
				if (delay)
					*(delay) += senseAmp->readLatency;
				if (dynamicEnergy)
					*(dynamicEnergy) += senseAmp->readDynamicEnergy;
				if (leakagePower)
					*(leakagePower) += senseAmp->leakage;

			} else {
				cout<<"Error: Low Swing Wires with Repeaters is not supported in this version!" <<endl;
				exit(-1);
			}
		} else {
			/* When it is not a low-swing */
			if (wireRepeaterType == repeated_none) {
				if (delay)
					*(delay) = 2.3 * resWirePerUnit * capWirePerUnit * _wireLength * _wireLength / 2;
				if (dynamicEnergy)
					*(dynamicEnergy) = capWirePerUnit * _wireLength * tech->vdd * tech->vdd;
				if (leakagePower)
					*(leakagePower) = 0;
			} else {		/* with repeaters */
				if (delay)
					*(delay) = getRepeatedWireUnitDelay() * _wireLength;
				if (dynamicEnergy)
					*(dynamicEnergy) = getRepeatedWireUnitDynamicEnergy() * _wireLength;
				if (leakagePower)
					*(leakagePower) = getRepeatedWireUnitLeakage() * _wireLength;
			}
		}
	}
}

void Wire::findOptimalRepeater() {
	/* Use minimum sized inverter */
	double nmosSize = MIN_NMOS_SIZE * tech->featureSize;
	double pmosSize = nmosSize * tech->pnSizeRatio;
	double inputCap = CalculateGateCap(nmosSize, *tech) + CalculateGateCap(pmosSize, *tech);
	double outputCap = CalculateDrainCap(nmosSize, NMOS, 1 /*no limit*/, *tech)
			+ CalculateDrainCap(pmosSize, PMOS, 1 /*no limit*/, *tech);
	double outputRes = CalculateOnResistance(nmosSize, NMOS, inputParameter->temperature, *tech)
			+ CalculateOnResistance(pmosSize, PMOS, inputParameter->temperature, *tech);

	repeaterSize = sqrt(outputRes * capWirePerUnit / inputCap / resWirePerUnit);
	repeaterSpacing = sqrt(2 * outputRes * (outputCap + inputCap) / (resWirePerUnit * capWirePerUnit));

	//double tau = outputRes * (inputCap + outputCap) + outputRes * capWirePerUnit * repeaterSpacing
	//		+ resWirePerUnit * repeaterSpacing * inputCap * repeaterSize
}

void Wire::findPenalizedRepeater(double _penalty) {
	double targetDelay = getRepeatedWireUnitDelay() * (1 + _penalty);
	double currentDynamicEnergy = getRepeatedWireUnitDynamicEnergy();
	double currentLeakage = getRepeatedWireUnitLeakage();

	double targetRepeaterSpacing = repeaterSpacing;
	double targetRepeaterSize = repeaterSize;
	double stepSpacing = 100e-6;	/* 100um */
	double endSpacing = 4 * repeaterSpacing;
	double stepSize = 1;			/* minimum buffer size */
	double endSize = 1;

	double thisDelay, thisDynamicEnergy, thisLeakage;
	/* Start finding the target repeated wire */
	for (; repeaterSpacing <= endSpacing; repeaterSpacing += stepSpacing) {
		for (; repeaterSize >= endSize; repeaterSize -= stepSize) {
			thisDelay = getRepeatedWireUnitDelay();
			thisDynamicEnergy = getRepeatedWireUnitDynamicEnergy();
			thisLeakage = getRepeatedWireUnitLeakage();
			if (thisDelay <= targetDelay && thisDynamicEnergy / currentDynamicEnergy + thisLeakage / currentLeakage < 2) {
				currentDynamicEnergy = thisDynamicEnergy;
				currentLeakage = thisLeakage;
				targetRepeaterSpacing = repeaterSpacing;
				targetRepeaterSize = repeaterSize;
			}
		}
	}
	repeaterSpacing = targetRepeaterSpacing;
	repeaterSize = targetRepeaterSize;
}

double Wire::getRepeatedWireUnitDelay() {
	/* Use the scaled size of the repeater */
	double nmosSize = MIN_NMOS_SIZE * tech->featureSize * repeaterSize;
	double pmosSize = nmosSize * tech->pnSizeRatio;
	double inputCap = CalculateGateCap(nmosSize, *tech) + CalculateGateCap(pmosSize, *tech);
	double outputCap = CalculateDrainCap(nmosSize, NMOS, 1 /*no limit*/, *tech)
			+ CalculateDrainCap(pmosSize, PMOS, 1 /*no limit*/, *tech);
	double outputRes = CalculateOnResistance(nmosSize, NMOS, inputParameter->temperature, *tech)
			+ CalculateOnResistance(pmosSize, PMOS, inputParameter->temperature, *tech);
	double wireCap = capWirePerUnit * repeaterSpacing;
	double wireRes = resWirePerUnit * repeaterSpacing;

	double tau = outputRes * (inputCap + outputCap) + outputRes * wireCap + wireRes * outputCap
			+ 0.5 * wireRes * wireCap;

	/* Return as a unit value */
	return 0.693 * tau / repeaterSpacing;
}

double Wire::getRepeatedWireUnitDynamicEnergy() {
	/* Use the scaled size of the repeater */
	double nmosSize = MIN_NMOS_SIZE * tech->featureSize * repeaterSize;
	double pmosSize = nmosSize * tech->pnSizeRatio;
	double inputCap = CalculateGateCap(nmosSize, *tech) + CalculateGateCap(pmosSize, *tech);
	double outputCap = CalculateDrainCap(nmosSize, NMOS, 1 /*no limit*/, *tech)
			+ CalculateDrainCap(pmosSize, PMOS, 1 /*no limit*/, *tech);
	double wireCap = capWirePerUnit * repeaterSpacing;

	double switchingEnergy = (inputCap + outputCap + wireCap) * tech->vdd * tech->vdd;
	double shortCircuitEnergy = 0;		/* TO-DO: no short circuit energy in this version */

	return (switchingEnergy + shortCircuitEnergy) / repeaterSpacing;
}

double Wire::getRepeatedWireUnitLeakage() {
	double nmosSize = MIN_NMOS_SIZE * tech->featureSize * repeaterSize;
	double pmosSize = nmosSize * tech->pnSizeRatio;
	double leakagePerRepeater = CalculateGateLeakage(INV, 1, nmosSize, pmosSize, inputParameter->temperature, *tech)
			* tech->vdd;

	return leakagePerRepeater / repeaterSpacing;
}

void Wire::PrintProperty() {
	if (wireRepeaterType == repeated_none) {
		cout << "Wire Type: passive (without repeaters)";
		if (isLowSwing) {
			cout << " Low Swing";
		}
		cout << endl;
		cout << "Wire Resistance: " << resWirePerUnit / 1e6 << "ohm/um" << endl;
		cout << "Wire Capacitance: " << capWirePerUnit / 1e6 << "F/um" << endl;
	} else {
		cout << "Wire type: active (with repeaters)" << endl;
		cout << "Repeater Size: " << repeaterSize << endl;
		cout << "Repeater Spacing: " << repeaterSpacing * 1e3 << "mm" <<endl;
		cout << "Delay: " << getRepeatedWireUnitDelay() * 1e6 << "ns/mm" <<endl;
		cout << "Dynamic Energy: " << getRepeatedWireUnitDynamicEnergy() * 1e6 << "nJ/mm" <<endl;
	    cout << "Subtheshold Leakage Power: " << getRepeatedWireUnitLeakage() << "mW/mm" << endl;
	}
}

Wire & Wire::operator=(const Wire &rhs) {
	initialized = rhs.initialized;
	featureSizeInNano = rhs.featureSizeInNano;
	featureSize = rhs.featureSize;
	wireType = rhs.wireType;
	wireRepeaterType = rhs.wireRepeaterType;
	temperature = rhs.temperature;
	isLowSwing = rhs.isLowSwing;
	barrierThickness = rhs.barrierThickness;
	horizontalDielectric = rhs.horizontalDielectric;
	wirePitch = rhs.wirePitch;
	aspectRatio = rhs.aspectRatio;
	ildThickness = rhs.ildThickness;
	wireWidth = rhs.wireWidth;
	wireThickness = rhs.wireThickness;
	wireSpacing = rhs.wireSpacing;
	repeaterSize = rhs.repeaterSize;
	repeaterSpacing = rhs.repeaterSpacing;
	repeaterHeight = rhs.repeaterHeight;
	repeaterWidth = rhs.repeaterWidth;
	repeatedWirePitch = rhs.repeatedWirePitch;
	resWirePerUnit = rhs.resWirePerUnit;
	capWirePerUnit = rhs.capWirePerUnit;

	return *this;
}
