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


#ifndef MACROS_H_
#define MACROS_H_


#define INITIAL_BASIC_WIRE { \
	WireType basicWireType; \
	WireRepeaterType basicWireRepeaterType; \
	bool isBasicLowSwing; \
	if (inputParameter->minLocalWireType == inputParameter->maxLocalWireType) \
		basicWireType = (WireType)inputParameter->minLocalWireType; \
	else \
		basicWireType = local_aggressive; \
	if (inputParameter->minLocalWireRepeaterType == inputParameter->maxLocalWireRepeaterType) \
		basicWireRepeaterType = (WireRepeaterType)inputParameter->minLocalWireRepeaterType; \
	else \
		basicWireRepeaterType = repeated_none; \
	if (inputParameter->minIsLocalWireLowSwing == inputParameter->maxIsLocalWireLowSwing) \
		isBasicLowSwing = inputParameter->minIsLocalWireLowSwing; \
	else \
		isBasicLowSwing = false; \
	localWire->Initialize(inputParameter->processNode, basicWireType, basicWireRepeaterType, inputParameter->temperature, isBasicLowSwing); \
	if (inputParameter->minGlobalWireType == inputParameter->maxGlobalWireType) \
		basicWireType = (WireType)inputParameter->minGlobalWireType; \
	else \
		basicWireType = global_aggressive; \
	if (inputParameter->minGlobalWireRepeaterType == inputParameter->maxGlobalWireRepeaterType) \
		basicWireRepeaterType = (WireRepeaterType)inputParameter->minGlobalWireRepeaterType; \
	else \
		basicWireRepeaterType = repeated_none; \
	if (inputParameter->minIsGlobalWireLowSwing == inputParameter->maxIsGlobalWireLowSwing) \
		isBasicLowSwing = inputParameter->minIsGlobalWireLowSwing; \
	else \
		isBasicLowSwing = false; \
	globalWire->Initialize(inputParameter->processNode, basicWireType, basicWireRepeaterType, inputParameter->temperature, isBasicLowSwing); \
}



#define REFINE_LOCAL_WIRE_FORLOOP \
	for (localWireType = inputParameter->minLocalWireType; localWireType <= inputParameter->maxLocalWireType; localWireType++) \
	for (localWireRepeaterType = inputParameter->minLocalWireRepeaterType; localWireRepeaterType <= inputParameter->maxLocalWireRepeaterType; localWireRepeaterType++) \
	for (isLocalWireLowSwing = inputParameter->minIsLocalWireLowSwing; isLocalWireLowSwing <= inputParameter->maxIsLocalWireLowSwing; isLocalWireLowSwing++) \
	if ((WireRepeaterType)localWireRepeaterType == repeated_none || (bool)isLocalWireLowSwing == false)


#define REFINE_GLOBAL_WIRE_FORLOOP \
	for (globalWireType = inputParameter->minGlobalWireType; globalWireType <= inputParameter->maxGlobalWireType; globalWireType++) \
	for (globalWireRepeaterType = inputParameter->minGlobalWireRepeaterType; globalWireRepeaterType <= inputParameter->maxGlobalWireRepeaterType; globalWireRepeaterType++) \
	for (isGlobalWireLowSwing = inputParameter->minIsGlobalWireLowSwing; isGlobalWireLowSwing <= inputParameter->maxIsGlobalWireLowSwing; isGlobalWireLowSwing++) \
	if ((WireRepeaterType)globalWireRepeaterType == repeated_none || (bool)isGlobalWireLowSwing == false)




#define LOAD_GLOBAL_WIRE(oldResult) { \
	globalWire->Initialize(inputParameter->processNode, (oldResult).globalWire->wireType, (oldResult).globalWire->wireRepeaterType, \
			inputParameter->temperature, (oldResult).globalWire->isLowSwing); \
}


#define LOAD_LOCAL_WIRE(oldResult) \
	localWire->Initialize(inputParameter->processNode, (oldResult).localWire->wireType, (oldResult).localWire->wireRepeaterType, \
			inputParameter->temperature, (oldResult).localWire->isLowSwing);



