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


#ifndef INPUTPARAMETER_H_
#define INPUTPARAMETER_H_

#include <iostream>
#include <string>
#include <stdint.h>

#include "typedef.h"

using namespace std;

class InputParameter {
public:
	InputParameter();
	virtual ~InputParameter();

	/* Functions */
	void ReadInputParameterFromFile(const std::string & inputFile);
	void PrintInputParameter();

	/* Properties */
	DesignTarget designTarget;		/* Cache, RAM, or CAM */
	OptimizationTarget optimizationTarget;	/* Either read latency, write latency, read energy, write energy, leakage, or area */
	int processNode;				/* Process node (nm) */
	int64_t capacity;				/* Memory/cache capacity, Unit: Byte */
	long wordWidth;					/* The width of each input/output word, Unit: bit */
	DeviceRoadmap deviceRoadmap;	/* ITRS roadmap: HP, LSTP, or LOP */
	string fileMemCell;				/* Input file name of memory cell type */
	int temperature;				/* The ambient temperature, Unit: K */
	double maxDriverCurrent;        /* The maximum driving current that the wordline/bitline driver can provide */
	WriteScheme writeScheme;		/* The write scheme */
	double readLatencyConstraint;	/* The allowed variation to the best read latency */
	double writeLatencyConstraint;	/* The allowed variation to the best write latency */
	double readDynamicEnergyConstraint;		/* The allowed variation to the best read dynamic energy */
	double writeDynamicEnergyConstraint;	/* The allowed variation to the best write dynamic energy */
	double leakageConstraint;		/* The allowed variation to the best leakage energy */
	double areaConstraint;			/* The allowed variation to the best leakage energy */
	double readEdpConstraint;		/* The allowed variation to the best read EDP */
	double writeEdpConstraint;		/* The allowed variation to the best write EDP */
	bool isConstraintApplied;		/* If any design constraint is applied */
	bool isPruningEnabled;			/* Whether to prune the results during the exploration */
	bool useCactiAssumption;		/* Use the CACTI assumptions on the array organization */

	int associativity;				/* Associativity, for cache design only */
	CacheAccessMode cacheAccessMode;	/* Access mode (for cache only) : normal, sequential, fast */

	long pageSize;					/* Unit: bit, For DRAM and NAND flash memory only */
	long flashBlockSize;				/* Unit: bit, For NAND flash memory only */

	RoutingMode routingMode;
	bool internalSensing;

	double maxNmosSize;				/* Default value is MAX_NMOS_SIZE in constant.h, however, user might change it, Unit: F */

	string outputFilePrefix;

	int minNumRowMat;
	int maxNumRowMat;
	int minNumColumnMat;
	int maxNumColumnMat;
	int minNumActiveMatPerRow;
	int maxNumActiveMatPerRow;
	int minNumActiveMatPerColumn;
	int maxNumActiveMatPerColumn;
	int minNumRowSubarray;
	int maxNumRowSubarray;
	int minNumColumnSubarray;
	int maxNumColumnSubarray;
	int minNumActiveSubarrayPerRow;
	int maxNumActiveSubarrayPerRow;
	int minNumActiveSubarrayPerColumn;
	int maxNumActiveSubarrayPerColumn;
	int minMuxSenseAmp;
	int maxMuxSenseAmp;
	int minMuxOutputLev1;
	int maxMuxOutputLev1;
	int minMuxOutputLev2;
	int maxMuxOutputLev2;
	int minNumRowPerSet;
	int maxNumRowPerSet;
	int minAreaOptimizationLevel;	/* This one is actually OptPriority type */
	int maxAreaOptimizationLevel;	/* This one is actually OptPriority type */
	int minLocalWireType;			/* This one is actually WireType type */
	int maxLocalWireType;			/* This one is actually WireType type */
	int minGlobalWireType;			/* This one is actually WireType type */
	int maxGlobalWireType;			/* This one is actually WireType type */
	int minLocalWireRepeaterType;		/* This one is actually WireRepeaterType type */
	int maxLocalWireRepeaterType;		/* This one is actually WireRepeaterType type */
	int minGlobalWireRepeaterType;		/* This one is actually WireRepeaterType type */
	int maxGlobalWireRepeaterType;		/* This one is actually WireRepeaterType type */
	int minIsLocalWireLowSwing;		/* This one is actually boolean */
	int maxIsLocalWireLowSwing;		/* This one is actually boolean */
	int minIsGlobalWireLowSwing;		/* This one is actually boolean */
	int maxIsGlobalWireLowSwing;		/* This one is actually boolean */
};

#endif /* INPUTPARAMETER_H_ */
