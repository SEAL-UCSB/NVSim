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


#include "Bank.h"

Bank::Bank() {
	// TODO Auto-generated constructor stub
	initialized = false;
	invalid = false;
}

Bank::~Bank() {
	// TODO Auto-generated destructor stub
}

void Bank::PrintProperty() {
	cout << "Bank Properties:" << endl;
	FunctionUnit::PrintProperty();
}

Bank & Bank::operator=(const Bank &rhs) {
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
	numRowMat = rhs.numRowMat;
	numColumnMat = rhs.numColumnMat;
	capacity = rhs.capacity;
	blockSize = rhs.blockSize;
	associativity = rhs.associativity;
	numRowPerSet = rhs.numRowPerSet;
	numActiveMatPerRow = rhs.numActiveMatPerRow;
	numActiveMatPerColumn = rhs.numActiveMatPerColumn;
	muxSenseAmp = rhs.muxSenseAmp;
	internalSenseAmp = rhs.internalSenseAmp;
	muxOutputLev1 = rhs.muxOutputLev1;
	muxOutputLev2 = rhs.muxOutputLev2;
	areaOptimizationLevel = rhs.areaOptimizationLevel;
	memoryType = rhs.memoryType;
	numRowSubarray = rhs.numRowSubarray;
	numColumnSubarray = rhs.numColumnSubarray;
	numActiveSubarrayPerRow = rhs.numActiveSubarrayPerRow;
	numActiveSubarrayPerColumn = rhs.numActiveSubarrayPerColumn;
	mat = rhs.mat;
	return *this;
}
