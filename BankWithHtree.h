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


#ifndef BANKWITHHTREE_H_
#define BANKWITHHTREE_H_

#include "Bank.h"

class BankWithHtree: public Bank {
public:
	BankWithHtree();
	virtual ~BankWithHtree();
	void Initialize(int _numRowMat, int _numColumnMat, long long _capacity,
			long _blockSize, int _associativity, int _numRowPerSet, int _numActiveMatPerRow,
			int _numActiveMatPerColumn, int _muxSenseAmp, bool _internalSenseAmp, int _muxOutputLev1, int _muxOutputLev2,
			int _numRowSubarray, int _numColumnSubarray,
			int _numActiveSubarrayPerRow, int _numActiveSubarrayPerColumn,
			BufferDesignTarget _areaOptimizationLevel, MemoryType _memoryType);
	void CalculateArea();
	void CalculateRC();
	void CalculateLatencyAndPower();
	BankWithHtree & operator=(const BankWithHtree &);

	int numAddressBit;		/* Number of bank address bits */
	int numDataDistributeBit;	/* Number of bank data bits (these bits will be distributed along with the address) */
	int numDataBroadcastBit;	/* Number of bank data bits (these bits will be broadcasted at every node) */

	int levelHorizontal;			/* The number of horizontal levels */
	int levelVertical;				/* The number of vertical levels */
	int * numHorizontalAddressBitToRoute;  /* The number of horizontal bits to route on level x */
	int * numHorizontalDataDistributeBitToRoute;	/* The number of horizontal data-in bits to route on level x */
	int * numHorizontalDataBroadcastBitToRoute;		/* The number of horizontal data-out bits to route on level x */
	int * numHorizontalWire;        /* The number of horizontal wire tiers on level x */
	int * numSumHorizontalWire;     /* The number of total horizontal wire groups on level x */
	int * numActiveHorizontalWire;  /* The number of active horizontal wire groups on level x */
	double * lengthHorizontalWire;	/* The length of horizontal wires on level x, Unit: m */
	int * numVerticalAddressBitToRoute;	/* The number of vertical address bits to route on level x */
	int * numVerticalDataDistributeBitToRoute;	/* The number of vertical data-in bits to route on level x */
	int * numVerticalDataBroadcastBitToRoute;	/* The number of vertical data-out bits to route on level x */
	int * numVerticalWire;          /* The number of vertical wire tiers on level x */
	int * numSumVerticalWire;       /* The number of total vertical wire groups on level x */
    int * numActiveVerticalWire;    /* The number of active vertical wire groups on level x */
	double * lengthVerticalWire;	/* The length of vertical wires on level x, Unit: m */
};

#endif /* BANKWITHHTREE_H_ */
