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


#include "Result.h"
#include "global.h"
#include "formula.h"
#include "macros.h"

#include <iostream>
#include <fstream>

using namespace std;

Result::Result() {
	// TODO Auto-generated constructor stub
	if (inputParameter->routingMode == h_tree)
		bank = new BankWithHtree();
	else
		bank = new BankWithoutHtree();
	localWire = new Wire();
	globalWire = new Wire();

	/* initialize the worst case */
	bank->readLatency = 1e41;
	bank->writeLatency = 1e41;
	bank->readDynamicEnergy = 1e41;
	bank->writeDynamicEnergy = 1e41;
	bank->leakage = 1e41;
	bank->height = 1e41;
	bank->width = 1e41;
	bank->area = 1e41;

	/* No constraints */
	limitReadLatency = 1e41;
	limitWriteLatency = 1e41;
	limitReadDynamicEnergy = 1e41;
	limitWriteDynamicEnergy = 1e41;
	limitReadEdp = 1e41;
	limitWriteEdp = 1e41;
	limitArea = 1e41;
	limitLeakage = 1e41;

	/* Default read latency optimization */
	optimizationTarget = read_latency_optimized;
}

Result::~Result() {
	// TODO Auto-generated destructor stub
	if (bank)
		delete bank;
	if (Result::localWire)
		delete Result::localWire;
	if (Result::globalWire)
		delete Result::globalWire;
}

void Result::reset() {
	bank->readLatency = 1e41;
	bank->writeLatency = 1e41;
	bank->readDynamicEnergy = 1e41;
	bank->writeDynamicEnergy = 1e41;
	bank->leakage = 1e41;
	bank->height = 1e41;
	bank->width = 1e41;
	bank->area = 1e41;
}

void Result::compareAndUpdate(Result &newResult) {
	if (newResult.bank->readLatency <= limitReadLatency && newResult.bank->writeLatency <= limitWriteLatency
			&& newResult.bank->readDynamicEnergy <= limitReadDynamicEnergy && newResult.bank->writeDynamicEnergy <= limitWriteDynamicEnergy
			&& newResult.bank->readLatency * newResult.bank->readDynamicEnergy <= limitReadEdp
			&& newResult.bank->writeLatency * newResult.bank->writeDynamicEnergy <= limitWriteEdp
			&& newResult.bank->area <= limitArea && newResult.bank->leakage <= limitLeakage) {
		bool toUpdate = false;
		switch (optimizationTarget) {
		case read_latency_optimized:
			if 	(newResult.bank->readLatency < bank->readLatency)
				toUpdate = true;
			break;
		case write_latency_optimized:
			if 	(newResult.bank->writeLatency < bank->writeLatency)
				toUpdate = true;
			break;
		case read_energy_optimized:
			if 	(newResult.bank->readDynamicEnergy < bank->readDynamicEnergy)
				toUpdate = true;
			break;
		case write_energy_optimized:
			if 	(newResult.bank->writeDynamicEnergy < bank->writeDynamicEnergy)
				toUpdate = true;
			break;
		case read_edp_optimized:
			if 	(newResult.bank->readLatency * newResult.bank->readDynamicEnergy < bank->readLatency * bank->readDynamicEnergy)
				toUpdate = true;
			break;
		case write_edp_optimized:
			if 	(newResult.bank->writeLatency * newResult.bank->writeDynamicEnergy < bank->writeLatency * bank->writeDynamicEnergy)
				toUpdate = true;
			break;
		case area_optimized:
			if 	(newResult.bank->area < bank->area)
				toUpdate = true;
			break;
		case leakage_optimized:
			if 	(newResult.bank->leakage < bank->leakage)
				toUpdate = true;
			break;
		default:	/* Exploration */
			/* should not happen */
			;
		}
		if (toUpdate) {
			*bank = *(newResult.bank);
			*localWire = *(newResult.localWire);
			*globalWire = *(newResult.globalWire);
		}
	}
}

