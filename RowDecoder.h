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


#ifndef ROWDECODER_H_
#define ROWDECODER_H_

#include "FunctionUnit.h"
#include "OutputDriver.h"
#include "typedef.h"

class RowDecoder: public FunctionUnit {
public:
	RowDecoder();
	virtual ~RowDecoder();

	/* Functions */
	void PrintProperty();
	void Initialize(int _numRow, double _capLoad, double _resLoad,
			bool _multipleRowPerSet, BufferDesignTarget _areaOptimizationLevel, double _minDriverCurrent);
	void CalculateArea();
	void CalculateRC();
	void CalculateLatency(double _rampInput);
	void CalculatePower();
	RowDecoder & operator=(const RowDecoder &);

	/* Properties */
	bool initialized;	/* Initialization flag */
	bool invalid;      /*Invalidatio flag */
	OutputDriver outputDriver;
	int numRow;			/* Number of rows */
	bool multipleRowPerSet;		/* For cache design, whether a set is partitioned into multiple wordlines */
	int numNandInput;	/* Type of NAND, NAND2 or NAND3 */
	double capLoad;		/* Load capacitance, i.e. wordline capacitance, Unit: F */
	double resLoad;		/* Load resistance, Unit: ohm */
	BufferDesignTarget areaOptimizationLevel; /* 0 for latency, 2 for area */
	double minDriverCurrent; /* Minimum driving current should be provided */

	double widthNandN, widthNandP;
	double capNandInput, capNandOutput;
	double rampInput, rampOutput;
};

#endif /* ROWDECODER_H_ */