#define TRY_AND_UPDATE(oldResult, memoryType) { \
	if (inputParameter->routingMode == h_tree) \
		trialBank = new BankWithHtree(); \
	else \
		trialBank = new BankWithoutHtree(); \
	trialBank->Initialize((oldResult).bank->numRowMat, (oldResult).bank->numColumnMat, (oldResult).bank->capacity, (oldResult).bank->blockSize, (oldResult).bank->associativity, \
				(oldResult).bank->numRowPerSet, (oldResult).bank->numActiveMatPerRow, (oldResult).bank->numActiveMatPerColumn, (oldResult).bank->muxSenseAmp, \
				inputParameter->internalSensing, (oldResult).bank->muxOutputLev1, (oldResult).bank->muxOutputLev2, (oldResult).bank->numRowSubarray, (oldResult).bank->numColumnSubarray, \
				(oldResult).bank->numActiveSubarrayPerRow, (oldResult).bank->numActiveSubarrayPerColumn, (oldResult).bank->areaOptimizationLevel, (memoryType)); \
	trialBank->CalculateArea(); \
	trialBank->CalculateRC(); \
	trialBank->CalculateLatencyAndPower(); \
	*(tempResult.bank) = *trialBank; \
	*(tempResult.localWire) = *localWire; \
	*(tempResult.globalWire) = *globalWire; \
	oldResult.compareAndUpdate(tempResult); \
	delete trialBank; \
}



#define BIGFOR \
	for (numRowMat = inputParameter->minNumRowMat; numRowMat <= inputParameter->maxNumRowMat; numRowMat *= 2) \
	for (numColumnMat = inputParameter->minNumColumnMat; numColumnMat <= inputParameter->maxNumColumnMat; numColumnMat *= 2) \
	for (numActiveMatPerRow = MIN(numColumnMat, inputParameter->minNumActiveMatPerRow); numActiveMatPerRow <= MIN(numColumnMat, inputParameter->maxNumActiveMatPerRow); numActiveMatPerRow *= 2) \
	for (numActiveMatPerColumn = MIN(numRowMat, inputParameter->minNumActiveMatPerColumn); numActiveMatPerColumn <= MIN(numRowMat, inputParameter->maxNumActiveMatPerColumn); numActiveMatPerColumn *= 2) \
	for (numRowSubarray = inputParameter->minNumRowSubarray; numRowSubarray <= inputParameter->maxNumRowSubarray; numRowSubarray *= 2) \
	for (numColumnSubarray = inputParameter->minNumColumnSubarray; numColumnSubarray <= inputParameter->maxNumColumnSubarray; numColumnSubarray *= 2) \
	for (numActiveSubarrayPerRow = MIN(numColumnSubarray, inputParameter->minNumActiveSubarrayPerRow); numActiveSubarrayPerRow <= MIN(numColumnSubarray, inputParameter->maxNumActiveSubarrayPerRow); numActiveSubarrayPerRow *=2) \
	for (numActiveSubarrayPerColumn = MIN(numRowSubarray, inputParameter->minNumActiveSubarrayPerColumn); numActiveSubarrayPerColumn <= MIN(numRowSubarray, inputParameter->maxNumActiveSubarrayPerColumn); numActiveSubarrayPerColumn *= 2) \
	for (muxSenseAmp = inputParameter->minMuxSenseAmp; muxSenseAmp <= inputParameter->maxMuxSenseAmp; muxSenseAmp *= 2) \
	for (muxOutputLev1 = inputParameter->minMuxOutputLev1; muxOutputLev1 <= inputParameter->maxMuxOutputLev1; muxOutputLev1 *= 2) \
	for (muxOutputLev2 = inputParameter->minMuxOutputLev2; muxOutputLev2 <= inputParameter->maxMuxOutputLev2; muxOutputLev2 *= 2) \
	for (numRowPerSet = inputParameter->minNumRowPerSet; numRowPerSet <= MIN(inputParameter->maxNumRowPerSet, inputParameter->associativity); numRowPerSet *= 2) \
	for (areaOptimizationLevel = inputParameter->minAreaOptimizationLevel; areaOptimizationLevel <= inputParameter->maxAreaOptimizationLevel; areaOptimizationLevel++)



