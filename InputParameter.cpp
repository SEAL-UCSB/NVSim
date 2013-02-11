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


#include "InputParameter.h"
#include "global.h"
#include "constant.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

InputParameter::InputParameter() {
	// TODO Auto-generated constructor stub
	designTarget = cache;
	optimizationTarget = read_latency_optimized;
	processNode = 90;
	maxDriverCurrent = 0;

	maxNmosSize = MAX_NMOS_SIZE;

	minNumRowMat = 1;
	maxNumRowMat = 512;
	minNumColumnMat = 1;
	maxNumColumnMat = 512;
	minNumActiveMatPerRow = 1;
	maxNumActiveMatPerRow = maxNumColumnMat;
	minNumActiveMatPerColumn = 1;
	maxNumActiveMatPerColumn = maxNumRowMat;
	minNumRowSubarray = 1;
	maxNumRowSubarray = 2;
	minNumColumnSubarray = 1;
	maxNumColumnSubarray = 2;
	minNumActiveSubarrayPerRow = 1;
	maxNumActiveSubarrayPerRow = maxNumColumnSubarray;
	minNumActiveSubarrayPerColumn = 1;
	maxNumActiveSubarrayPerColumn = maxNumRowSubarray;
	minMuxSenseAmp = 1;
	maxMuxSenseAmp = 256;
	minMuxOutputLev1 = 1;
	maxMuxOutputLev1 = 256;
	minMuxOutputLev2 = 1;
	maxMuxOutputLev2 = 256;
	minNumRowPerSet = 1;
	maxNumRowPerSet = 256;
	minAreaOptimizationLevel = latency_first;
	maxAreaOptimizationLevel = area_first;
	minLocalWireType = local_aggressive;
	maxLocalWireType = local_conservative;
	minGlobalWireType = global_aggressive;
	maxGlobalWireType = global_conservative;
	minLocalWireRepeaterType = repeated_none;
	maxLocalWireRepeaterType = repeated_50;		/* The limit is repeated_50 */
	minGlobalWireRepeaterType = repeated_none;
	maxGlobalWireRepeaterType = repeated_50;	/* The limit is repeated_50 */
	minIsLocalWireLowSwing = false;
	maxIsLocalWireLowSwing = true;
	minIsGlobalWireLowSwing = false;
	maxIsGlobalWireLowSwing = true;

	associativity = 1;				/* Default value for non-cache design */
	routingMode = h_tree;
	internalSensing = true;

	useCactiAssumption = false;

	writeScheme = normal_write;
	cacheAccessMode = normal_access_mode;

	readLatencyConstraint = 1e41;
	writeLatencyConstraint = 1e41;
	readDynamicEnergyConstraint = 1e41;
	writeDynamicEnergyConstraint = 1e41;
	leakageConstraint = 1e41;
	areaConstraint = 1e41;
	readEdpConstraint = 1e41;
	writeEdpConstraint = 1e41;
	isConstraintApplied = false;
	isPruningEnabled = false;

	pageSize = 0;
	flashBlockSize = 0;

	outputFilePrefix = "output";	/* Default output file name */
}

InputParameter::~InputParameter() {
	// TODO Auto-generated destructor stub
}

