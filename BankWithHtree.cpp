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


#include "BankWithHtree.h"
#include "formula.h"
#include "global.h"


BankWithHtree::BankWithHtree() {
	// TODO Auto-generated constructor stub
	initialized = false;
	invalid = false;
	numHorizontalAddressBitToRoute = NULL;  /* The number of horizontal bits to route on level x */
	numHorizontalDataDistributeBitToRoute = NULL;   /* The number of horizontal data-in bits to route on level x */
	numHorizontalDataBroadcastBitToRoute = NULL;  /* The number of horizontal data-out bits to route on level x */
	numHorizontalWire = NULL;		/* The number of horizontal wires on level x */
	numSumHorizontalWire = NULL;	/* The number of total horizontal wires on level x */
	numActiveHorizontalWire = NULL;	/* The number of active horizontal wires on level x */
	lengthHorizontalWire = NULL;	/* The length of horizontal wires on level x, Unit: m */
	numVerticalAddressBitToRoute = NULL;	/* The number of vertical address bits to route on level x */
	numVerticalDataDistributeBitToRoute = NULL;  /* The number of vertical data-in bits to route on level x */
	numVerticalDataBroadcastBitToRoute = NULL; /* The number of vertical data-out bits to route on level x */
	numVerticalWire = NULL;			/* The number of vertical wires on level x */
	numSumVerticalWire = NULL;		/* The number of total vertical wires on level x */
    numActiveVerticalWire = NULL;	/* The number of active vertical wires on level x */
	lengthVerticalWire = NULL;		/* The length of vertical wires on level 2, Unit: m */
}

BankWithHtree::~BankWithHtree() {
	// TODO Auto-generated destructor stub
	if (numHorizontalAddressBitToRoute)
		delete [] numHorizontalAddressBitToRoute;
	if (numHorizontalDataDistributeBitToRoute)
		delete [] numHorizontalDataDistributeBitToRoute;
	if (numHorizontalDataBroadcastBitToRoute)
		delete [] numHorizontalDataBroadcastBitToRoute;
	if (numHorizontalWire)
		delete [] numHorizontalWire;
	if (numSumHorizontalWire)
		delete [] numSumHorizontalWire;
	if (numActiveHorizontalWire)
		delete [] numActiveHorizontalWire;
	if (lengthHorizontalWire)
		delete [] lengthHorizontalWire;
	if (numVerticalAddressBitToRoute)
		delete [] numVerticalAddressBitToRoute;
	if (numVerticalDataDistributeBitToRoute)
		delete [] numVerticalDataDistributeBitToRoute;
	if (numVerticalDataBroadcastBitToRoute)
		delete [] numVerticalDataBroadcastBitToRoute;
	if (numVerticalWire)
		delete [] numVerticalWire;
	if (numSumVerticalWire)
		delete [] numSumVerticalWire;
	if (numActiveVerticalWire)
		delete [] numActiveVerticalWire;
	if (lengthVerticalWire)
		delete [] lengthVerticalWire;
}