#define CALCULATE(bank, memoryType) { \
	if (inputParameter->routingMode == h_tree) \
		(bank) = new BankWithHtree(); \
	else \
		(bank) = new BankWithoutHtree(); \
	(bank)->Initialize(numRowMat, numColumnMat, capacity, blockSize, associativity, \
				numRowPerSet, numActiveMatPerRow, numActiveMatPerColumn, muxSenseAmp, \
				inputParameter->internalSensing, muxOutputLev1, muxOutputLev2, numRowSubarray, numColumnSubarray, \
				numActiveSubarrayPerRow, numActiveSubarrayPerColumn, (BufferDesignTarget)areaOptimizationLevel, (memoryType)); \
	(bank)->CalculateArea(); \
	(bank)->CalculateRC(); \
	(bank)->CalculateLatencyAndPower(); \
}


#define UPDATE_BEST_DATA { \
	*(tempResult.bank) = *dataBank; \
	*(tempResult.localWire) = *localWire; \
	*(tempResult.globalWire) = *globalWire; \
	for (int i = 0; i < (int)full_exploration; i++) \
		bestDataResults[i].compareAndUpdate(tempResult); \
}


#define VERIFY_DATA_CAPACITY { \
	if ((long long)dataBank->mat.subarray.numColumn * dataBank->mat.subarray.numRow * dataBank->numColumnMat * \
			dataBank->numRowMat * dataBank->numColumnSubarray * dataBank->numRowSubarray != capacity) { \
				cout << "1 Bank = " << dataBank->numRowMat << "x" << dataBank->numColumnMat << " Mats" << endl; \
				cout << "Activation - " << dataBank->numActiveMatPerColumn << "x" << dataBank->numActiveMatPerRow << " Mats" << endl; \
				cout << "1 Mat  = " << dataBank->numRowSubarray << "x" << dataBank->numColumnSubarray << " Subarrays" << endl; \
				cout << "Activation - " << dataBank->numActiveSubarrayPerColumn << "x" << dataBank->numActiveSubarrayPerRow << " Subarrays" << endl; \
				cout << "Mux Degree - " << dataBank->muxSenseAmp << " x " << dataBank->muxOutputLev1 << " x " << dataBank->muxOutputLev2 << endl; \
				cout << "ERROR: DATA capacity violation. Shouldn't happen" << endl; \
				exit(-1); \
			} \
}


#define UPDATE_BEST_TAG { \
	*(tempResult.bank) = *tagBank; \
	*(tempResult.localWire) = *localWire; \
	*(tempResult.globalWire) = *globalWire; \
	for (int i = 0; i < (int)full_exploration; i++) \
		bestTagResults[i].compareAndUpdate(tempResult); \
}


#define VERIFY_TAG_CAPACITY { \
	if ((long long)tagBank->mat.subarray.numColumn * tagBank->mat.subarray.numRow * tagBank->numColumnMat * \
			tagBank->numRowMat * tagBank->numColumnSubarray * tagBank->numRowSubarray != capacity) { \
				cout << "1 Bank = " << tagBank->numRowMat << "x" << tagBank->numColumnMat << " Mats" << endl; \
				cout << "Activation - " << tagBank->numActiveMatPerColumn << "x" << tagBank->numActiveMatPerRow << " Mats" << endl; \
				cout << "1 Mat  = " << tagBank->numRowSubarray << "x" << tagBank->numColumnSubarray << " Subarrays" << endl; \
				cout << "Activation - " << tagBank->numActiveSubarrayPerColumn << "x" << tagBank->numActiveSubarrayPerRow << " Subarrays" << endl; \
				cout << "Mux Degree - " << tagBank->muxSenseAmp << " x " << tagBank->muxOutputLev1 << " x " << tagBank->muxOutputLev2 << endl; \
				cout << "ERROR: DATA capacity violation. Shouldn't happen" << endl; \
				exit(-1); \
			} \
}