void Result::print() {
	cout << endl << "=============" << endl << "CONFIGURATION" << endl << "=============" << endl;
	cout << "Bank Organization: " << bank->numRowMat << " x " << bank->numColumnMat << endl;
	cout << " - Row Activation   : " << bank->numActiveMatPerColumn << " / " << bank->numRowMat << endl;
	cout << " - Column Activation: " << bank->numActiveMatPerRow << " / " << bank->numColumnMat << endl;
	cout << "Mat Organization: " << bank->numRowSubarray << " x " << bank->numColumnSubarray << endl;
	cout << " - Row Activation   : " << bank->numActiveSubarrayPerColumn << " / " << bank->numRowSubarray << endl;
	cout << " - Column Activation: " << bank->numActiveSubarrayPerRow << " / " << bank->numColumnSubarray << endl;
	cout << " - Subarray Size    : " << bank->mat.subarray.numRow << " Rows x " << bank->mat.subarray.numColumn << " Columns" << endl;
	cout << "Mux Level:" << endl;
	cout << " - Senseamp Mux      : " << bank->muxSenseAmp << endl;
	cout << " - Output Level-1 Mux: " << bank->muxOutputLev1 << endl;
	cout << " - Output Level-2 Mux: " << bank->muxOutputLev2 << endl;
	if (inputParameter->designTarget == cache)
		cout << " - One set is partitioned into " << bank->numRowPerSet << " rows" << endl;
	cout << "Local Wire:" << endl;
	cout << " - Wire Type : ";
	switch (localWire->wireType) {
	case local_aggressive:
		cout << "Local Aggressive" << endl;
		break;
	case local_conservative:
		cout << "Local Conservative" << endl;
		break;
	case semi_aggressive:
		cout << "Semi-Global Aggressive" << endl;
		break;
	case semi_conservative:
		cout << "Semi-Global Conservative" << endl;
		break;
	case global_aggressive:
		cout << "Global Aggressive" << endl;
		break;
	case global_conservative:
		cout << "Global Conservative" << endl;
		break;
	default:
		cout << "DRAM Wire" << endl;
	}
	cout << " - Repeater Type: ";
	switch (localWire->wireRepeaterType) {
	case repeated_none:
		cout << "No Repeaters" << endl;
		break;
	case repeated_opt:
		cout << "Fully-Optimized Repeaters" << endl;
		break;
	case repeated_5:
		cout << "Repeaters with 5% Overhead" << endl;
		break;
	case repeated_10:
		cout << "Repeaters with 10% Overhead" << endl;
		break;
	case repeated_20:
		cout << "Repeaters with 20% Overhead" << endl;
		break;
	case repeated_30:
		cout << "Repeaters with 30% Overhead" << endl;
		break;
	case repeated_40:
		cout << "Repeaters with 40% Overhead" << endl;
		break;
	case repeated_50:
		cout << "Repeaters with 50% Overhead" << endl;
		break;
	default:
		cout << "Unknown" << endl;
	}
	cout << " - Low Swing : ";
	if (localWire->isLowSwing)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	cout << "Global Wire:" << endl;
	cout << " - Wire Type : ";
	switch (globalWire->wireType) {
	case local_aggressive:
		cout << "Local Aggressive" << endl;
		break;
	case local_conservative:
		cout << "Local Conservative" << endl;
		break;
	case semi_aggressive:
		cout << "Semi-Global Aggressive" << endl;
		break;
	case semi_conservative:
		cout << "Semi-Global Conservative" << endl;
		break;
	case global_aggressive:
		cout << "Global Aggressive" << endl;
		break;
	case global_conservative:
		cout << "Global Conservative" << endl;
		break;
	default:
		cout << "DRAM Wire" << endl;
	}
	cout << " - Repeater Type: ";
	switch (globalWire->wireRepeaterType) {
	case repeated_none:
		cout << "No Repeaters" << endl;
		break;
	case repeated_opt:
		cout << "Fully-Optimized Repeaters" << endl;
		break;
	case repeated_5:
		cout << "Repeaters with 5% Overhead" << endl;
		break;
	case repeated_10:
		cout << "Repeaters with 10% Overhead" << endl;
		break;
	case repeated_20:
		cout << "Repeaters with 20% Overhead" << endl;
		break;
	case repeated_30:
		cout << "Repeaters with 30% Overhead" << endl;
		break;
	case repeated_40:
		cout << "Repeaters with 40% Overhead" << endl;
		break;
	case repeated_50:
		cout << "Repeaters with 50% Overhead" << endl;
		break;
	default:
		cout << "Unknown" << endl;
	}
	cout << " - Low Swing : ";
	if (globalWire->isLowSwing)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	cout << "Buffer Design Style: ";
	switch (bank->areaOptimizationLevel) {
	case latency_first:
		cout << "Latency-Optimized" << endl;
		break;
	case area_first:
		cout << "Area-Optimized" << endl;
		break;
	default:	/* balance */
		cout << "Balanced" << endl;
	}

	cout << "=============" << endl << "   RESULT" << endl << "=============" << endl;

	cout << "Area:" << endl;

	cout << " - Total Area = " << TO_METER(bank->height) << " x " << TO_METER(bank->width)
			<< " = " << TO_SQM(bank->area) << endl;
	cout << " |--- Mat Area      = " << TO_METER(bank->mat.height) << " x " << TO_METER(bank->mat.width)
			<< " = " << TO_SQM(bank->mat.area) << "   (" << cell->area * tech->featureSize * tech->featureSize
			* bank->capacity / bank->numRowMat / bank->numColumnMat / bank->mat.area * 100 << "%)" << endl;
	cout << " |--- Subarray Area = " << TO_METER(bank->mat.subarray.height) << " x "
			<< TO_METER(bank->mat.subarray.width) << " = " << TO_SQM(bank->mat.subarray.area) << "   ("
			<< cell->area * tech->featureSize * tech->featureSize * bank->capacity / bank->numRowMat
			/ bank->numColumnMat / bank->numRowSubarray / bank->numColumnSubarray
			/ bank->mat.subarray.area * 100 << "%)" <<endl;
	cout << " - Area Efficiency = " << cell->area * tech->featureSize * tech->featureSize
			* bank->capacity / bank->area * 100 << "%" << endl;

	cout << "Timing:" << endl;

	cout << " -  Read Latency = " << TO_SECOND(bank->readLatency) << endl;
	if (inputParameter->routingMode == h_tree)
		cout << " |--- H-Tree Latency = " << TO_SECOND(bank->readLatency - bank->mat.readLatency) << endl;
	else
		cout << " |--- Non-H-Tree Latency = " << TO_SECOND(bank->readLatency - bank->mat.readLatency) << endl;
	cout << " |--- Mat Latency    = " << TO_SECOND(bank->mat.readLatency) << endl;
	cout << "    |--- Predecoder Latency = " << TO_SECOND(bank->mat.predecoderLatency) << endl;
	cout << "    |--- Subarray Latency   = " << TO_SECOND(bank->mat.subarray.readLatency) << endl;
	cout << "       |--- Row Decoder Latency = " << TO_SECOND(bank->mat.subarray.rowDecoder.readLatency) << endl;
	cout << "       |--- Bitline Latency     = " << TO_SECOND(bank->mat.subarray.bitlineDelay) << endl;
	if (inputParameter->internalSensing)
		cout << "       |--- Senseamp Latency    = " << TO_SECOND(bank->mat.subarray.senseAmp.readLatency) << endl;
	cout << "       |--- Mux Latency         = " << TO_SECOND(bank->mat.subarray.bitlineMux.readLatency
													+ bank->mat.subarray.senseAmpMuxLev1.readLatency
													+ bank->mat.subarray.senseAmpMuxLev2.readLatency) << endl;
	cout << "       |--- Precharge Latency   = " << TO_SECOND(bank->mat.subarray.precharger.readLatency) << endl;
	if (bank->mat.memoryType == tag && bank->mat.internalSenseAmp)
		cout << "    |--- Comparator Latency  = " << TO_SECOND(bank->mat.comparator.readLatency) << endl;

	if (cell->memCellType == PCRAM || cell->memCellType == FBRAM ||
			(cell->memCellType == memristor && (cell->accessType == CMOS_access || cell->accessType == BJT_access))) {
		cout << " - RESET Latency = " << TO_SECOND(bank->resetLatency) << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Latency = " << TO_SECOND(bank->resetLatency - bank->mat.resetLatency) << endl;
		else
			cout << " |--- Non-H-Tree Latency = " << TO_SECOND(bank->resetLatency - bank->mat.resetLatency) << endl;
		cout << " |--- Mat Latency    = " << TO_SECOND(bank->mat.resetLatency) << endl;
		cout << "    |--- Predecoder Latency = " << TO_SECOND(bank->mat.predecoderLatency) << endl;
		cout << "    |--- Subarray Latency   = " << TO_SECOND(bank->mat.subarray.resetLatency) << endl;
		cout << "       |--- RESET Pulse Duration = " << TO_SECOND(cell->resetPulse) << endl;
		cout << "       |--- Row Decoder Latency  = " << TO_SECOND(bank->mat.subarray.rowDecoder.writeLatency) << endl;
		cout << "       |--- Charge Latency   = " << TO_SECOND(bank->mat.subarray.chargeLatency) << endl;
		cout << " - SET Latency   = " << TO_SECOND(bank->setLatency) << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Latency = " << TO_SECOND(bank->setLatency - bank->mat.setLatency) << endl;
		else
			cout << " |--- Non-H-Tree Latency = " << TO_SECOND(bank->setLatency - bank->mat.setLatency) << endl;
		cout << " |--- Mat Latency    = " << TO_SECOND(bank->mat.setLatency) << endl;
		cout << "    |--- Predecoder Latency = " << TO_SECOND(bank->mat.predecoderLatency) << endl;
		cout << "    |--- Subarray Latency   = " << TO_SECOND(bank->mat.subarray.setLatency) << endl;
		cout << "       |--- SET Pulse Duration   = " << TO_SECOND(cell->setPulse) << endl;
		cout << "       |--- Row Decoder Latency  = " << TO_SECOND(bank->mat.subarray.rowDecoder.writeLatency) << endl;
		cout << "       |--- Charger Latency      = " << TO_SECOND(bank->mat.subarray.chargeLatency) << endl;
	} else if (cell->memCellType == SLCNAND) {
		cout << " - Erase Latency = " << TO_SECOND(bank->resetLatency) << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Latency = " << TO_SECOND(bank->resetLatency - bank->mat.resetLatency) << endl;
		else
			cout << " |--- Non-H-Tree Latency = " << TO_SECOND(bank->resetLatency - bank->mat.resetLatency) << endl;
		cout << " |--- Mat Latency    = " << TO_SECOND(bank->mat.resetLatency) << endl;
		cout << " - Programming Latency   = " << TO_SECOND(bank->setLatency) << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Latency = " << TO_SECOND(bank->setLatency - bank->mat.setLatency) << endl;
		else
			cout << " |--- Non-H-Tree Latency = " << TO_SECOND(bank->setLatency - bank->mat.setLatency) << endl;
		cout << " |--- Mat Latency    = " << TO_SECOND(bank->mat.setLatency) << endl;
	} else {
		cout << " - Write Latency = " << TO_SECOND(bank->writeLatency) << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Latency = " << TO_SECOND(bank->writeLatency - bank->mat.writeLatency) << endl;
		else
			cout << " |--- Non-H-Tree Latency = " << TO_SECOND(bank->writeLatency - bank->mat.writeLatency) << endl;
		cout << " |--- Mat Latency    = " << TO_SECOND(bank->mat.writeLatency) << endl;
		cout << "    |--- Predecoder Latency = " << TO_SECOND(bank->mat.predecoderLatency) << endl;
		cout << "    |--- Subarray Latency   = " << TO_SECOND(bank->mat.subarray.writeLatency) << endl;
		if (cell->memCellType == MRAM)
			cout << "       |--- Write Pulse Duration = " << TO_SECOND(cell->resetPulse) << endl;	// MRAM reset/set is equal
		cout << "       |--- Row Decoder Latency = " << TO_SECOND(bank->mat.subarray.rowDecoder.writeLatency) << endl;
		cout << "       |--- Charge Latency      = " << TO_SECOND(bank->mat.subarray.chargeLatency) << endl;
	}

	double readBandwidth = (double)bank->blockSize /
			(bank->mat.subarray.readLatency - bank->mat.subarray.rowDecoder.readLatency
			+ bank->mat.subarray.precharger.readLatency) / 8;
	cout << " - Read Bandwidth  = " << TO_BPS(readBandwidth) << endl;
	double writeBandwidth = (double)bank->blockSize /
			(bank->mat.subarray.writeLatency) / 8;
	cout << " - Write Bandwidth = " << TO_BPS(writeBandwidth) << endl;

	cout << "Power:" << endl;

	cout << " -  Read Dynamic Energy = " << TO_JOULE(bank->readDynamicEnergy) << endl;
	if (inputParameter->routingMode == h_tree)
		cout << " |--- H-Tree Dynamic Energy = " << TO_JOULE(bank->readDynamicEnergy - bank->mat.readDynamicEnergy
													* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
													<< endl;
	else
		cout << " |--- Non-H-Tree Dynamic Energy = " << TO_JOULE(bank->readDynamicEnergy - bank->mat.readDynamicEnergy
													* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
													<< endl;
	cout << " |--- Mat Dynamic Energy    = " << TO_JOULE(bank->mat.readDynamicEnergy) << " per mat" << endl;
	cout << "    |--- Predecoder Dynamic Energy = " << TO_JOULE(bank->mat.readDynamicEnergy - bank->mat.subarray.readDynamicEnergy
														* bank->numActiveSubarrayPerRow * bank->numActiveSubarrayPerColumn)
														<< endl;
	cout << "    |--- Subarray Dynamic Energy   = " << TO_JOULE(bank->mat.subarray.readDynamicEnergy) << " per active subarray" << endl;
	cout << "       |--- Row Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.rowDecoder.readDynamicEnergy) << endl;
	cout << "       |--- Mux Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.bitlineMuxDecoder.readDynamicEnergy
													+ bank->mat.subarray.senseAmpMuxLev1Decoder.readDynamicEnergy
													+ bank->mat.subarray.senseAmpMuxLev2Decoder.readDynamicEnergy) << endl;
	if (cell->memCellType == PCRAM || cell->memCellType == FBRAM || cell->memCellType == MRAM || cell->memCellType == memristor ) {
		cout << "       |--- Bitline & Cell Read Energy = " << TO_JOULE(bank->mat.subarray.cellReadEnergy) << endl;
	}
	if (inputParameter->internalSensing)
		cout << "       |--- Senseamp Dynamic Energy    = " << TO_JOULE(bank->mat.subarray.senseAmp.readDynamicEnergy) << endl;
	cout << "       |--- Mux Dynamic Energy         = " << TO_JOULE(bank->mat.subarray.bitlineMux.readDynamicEnergy
													+ bank->mat.subarray.senseAmpMuxLev1.readDynamicEnergy
													+ bank->mat.subarray.senseAmpMuxLev2.readDynamicEnergy) << endl;
	cout << "       |--- Precharge Dynamic Energy   = " << TO_JOULE(bank->mat.subarray.precharger.readDynamicEnergy) << endl;

	if (cell->memCellType == PCRAM || cell->memCellType == FBRAM ||
			(cell->memCellType == memristor && (cell->accessType == CMOS_access || cell->accessType == BJT_access))) {
		cout << " - RESET Dynamic Energy = " << TO_JOULE(bank->resetDynamicEnergy) << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Dynamic Energy = " << TO_JOULE(bank->resetDynamicEnergy - bank->mat.resetDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		else
			cout << " |--- H-Tree Dynamic Energy = " << TO_JOULE(bank->resetDynamicEnergy - bank->mat.resetDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		cout << " |--- Mat Dynamic Energy    = " << TO_JOULE(bank->mat.resetDynamicEnergy) << " per mat" << endl;
		cout << "    |--- Predecoder Dynamic Energy = " << TO_JOULE(bank->mat.writeDynamicEnergy - bank->mat.subarray.writeDynamicEnergy
															* bank->numActiveSubarrayPerRow * bank->numActiveSubarrayPerColumn)
															<< endl;
		cout << "    |--- Subarray Dynamic Energy   = " << TO_JOULE(bank->mat.subarray.writeDynamicEnergy) << " per active subarray" << endl;
		cout << "       |--- Row Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.rowDecoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.bitlineMuxDecoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1Decoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2Decoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Dynamic Energy         = " << TO_JOULE(bank->mat.subarray.bitlineMux.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2.writeDynamicEnergy) << endl;
		cout << "       |--- Cell RESET Dynamic Energy  = " << TO_JOULE(bank->mat.subarray.cellResetEnergy) << endl;
		cout << " - SET Dynamic Energy = " << TO_JOULE(bank->setDynamicEnergy) << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Dynamic Energy = " << TO_JOULE(bank->setDynamicEnergy - bank->mat.setDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		else
			cout << " |--- Non-H-Tree Dynamic Energy = " << TO_JOULE(bank->setDynamicEnergy - bank->mat.setDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		cout << " |--- Mat Dynamic Energy    = " << TO_JOULE(bank->mat.setDynamicEnergy) << " per mat" << endl;
		cout << "    |--- Predecoder Dynamic Energy = " << TO_JOULE(bank->mat.writeDynamicEnergy - bank->mat.subarray.writeDynamicEnergy
															* bank->numActiveSubarrayPerRow * bank->numActiveSubarrayPerColumn)
															<< endl;
		cout << "    |--- Subarray Dynamic Energy   = " << TO_JOULE(bank->mat.subarray.writeDynamicEnergy) << " per active subarray" << endl;
		cout << "       |--- Row Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.rowDecoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.bitlineMuxDecoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1Decoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2Decoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Dynamic Energy         = " << TO_JOULE(bank->mat.subarray.bitlineMux.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2.writeDynamicEnergy) << endl;
		cout << "       |--- Cell SET Dynamic Energy    = " << TO_JOULE(bank->mat.subarray.cellSetEnergy) << endl;
	} else if (cell->memCellType == SLCNAND) {
		cout << " - Erase Dynamic Energy = " << TO_JOULE(bank->resetDynamicEnergy) << " per block" << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Dynamic Energy = " << TO_JOULE(bank->resetDynamicEnergy - bank->mat.resetDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		else
			cout << " |--- Non-H-Tree Dynamic Energy = " << TO_JOULE(bank->resetDynamicEnergy - bank->mat.resetDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		cout << " |--- Mat Dynamic Energy    = " << TO_JOULE(bank->mat.resetDynamicEnergy) << " per mat" << endl;
		cout << "    |--- Predecoder Dynamic Energy = " << TO_JOULE(bank->mat.writeDynamicEnergy - bank->mat.subarray.writeDynamicEnergy
															* bank->numActiveSubarrayPerRow * bank->numActiveSubarrayPerColumn)
															<< endl;
		cout << "    |--- Subarray Dynamic Energy   = " << TO_JOULE(bank->mat.subarray.writeDynamicEnergy) << " per active subarray" << endl;
		cout << "       |--- Row Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.rowDecoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.bitlineMuxDecoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1Decoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2Decoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Dynamic Energy         = " << TO_JOULE(bank->mat.subarray.bitlineMux.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2.writeDynamicEnergy) << endl;
		cout << " - Programming Dynamic Energy = " << TO_JOULE(bank->setDynamicEnergy) << " per page" << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Dynamic Energy = " << TO_JOULE(bank->setDynamicEnergy - bank->mat.setDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		else
			cout << " |--- Non-H-Tree Dynamic Energy = " << TO_JOULE(bank->setDynamicEnergy - bank->mat.setDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		cout << " |--- Mat Dynamic Energy    = " << TO_JOULE(bank->mat.setDynamicEnergy) << " per mat" << endl;
		cout << "    |--- Predecoder Dynamic Energy = " << TO_JOULE(bank->mat.writeDynamicEnergy - bank->mat.subarray.writeDynamicEnergy
															* bank->numActiveSubarrayPerRow * bank->numActiveSubarrayPerColumn)
															<< endl;
		cout << "    |--- Subarray Dynamic Energy   = " << TO_JOULE(bank->mat.subarray.writeDynamicEnergy) << " per active subarray" << endl;
		cout << "       |--- Row Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.rowDecoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.bitlineMuxDecoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1Decoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2Decoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Dynamic Energy         = " << TO_JOULE(bank->mat.subarray.bitlineMux.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2.writeDynamicEnergy) << endl;
	} else {
		cout << " - Write Dynamic Energy = " << TO_JOULE(bank->writeDynamicEnergy) << endl;
		if (inputParameter->routingMode == h_tree)
			cout << " |--- H-Tree Dynamic Energy = " << TO_JOULE(bank->writeDynamicEnergy - bank->mat.writeDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		else
			cout << " |--- Non-H-Tree Dynamic Energy = " << TO_JOULE(bank->writeDynamicEnergy - bank->mat.writeDynamicEnergy
														* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
														<< endl;
		cout << " |--- Mat Dynamic Energy    = " << TO_JOULE(bank->mat.writeDynamicEnergy) << " per mat" << endl;
		cout << "    |--- Predecoder Dynamic Energy = " << TO_JOULE(bank->mat.writeDynamicEnergy - bank->mat.subarray.writeDynamicEnergy
															* bank->numActiveSubarrayPerRow * bank->numActiveSubarrayPerColumn)
															<< endl;
		cout << "    |--- Subarray Dynamic Energy   = " << TO_JOULE(bank->mat.subarray.writeDynamicEnergy) << " per active subarray" << endl;
		cout << "       |--- Row Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.rowDecoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Decoder Dynamic Energy = " << TO_JOULE(bank->mat.subarray.bitlineMuxDecoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1Decoder.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2Decoder.writeDynamicEnergy) << endl;
		cout << "       |--- Mux Dynamic Energy         = " << TO_JOULE(bank->mat.subarray.bitlineMux.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev1.writeDynamicEnergy
														+ bank->mat.subarray.senseAmpMuxLev2.writeDynamicEnergy) << endl;
		if (cell->memCellType == MRAM) {
			cout << "       |--- Bitline & Cell Write Energy= " << TO_JOULE(bank->mat.subarray.cellResetEnergy) << endl;
		}
	}

	cout << " - Leakage Power = " << TO_WATT(bank->leakage) << endl;
	if (inputParameter->routingMode == h_tree)
		cout << " |--- H-Tree Leakage Power = " << TO_WATT(bank->leakage - bank->mat.leakage
													* bank->numColumnMat * bank->numRowMat)
													<< endl;
	else
		cout << " |--- Non-H-Tree Leakage Power = " << TO_WATT(bank->leakage - bank->mat.leakage
													* bank->numColumnMat * bank->numRowMat)
													<< endl;
	cout << " |--- Mat Leakage Power    = " << TO_WATT(bank->mat.leakage) << " per mat" << endl;
}


void Result::printAsCache(Result &tagResult, CacheAccessMode cacheAccessMode) {
	if (bank->memoryType != data || tagResult.bank->memoryType != tag) {
		cout << "This is not a valid cache configuration." << endl;
		return;
	} else {
		double cacheHitLatency, cacheMissLatency, cacheWriteLatency;
		double cacheHitDynamicEnergy, cacheMissDynamicEnergy, cacheWriteDynamicEnergy;
		double cacheLeakage;
		double cacheArea;
		if (cacheAccessMode == normal_access_mode) {
			/* Calculate latencies */
			cacheMissLatency = tagResult.bank->readLatency;		/* only the tag access latency */
			cacheHitLatency = MAX(tagResult.bank->readLatency, bank->mat.readLatency);	/* access tag and activate data row in parallel */
			cacheHitLatency += bank->mat.subarray.columnDecoderLatency;		/* add column decoder latency after hit signal arrives */
			cacheHitLatency += bank->readLatency - bank->mat.readLatency;	/* H-tree in and out latency */
			cacheWriteLatency = MAX(tagResult.bank->writeLatency, bank->writeLatency);	/* Data and tag are written in parallel */
			/* Calculate power */
			cacheMissDynamicEnergy = tagResult.bank->readDynamicEnergy;	/* no matter what tag is always accessed */
			cacheMissDynamicEnergy += bank->readDynamicEnergy;	/* data is also partially accessed, TO-DO: not accurate here */
			cacheHitDynamicEnergy = tagResult.bank->readDynamicEnergy + bank->readDynamicEnergy;
			cacheWriteDynamicEnergy = tagResult.bank->writeDynamicEnergy + bank->writeDynamicEnergy;
		} else if (cacheAccessMode == fast_access_mode) {
			/* Calculate latencies */
			cacheMissLatency = tagResult.bank->readLatency;
			cacheHitLatency = MAX(tagResult.bank->readLatency, bank->readLatency);
			cacheWriteLatency = MAX(tagResult.bank->writeLatency, bank->writeLatency);
			/* Calculate power */
			cacheMissDynamicEnergy = tagResult.bank->readDynamicEnergy;	/* no matter what tag is always accessed */
			cacheMissDynamicEnergy += bank->readDynamicEnergy;	/* data is also partially accessed, TO-DO: not accurate here */
			cacheHitDynamicEnergy = tagResult.bank->readDynamicEnergy + bank->readDynamicEnergy;
			cacheWriteDynamicEnergy = tagResult.bank->writeDynamicEnergy + bank->writeDynamicEnergy;
		} else {		/* sequential access */
			/* Calculate latencies */
			cacheMissLatency = tagResult.bank->readLatency;
			cacheHitLatency = tagResult.bank->readLatency + bank->readLatency;
			cacheWriteLatency = MAX(tagResult.bank->writeLatency, bank->writeLatency);
			/* Calculate power */
			cacheMissDynamicEnergy = tagResult.bank->readDynamicEnergy;	/* no matter what tag is always accessed */
			cacheHitDynamicEnergy = tagResult.bank->readDynamicEnergy + bank->readDynamicEnergy;
			cacheWriteDynamicEnergy = tagResult.bank->writeDynamicEnergy + bank->writeDynamicEnergy;
		}
		/* Calculate leakage */
		cacheLeakage = tagResult.bank->leakage + bank->leakage;
		/* Calculate area */
		cacheArea = tagResult.bank->area + bank->area;	/* TO-DO: simply add them together here */

		/* start printing */
		cout << endl << "=======================" << endl << "CACHE DESIGN -- SUMMARY" << endl << "=======================" << endl;
		cout << "Access Mode: ";
		switch (cacheAccessMode) {
		case normal_access_mode:
			cout << "Normal" << endl;
			break;
		case fast_access_mode:
			cout << "Fast" << endl;
			break;
		default:	/* sequential */
			cout << "Sequential" << endl;
		}
		cout << "Area:" << endl;
		cout << " - Total Area = " << cacheArea * 1e6 << "mm^2" << endl;
		cout << " |--- Data Array Area = " << bank->height * 1e6 << "um x " << bank->width * 1e6 << "um = " << bank->area * 1e6 << "mm^2" << endl;
		cout << " |--- Tag Array Area  = " << tagResult.bank->height * 1e6 << "um x " << tagResult.bank->width * 1e6 << "um = " << tagResult.bank->area * 1e6 << "mm^2" << endl;
		cout << "Timing:" << endl;
		cout << " - Cache Hit Latency   = " << cacheHitLatency * 1e9 << "ns" << endl;
		cout << " - Cache Miss Latency  = " << cacheMissLatency * 1e9 << "ns" << endl;
		cout << " - Cache Write Latency = " << cacheWriteLatency * 1e9 << "ns" << endl;
		cout << "Power:" << endl;
		cout << " - Cache Hit Dynamic Energy   = " << cacheHitDynamicEnergy * 1e9 << "nJ per access" << endl;
		cout << " - Cache Miss Dynamic Energy  = " << cacheMissDynamicEnergy * 1e9 << "nJ per access" << endl;
		cout << " - Cache Write Dynamic Energy = " << cacheWriteDynamicEnergy * 1e9 << "nJ per access" << endl;
		cout << " - Cache Total Leakage Power  = " << cacheLeakage * 1e3 << "mW" << endl;
		cout << " |--- Cache Data Array Leakage Power = " << bank->leakage * 1e3 << "mW" << endl;
		cout << " |--- Cache Tag Array Leakage Power  = " << tagResult.bank->leakage * 1e3 << "mW" << endl;

		cout << endl << "CACHE DATA ARRAY";
		print();
		cout << endl << "CACHE TAG ARRAY";
		tagResult.print();
	}
}

void Result::printToCsvFile(ofstream &outputFile) {
/*
	outputFile << bank->readDynamicEnergy * 1e12 << ",";
	outputFile << (bank->readDynamicEnergy - bank->mat.readDynamicEnergy
					* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
					* 1e12 << ",";
	outputFile << bank->mat.readDynamicEnergy * 1e12 << ",";
	outputFile << (bank->mat.readDynamicEnergy - bank->mat.subarray.readDynamicEnergy
					* bank->numActiveSubarrayPerRow * bank->numActiveSubarrayPerColumn)
					* 1e12 << ",";
	outputFile << bank->mat.subarray.readDynamicEnergy * 1e12 << ",";
	outputFile << bank->mat.subarray.rowDecoder.readDynamicEnergy * 1e12 << ",";
	outputFile << (bank->mat.subarray.bitlineMuxDecoder.readDynamicEnergy
					+ bank->mat.subarray.senseAmpMuxLev1Decoder.readDynamicEnergy
					+ bank->mat.subarray.senseAmpMuxLev2Decoder.readDynamicEnergy) * 1e12 << ",";
	outputFile << bank->mat.subarray.senseAmp.readDynamicEnergy * 1e12 << ",";
	outputFile << (bank->mat.subarray.bitlineMux.readDynamicEnergy
					+ bank->mat.subarray.senseAmpMuxLev1.readDynamicEnergy
					+ bank->mat.subarray.senseAmpMuxLev2.readDynamicEnergy) * 1e12 << ",";
	outputFile << bank->mat.subarray.precharger.readDynamicEnergy * 1e12 << ",";
	outputFile << bank->writeDynamicEnergy * 1e12 << ",";
	outputFile << (bank->writeDynamicEnergy - bank->mat.writeDynamicEnergy
					* bank->numActiveMatPerColumn * bank->numActiveMatPerRow)
					* 1e12 << ",";
	outputFile << bank->mat.writeDynamicEnergy * 1e12 << ",";
	outputFile << (bank->mat.writeDynamicEnergy - bank->mat.subarray.writeDynamicEnergy
					* bank->numActiveSubarrayPerRow * bank->numActiveSubarrayPerColumn)
					* 1e12 << ",";
	outputFile << bank->mat.subarray.writeDynamicEnergy * 1e12 << ",";
	outputFile << bank->mat.subarray.rowDecoder.writeDynamicEnergy * 1e12 << ",";
	outputFile << (bank->mat.subarray.bitlineMuxDecoder.writeDynamicEnergy
					+ bank->mat.subarray.senseAmpMuxLev1Decoder.writeDynamicEnergy
					+ bank->mat.subarray.senseAmpMuxLev2Decoder.writeDynamicEnergy) * 1e12 << ",";
	outputFile << (bank->mat.subarray.bitlineMux.writeDynamicEnergy
					+ bank->mat.subarray.senseAmpMuxLev1.writeDynamicEnergy
					+ bank->mat.subarray.senseAmpMuxLev2.writeDynamicEnergy) * 1e12 << endl;
*/
	outputFile << bank->numRowMat << "," << bank->numColumnMat << "," << bank->numActiveMatPerColumn << "," << bank->numActiveMatPerRow << ",";
	outputFile << bank->numRowSubarray << "," << bank->numColumnSubarray << "," << bank->numActiveSubarrayPerColumn << "," << bank->numActiveSubarrayPerRow << ",";
	outputFile << bank->mat.subarray.numRow << "," << bank->mat.subarray.numColumn << ",";
	outputFile << bank->muxSenseAmp << "," << bank->muxOutputLev1 << "," << bank->muxOutputLev2 << ",";
	if (inputParameter->designTarget == cache)
		outputFile << bank->numRowPerSet << ",";
	else
		outputFile << "N/A,";
	switch (localWire->wireType) {
	case local_aggressive:
		outputFile << "Local Aggressive" << ",";
		break;
	case local_conservative:
		outputFile << "Local Conservative" << ",";
		break;
	case semi_aggressive:
		outputFile << "Semi-Global Aggressive" << ",";
		break;
	case semi_conservative:
		outputFile << "Semi-Global Conservative" << ",";
		break;
	case global_aggressive:
		outputFile << "Global Aggressive" << ",";
		break;
	case global_conservative:
		outputFile << "Global Conservative" << ",";
		break;
	default:
		outputFile << "DRAM Wire" << ",";
	}
	switch (localWire->wireRepeaterType) {
	case repeated_none:
		outputFile << "No Repeaters" << ",";
		break;
	case repeated_opt:
		outputFile << "Fully-Optimized Repeaters" << ",";
		break;
	case repeated_5:
		outputFile << "Repeaters with 5% Overhead" << ",";
		break;
	case repeated_10:
		outputFile << "Repeaters with 10% Overhead" << ",";
		break;
	case repeated_20:
		outputFile << "Repeaters with 20% Overhead" << ",";
		break;
	case repeated_30:
		outputFile << "Repeaters with 30% Overhead" << ",";
		break;
	case repeated_40:
		outputFile << "Repeaters with 40% Overhead" << ",";
		break;
	case repeated_50:
		outputFile << "Repeaters with 50% Overhead" << ",";
		break;
	default:
		outputFile << "N/A" << ",";
	}
	if (localWire->isLowSwing)
		outputFile << "Yes" << ",";
	else
		outputFile << "No" << ",";
	switch (globalWire->wireType) {
	case local_aggressive:
		outputFile << "Local Aggressive" << ",";
		break;
	case local_conservative:
		outputFile << "Local Conservative" << ",";
		break;
	case semi_aggressive:
		outputFile << "Semi-Global Aggressive" << ",";
		break;
	case semi_conservative:
		outputFile << "Semi-Global Conservative" << ",";
		break;
	case global_aggressive:
		outputFile << "Global Aggressive" << ",";
		break;
	case global_conservative:
		outputFile << "Global Conservative" << ",";
		break;
	default:
		outputFile << "DRAM Wire" << ",";
	}
	switch (globalWire->wireRepeaterType) {
	case repeated_none:
		outputFile << "No Repeaters" << ",";
		break;
	case repeated_opt:
		outputFile << "Fully-Optimized Repeaters" << ",";
		break;
	case repeated_5:
		outputFile << "Repeaters with 5% Overhead" << ",";
		break;
	case repeated_10:
		outputFile << "Repeaters with 10% Overhead" << ",";
		break;
	case repeated_20:
		outputFile << "Repeaters with 20% Overhead" << ",";
		break;
	case repeated_30:
		outputFile << "Repeaters with 30% Overhead" << ",";
		break;
	case repeated_40:
		outputFile << "Repeaters with 40% Overhead" << ",";
		break;
	case repeated_50:
		outputFile << "Repeaters with 50% Overhead" << ",";
		break;
	default:
		outputFile << "N/A" << ",";
	}
	if (globalWire->isLowSwing)
		outputFile << "Yes" << ",";
	else
		outputFile << "No" << ",";
	switch (bank->areaOptimizationLevel) {
	case latency_first:
		outputFile << "Latency-Optimized" << ",";
		break;
	case area_first:
		outputFile << "Area-Optimized" << ",";
		break;
	default:	/* balance */
		outputFile << "Balanced" << ",";
	}
	outputFile << bank->height * 1e6 << "," << bank->width * 1e6 << "," << bank->area * 1e6 << ",";
	outputFile << bank->mat.height * 1e6 << "," << bank->mat.width * 1e6 << "," << bank->mat.area * 1e6 << ",";
	outputFile << bank->mat.subarray.height * 1e6 << "," << bank->mat.subarray.width * 1e6 << "," << bank->mat.subarray.area * 1e6 << ",";
	outputFile << cell->area * tech->featureSize * tech->featureSize * bank->capacity / bank->area * 100 << ",";
	outputFile << bank->readLatency * 1e9 << "," << bank->writeLatency * 1e9 << ",";
	outputFile << bank->readDynamicEnergy * 1e12 << "," << bank->writeDynamicEnergy * 1e12 << ",";
	outputFile << bank->leakage * 1e3 << ",";
}

void Result::printAsCacheToCsvFile(Result &tagResult, CacheAccessMode cacheAccessMode, ofstream &outputFile) {
	if (bank->memoryType != data || tagResult.bank->memoryType != tag) {
		cout << "This is not a valid cache configuration." << endl;
		return;
	} else {
		double cacheHitLatency, cacheMissLatency, cacheWriteLatency;
		double cacheHitDynamicEnergy, cacheMissDynamicEnergy, cacheWriteDynamicEnergy;
		double cacheLeakage;
		double cacheArea;
		if (cacheAccessMode == normal_access_mode) {
			/* Calculate latencies */
			cacheMissLatency = tagResult.bank->readLatency;		/* only the tag access latency */
			cacheHitLatency = MAX(tagResult.bank->readLatency, bank->mat.readLatency);	/* access tag and activate data row in parallel */
			cacheHitLatency += bank->mat.subarray.columnDecoderLatency;		/* add column decoder latency after hit signal arrives */
			cacheHitLatency += bank->readLatency - bank->mat.readLatency;	/* H-tree in and out latency */
			cacheWriteLatency = MAX(tagResult.bank->writeLatency, bank->writeLatency);	/* Data and tag are written in parallel */
			/* Calculate power */
			cacheMissDynamicEnergy = tagResult.bank->readDynamicEnergy;	/* no matter what tag is always accessed */
			cacheMissDynamicEnergy += bank->readDynamicEnergy;	/* data is also partially accessed, TO-DO: not accurate here */
			cacheHitDynamicEnergy = tagResult.bank->readDynamicEnergy + bank->readDynamicEnergy;
			cacheWriteDynamicEnergy = tagResult.bank->writeDynamicEnergy + bank->writeDynamicEnergy;
		} else if (cacheAccessMode == fast_access_mode) {
			/* Calculate latencies */
			cacheMissLatency = tagResult.bank->readLatency;
			cacheHitLatency = MAX(tagResult.bank->readLatency, bank->readLatency);
			cacheWriteLatency = MAX(tagResult.bank->writeLatency, bank->writeLatency);
			/* Calculate power */
			cacheMissDynamicEnergy = tagResult.bank->readDynamicEnergy;	/* no matter what tag is always accessed */
			cacheMissDynamicEnergy += bank->readDynamicEnergy;	/* data is also partially accessed, TO-DO: not accurate here */
			cacheHitDynamicEnergy = tagResult.bank->readDynamicEnergy + bank->readDynamicEnergy;
			cacheWriteDynamicEnergy = tagResult.bank->writeDynamicEnergy + bank->writeDynamicEnergy;
		} else {		/* sequential access */
			/* Calculate latencies */
			cacheMissLatency = tagResult.bank->readLatency;
			cacheHitLatency = tagResult.bank->readLatency + bank->readLatency;
			cacheWriteLatency = MAX(tagResult.bank->writeLatency, bank->writeLatency);
			/* Calculate power */
			cacheMissDynamicEnergy = tagResult.bank->readDynamicEnergy;	/* no matter what tag is always accessed */
			cacheHitDynamicEnergy = tagResult.bank->readDynamicEnergy + bank->readDynamicEnergy;
			cacheWriteDynamicEnergy = tagResult.bank->writeDynamicEnergy + bank->writeDynamicEnergy;
		}
		/* Calculate leakage */
		cacheLeakage = tagResult.bank->leakage + bank->leakage;
		/* Calculate area */
		cacheArea = tagResult.bank->area + bank->area;	/* TO-DO: simply add them together here */

		/* start printing */
		switch (cacheAccessMode) {
		case normal_access_mode:
			outputFile << "Normal" << ",";
			break;
		case fast_access_mode:
			outputFile << "Fast" << ",";
			break;
		default:	/* sequential */
			outputFile << "Sequential" << ",";
		}
		outputFile << cacheArea * 1e6 << ",";
		outputFile << cacheHitLatency * 1e9 << ",";
		outputFile << cacheMissLatency * 1e9 << ",";
		outputFile << cacheWriteLatency * 1e9 << ",";
		outputFile << cacheHitDynamicEnergy * 1e9 << ",";
		outputFile << cacheMissDynamicEnergy * 1e9 << ",";
		outputFile << cacheWriteDynamicEnergy * 1e9 << ",";
		outputFile << cacheLeakage * 1e3 << ",";
		printToCsvFile(outputFile);
		tagResult.printToCsvFile(outputFile);
		outputFile << endl;
	}
}