void BankWithHtree::Initialize(int _numRowMat, int _numColumnMat, long long _capacity,
		long _blockSize, int _associativity, int _numRowPerSet, int _numActiveMatPerRow,
		int _numActiveMatPerColumn, int _muxSenseAmp, bool _internalSenseAmp, int _muxOutputLev1, int _muxOutputLev2,
		int _numRowSubarray, int _numColumnSubarray,
		int _numActiveSubarrayPerRow, int _numActiveSubarrayPerColumn,
		BufferDesignTarget _areaOptimizationLevel, MemoryType _memoryType) {
	if (initialized) {
		/* Reset the class for re-initialization */
		if (numHorizontalAddressBitToRoute)
			delete [] numHorizontalAddressBitToRoute;
		if (numHorizontalDataDistributeBitToRoute)
			delete [] numHorizontalDataDistributeBitToRoute;
		if (numHorizontalDataBroadcastBitToRoute)
			delete [] numHorizontalDataBroadcastBitToRoute;
		if (numHorizontalWire)
			delete [] numHorizontalWire;
		if (numSumHorizontalWire)
			delete [] numSumHorizontalWire;
		if (numActiveHorizontalWire)
			delete [] numActiveHorizontalWire;
		if (lengthHorizontalWire)
			delete [] lengthHorizontalWire;
		if (numVerticalAddressBitToRoute)
			delete [] numVerticalAddressBitToRoute;
		if (numVerticalDataDistributeBitToRoute)
			delete [] numVerticalDataDistributeBitToRoute;
		if (numVerticalDataBroadcastBitToRoute)
			delete [] numVerticalDataBroadcastBitToRoute;
		if (numVerticalWire)
			delete [] numVerticalWire;
		if (numSumVerticalWire)
			delete [] numSumVerticalWire;
		if (numActiveVerticalWire)
			delete [] numActiveVerticalWire;
		if (lengthVerticalWire)
			delete [] lengthVerticalWire;
		initialized = false;
		invalid = false;
		numHorizontalAddressBitToRoute = NULL;  /* The number of horizontal bits to route on level x */
		numHorizontalDataDistributeBitToRoute = NULL;   /* The number of horizontal data-in bits to route on level x */
		numHorizontalDataBroadcastBitToRoute = NULL;  /* The number of horizontal data-out bits to route on level x */
		numHorizontalWire = NULL;		/* The number of horizontal wires on level x */
		numSumHorizontalWire = NULL;	/* The number of total horizontal wires on level x */
		numActiveHorizontalWire = NULL;	/* The number of active horizontal wires on level x */
		lengthHorizontalWire = NULL;	/* The length of horizontal wires on level x, Unit: m */
		numVerticalAddressBitToRoute = NULL;	/* The number of vertical address bits to route on level x */
		numVerticalDataDistributeBitToRoute = NULL;  /* The number of vertical data-in bits to route on level x */
		numVerticalDataBroadcastBitToRoute = NULL; /* The number of vertical data-out bits to route on level x */
		numVerticalWire = NULL;			/* The number of vertical wires on level x */
		numSumVerticalWire = NULL;		/* The number of total vertical wires on level x */
	    numActiveVerticalWire = NULL;	/* The number of active vertical wires on level x */
		lengthVerticalWire = NULL;		/* The length of vertical wires on level 2, Unit: m */
	}

	if (!_internalSenseAmp) {
		invalid = true;
		cout << "[Bank] Htree organization does not support external sense amplification scheme" << endl;
		return;
	}
	if (initialized)
		cout << "[Bank] Warning: Already initialized!" << endl;

	numRowMat = _numRowMat;
	numColumnMat = _numColumnMat;
	capacity = _capacity;
	blockSize = _blockSize;
	associativity = _associativity;
	numRowPerSet = _numRowPerSet;
	internalSenseAmp = _internalSenseAmp;
	areaOptimizationLevel = _areaOptimizationLevel;
	memoryType = _memoryType;
	int numWay = 1;	/* default value for non-cache design */

	/* Calculate the physical signals that are required in routing */
	numAddressBit = (int)(log2((double)capacity / blockSize / associativity) + 0.1);
			/* use double during the calculation to avoid overflow */
	if (memoryType == data) {
		numDataDistributeBit = blockSize;
		numDataBroadcastBit = (int)(log2(associativity));	/* TO-DO: this is not the only way */
	} else if (memoryType == tag) {
		numDataDistributeBit = associativity;		/* TO-DO: it seems that it only supports power of 2 here */
		numDataBroadcastBit = blockSize;
	} else {	/* CAM */
		numDataDistributeBit = 0;
		numDataBroadcastBit = blockSize;
	}

	if (_numActiveMatPerRow > numColumnMat) {
		cout << "[Bank] Warning: The number of active subarray per row is larger than the number of subarray per row!"  << endl;
		cout << _numActiveMatPerRow << " > " << numColumnMat << endl;
		numActiveMatPerRow = numColumnMat;
	} else {
		numActiveMatPerRow = _numActiveMatPerRow;
	}
	if (_numActiveMatPerColumn > numRowMat) {
		cout << "[Bank] Warning: The number of active subarray per column is larger than the number of subarray per column!"  << endl;
		cout << _numActiveMatPerColumn << " > " << numRowMat << endl;
		numActiveMatPerColumn = numRowMat;
	} else {
		numActiveMatPerColumn = _numActiveMatPerColumn;
	}
	muxSenseAmp = _muxSenseAmp;
	muxOutputLev1 = _muxOutputLev1;
	muxOutputLev2 = _muxOutputLev2;

	numRowSubarray = _numRowSubarray;
	numColumnSubarray = _numColumnSubarray;
	if (_numActiveSubarrayPerRow > numColumnSubarray) {
		cout << "[Bank] Warning: The number of active subarray per row is larger than the number of subarray per row!"  << endl;
		cout << _numActiveSubarrayPerRow << " > " << numColumnSubarray << endl;
		numActiveSubarrayPerRow = numColumnSubarray;
	} else {
		numActiveSubarrayPerRow = _numActiveSubarrayPerRow;
	}
	if (_numActiveSubarrayPerColumn > numRowSubarray) {
		cout << "[Bank] Warning: The number of active subarray per column is larger than the number of subarray per column!"  << endl;
		cout << _numActiveSubarrayPerColumn << " > " << numRowSubarray << endl;
		numActiveSubarrayPerColumn = numRowSubarray;
	} else {
		numActiveSubarrayPerColumn = _numActiveSubarrayPerColumn;
	}

	levelHorizontal = (int)(log2(numColumnMat)+0.1);
	levelVertical = (int)(log2(numRowMat)+0.1);
	if (levelHorizontal > 0) {
		numHorizontalAddressBitToRoute = new int[levelHorizontal];
		numHorizontalDataDistributeBitToRoute = new int[levelHorizontal];
		numHorizontalDataBroadcastBitToRoute = new int[levelHorizontal];
		numHorizontalWire = new int[levelHorizontal];
		numSumHorizontalWire = new int[levelHorizontal];
		numActiveHorizontalWire = new int[levelHorizontal];
		lengthHorizontalWire = new double[levelHorizontal];
	}
	if (levelVertical > 0) {
		numVerticalAddressBitToRoute = new int[levelVertical];
		numVerticalDataDistributeBitToRoute = new int[levelVertical];
		numVerticalDataBroadcastBitToRoute = new int[levelVertical];
		numVerticalWire = new int[levelVertical];
		numSumVerticalWire = new int[levelVertical];
		numActiveVerticalWire = new int[levelVertical];
		lengthVerticalWire = new double[levelVertical];
	}

	/* When H > V */
	int h = levelHorizontal;
	int v = levelVertical;
	int rowToActive = numActiveMatPerColumn;
	int columnToActive = numActiveMatPerRow;
	int numAddressBitToRoute = numAddressBit;
	int numDataDistributeBitToRoute = numDataDistributeBit;
	int numDataBroadcastBitToRoute = numDataBroadcastBit;

	/* Always route H as the first step, TO-DO: this constraint is not valid */
	if (h > 0) {
		if (numDataDistributeBitToRoute + numDataBroadcastBitToRoute == 0 || numAddressBitToRoute == 0) {
			invalid = true;
			initialized = true;
			return;
		}
		numHorizontalAddressBitToRoute[0] = numAddressBitToRoute;
		numHorizontalDataDistributeBitToRoute[0] = numDataDistributeBitToRoute;
		numHorizontalDataBroadcastBitToRoute[0] = numDataBroadcastBitToRoute;
		numHorizontalWire[0] = 1;
		numSumHorizontalWire[0] = 1;
		numActiveHorizontalWire[0] = 1;
		h--;
	}

	int hTemp, vTemp;
	hTemp = 1;
	vTemp = 1;
	/* If H is larger than V, then reduce H to V */
	while (h > v) {
		if (numDataDistributeBitToRoute + numDataBroadcastBitToRoute == 0 || numAddressBitToRoute == 0) {
			invalid = true;
			initialized = true;
			return;
		}
		/* If there is possibility to reduce the data bits */
		if (columnToActive > 1) {
			numDataDistributeBitToRoute /= 2;
			columnToActive /= 2;
			numActiveHorizontalWire[levelHorizontal - h] = 2 * numActiveHorizontalWire[levelHorizontal - h - 1];
		} else {
			numAddressBitToRoute--;
			numActiveHorizontalWire[levelHorizontal - h] = numActiveHorizontalWire[levelHorizontal - h - 1];
		}
		numHorizontalAddressBitToRoute[levelHorizontal - h] = numAddressBitToRoute;
		numHorizontalDataDistributeBitToRoute[levelHorizontal - h] = numDataDistributeBitToRoute;
		numHorizontalDataBroadcastBitToRoute[levelHorizontal - h] = numDataBroadcastBitToRoute;
		numHorizontalWire[levelHorizontal - h] = 1;
		numSumHorizontalWire[levelHorizontal - h] = 2 * numSumHorizontalWire[levelHorizontal - h - 1];
		h--;
		vTemp *= 2;
	}
	/* If V is larger than H, then reduce V to H */
	while (v > h) {
		if (numDataDistributeBitToRoute + numDataBroadcastBitToRoute == 0 || numAddressBitToRoute == 0) {
			invalid = true;
			initialized = true;
			return;
		}
		/* If there is possibility to reduce the data bits on vertical */
		if (rowToActive > 1) {
			numDataDistributeBitToRoute /= 2;
			rowToActive /= 2;
			if (v == levelVertical) {
				numActiveVerticalWire[0] = 2;
			} else {
				numActiveVerticalWire[levelVertical - v] = 2 * numActiveVerticalWire[levelVertical - v - 1];
			}
		} else {
			numAddressBitToRoute--;
			if (v == levelVertical) {
				numActiveVerticalWire[0] = 1;
			} else {
				numActiveVerticalWire[levelVertical - v] = numActiveVerticalWire[levelVertical - v - 1];
			}
		}
		numVerticalAddressBitToRoute[levelVertical - v] = numAddressBitToRoute;
		numVerticalDataDistributeBitToRoute[levelVertical - v] = numDataDistributeBitToRoute;
		numVerticalDataBroadcastBitToRoute[levelVertical - v] = numDataBroadcastBitToRoute;
		numVerticalWire[levelVertical - v] = 1;
		if (v == levelVertical) {
			numSumVerticalWire[0] = 2;
		} else {
			numSumVerticalWire[levelVertical - v] = 2 * numSumVerticalWire[levelVertical - v - 1];
		}
		v--;
		hTemp *= 2;
	}
	/* Reduce H an V to zero */
	while (h > 0) {
		if (numDataDistributeBitToRoute + numDataBroadcastBitToRoute == 0 || numAddressBitToRoute == 0) {
			invalid = true;
			initialized = true;
			return;
		}
		/* If there is possibility to reduce the data bits */
		if (columnToActive > 1) {
			numDataDistributeBitToRoute /= 2;
			columnToActive /= 2;
			if (v == levelVertical) {
				numActiveHorizontalWire[levelHorizontal - h] = 2 * numActiveHorizontalWire[levelHorizontal - h - 1];
			} else {
				numActiveHorizontalWire[levelHorizontal - h] = 2 * numActiveVerticalWire[levelVertical - v - 1];
			}
		} else {
			numAddressBitToRoute--;
			if (v == levelVertical) {
				numActiveHorizontalWire[levelHorizontal - h] = numActiveHorizontalWire[levelHorizontal - h - 1];
			} else {
				numActiveHorizontalWire[levelHorizontal - h] = numActiveVerticalWire[levelVertical - v - 1];
			}
		}
		numHorizontalAddressBitToRoute[levelHorizontal - h] = numAddressBitToRoute;
		numHorizontalDataDistributeBitToRoute[levelHorizontal - h] = numDataDistributeBitToRoute;
		numHorizontalDataBroadcastBitToRoute[levelHorizontal - h] = numDataBroadcastBitToRoute;
		numHorizontalWire[levelHorizontal - h] = hTemp;
		if (v == levelVertical) {
			numSumHorizontalWire[levelHorizontal - h] = 2 * numSumHorizontalWire[levelHorizontal - h - 1];
		} else {
			numSumHorizontalWire[levelHorizontal - h] = 2 * numSumVerticalWire[levelVertical - v - 1];
		}
		if (numDataDistributeBitToRoute + numDataBroadcastBitToRoute == 0 || numAddressBitToRoute == 0) {
			invalid = true;
			initialized = true;
			return;
		}
		/* If there is possibility to reduce the data bits on vertical */
		if (rowToActive > 1) {
			numDataDistributeBitToRoute /= 2;
			rowToActive /= 2;
			numActiveVerticalWire[levelVertical - v] = 2 * numActiveHorizontalWire[levelHorizontal - h];
		} else {
			numAddressBitToRoute--;
			numActiveVerticalWire[levelVertical - v] = numActiveHorizontalWire[levelHorizontal - h];
		}
		numVerticalAddressBitToRoute[levelVertical - v] = numAddressBitToRoute;
		numVerticalDataDistributeBitToRoute[levelVertical - v] = numDataDistributeBitToRoute;
		numVerticalDataBroadcastBitToRoute[levelVertical - v] = numDataBroadcastBitToRoute;
		if (levelHorizontal == 2) {
			numVerticalWire[levelVertical - v] = vTemp;
		} else {
			numVerticalWire[levelVertical - v] = 2 * vTemp;
		}
		numSumVerticalWire[levelVertical - v] = 2 * numSumHorizontalWire[levelHorizontal - h];
		h--;
		v--;
		hTemp *= 2;
		vTemp *= 2;
	}

	if (numDataDistributeBitToRoute + numDataBroadcastBitToRoute == 0 || numAddressBitToRoute == 0) {
		invalid = true;
		initialized = true;
		return;
	}
	if (columnToActive > 1) {
		numDataDistributeBitToRoute /= 2;
		columnToActive /= 2;
	} else {
		if (levelHorizontal > 0) {
			numAddressBitToRoute--;
		}
	}

	/* If this mat is cache data array, determine if the number of cache ways assigned to this mat is legal */
	if (memoryType == data) {
		if (numRowPerSet > (int)pow(2, numDataBroadcastBitToRoute)) {
			/* There is no enough ways to distribute into multiple rows */
			invalid = true;
			initialized = true;
			return;
		}
	}

	/* If this mat is cache tag array, determine if the number of cache ways assigned to this mat is legal */
	if (memoryType == tag) {
		if (numRowPerSet > 1) {
			/* tag array cannot have multiple rows to contain ways in a set, otherwise the bitline has to be shared */
			invalid = true;
			initialized = true;
			return;
		}
		if (numDataDistributeBitToRoute == 0) {
			/* This mat does not contain at least one way */
			invalid = true;
			initialized = true;
			return;
		}
	}

	/* Determine the number of columns in a mat */
	long matBlockSize;
	if (memoryType == data) {		/* Data array */
		/* numDataDistributeBit is the bits in a data word that is assigned to this mat */
		matBlockSize = numDataDistributeBitToRoute;
		numWay = (int)pow(2, numDataBroadcastBitToRoute);
		/* Consider the case if each mat is a cache data array that contains multiple ways */
		int numWayPerRow = numWay / numRowPerSet;	/* At least 1, otherwise it is invalid, and returned already */
		if (numWayPerRow > 1) {		/* multiple ways per row, needs extra mux level */
			/* Do mux level recalculation to contain the multiple ways */
			if (cell->memCellType == DRAM || cell->memCellType == eDRAM) {
				/* for DRAM, mux before sense amp has to be 1, only mux output1 and mux output2 can be used */
				int numWayPerRowInLog = (int)(log2((double)numWayPerRow) + 0.1);
				int extraMuxOutputLev2 = (int)pow(2, numWayPerRowInLog / 2);
				int extraMuxOutputLev1 = numWayPerRow / extraMuxOutputLev2;
				muxOutputLev1 *= extraMuxOutputLev1;
				muxOutputLev2 *= extraMuxOutputLev2;
			} else {
				/* for non-DRAM, all mux levels can be used */
				int numWayPerRowInLog = (int)(log2((double)numWayPerRow) + 0.1);
				int extraMuxOutputLev2 = (int)pow(2, numWayPerRowInLog / 3);
				int extraMuxOutputLev1 = extraMuxOutputLev2;
				int extraMuxSenseAmp = numWayPerRow / extraMuxOutputLev1 / extraMuxOutputLev2;
				muxSenseAmp *= extraMuxSenseAmp;
				muxOutputLev1 *= extraMuxOutputLev1;
				muxOutputLev2 *= extraMuxOutputLev2;
			}
		}
	} else if (memoryType == tag) {	/* Tag array */
		/* numDataBroadcastBit is the tag width, numDataDistributeBit is the number of ways assigned to this mat */
		matBlockSize = numDataBroadcastBitToRoute;
		numWay = numDataDistributeBitToRoute;
	} else {						/* CAM */
		matBlockSize = numDataBroadcastBitToRoute;
		numWay = 1;
	}

	mat.Initialize(numRowSubarray, numColumnSubarray, numAddressBitToRoute, matBlockSize,
			numWay, numRowPerSet, false, numActiveSubarrayPerRow, numActiveSubarrayPerColumn,
			muxSenseAmp, internalSenseAmp, muxOutputLev1, muxOutputLev2, areaOptimizationLevel, memoryType);

	/* Check if mat is under a legal configuration */
	if (mat.invalid) {
		invalid = true;
		initialized = true;
		return;
	}

	/* Reset the mux values for correct printing */
	muxSenseAmp = _muxSenseAmp;
	muxOutputLev1 = _muxOutputLev1;
	muxOutputLev2 = _muxOutputLev2;

	initialized = true;
}