#define REDUCE_SEARCH_SIZE { \
	inputParameter->minNumRowMat = 1; \
	inputParameter->maxNumRowMat = 64; \
	inputParameter->minNumColumnMat = 1; \
	inputParameter->maxNumColumnMat = 64; \
	inputParameter->minNumActiveMatPerRow = 1; \
	inputParameter->maxNumActiveMatPerRow = inputParameter->maxNumColumnMat; \
	inputParameter->minNumActiveMatPerColumn = 1; \
	inputParameter->maxNumActiveMatPerColumn = inputParameter->maxNumRowMat; \
	inputParameter->minNumRowSubarray = 1; \
	inputParameter->maxNumRowSubarray = 2; \
	inputParameter->minNumColumnSubarray = 1; \
	inputParameter->maxNumColumnSubarray = 2; \
	inputParameter->minNumActiveSubarrayPerRow = 1; \
	inputParameter->maxNumActiveSubarrayPerRow = inputParameter->maxNumColumnSubarray; \
	inputParameter->minNumActiveSubarrayPerColumn = 1; \
	inputParameter->maxNumActiveSubarrayPerColumn = inputParameter->maxNumRowSubarray; \
	inputParameter->minMuxSenseAmp = 1; \
	inputParameter->maxMuxSenseAmp = 64; \
	inputParameter->minMuxOutputLev1 = 1; \
	inputParameter->maxMuxOutputLev1 = 64; \
	inputParameter->minMuxOutputLev2 = 1; \
	inputParameter->maxMuxOutputLev2 = 64; \
	inputParameter->minNumRowPerSet = 1; \
	inputParameter->maxNumRowPerSet = 1; \
	inputParameter->minAreaOptimizationLevel = latency_first; \
	inputParameter->maxAreaOptimizationLevel = area_first;	\
	inputParameter->minLocalWireType = local_aggressive; \
	inputParameter->maxLocalWireType = local_conservative; \
	inputParameter->minGlobalWireType = global_aggressive; \
	inputParameter->maxGlobalWireType = global_conservative; \
	inputParameter->minLocalWireRepeaterType = repeated_none; \
	inputParameter->maxLocalWireRepeaterType = repeated_opt; \
	inputParameter->minGlobalWireRepeaterType = repeated_none; \
	inputParameter->maxGlobalWireRepeaterType = repeated_opt; \
	inputParameter->minIsLocalWireLowSwing = false; \
	inputParameter->maxIsLocalWireLowSwing = true; \
	inputParameter->minIsGlobalWireLowSwing = false; \
	inputParameter->maxIsGlobalWireLowSwing = true; \
}


#define RESTORE_SEARCH_SIZE { \
	inputParameter->minNumRowMat = 1; \
	inputParameter->maxNumRowMat = 512; \
	inputParameter->minNumColumnMat = 1; \
	inputParameter->maxNumColumnMat = 512; \
	inputParameter->minNumActiveMatPerRow = 1; \
	inputParameter->maxNumActiveMatPerRow = inputParameter->maxNumColumnMat; \
	inputParameter->minNumActiveMatPerColumn = 1; \
	inputParameter->maxNumActiveMatPerColumn = inputParameter->maxNumRowMat; \
	inputParameter->minNumRowSubarray = 1; \
	inputParameter->maxNumRowSubarray = 2; \
	inputParameter->minNumColumnSubarray = 1; \
	inputParameter->maxNumColumnSubarray = 2; \
	inputParameter->minNumActiveSubarrayPerRow = 1; \
	inputParameter->maxNumActiveSubarrayPerRow = inputParameter->maxNumColumnSubarray; \
	inputParameter->minNumActiveSubarrayPerColumn = 1; \
	inputParameter->maxNumActiveSubarrayPerColumn = inputParameter->maxNumRowSubarray; \
	inputParameter->minMuxSenseAmp = 1; \
	inputParameter->maxMuxSenseAmp = 256; \
	inputParameter->minMuxOutputLev1 = 1; \
	inputParameter->maxMuxOutputLev1 = 256; \
	inputParameter->minMuxOutputLev2 = 1; \
	inputParameter->maxMuxOutputLev2 = 256; \
	inputParameter->minNumRowPerSet = 1; \
	inputParameter->maxNumRowPerSet = inputParameter->associativity; \
	inputParameter->minAreaOptimizationLevel = latency_first; \
	inputParameter->maxAreaOptimizationLevel = area_first; \
	inputParameter->minLocalWireType = local_aggressive; \
	inputParameter->maxLocalWireType = semi_conservative; \
	inputParameter->minGlobalWireType = semi_aggressive; \
	inputParameter->maxGlobalWireType = global_conservative; \
	inputParameter->minLocalWireRepeaterType = repeated_none; \
	inputParameter->maxLocalWireRepeaterType = repeated_50;		/* The limit is repeated_50 */ \
	inputParameter->minGlobalWireRepeaterType = repeated_none; \
	inputParameter->maxGlobalWireRepeaterType = repeated_50;	/* The limit is repeated_50 */ \
	inputParameter->minIsLocalWireLowSwing = false; \
	inputParameter->maxIsLocalWireLowSwing = true; \
	inputParameter->minIsGlobalWireLowSwing = false; \
	inputParameter->maxIsGlobalWireLowSwing = true; \
}


