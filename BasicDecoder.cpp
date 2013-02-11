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


#include "BasicDecoder.h"
#include "formula.h"
#include "global.h"

BasicDecoder::BasicDecoder() {
	// TODO Auto-generated constructor stub
	initialized = false;
}

BasicDecoder::~BasicDecoder() {
	// TODO Auto-generated destructor stub
}

void BasicDecoder::Initialize(int _numAddressBit, double _capLoad, double _resLoad){
	/*if (initialized)
			cout << "Warning: Already initialized!" << endl;*/
	/* might be re-initialized by predecodeblock */
	if (_numAddressBit == 1) {
		numNandInput = 0;
	}
	else {
		numNandInput = _numAddressBit;
	}
	capLoad = _capLoad;
	resLoad = _resLoad;

	if (numNandInput == 0) {
		numNandGate = 0;
		double logicEffortInv = 1;
		double widthInvN = MIN_NMOS_SIZE * tech->featureSize;
		double widthInvP = tech->pnSizeRatio * MIN_NMOS_SIZE * tech->featureSize;
		double capInv = CalculateGateCap(widthInvN, *tech) + CalculateGateCap(widthInvP, *tech);
		outputDriver.Initialize(logicEffortInv, capInv, capLoad, resLoad, true, latency_first, 0);  /* Always Latency First */
	}
	else{
		double logicEffortNand;
		double capNand;
		if (numNandInput == 2) {	/* NAND2 */
			numNandGate = 4;
			widthNandN = 2 * MIN_NMOS_SIZE * tech->featureSize;
			logicEffortNand = (2+tech->pnSizeRatio) / (1+tech->pnSizeRatio);
		} else {					/* NAND3 */
			numNandGate = 8;
			widthNandN = 3 * MIN_NMOS_SIZE * tech->featureSize;
			logicEffortNand = (3+tech->pnSizeRatio) / (1+tech->pnSizeRatio);
		}
		widthNandP = tech->pnSizeRatio * MIN_NMOS_SIZE * tech->featureSize;
		capNand = CalculateGateCap(widthNandN, *tech) + CalculateGateCap(widthNandP, *tech);
		outputDriver.Initialize(logicEffortNand, capNand, capLoad, resLoad, true, latency_first, 0);  /* Always Latency First */
	}
	initialized = true;
}

void BasicDecoder::CalculateArea() {
	if (!initialized) {
		cout << "[Basic Decoder] Error: Require initialization first!" << endl;
	} else {
		outputDriver.CalculateArea();
		if (numNandInput == 0){
			height = 2 * outputDriver.height;
			width = outputDriver.width;
		}
		else {
			double hNand, wNand;
			CalculateGateArea(NAND, numNandInput, widthNandN, widthNandP, tech->featureSize*40, *tech, &hNand, &wNand);
			height = MAX(hNand, outputDriver.height);
			width = wNand + outputDriver.width;
			height *= numNandGate;
		}
		area = height * width;
	}
}

void BasicDecoder::CalculateRC() {
	if (!initialized) {
		cout << "[Basic Decoder] Error: Require initialization first!" << endl;
	} else {
		outputDriver.CalculateRC();
		if (numNandInput > 0) {
			CalculateGateCapacitance(NAND, numNandInput, widthNandN, widthNandP, tech->featureSize * MAX_TRANSISTOR_HEIGHT, *tech, &capNandInput, &capNandOutput);
		}
	}
}

void BasicDecoder::CalculateLatency(double _rampInput) {
	if (!initialized) {
		cout << "[Basic Decoder] Error: Require initialization first!" << endl;
	} else {
		rampInput = _rampInput;
        if (numNandInput == 0) {
        	outputDriver.CalculateLatency(rampInput);
        	readLatency  = outputDriver.readLatency;
        	writeLatency = readLatency;
        } else {
        	double resPullDown;
        	double capLoad;
        	double tr;	/* time constant */
        	double gm;	/* transconductance */
        	double beta;	/* for horowitz calculation */
        	double rampInputForDriver;

        	resPullDown = CalculateOnResistance(widthNandN, NMOS, inputParameter->temperature, *tech) * numNandInput;
        	capLoad = capNandOutput + outputDriver.capInput[0];
        	tr = resPullDown * capLoad;
        	gm = CalculateTransconductance(widthNandN, NMOS, *tech);
        	beta = 1 / (resPullDown * gm);
        	readLatency = horowitz(tr, beta, rampInput, &rampInputForDriver);

        	outputDriver.CalculateLatency(rampInputForDriver);
        	readLatency += outputDriver.readLatency;
        	writeLatency = readLatency;
        }
        rampOutput = outputDriver.rampOutput;
	}
}

void BasicDecoder::CalculatePower() {
	if (!initialized) {
		cout << "[Basic Decoder] Error: Require initialization first!" << endl;
	} else {
		outputDriver.CalculatePower();
		double capLoad;
		if (numNandInput == 0) {
			leakage = 2 * outputDriver.leakage;
			capLoad = outputDriver.capInput[0] + outputDriver.capOutput[0];
			readDynamicEnergy = capLoad * tech->vdd * tech->vdd;
			readDynamicEnergy += outputDriver.readDynamicEnergy;
			readDynamicEnergy *= 1;	/* only one row is activated each time */
			writeDynamicEnergy = readDynamicEnergy;

		} else {
			/* Leakage power */
			leakage = CalculateGateLeakage(NAND, numNandInput, widthNandN, widthNandP,
					inputParameter->temperature, *tech) * tech->vdd;
			leakage += outputDriver.leakage;
			leakage *= numNandGate;
			/* Dynamic energy */
			capLoad = capNandOutput + outputDriver.capInput[0];
			readDynamicEnergy = capLoad * tech->vdd * tech->vdd;
			readDynamicEnergy += outputDriver.readDynamicEnergy;
			readDynamicEnergy *= 1;	/* only one row is activated each time */
			writeDynamicEnergy = readDynamicEnergy;
		}
	}
}

void BasicDecoder::PrintProperty() {
	cout << numNandInput << " to " << numNandGate << " Decoder Properties:" << endl;
	FunctionUnit::PrintProperty();
}