void BankWithHtree::CalculateArea() {
	if (!initialized) {
		cout << "[Bank] Error: Require initialization first!" << endl;
	} else if (invalid) {
		height = width = area = 1e41;
	} else {
		mat.CalculateArea();
		height = mat.height * numRowMat;
		width = mat.width * numColumnMat;


		/* Add wire area */
		int numWireSharingWidth;
		double effectivePitch;
		if (globalWire->wireRepeaterType == repeated_none) {
			numWireSharingWidth = 1;
			effectivePitch = 0;		/* assume that the wire is built on another metal layer, there does not cause silicon area */
			//effectivePitch = globalWire->wirePitch;
		} else {
			numWireSharingWidth = (int)floor(globalWire->repeaterSpacing / globalWire->repeaterHeight);
			effectivePitch = globalWire->repeatedWirePitch;
		}

		for (int i = 0; i < levelHorizontal; i++) {
			height += ceil((double)(numHorizontalAddressBitToRoute[i] + numHorizontalDataDistributeBitToRoute[i] +
					numHorizontalDataBroadcastBitToRoute[i]) * numHorizontalWire[i] / numWireSharingWidth) * effectivePitch ;
		}
		for (int i = 0; i < levelVertical; i++) {
			width += ceil((double)(numVerticalAddressBitToRoute[i] + numVerticalDataDistributeBitToRoute[i] +
					numVerticalDataBroadcastBitToRoute[i]) * numVerticalWire[i] / numWireSharingWidth) * effectivePitch;
		}

		/* Determine if the aspect ratio meets the constraint */
		if (memoryType == data)
			if (height / width > CONSTRAINT_ASPECT_RATIO_BANK || width / height > CONSTRAINT_ASPECT_RATIO_BANK) {
				/* illegal */
				invalid = true;
				height = width = area = 1e41;
				return;
			}

		area = height * width;

		/* Calculate the length of each H-tree wire */
		int h = levelHorizontal - 1;
		int v = levelVertical - 1;
		while (v > h) {
			if (v == levelVertical - 1)
				lengthVerticalWire[v] = mat.height / 2;
			else
				lengthVerticalWire[v] = lengthVerticalWire[v + 1] * 2;
			v--;
		}

		double numHorizontalBitToRoute = 0;
		double numVerticalBitToRoute = 0;
		while (v >= 0) {
			if (v == levelVertical - 1) {
				lengthVerticalWire[v] = mat.height / 2;
			} else {
				if (h == levelHorizontal - 1)
					lengthVerticalWire[v] = lengthVerticalWire[v + 1] * 2;
				else {
					numHorizontalBitToRoute = numHorizontalAddressBitToRoute[h + 1]
							+ numHorizontalDataDistributeBitToRoute[h + 1] + numHorizontalDataBroadcastBitToRoute[h + 1];
					lengthVerticalWire[v] = lengthVerticalWire[v + 1] * 2
							+ ceil((double)numHorizontalBitToRoute / numWireSharingWidth) * effectivePitch / 2;
				}
			}
			if (h == levelHorizontal - 1) {
				lengthHorizontalWire[h] = mat.width;
				for (int i = v; i < levelVertical; i++) {
					numVerticalBitToRoute = numVerticalAddressBitToRoute[i]
							+ numVerticalDataDistributeBitToRoute[i] + numVerticalDataBroadcastBitToRoute[i];
					lengthHorizontalWire[h] += ceil((double)numVerticalBitToRoute / numWireSharingWidth) * effectivePitch / 2;
				}
			} else {
				numVerticalBitToRoute = numVerticalAddressBitToRoute[v]
						+ numVerticalDataDistributeBitToRoute[v] + numVerticalDataBroadcastBitToRoute[v];
				lengthHorizontalWire[h] = lengthHorizontalWire[h + 1] * 2
						+ ceil((double)numVerticalBitToRoute / numWireSharingWidth) * effectivePitch / 2;
			}
			v--;
			h--;
		}
		while (h >=  0) {
			if (h == levelHorizontal - 1)
				lengthHorizontalWire[h] = mat.width;
			else
				lengthHorizontalWire[h] = lengthHorizontalWire[h + 1] * 2;
			h--;
		}
	}
}