void InputParameter::ReadInputParameterFromFile(const std::string & inputFile) {
	FILE *fp = fopen(inputFile.c_str(), "r");
	char line[5000];
	char tmp[5000];

	if (!fp) {
		cout << inputFile << " cannot be found!\n";
		exit(-1);
	}

	while (fscanf(fp, "%[^\n]\n", line) != EOF) {
		if (!strncmp("-DesignTarget", line, strlen("-DesignTarget"))) {
			sscanf(line, "-DesignTarget: %s", tmp);
			if (!strcmp(tmp, "cache"))
				designTarget = cache;
			else if (!strcmp(tmp, "RAM")) {
				designTarget = RAM_chip;
				minNumRowPerSet = 1;
				maxNumRowPerSet = 1;
			} else {
				designTarget = CAM_chip;
				minNumRowPerSet = 1;
				maxNumRowPerSet = 1;
			}
			continue;
		}

		if (!strncmp("-OptimizationTarget", line, strlen("-OptimizationTarget"))) {
			sscanf(line, "-OptimizationTarget: %s", tmp);
			if (!strcmp(tmp, "ReadLatency"))
				optimizationTarget = read_latency_optimized;
			else if (!strcmp(tmp, "WriteLatency"))
				optimizationTarget = write_latency_optimized;
			else if (!strcmp(tmp, "ReadDynamicEnergy"))
				optimizationTarget = read_energy_optimized;
			else if (!strcmp(tmp, "WriteDynamicEnergy"))
				optimizationTarget = write_energy_optimized;
			else if (!strcmp(tmp, "ReadEDP"))
				optimizationTarget = read_edp_optimized;
			else if (!strcmp(tmp, "WriteEDP"))
				optimizationTarget = write_edp_optimized;
			else if (!strcmp(tmp, "LeakagePower"))
				optimizationTarget = leakage_optimized;
			else if (!strcmp(tmp, "Area"))
				optimizationTarget = area_optimized;
			else
				optimizationTarget = full_exploration;
			continue;
		}

		if (!strncmp("-OutputFilePrefix", line, strlen("-OutputFilePrefix"))) {
			sscanf(line, "-OutputFilePrefix: %s", tmp);
			outputFilePrefix = (string)tmp;
			continue;
		}

		if (!strncmp("-ProcessNode", line, strlen("-ProcessNode"))) {
			sscanf(line, "-ProcessNode: %d", &processNode);
			continue;
		}
		if (!strncmp("-Capacity (B)", line, strlen("-Capacity (B)"))) {
			long cap;
			sscanf(line, "-Capacity (B): %ld", &cap);
			capacity = cap;
			continue;
		}
		if (!strncmp("-Capacity (KB)", line, strlen("-Capacity (KB)"))) {
			long cap;
			sscanf(line, "-Capacity (KB): %ld", &cap);
			capacity = cap * 1024;
			continue;
		}
		if (!strncmp("-Capacity (MB)", line, strlen("-Capacity (MB)"))) {
			long cap;
			sscanf(line, "-Capacity (MB): %ld", &cap);
			capacity = cap * 1024*1024;
			continue;
		}
		if (!strncmp("-WordWidth", line, strlen("-WordWidth"))) {
			sscanf(line, "-WordWidth (bit): %ld", &wordWidth);
			continue;
		}
		if (!strncmp("-Associativity", line, strlen("-Associativity"))) {
			sscanf(line, "-Associativity (for cache only): %d", &associativity);
			continue;
		}
		if (!strncmp("-Temperature", line, strlen("-Temperature"))) {
			sscanf(line, "-Temperature (K): %d", &temperature);
			continue;
		}
		if (!strncmp("-MaxDriverCurrent", line, strlen("-MaxDriverCurrent"))) {
			sscanf(line, "-MaxDriverCurrent (uA): %lf", &maxDriverCurrent);
			continue;
		}
		if (!strncmp("-DeviceRoadmap", line, strlen("-DeviceRoadmap"))) {
			sscanf(line, "-DeviceRoadmap: %s", tmp);
			if (!strcmp(tmp, "HP"))
				deviceRoadmap = HP;
			else if (!strcmp(tmp, "LSTP"))
				deviceRoadmap = LSTP;
			else
				deviceRoadmap = LOP;
			continue;
		}

		if (!strncmp("-WriteScheme", line, strlen("-WriteScheme"))) {
			sscanf(line, "-WriteScheme: %s", tmp);
			if (!strcmp(tmp, "SetBeforeReset"))
				writeScheme = set_before_reset;
			else if (!strcmp(tmp, "ResetBeforeSet"))
				writeScheme = reset_before_set;
			else if (!strcmp(tmp, "EraseBeforeSet"))
				writeScheme = erase_before_set;
			else if (!strcmp(tmp, "EraseBeforeReset"))
				writeScheme = erase_before_reset;
			else if (!strcmp(tmp, "WriteAndVerify"))
				writeScheme = write_and_verify;
			else
				writeScheme = normal_write;
			continue;
		}

		if (!strncmp("-CacheAccessMode", line, strlen("-CacheAccessMode"))) {
			sscanf(line, "-CacheAccessMode: %s", tmp);
			if (!strcmp(tmp, "Sequential"))
				cacheAccessMode = sequential_access_mode;
			else if (!strcmp(tmp, "Fast"))
				cacheAccessMode = fast_access_mode;
			else
				cacheAccessMode = normal_access_mode;
			continue;
		}

		if (!strncmp("-LocalWireType", line, strlen("-LocalWireType"))) {
			sscanf(line, "-LocalWireType: %s", tmp);
			if (!strcmp(tmp, "LocalAggressive")) {
				minLocalWireType = local_aggressive;
				maxLocalWireType = local_aggressive;
			} else if (!strcmp(tmp, "LocalConservative")) {
				minLocalWireType = local_conservative;
				maxLocalWireType = local_conservative;
			} else if (!strcmp(tmp, "SemiAggressive")) {
				minLocalWireType = semi_aggressive;
				maxLocalWireType = semi_aggressive;
			} else if (!strcmp(tmp, "SemiConservative")) {
				minLocalWireType = semi_conservative;
				maxLocalWireType = semi_conservative;
			} else if (!strcmp(tmp, "GlobalAggressive")) {
				minLocalWireType = global_aggressive;
				maxLocalWireType = global_aggressive;
			} else if (!strcmp(tmp, "GlobalConservative")) {
				minLocalWireType = global_conservative;
				maxLocalWireType = global_conservative;
			} else {	/* no supported yet */
				minLocalWireType = dram_wordline;
				maxLocalWireType = dram_wordline;
			}
			continue;
		}
		if (!strncmp("-LocalWireRepeaterType", line, strlen("-LocalWireRepeaterType"))) {
			sscanf(line, "-LocalWireRepeaterType: %s", tmp);
			if (!strcmp(tmp, "RepeatedOpt")) {
				minLocalWireRepeaterType = repeated_opt;
				maxLocalWireRepeaterType = repeated_opt;
			} else if (!strcmp(tmp, "Repeated5%Penalty")) {
				minLocalWireRepeaterType = repeated_5;
				maxLocalWireRepeaterType = repeated_5;
			} else if (!strcmp(tmp, "Repeated10%Penalty")) {
				minLocalWireRepeaterType = repeated_10;
				maxLocalWireRepeaterType = repeated_10;
			} else if (!strcmp(tmp, "Repeated20%Penalty")) {
				minLocalWireRepeaterType = repeated_20;
				maxLocalWireRepeaterType = repeated_20;
			} else if (!strcmp(tmp, "Repeated30%Penalty")) {
				minLocalWireRepeaterType = repeated_30;
				maxLocalWireRepeaterType = repeated_30;
			} else if (!strcmp(tmp, "Repeated40%Penalty")) {
				minLocalWireRepeaterType = repeated_40;
				maxLocalWireRepeaterType = repeated_40;
			} else if (!strcmp(tmp, "Repeated50%Penalty")) {
				minLocalWireRepeaterType = repeated_50;
				maxLocalWireRepeaterType = repeated_50;
			} else {
				minLocalWireRepeaterType = repeated_none;
				maxLocalWireRepeaterType = repeated_none;
			}
			continue;
		}
		if (!strncmp("-LocalWireUseLowSwing", line, strlen("-LocalWireUseLowSwing"))) {
			sscanf(line, "-LocalWireUseLowSwing: %s", tmp);
			if (!strcmp(tmp, "Yes")) {
				minIsLocalWireLowSwing = 1;
				maxIsLocalWireLowSwing = 1;
			} else {
				minIsLocalWireLowSwing = 0;
				maxIsLocalWireLowSwing = 0;
			}
			continue;
		}

		if (!strncmp("-GlobalWireType", line, strlen("-GlobalWireType"))) {
			sscanf(line, "-GlobalWireType: %s", tmp);
			if (!strcmp(tmp, "LocalAggressive")) {
				minGlobalWireType = local_aggressive;
				maxGlobalWireType = local_aggressive;
			} else if (!strcmp(tmp, "LocalConservative")) {
				minGlobalWireType = local_conservative;
				maxGlobalWireType = local_conservative;
			} else if (!strcmp(tmp, "SemiAggressive")) {
				minGlobalWireType = semi_aggressive;
				maxGlobalWireType = semi_aggressive;
			} else if (!strcmp(tmp, "SemiConservative")) {
				minGlobalWireType = semi_conservative;
				maxGlobalWireType = semi_conservative;
			} else if (!strcmp(tmp, "GlobalAggressive")) {
				minGlobalWireType = global_aggressive;
				maxGlobalWireType = global_aggressive;
			} else if (!strcmp(tmp, "GlobalConservative")) {
				minGlobalWireType = global_conservative;
				maxGlobalWireType = global_conservative;
			} else {	/* no supported yet */
				minGlobalWireType = dram_wordline;
				maxGlobalWireType = dram_wordline;
			}
			continue;
		}
		if (!strncmp("-GlobalWireRepeaterType", line, strlen("-GlobalWireRepeaterType"))) {
			sscanf(line, "-GlobalWireRepeaterType: %s", tmp);
			if (!strcmp(tmp, "RepeatedOpt")) {
				minGlobalWireRepeaterType = repeated_opt;
				maxGlobalWireRepeaterType = repeated_opt;
			} else if (!strcmp(tmp, "Repeated5%Penalty")) {
				minGlobalWireRepeaterType = repeated_5;
				maxGlobalWireRepeaterType = repeated_5;
			} else if (!strcmp(tmp, "Repeated10%Penalty")) {
				minGlobalWireRepeaterType = repeated_10;
				maxGlobalWireRepeaterType = repeated_10;
			} else if (!strcmp(tmp, "Repeated20%Penalty")) {
				minGlobalWireRepeaterType = repeated_20;
				maxGlobalWireRepeaterType = repeated_20;
			} else if (!strcmp(tmp, "Repeated30%Penalty")) {
				minGlobalWireRepeaterType = repeated_30;
				maxGlobalWireRepeaterType = repeated_30;
			} else if (!strcmp(tmp, "Repeated40%Penalty")) {
				minGlobalWireRepeaterType = repeated_40;
				maxGlobalWireRepeaterType = repeated_40;
			} else if (!strcmp(tmp, "Repeated50%Penalty")) {
				minGlobalWireRepeaterType = repeated_50;
				maxGlobalWireRepeaterType = repeated_50;
			} else {
				minGlobalWireRepeaterType = repeated_none;
				maxGlobalWireRepeaterType = repeated_none;
			}
			continue;
		}
		if (!strncmp("-GlobalWireUseLowSwing", line, strlen("-GlobalWireUseLowSwing"))) {
			sscanf(line, "-GlobalWireUseLowSwing: %s", tmp);
			if (!strcmp(tmp, "Yes")) {
				minIsGlobalWireLowSwing = 1;
				maxIsGlobalWireLowSwing = 1;
			} else {
				minIsGlobalWireLowSwing = 0;
				maxIsGlobalWireLowSwing = 0;
			}
			continue;
		}

		if (!strncmp("-Routing", line, strlen("-Routing"))) {
			sscanf(line, "-Routing: %s", tmp);
			if (!strcmp(tmp, "H-tree"))
				routingMode = h_tree;
			else
				routingMode = non_h_tree;
			continue;
		}

		if (!strncmp("-InternalSensing", line, strlen("-InternalSensing"))) {
			sscanf(line, "-InternalSensing: %s", tmp);
			if (!strcmp(tmp, "true"))
				internalSensing = true;
			else
				internalSensing = false;
			continue;
		}

		if (!strncmp("-MemoryCellInputFile", line, strlen("-MemoryCellInputFile"))) {
			sscanf(line, "-MemoryCellInputFile: %s", tmp);
			fileMemCell = string(tmp);
			continue;
		}

		if (!strncmp("-MaxNmosSize", line, strlen("-MaxNmosSize"))) {
			sscanf(line, "-MaxNmosSize (F): %lf", &maxNmosSize);
			continue;
		}

		if (!strncmp("-ForceBank", line, strlen("-ForceBank"))) {
			sscanf(line, "-ForceBank (Total AxB, Active CxD): %dx%d, %dx%d",
					&minNumRowMat, &minNumColumnMat, &minNumActiveMatPerColumn, &minNumActiveMatPerRow);
			maxNumRowMat = minNumRowMat;
			maxNumColumnMat = minNumColumnMat;
			maxNumActiveMatPerColumn = minNumActiveMatPerColumn;
			maxNumActiveMatPerRow = minNumActiveMatPerRow;
			continue;
		}

		if (!strncmp("-ForceMat", line, strlen("-ForceMat"))) {
			sscanf(line, "-ForceMat (Total AxB, Active CxD): %dx%d, %dx%d",
					&minNumRowSubarray, &minNumColumnSubarray, &minNumActiveSubarrayPerColumn, &minNumActiveSubarrayPerRow);
			maxNumRowSubarray = minNumRowSubarray;
			maxNumColumnSubarray = minNumColumnSubarray;
			maxNumActiveSubarrayPerColumn = minNumActiveSubarrayPerColumn;
			maxNumActiveSubarrayPerRow = minNumActiveSubarrayPerRow;
			continue;
		}

		if (!strncmp("-ForceMuxSenseAmp", line, strlen("-ForceMuxSenseAmp"))) {
			sscanf(line, "-ForceMuxSenseAmp: %d", &minMuxSenseAmp);
			maxMuxSenseAmp = minMuxSenseAmp;
			continue;
		}

		if (!strncmp("-ForceMuxOutputLev1", line, strlen("-ForceMuxOutputLev1"))) {
			sscanf(line, "-ForceMuxOutputLev1: %d", &minMuxOutputLev1);
			maxMuxOutputLev1 = minMuxOutputLev1;
			continue;
		}

		if (!strncmp("-ForceMuxOutputLev2", line, strlen("-ForceMuxOutputLev2"))) {
			sscanf(line, "-ForceMuxOutputLev2: %d", &minMuxOutputLev2);
			maxMuxOutputLev2 = minMuxOutputLev2;
			continue;
		}

		if (!strncmp("-UseCactiAssumption", line, strlen("-UseCactiAssumption"))) {
			sscanf(line, "-UseCactiAssumption: %s", tmp);
			if (!strcmp(tmp, "Yes")) {
				useCactiAssumption = true;
				minNumActiveMatPerRow = maxNumColumnMat;
				maxNumActiveMatPerRow = maxNumColumnMat;
				minNumActiveMatPerColumn = 1;
				maxNumActiveMatPerColumn = 1;
				minNumRowSubarray = 2;
				maxNumRowSubarray = 2;
				minNumColumnSubarray = 2;
				maxNumColumnSubarray = 2;
				minNumActiveSubarrayPerRow = 2;
				maxNumActiveSubarrayPerRow = 2;
				minNumActiveSubarrayPerColumn = 2;
				maxNumActiveSubarrayPerColumn = 2;
			} else
				useCactiAssumption = false;
			continue;
		}

		if (!strncmp("-EnablePruning", line, strlen("-EnablePruning"))) {
			sscanf(line, "-EnablePruning: %s", tmp);
			if (!strcmp(tmp, "Yes"))
				isPruningEnabled = true;
			else
				isPruningEnabled = false;
			continue;
		}

		if (!strncmp("-BufferDesignOptimization", line, strlen("-BufferDesignOptimization"))) {
			sscanf(line, "-BufferDesignOptimization: %s", tmp);
			if (!strcmp(tmp, "latency")) {
				minAreaOptimizationLevel = 0;
				maxAreaOptimizationLevel = 0;
			} else if (!strcmp(tmp, "area")) {
				minAreaOptimizationLevel = 2;
				maxAreaOptimizationLevel = 2;
			} else {
				minAreaOptimizationLevel = 1;
				maxAreaOptimizationLevel = 1;
			}
		}

		if (!strncmp("-FlashPageSize", line, strlen("-FlashPageSize"))) {
			sscanf(line, "-FlashPageSize (Byte): %ld", &pageSize);
			pageSize *= 8;	/* Byte to bit */
			continue;
		}

		if (!strncmp("-FlashBlockSize", line, strlen("-FlashBlockSize"))) {
			sscanf(line, "-FlashBlockSize (KB): %ld", &flashBlockSize);
			flashBlockSize *= (8 * 1024);	/* KB to bit */
			continue;
		}

		if (!strncmp("-ApplyReadLatencyConstraint", line, strlen("-ApplyReadLatencyConstraint"))) {
			sscanf(line, "-ApplyReadLatencyConstraint: %lf", &readLatencyConstraint);
			isConstraintApplied = true;
			continue;
		}

		if (!strncmp("-ApplyWriteLatencyConstraint", line, strlen("-ApplyWriteLatencyConstraint"))) {
			sscanf(line, "-ApplyWriteLatencyConstraint: %lf", &writeLatencyConstraint);
			isConstraintApplied = true;
			continue;
		}

		if (!strncmp("-ApplyReadDynamicEnergyConstraint", line, strlen("-ApplyReadDynamicEnergyConstraint"))) {
			sscanf(line, "-ApplyReadDynamicEnergyConstraint: %lf", &readDynamicEnergyConstraint);
			isConstraintApplied = true;
			continue;
		}

		if (!strncmp("-ApplyWriteDynamicEnergyConstraint", line, strlen("-ApplyWriteDynamicEnergyConstraint"))) {
			sscanf(line, "-ApplyWriteDynamicEnergyConstraint: %lf", &writeDynamicEnergyConstraint);
			isConstraintApplied = true;
			continue;
		}

		if (!strncmp("-ApplyLeakageConstraint", line, strlen("-ApplyLeakageConstraint"))) {
			sscanf(line, "-ApplyLeakageConstraint: %lf", &leakageConstraint);
			isConstraintApplied = true;
			continue;
		}

		if (!strncmp("-ApplyAreaConstraint", line, strlen("-ApplyAreaConstraint"))) {
			sscanf(line, "-ApplyAreaConstraint: %lf", &areaConstraint);
			isConstraintApplied = true;
			continue;
		}

		if (!strncmp("-ApplyReadEdpConstraint", line, strlen("-ApplyReadEdpConstraint"))) {
			sscanf(line, "-ApplyReadEdpConstraint: %lf", &readEdpConstraint);
			isConstraintApplied = true;
			continue;
		}

		if (!strncmp("-ApplyWriteEdpConstraint", line, strlen("-ApplyWriteEdpConstraint"))) {
			sscanf(line, "-ApplyWriteEdpConstraint: %lf", &writeEdpConstraint);
			isConstraintApplied = true;
			continue;
		}
	}

	fclose(fp);
}

