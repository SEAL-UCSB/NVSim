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


#ifndef SUBARRAY_H_
#define SUBARRAY_H_

#include "FunctionUnit.h"
#include "RowDecoder.h"
#include "Precharger.h"
#include "SenseAmp.h"
#include "Mux.h"
#include "typedef.h"

class SubArray: public FunctionUnit {
public:
	SubArray();
	virtual ~SubArray();

	/* Functions */
	void PrintProperty();
	void Initialize(long long _numRow, long long _numColumn, bool _multipleRowPerSet, bool _split,
			int _muxSenseAmp, bool _internalSenseAmp, int _muxOutputLev1, int _muxOutputLev2,
			BufferDesignTarget _areaOptimizationLevel);
	void CalculateArea();
	//void CalculateRC();
	void CalculateLatency(double _rampInput);
	void CalculatePower();
	SubArray & operator=(const SubArray &);

	/* Properties */
	bool initialized;	/* Initialization flag */
	bool invalid;		/* Indicate that the current configuration is not valid, pass down to all the sub-components */
	bool internalSenseAmp; /* Indicate whether sense amp is within subarray */
	long long numRow;			/* Number of rows */
	long long numColumn;		/* Number of columns */
	bool multipleRowPerSet;		/* For cache design, whether a set is partitioned into multiple wordlines */
	bool split;			/* Whether the row decoder is at the middle of subarrays */
	int muxSenseAmp;	/* How many bitlines connect to one sense amplifier */
	int muxOutputLev1;	/* How many sense amplifiers connect to one output bit, level-1 */
	int muxOutputLev2;	/* How many sense amplifiers connect to one output bit, level-2 */
	BufferDesignTarget areaOptimizationLevel;

	bool voltageSense;	/* Whether the sense amplifier is voltage-sensing */
	double senseVoltage;/* Minimum sensible voltage */
	double voltagePrecharge;
	long long numSenseAmp;	/* Number of sense amplifiers */
	double lenWordline;	/* Length of wordlines, Unit: m */
	double lenBitline;	/* Length of bitlines, Unit: m */
	double capWordline;	/* Wordline capacitance, Unit: F */
	double capBitline;	/* Bitline capacitance, Unit: F */
	double resWordline;	/* Wordline resistance, Unit: ohm */
	double resBitline;	/* Bitline resistance, Unit: ohm */
	double resCellAccess; /* Resistance of access device, Unit: ohm */
	double capCellAccess; /* Capacitance of access device, Unit: ohm */
	double resMemCellOff;  /* HRS resistance, Unit: ohm */
	double resMemCellOn;   /* LRS resistance, Unit: ohm */
	double voltageMemCellOff; /* Voltage drop on HRS during read operation, Unit: V */
	double voltageMemCellOn;   /* Voltage drop on LRS druing read operation, Unit: V */
	double resInSerialForSenseAmp; /* Serial resistance of voltage-in voltage sensing as a voltage divider, Unit: ohm */
	double resEquivalentOn;          /* resInSerialForSenseAmp in parallel with resMemCellOn, Unit: ohm */
	double resEquivalentOff;          /* resInSerialForSenseAmp in parallel with resMemCellOn, Unit: ohm */
	double bitlineDelay;	/* Bitline delay, Unit: s */
	double chargeLatency;	/* The bitline charge delay during write operations, Unit: s */
	double columnDecoderLatency;	/* The worst-case mux latency, Unit: s */
	double bitlineDelayOn;  /* Bitline delay of LRS, Unit: s */
	double bitlineDelayOff; /* Bitline delay of HRS, Unit: s */

	RowDecoder	rowDecoder;
	RowDecoder	bitlineMuxDecoder;
	Mux			bitlineMux;
	RowDecoder	senseAmpMuxLev1Decoder;
	Mux			senseAmpMuxLev1;
	RowDecoder	senseAmpMuxLev2Decoder;
	Mux			senseAmpMuxLev2;
	Precharger	precharger;
	SenseAmp	senseAmp;
};

#endif /* SUBARRAY_H_ */