#define APPLY_LIMIT(result) { \
	(result).reset(); \
	(result).limitReadLatency = allowedDataReadLatency; \
	(result).limitWriteLatency = allowedDataWriteLatency; \
	(result).limitReadDynamicEnergy = allowedDataReadDynamicEnergy; \
	(result).limitWriteDynamicEnergy = allowedDataWriteDynamicEnergy; \
	(result).limitReadEdp = allowedDataReadEdp; \
	(result).limitWriteEdp = allowedDataWriteEdp; \
	(result).limitArea = allowedDataArea; \
	(result).limitLeakage = allowedDataLeakage; \
}


#define OUTPUT_TO_FILE { \
	if (inputParameter->designTarget == cache) { \
		for (int i = 0; i < (int)full_exploration; i++) \
			tempResult.printAsCacheToCsvFile(bestTagResults[i], inputParameter->cacheAccessMode, outputFile); \
	} else { \
		tempResult.printToCsvFile(outputFile); \
		outputFile << endl; \
	} \
}

#define TO_SECOND(x) \
	((x) < 1e-9 ? (x) * 1e12 : (x) < 1e-6 ? (x) * 1e9 : (x) < 1e-3 ? (x) * 1e6 : (x) < 1 ? (x) * 1e3 : (x)) \
	<< \
	((x) < 1e-9 ? "ps" : (x) < 1e-6 ? "ns" : (x) < 1e-3 ? "us" : (x) < 1 ? "ms" : "s")

#define TO_BPS(x) \
	((x) < 1e3 ? (x) : (x) < 1e6 ? (x) / 1e3 : (x) < 1e9 ? (x) / 1e6 : (x) < 1e12 ? (x) / 1e9 : (x) / 1e12) \
	<< \
	((x) < 1e3 ? "B/s" : (x) < 1e6 ? "KB/s" : (x) < 1e9 ? "MB/s" : (x) < 1e12 ? "GB/s" : "TB/s")

#define TO_JOULE(x) \
	((x) < 1e-9 ? (x) * 1e12 : (x) < 1e-6 ? (x) * 1e9 : (x) < 1e-3 ? (x) * 1e6 : (x) < 1 ? (x) * 1e3 : (x)) \
	<< \
	((x) < 1e-9 ? "pJ" : (x) < 1e-6 ? "nJ" : (x) < 1e-3 ? "uJ" : (x) < 1 ? "mJ" : "J")

#define TO_WATT(x) \
	((x) < 1e-9 ? (x) * 1e12 : (x) < 1e-6 ? (x) * 1e9 : (x) < 1e-3 ? (x) * 1e6 : (x) < 1 ? (x) * 1e3 : (x)) \
	<< \
	((x) < 1e-9 ? "pW" : (x) < 1e-6 ? "nW" : (x) < 1e-3 ? "uW" : (x) < 1 ? "mW" : "W")

#define TO_METER(x) \
	((x) < 1e-9 ? (x) * 1e12 : (x) < 1e-6 ? (x) * 1e9 : (x) < 1e-3 ? (x) * 1e6 : (x) < 1 ? (x) * 1e3 : (x)) \
	<< \
	((x) < 1e-9 ? "pm" : (x) < 1e-6 ? "nm" : (x) < 1e-3 ? "um" : (x) < 1 ? "mm" : "m")

#define TO_SQM(x) \
	((x) < 1e-12 ? (x) * 1e18 : (x) < 1e-6 ? (x) * 1e12 : (x) < 1 ? (x) * 1e6 : (x)) \
	<< \
	((x) < 1e-12 ? "nm^2" : (x) < 1e-6 ? "um^2" : (x) < 1 ? "mm^2" : "m^2")

#endif /* MACROS_H_ */