void InputParameter::PrintInputParameter() {
	cout << endl << "====================" << endl << "DESIGN SPECIFICATION" << endl << "====================" << endl;
	cout << "Design Target: ";
	switch (designTarget) {
	case cache:
		cout << "Cache" << endl;
		break;
	case RAM_chip:
		cout << "Random Access Memory" << endl;
		break;
	default:	/* CAM */
		cout << "Content Addressable Memory" << endl;
	}

	cout << "Capacity   : ";
	if (capacity < 1024 * 1024)
		cout << capacity / 1024 << "KB" << endl;
	else if (capacity < 1024 * 1024 * 1024)
		cout << capacity / 1024 / 1024 << "MB" << endl;
	else
		cout << capacity / 1024 / 1024 / 1024 << "GB" << endl;

	if (designTarget == cache) {
		cout << "Cache Line Size: " << wordWidth / 8 << "Bytes" << endl;
		cout << "Cache Associativity: " << associativity << " Ways" << endl;
	} else {
		cout << "Data Width : " << wordWidth << "Bits";
		if (wordWidth % 8 == 0)
			cout << " (" << wordWidth / 8 << "Bytes)" << endl;
		else
			cout << endl;
	}
	if (designTarget == RAM_chip && (cell->memCellType == SLCNAND || cell->memCellType == MLCNAND)) {
		cout << "Page Size  : " << pageSize / 8 << "Bytes" << endl;
		cout << "Block Size : " << flashBlockSize / 8 / 1024 << "KB" << endl;
	}
	// TO-DO: tedious work here!!!

	if (optimizationTarget == full_exploration) {
		cout << endl << "Full design space exploration ... might take hours" << endl;
	} else {
		cout << endl << "Searching for the best solution that is optimized for ";
		switch (optimizationTarget) {
		case read_latency_optimized:
			cout << "read latency ..." << endl;
			break;
		case write_latency_optimized:
			cout << "write latency ..." << endl;
			break;
		case read_energy_optimized:
			cout << "read energy ..." << endl;
			break;
		case write_energy_optimized:
			cout << "write energy ..." << endl;
			break;
		case read_edp_optimized:
			cout << "read energy-delay-product ..." << endl;
			break;
		case write_edp_optimized:
			cout << "write energy-delay-product ..." << endl;
			break;
		case leakage_optimized:
			cout << "leakage power ..." << endl;
			break;
		default:	/* area */
			cout << "area ..." << endl;
		}
	}
}