void BankWithHtree::CalculateRC() {
	if (!initialized) {
		cout << "[Bank] Error: Require initialization first!" << endl;
	} else if (!invalid) {
		mat.CalculateRC();
	}
}

void BankWithHtree::CalculateLatencyAndPower() {
	if (!initialized) {
		cout << "[Bank] Error: Require initialization first!" << endl;
	} else if (invalid) {
		readLatency = writeLatency = 1e41;
		readDynamicEnergy = writeDynamicEnergy = 1e41;
		leakage = 1e41;
	} else {
		double latency;
		double energy;
		double leakageWire;
		int beta = 1;	/* Default value is 1. For fast access mode cache, this value is equal to associativity, which means only 1/beta interconnect wires are activated */

		mat.CalculateLatency(1e41 /* means Inf */);
		mat.CalculatePower();
		readLatency = mat.readLatency;
		writeLatency = mat.writeLatency;
		readDynamicEnergy = mat.readDynamicEnergy * numActiveMatPerRow * numActiveMatPerColumn;
		writeDynamicEnergy = mat.writeDynamicEnergy * numActiveMatPerRow * numActiveMatPerColumn;
		leakage = mat.leakage * numRowMat * numColumnMat;

		/* energy consumption on cells */
		cellReadEnergy = mat.cellReadEnergy * numActiveMatPerRow * numActiveMatPerColumn;
		cellSetEnergy = mat.cellSetEnergy * numActiveMatPerRow * numActiveMatPerColumn;
		cellResetEnergy = mat.cellResetEnergy * numActiveMatPerRow * numActiveMatPerColumn;

		/* for asymmetric RESET/SET only */
		resetLatency = mat.resetLatency;
		setLatency = mat.setLatency;
		resetDynamicEnergy = mat.resetDynamicEnergy * numActiveMatPerRow * numActiveMatPerColumn;
		setDynamicEnergy = mat.setDynamicEnergy * numActiveMatPerRow * numActiveMatPerColumn;

		if (inputParameter->designTarget == cache && inputParameter->cacheAccessMode == fast_access_mode)
			beta = inputParameter->associativity;

		for (int i = 0; i < levelHorizontal; i++) {
			globalWire->CalculateLatencyAndPower(lengthHorizontalWire[i], &latency, &energy, &leakageWire);
			readLatency += latency * 2;						/* 2 due to in/out */
			writeLatency += latency;						/* only in */
			resetLatency += latency;
			setLatency += latency;
			/* Read and write energy for H-tree should be the same, each wire is activated on exactly one way */
			readDynamicEnergy += energy * numActiveHorizontalWire[i] *
					(numHorizontalAddressBitToRoute[i] + numHorizontalDataDistributeBitToRoute[i] + numHorizontalDataBroadcastBitToRoute[i]);
			writeDynamicEnergy += energy * numActiveHorizontalWire[i] *
					(numHorizontalAddressBitToRoute[i] + numHorizontalDataDistributeBitToRoute[i] + numHorizontalDataBroadcastBitToRoute[i]) / beta;
			resetDynamicEnergy += energy * numActiveHorizontalWire[i] *
					(numHorizontalAddressBitToRoute[i] + numHorizontalDataDistributeBitToRoute[i] + numHorizontalDataBroadcastBitToRoute[i]) / beta;
			setDynamicEnergy += energy * numActiveHorizontalWire[i] *
					(numHorizontalAddressBitToRoute[i] + numHorizontalDataDistributeBitToRoute[i] + numHorizontalDataBroadcastBitToRoute[i]) / beta;
			leakage += leakageWire * numSumHorizontalWire[i] * (numHorizontalAddressBitToRoute[i] +
					numHorizontalDataDistributeBitToRoute[i] + numHorizontalDataBroadcastBitToRoute[i]);
		}
		for (int i = 0; i < levelVertical; i++) {
			globalWire->CalculateLatencyAndPower(lengthVerticalWire[i], &latency, &energy, &leakageWire);
			readLatency += latency * 2;						/* 2 due to in/out */
			writeLatency += latency;						/* only in */
			resetLatency += latency;
			setLatency += latency;
			readDynamicEnergy += energy * numActiveVerticalWire[i] *
					(numVerticalAddressBitToRoute[i] + numVerticalDataDistributeBitToRoute[i] + numVerticalDataBroadcastBitToRoute[i]);
			writeDynamicEnergy += energy * numActiveVerticalWire[i] *
					(numVerticalAddressBitToRoute[i] + numVerticalDataDistributeBitToRoute[i] + numVerticalDataBroadcastBitToRoute[i]) / beta;
			resetDynamicEnergy += energy * numActiveVerticalWire[i] *
					(numVerticalAddressBitToRoute[i] + numVerticalDataDistributeBitToRoute[i] + numVerticalDataBroadcastBitToRoute[i]) / beta;
			setDynamicEnergy += energy * numActiveVerticalWire[i] *
					(numVerticalAddressBitToRoute[i] + numVerticalDataDistributeBitToRoute[i] + numVerticalDataBroadcastBitToRoute[i]) / beta;
			leakage += leakageWire * numSumVerticalWire[i] * (numVerticalAddressBitToRoute[i] +
					numVerticalDataDistributeBitToRoute[i] + numVerticalDataBroadcastBitToRoute[i]);
		}
	}
}

BankWithHtree & BankWithHtree::operator=(const BankWithHtree &rhs) {
	Bank::operator=(rhs);
	levelHorizontal = rhs.levelHorizontal;
	levelVertical = rhs.levelVertical;
	return *this;
}
