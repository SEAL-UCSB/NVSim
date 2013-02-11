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


#include "Comparator.h"
#include "global.h"
#include "formula.h"
#include <math.h>

Comparator::Comparator() {
	initialized = false;
	capLoad = 0;
	rampOutput = 1e40;
	// TODO Auto-generated constructor stub

}

Comparator::~Comparator() {
	// TODO Auto-generated destructor stub
}

void Comparator::Initialize(int _numTagBits, double _capLoad){
	if (initialized)
		cout << "[Comparator] Warning: Already initialized!" << endl;

	numTagBits = _numTagBits / 4;  /* Assuming there are 4 quarter comparators. input tagbits is already a multiple of 4 */
	capLoad = _capLoad;
	widthNMOSInv[0] = 7.5 * tech->featureSize;
	widthPMOSInv[0] = 12.5 * tech->featureSize;
	widthNMOSInv[1] = 15 * tech->featureSize;
	widthPMOSInv[1] = 25 * tech->featureSize;
	widthNMOSInv[2] = 30 * tech->featureSize;
	widthPMOSInv[2] = 50 * tech->featureSize;
	widthNMOSInv[3] = 50 * tech->featureSize;
	widthPMOSInv[3] = 100 * tech->featureSize;
	widthNMOSComp = 12.5 * tech->featureSize;
	widthPMOSComp = 37.5 * tech->featureSize;

	initialized = true;
}

void Comparator::CalculateArea() {
	if (!initialized) {
		cout << "[Comparator] Error: Require initialization first!" << endl;
	} else {
		double totalHeight = 0;
		double totalWidth = 0;
		double h, w;
		for (int i = 0; i < COMPARATOR_INV_CHAIN_LEN; i++) {
			CalculateGateArea(INV, 1, widthNMOSInv[i], widthPMOSInv[i], tech->featureSize*40, *tech, &h, &w);
			totalHeight = MAX(totalHeight, h);
			totalWidth += w;
		}
		CalculateGateArea(NAND, 2, widthNMOSComp, 0, tech->featureSize*40, *tech, &h, &w);
		totalHeight += h;
		totalWidth = MAX(totalWidth, numTagBits * w);
		height = totalHeight * 1; // 4 quarter comparators can have different placement, here assumes 1*4
		width = totalWidth * 4;
		area = height * width;
	}
}

void Comparator::CalculateRC() {
	if (!initialized) {
		cout << "[Comparator] Error: Require initialization first!" << endl;
	} else {
		for (int i = 0; i < COMPARATOR_INV_CHAIN_LEN; i++) {
			CalculateGateCapacitance(INV, 1, widthNMOSInv[i], widthPMOSInv[i], tech->featureSize * MAX_TRANSISTOR_HEIGHT, *tech, &(capInput[i]), &(capOutput[i]));
		}
		double capComp, capTemp;
		CalculateGateCapacitance(NAND, 2, widthNMOSComp, 0, tech->featureSize*40, *tech, &capTemp, &capComp);
		capBottom = capOutput[COMPARATOR_INV_CHAIN_LEN-1] + numTagBits * capComp;
		capTop = numTagBits * capComp + CalculateDrainCap(widthPMOSComp, PMOS, tech->featureSize * MAX_TRANSISTOR_HEIGHT, *tech) + capLoad;
		resBottom = CalculateOnResistance(widthNMOSInv[COMPARATOR_INV_CHAIN_LEN-1], NMOS, inputParameter->temperature, *tech);
		resTop = 2 * CalculateOnResistance(widthNMOSComp, NMOS, inputParameter->temperature, *tech);
	}
}

void Comparator::CalculateLatency(double _rampInput) {
	if (!initialized) {
		cout << "[Comparator] Error: Require initialization first!" << endl;
	} else {
		rampInput = _rampInput;
		double resPullDown;
		double capNode;
		double tr;	/* time constant */
		double gm;	/* transconductance */
		double beta;	/* for horowitz calculation */
		double temp;
		readLatency = 0;
		for (int i = 0; i < COMPARATOR_INV_CHAIN_LEN - 1; i++) {
			resPullDown = CalculateOnResistance(widthNMOSInv[i], NMOS, inputParameter->temperature, *tech);
			capNode = capOutput[i] + capInput[i+1];
			tr = resPullDown * capNode;
			gm = CalculateTransconductance(widthNMOSInv[i], NMOS, *tech);
			beta = 1 / (resPullDown * gm);
			readLatency += horowitz(tr, beta, rampInput, &temp);
			rampInput = temp;	/* for next stage */
		}
		tr = resBottom * capBottom + (resBottom + resTop) * capTop;
		readLatency += horowitz(tr, 0, rampInput, &rampOutput);
		rampInput = _rampInput;
		writeLatency = readLatency;
	}
}

void Comparator::CalculatePower() {
	if (!initialized) {
		cout << "[Comparator] Error: Require initialization first!" << endl;
	} else {
		/* Leakage power */
		leakage = 0;
		for (int i = 0; i < COMPARATOR_INV_CHAIN_LEN; i++) {
			leakage += CalculateGateLeakage(INV, 1, widthNMOSInv[i], widthPMOSInv[i], inputParameter->temperature, *tech)
					* tech->vdd;
		}
		leakage += numTagBits * CalculateGateLeakage(NAND, 2, widthNMOSComp, 0, inputParameter->temperature, *tech)
				* tech->vdd;
		leakage *= 4;
		/* Dynamic energy */
		readDynamicEnergy = 0;
		double capNode;
		for (int i = 0; i < COMPARATOR_INV_CHAIN_LEN - 1; i++) {
			capNode = capOutput[i] + capInput[i+1];
			readDynamicEnergy += capNode * tech->vdd * tech->vdd;
		}
		readDynamicEnergy += (capBottom + capTop) * tech->vdd * tech->vdd;
		readDynamicEnergy *= 4;
		writeDynamicEnergy = readDynamicEnergy;
	}
}

void Comparator::PrintProperty() {
	cout << "Comparator Properties:" << endl;
	FunctionUnit::PrintProperty();
}

Comparator & Comparator::operator=(const Comparator &rhs) {
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
	numTagBits = rhs.numTagBits;
	capLoad = rhs.capLoad;
	widthNMOSComp = rhs.widthNMOSComp;
	widthPMOSComp = rhs.widthPMOSComp;
	capBottom = rhs.capBottom;
	capTop = rhs.capTop;
	resBottom = rhs.resBottom;
	resTop = rhs.resTop;
	for (int i = 0; i < COMPARATOR_INV_CHAIN_LEN; i++) {
		widthNMOSInv[i] = rhs.widthNMOSInv[i];
		widthPMOSInv[i] = rhs.widthPMOSInv[i];
		capInput[i] = rhs.capInput[i];
		capOutput[i] =rhs.capOutput[i];
	}
	rampInput = rhs.rampInput;
	rampOutput = rhs.rampOutput;

	return *this;
}
