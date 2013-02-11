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


#ifndef BANK_H_
#define BANK_H_

#include "FunctionUnit.h"
#include "Mat.h"
#include "typedef.h"

class Bank: public FunctionUnit {
public:
	Bank();
	virtual ~Bank();

	/* Functions */
	void PrintProperty();
	virtual void Initialize(int _numRowMat, int _numColumnMat, long long _capacity,
			long _blockSize, int _associativity, int _numRowPerSet, int _numActiveMatPerRow,
			int _numActiveMatPerColumn, int _muxSenseAmp, bool _internalSenseAmp, int _muxOutputLev1, int _muxOutputLev2,
			int _numRowSubarray, int _numColumnSubarray,
			int _numActiveSubarrayPerRow, int _numActiveSubarrayPerColumn,
			BufferDesignTarget _areaOptimizationLevel, MemoryType _memoryType) = 0;
	virtual void CalculateArea() = 0;
	virtual void CalculateRC() = 0;
	virtual void CalculateLatencyAndPower() = 0;
	virtual Bank & operator=(const Bank &);

	/* Properties */
	bool initialized;	/* Initialization flag */
	bool invalid;		/* Indicate that the current configuration is not valid, pass down to all the sub-components */
	bool internalSenseAmp;
	int numRowMat;		/* Number of mat rows in a bank */
	int numColumnMat;	/* Number of mat columns in a bank */
	long long capacity;		/* The capacity of this bank, Unit: bit */
	long blockSize;		/* The basic block size in this bank, Unit: bit */
	int associativity;	/* Associativity, for cache design only */
	int numRowPerSet;		/* For cache design, the number of wordlines which a set is partitioned into */
	int numActiveMatPerRow;	/* For different access types */
	int numActiveMatPerColumn;	/* For different access types */
	int muxSenseAmp;	/* How many bitlines connect to one sense amplifier */
	int muxOutputLev1;	/* How many sense amplifiers connect to one output bit, level-1 */
	int muxOutputLev2;	/* How many sense amplifiers connect to one output bit, level-2 */
	int numRowSubarray;		/* Number of subarray rows in a mat */
	int numColumnSubarray;	/* Number of subarray columns in a mat */
	int numActiveSubarrayPerRow;	/* For different access types */
	int numActiveSubarrayPerColumn;	/* For different access types */
	BufferDesignTarget areaOptimizationLevel;
	MemoryType memoryType;

	Mat mat;
};

#endif /* BANK_H_ */
