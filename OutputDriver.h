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


#ifndef OUTPUTDRIVER_H_
#define OUTPUTDRIVER_H_

#include "FunctionUnit.h"
#include "constant.h"
#include "typedef.h"

class OutputDriver: public FunctionUnit {
public:
	OutputDriver();
	virtual ~OutputDriver();

	/* Functions */
	void PrintProperty();
	void Initialize(double _logicEffort, double _inputCap, double _outputCap, double _outputRes,
			bool _inv, BufferDesignTarget _areaOptimizationLevel, double _minDriverCurrent);
	void CalculateArea();
	void CalculateRC();
	void CalculateLatency(double _rampInput);
	void CalculatePower();
	OutputDriver & operator=(const OutputDriver &);

	/* Properties */
	bool initialized;	/* Initialization flag */
	bool invalid;      /*Invalidatio flag */
	double logicEffort;	/* The logic effort of the gate that needs this driver */
	double inputCap;	/* Input capacitance, unit: F */
	double outputCap;	/* Output capacitance, unit: F */
	double outputRes;	/* Output resistance, unit: ohm */
	bool inv;			/* Whether the invert chain causes a flip */
	int numStage;		/* Number of inverter chain stages */
	BufferDesignTarget areaOptimizationLevel; /* 0 for latency, 2 for area */
	double minDriverCurrent; /* Minimum driving current should be provided */
	double widthNMOS[MAX_INV_CHAIN_LEN];
	double widthPMOS[MAX_INV_CHAIN_LEN];
	double capInput[MAX_INV_CHAIN_LEN];
	double capOutput[MAX_INV_CHAIN_LEN];
	double rampInput, rampOutput;
};

#endif /* OUTPUTDRIVER_H_ */
