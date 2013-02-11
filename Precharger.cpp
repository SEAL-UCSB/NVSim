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


#include "Precharger.h"
#include "formula.h"
#include "global.h"

Precharger::Precharger() {
	// TODO Auto-generated constructor stub
	initialized = false;
	enableLatency = 0;
}

Precharger::~Precharger() {
	// TODO Auto-generated destructor stub
}

void Precharger::Initialize(double _voltagePrecharge, int _numColumn, double _capBitline, double _resBitline){
	if (initialized)
		cout << "[Precharger] Warning: Already initialized!" << endl;

	voltagePrecharge = _voltagePrecharge;
	numColumn  = _numColumn;
	capBitline = _capBitline;
	resBitline = _resBitline;
	capWireLoadPerColumn = cell->widthInFeatureSize * tech->featureSize * localWire->capWirePerUnit;
	resWireLoadPerColumn = cell->widthInFeatureSize * tech->featureSize * localWire->resWirePerUnit;
	widthInvNmos = MIN_NMOS_SIZE * tech->featureSize;
	widthInvPmos = widthInvNmos * tech->pnSizeRatio;
	widthPMOSBitlineEqual      = MIN_NMOS_SIZE * tech->featureSize;
	widthPMOSBitlinePrecharger = 6 * tech->featureSize;
	capLoadInv  = CalculateGateCap(widthPMOSBitlineEqual, *tech) + 2 * CalculateGateCap(widthPMOSBitlinePrecharger, *tech)
			+ CalculateDrainCap(widthInvNmos, NMOS, tech->featureSize*40, *tech)
			+ CalculateDrainCap(widthInvPmos, PMOS, tech->featureSize*40, *tech);
	capOutputBitlinePrecharger = CalculateDrainCap(widthPMOSBitlinePrecharger, PMOS, tech->featureSize*40, *tech) + CalculateDrainCap(widthPMOSBitlineEqual, PMOS, tech->featureSize*40, *tech);
	double capInputInv         = CalculateGateCap(widthInvNmos, *tech) + CalculateGateCap(widthInvPmos, *tech);
	capLoadPerColumn           = capInputInv + capWireLoadPerColumn;
	double capLoadOutputDriver = numColumn * capLoadPerColumn;
	outputDriver.Initialize(1, capInputInv, capLoadOutputDriver, 0 /* TO-DO */, true, latency_first, 0);  /* Always Latency First */

	initialized = true;
}

void Precharger::CalculateArea() {
	if (!initialized) {
		cout << "[Precharger] Error: Require initialization first!" << endl;
	} else {
		outputDriver.CalculateArea();
		double hBitlinePrechareger, wBitlinePrechareger;
		double hBitlineEqual, wBitlineEqual;
		double hInverter, wInverter;
		CalculateGateArea(INV, 1, 0, widthPMOSBitlinePrecharger, tech->featureSize*40, *tech, &hBitlinePrechareger, &wBitlinePrechareger);
		CalculateGateArea(INV, 1, 0, widthPMOSBitlineEqual, tech->featureSize*40, *tech, &hBitlineEqual, &wBitlineEqual);
		CalculateGateArea(INV, 1, widthInvNmos, widthInvPmos, tech->featureSize*40, *tech, &hInverter, &wInverter);
		width = 2 * wBitlinePrechareger + wBitlineEqual;
		width = MAX(width, wInverter);
		width *= numColumn;
		width = MAX(width, outputDriver.width);
		height = MAX(hBitlinePrechareger, hBitlineEqual);
		height += hInverter;
		height = MAX(height, outputDriver.height);
		area = height * width;
	}
}

void Precharger::CalculateRC() {
	if (!initialized) {
		cout << "[Precharger] Error: Require initialization first!" << endl;
	} else {
		outputDriver.CalculateRC();
		//more accurate RC model would include drain Capacitances of Precharger and Equalization PMOS transistors
	}
}

void Precharger::CalculateLatency(double _rampInput){
	if (!initialized) {
		cout << "[Precharger] Error: Require initialization first!" << endl;
	} else {
		rampInput= _rampInput;
		outputDriver.CalculateLatency(rampInput);
		enableLatency = outputDriver.readLatency;
		double resPullDown;
		double tr;	/* time constant */
		double gm;	/* transconductance */
		double beta;	/* for horowitz calculation */
		double temp;
		resPullDown = CalculateOnResistance(widthInvNmos, NMOS, inputParameter->temperature, *tech);
		tr = resPullDown * capLoadInv;
		gm = CalculateTransconductance(widthInvNmos, NMOS, *tech);
		beta = 1 / (resPullDown * gm);
		enableLatency += horowitz(tr, beta, outputDriver.rampOutput, &temp);
		readLatency = 0;
		double resPullUp = CalculateOnResistance(widthPMOSBitlinePrecharger, PMOS,
				inputParameter->temperature, *tech);
		double tau = resPullUp * (capBitline + capOutputBitlinePrecharger) + resBitline * capBitline / 2;
		gm = CalculateTransconductance(widthPMOSBitlinePrecharger, PMOS, *tech);
		beta = 1 / (resPullUp * gm);
		readLatency += horowitz(tau, beta, temp, &rampOutput);
		writeLatency = readLatency;
	}
}

void Precharger::CalculatePower() {
	if (!initialized) {
		cout << "[Precharger] Error: Require initialization first!" << endl;
	} else {
		outputDriver.CalculatePower();
		/* Leakage power */
		leakage = outputDriver.leakage;
		leakage += numColumn * tech->vdd * CalculateGateLeakage(INV, 1, widthInvNmos, widthInvPmos, inputParameter->temperature, *tech);
		leakage += numColumn * voltagePrecharge * CalculateGateLeakage(INV, 1, 0, widthPMOSBitlinePrecharger,
				inputParameter->temperature, *tech);

		/* Dynamic energy */
		/* We don't count bitline precharge energy into account because it is a charging process */
		readDynamicEnergy = outputDriver.readDynamicEnergy;
		readDynamicEnergy += capLoadInv * tech->vdd * tech->vdd * numColumn;
		writeDynamicEnergy = 0;		/* No precharging is needed during the write operation */
	}
}

void Precharger::PrintProperty() {
	cout << "Precharger Properties:" << endl;
	FunctionUnit::PrintProperty();
}

Precharger & Precharger::operator=(const Precharger &rhs) {
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
	outputDriver = rhs.outputDriver;
	capBitline = rhs.capBitline;
	resBitline = rhs.resBitline;
	capLoadInv = rhs.capLoadInv;
	capOutputBitlinePrecharger = rhs.capOutputBitlinePrecharger;
	capWireLoadPerColumn = rhs.capWireLoadPerColumn;
	resWireLoadPerColumn = rhs.resWireLoadPerColumn;
	enableLatency = rhs.enableLatency;
	numColumn = rhs.numColumn;
	widthPMOSBitlinePrecharger = rhs.widthPMOSBitlinePrecharger;
	widthPMOSBitlineEqual = rhs.widthPMOSBitlineEqual;
	capLoadPerColumn = rhs.capLoadPerColumn;
	rampInput = rhs.rampInput;
	rampOutput = rhs.rampOutput;

	return *this;
}
