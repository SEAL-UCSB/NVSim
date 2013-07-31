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


#include "SenseAmp.h"
#include "formula.h"
#include "global.h"

SenseAmp::SenseAmp() {
	// TODO Auto-generated constructor stub
	initialized = false;
	invalid = false;
}

SenseAmp::~SenseAmp() {
	// TODO Auto-generated destructor stub
}

void SenseAmp::Initialize(long long _numColumn, bool _currentSense, double _senseVoltage, double _pitchSenseAmp) {
	if (initialized)
		cout << "[Sense Amp] Warning: Already initialized!" << endl;

	numColumn = _numColumn;
	currentSense = _currentSense;
	senseVoltage = _senseVoltage;
	pitchSenseAmp = _pitchSenseAmp;

	if (pitchSenseAmp <= tech->featureSize * 2) {
		/* too small, cannot do the layout */
		invalid = true;
	}

	initialized = true;
}

void SenseAmp::CalculateArea() {
	if (!initialized) {
		cout << "[Sense Amp] Error: Require initialization first!" << endl;
	} else if (invalid) {
		height = width = area = 1e41;
	} else {
		height = width = area = 0;
		if (currentSense) {	/* current-sensing needs IV converter */
			area += IV_CONVERTER_AREA * tech->featureSize * tech->featureSize;
		}
		/* the following codes are transformed from CACTI 6.5 */
		double tempHeight = 0;
		double tempWidth = 0;

		CalculateGateArea(INV, 1, 0, W_SENSE_P * tech->featureSize,
				pitchSenseAmp, *tech, &tempWidth, &tempHeight);	/* exchange width and height for senseamp layout */
		width = MAX(width, tempWidth);
		height += 2 * tempHeight;
		CalculateGateArea(INV, 1, 0, W_SENSE_ISO * tech->featureSize,
				pitchSenseAmp, *tech, &tempWidth, &tempHeight);	/* exchange width and height for senseamp layout */
		width = MAX(width, tempWidth);
		height += tempHeight;
		height += 2 * MIN_GAP_BET_SAME_TYPE_DIFFS * tech->featureSize;

		CalculateGateArea(INV, 1, W_SENSE_N * tech->featureSize, 0,
				pitchSenseAmp, *tech, &tempWidth, &tempHeight);	/* exchange width and height for senseamp layout */
		width = MAX(width, tempWidth);
		height += 2 * tempHeight;
		CalculateGateArea(INV, 1, W_SENSE_EN * tech->featureSize, 0,
				pitchSenseAmp, *tech, &tempWidth, &tempHeight);	/* exchange width and height for senseamp layout */
		width = MAX(width, tempWidth);
		height += tempHeight;
		height += 2 * MIN_GAP_BET_SAME_TYPE_DIFFS * tech->featureSize;

		height += MIN_GAP_BET_P_AND_N_DIFFS * tech->featureSize;

		/* transformation so that width meets the pitch */
		height = height * width / pitchSenseAmp;
		width = pitchSenseAmp;

		/* Add additional area if IV converter exists */
		height += area / width;
		width *= numColumn;

		area = height * width;
	}
}

void SenseAmp::CalculateRC() {
	if (!initialized) {
		cout << "[Sense Amp] Error: Require initialization first!" << endl;
	} else if (invalid) {
		readLatency = writeLatency = 1e41;
	} else {
		capLoad = CalculateGateCap((W_SENSE_P + W_SENSE_N) * tech->featureSize, *tech)
				+ CalculateDrainCap(W_SENSE_N * tech->featureSize, NMOS, pitchSenseAmp, *tech)
				+ CalculateDrainCap(W_SENSE_P * tech->featureSize, PMOS, pitchSenseAmp, *tech)
				+ CalculateDrainCap(W_SENSE_ISO * tech->featureSize, PMOS, pitchSenseAmp, *tech)
				+ CalculateDrainCap(W_SENSE_MUX * tech->featureSize, NMOS, pitchSenseAmp, *tech);
	}
}

void SenseAmp::CalculateLatency(double _rampInput) {	/* _rampInput is actually no use in SenseAmp */
	if (!initialized) {
		cout << "[Sense Amp] Error: Require initialization first!" << endl;
	} else {
		readLatency = writeLatency = 0;
		if (currentSense) {	/* current-sensing needs IV converter */
			/* all the following values achieved from HSPICE */
			if (tech->featureSize >= 119e-9)
				readLatency += 0.49e-9;		/* 120nm */
			else if (tech->featureSize >= 89e-9)
				readLatency += 0.53e-9;		/* 90nm */
			else if (tech->featureSize >= 64e-9)
				readLatency += 0.62e-9;		/* 65nm */
			else if (tech->featureSize >= 44e-9)
				readLatency += 0.80e-9;		/* 45nm */
			else if (tech->featureSize >= 31e-9)
				readLatency += 1.07e-9;		/* 32nm */
			else
				readLatency += 1.45e-9;     /* below 22nm */
		}

		/* Voltage sense amplifier */
		double gm = CalculateTransconductance(W_SENSE_N * tech->featureSize, NMOS, *tech)
				+ CalculateTransconductance(W_SENSE_P * tech->featureSize, PMOS, *tech);
		double tau = capLoad / gm;
		readLatency += tau * log(tech->vdd / senseVoltage);
	}
}

void SenseAmp::CalculatePower() {
	if (!initialized) {
		cout << "[Sense Amp] Error: Require initialization first!" << endl;
	} else if (invalid) {
		readDynamicEnergy = writeDynamicEnergy = leakage = 1e41;
	} else {
		readDynamicEnergy = writeDynamicEnergy = 0;
		leakage = 0;
		if (currentSense) {	/* current-sensing needs IV converter */
			/* all the following values achieved from HSPICE */
			if (tech->featureSize >= 119e-9) {			/* 120nm */
				readDynamicEnergy += 8.52e-14;	/* Unit: J */
				leakage += 1.40e-8;				/* Unit: W */
			} else if (tech->featureSize >= 89e-9) {	/* 90nm */
				readDynamicEnergy += 8.72e-14;
				leakage += 1.87e-8;
			} else if (tech->featureSize >= 64e-9) {	/* 65nm */
				readDynamicEnergy += 9.00e-14;
				leakage += 2.57e-8;
			} else if (tech->featureSize >= 44e-9) {	/* 45nm */
				readDynamicEnergy += 10.26e-14;
				leakage += 4.41e-9;
			} else if (tech->featureSize >= 31e-9) {	/* 32nm */
				readDynamicEnergy += 12.56e-14;
				leakage += 12.54e-8;
			} else {                                    /* TO-DO, need calibration below 22nm */
				readDynamicEnergy += 15e-14;
				leakage += 15e-8;
			}
		}

		/* Voltage sense amplifier */
		readDynamicEnergy += capLoad * tech->vdd * tech->vdd;
		double idleCurrent =  CalculateGateLeakage(INV, 1, W_SENSE_EN * tech->featureSize, 0,
				inputParameter->temperature, *tech) * tech->vdd;
		leakage += idleCurrent * tech->vdd;

		readDynamicEnergy *= numColumn;
		leakage *= numColumn;
	}
}

void SenseAmp::PrintProperty() {
	cout << "Sense Amplifier Properties:" << endl;
	FunctionUnit::PrintProperty();
}

SenseAmp & SenseAmp::operator=(const SenseAmp &rhs) {
	height = rhs.height;
	width = rhs.width;
	area = rhs.area;
	readLatency = rhs.readLatency;
	writeLatency = rhs.writeLatency;
	readDynamicEnergy = rhs.readDynamicEnergy;
	writeDynamicEnergy = rhs.writeDynamicEnergy;
	resetLatency = rhs.resetLatency;
	setLatency = rhs.setLatency;
	resetDynamicEnergy = rhs.resetDynamicEnergy;
	setDynamicEnergy = rhs.setDynamicEnergy;
	cellReadEnergy = rhs.cellReadEnergy;
	cellSetEnergy = rhs.cellSetEnergy;
	cellResetEnergy = rhs.cellResetEnergy;
	leakage = rhs.leakage;
	initialized = rhs.initialized;
	invalid = rhs.invalid;
	numColumn = rhs.numColumn;
	currentSense = rhs.currentSense;
	senseVoltage = rhs.senseVoltage;
	capLoad = rhs.capLoad;
	pitchSenseAmp = rhs.pitchSenseAmp;

	return *this;
}
